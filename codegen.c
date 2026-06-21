#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

/* ── Helpers ────────────────────────────────────────────────── */
static LLVMTypeRef ty_int(CG *g)  { return LLVMInt32TypeInContext(g->ctx); }
static LLVMTypeRef ty_bool(CG *g) { return LLVMInt1TypeInContext(g->ctx);  }
static LLVMTypeRef ty_i8p(CG *g)  { return LLVMPointerType(LLVMInt8TypeInContext(g->ctx), 0); }
static LLVMTypeRef ty_void(CG *g) { return LLVMVoidTypeInContext(g->ctx);  }

static LLVMTypeRef pascal_to_llvm(CG *g, PascalType t) {
    switch (t) {
        case TY_INT:  return ty_int(g);
        case TY_BOOL: return ty_bool(g);
        default:      return ty_void(g);
    }
}

static LLVMValueRef const_i32(CG *g, int v) {
    return LLVMConstInt(ty_int(g), (unsigned long long)v, 1);
}

static LLVMValueRef const_i1(CG *g, int v) {
    return LLVMConstInt(ty_bool(g), (unsigned long long)v, 0);
}

/* Forward declarations */
static LLVMValueRef emit_expr(CG *g, AstNode *n);
static void         emit_stmt(CG *g, AstNode *n);
static void         emit_decls(CG *g, AstNode *n);

/* ── Extern declarations ────────────────────────────────────── */
static void declare_externs(CG *g) {
    LLVMTypeRef p_args[] = { ty_i8p(g) };
    LLVMTypeRef p_type = LLVMFunctionType(ty_int(g), p_args, 1, /*vararg=*/1);
    g->fn_printf = LLVMAddFunction(g->mod, "printf", p_type);

    LLVMTypeRef a_args[] = { ty_i8p(g) };
    LLVMTypeRef a_type = LLVMFunctionType(ty_int(g), a_args, 1, 0);
    g->fn_atoi = LLVMAddFunction(g->mod, "atoi", a_type);
}

/* ── Codegen state lifecycle ────────────────────────────────── */
CG *cg_create(const char *module_name) {
    CG *g = calloc(1, sizeof(CG));
    g->ctx = LLVMContextCreate();
    g->mod = LLVMModuleCreateWithNameInContext(module_name, g->ctx);
    g->bld = LLVMCreateBuilderInContext(g->ctx);
    declare_externs(g);
    return g;
}

void cg_destroy(CG *cg) {
    LLVMDisposeBuilder(cg->bld);
    LLVMDisposeModule(cg->mod);
    LLVMContextDispose(cg->ctx);
    free(cg);
}

/* ── Symbol slot lookup (returns alloca ptr) ────────────────── */
static LLVMValueRef lookup_slot(CG *g, const char *name) {
    if (!strcmp(name, "__paramcount")) {
        /* paramcount = argc - 1 */
        return NULL; /* handled inline in emit_expr */
    }
    Symbol *sym = sym_lookup(g->syms, name);
    if (!sym) {
        /* could be the function return variable */
        if (g->cur_fn && !strcmp(name, LLVMGetValueName(g->cur_fn))) {
            return g->cur_fn_retslot;
        }
        fprintf(stderr, "codegen: undefined symbol '%s'\n", name);
        exit(1);
    }
    return sym->llvm_val;
}

/* ── printf format string helper ────────────────────────────── */
static LLVMValueRef make_str(CG *g, const char *s, const char *name) {
    LLVMValueRef gs = LLVMAddGlobal(g->mod,
        LLVMArrayType(LLVMInt8TypeInContext(g->ctx), (unsigned)strlen(s)+1), name);
    LLVMSetInitializer(gs, LLVMConstStringInContext(g->ctx, s, (unsigned)strlen(s), 0));
    LLVMSetGlobalConstant(gs, 1);
    LLVMSetLinkage(gs, LLVMPrivateLinkage);
    LLVMValueRef zero = LLVMConstInt(LLVMInt32TypeInContext(g->ctx), 0, 0);
    LLVMValueRef idxs[2] = { zero, zero };
    return LLVMConstGEP2(LLVMArrayType(LLVMInt8TypeInContext(g->ctx),
                         (unsigned)strlen(s)+1), gs, idxs, 2);
}

/* ── Expression emitter ─────────────────────────────────────── */
static LLVMValueRef emit_expr(CG *g, AstNode *n) {
    if (!n) return const_i32(g, 0);

    switch (n->kind) {

        case NK_INT_LIT:
            return LLVMConstInt(ty_int(g), (unsigned long long)n->u.iliteral.value, 1);

        case NK_BOOL_LIT:
            return const_i1(g, n->u.bliteral.value);

        case NK_IDENT: {
            const char *name = n->u.ident.name;
            /* paramcount */
            if (!strcmp(name, "__paramcount")) {
                return LLVMBuildSub(g->bld, g->llvm_argc, const_i32(g, 1), "paramcount");
            }
            LLVMValueRef slot = lookup_slot(g, name);
            Symbol *sym = sym_lookup(g->syms, name);
            LLVMTypeRef ty = sym ? pascal_to_llvm(g, sym->type) : ty_int(g);
            return LLVMBuildLoad2(g->bld, ty, slot, name);
        }

        case NK_CALL: {
            const char *name = n->u.call.name;

            /* paramcount */
            if (!strcmp(name, "__paramcount")) {
                return LLVMBuildSub(g->bld, g->llvm_argc, const_i32(g, 1), "paramcount");
            }
            /* paramstr(i) → argv[i] converted to int via atoi */
            if (!strcmp(name, "__paramstr")) {
                AstNode *idx_node = n->u.call.args;
                LLVMValueRef idx = emit_expr(g, idx_node);
                /* argv is i8**, load argv[idx] */
                LLVMTypeRef i8p  = ty_i8p(g);
                LLVMTypeRef i8pp = LLVMPointerType(i8p, 0);
                LLVMValueRef argv_ptr = LLVMBuildGEP2(g->bld, i8p, g->llvm_argv, &idx, 1, "argv_i");
                LLVMValueRef str = LLVMBuildLoad2(g->bld, i8p, argv_ptr, "argv_str");
                /* call atoi */
                LLVMTypeRef  atoi_t = LLVMFunctionType(ty_int(g), &i8p, 1, 0);
                LLVMValueRef args[] = { str };
                return LLVMBuildCall2(g->bld, atoi_t, g->fn_atoi, args, 1, "atoi_res");
            }

            /* user-defined function call */
            Symbol *sym = sym_lookup(g->syms, name);
            if (!sym || sym->kind != SYM_FUNC) {
                fprintf(stderr, "codegen: unknown function '%s'\n", name);
                exit(1);
            }
            LLVMValueRef fn = sym->llvm_val;
            /* collect args */
            LLVMValueRef call_args[64];
            unsigned     nargs = 0;
            for (AstNode *a = n->u.call.args; a && nargs < 64; a = a->next)
                call_args[nargs++] = emit_expr(g, a);
            LLVMTypeRef fn_type = LLVMGlobalGetValueType(fn);
            return LLVMBuildCall2(g->bld, fn_type, fn, call_args, nargs, "call_res");
        }

        case NK_BINOP: {
            /* short-circuit AND / OR */
            if (n->u.binop.op == OP_AND || n->u.binop.op == OP_OR) {
                LLVMValueRef l = emit_expr(g, n->u.binop.left);
                LLVMValueRef r = emit_expr(g, n->u.binop.right);
                return (n->u.binop.op == OP_AND)
                    ? LLVMBuildAnd(g->bld, l, r, "and")
                    : LLVMBuildOr (g->bld, l, r, "or");
            }
            LLVMValueRef l = emit_expr(g, n->u.binop.left);
            LLVMValueRef r = emit_expr(g, n->u.binop.right);
            switch (n->u.binop.op) {
                case OP_ADD: return LLVMBuildAdd (g->bld, l, r, "add");
                case OP_SUB: return LLVMBuildSub (g->bld, l, r, "sub");
                case OP_MUL: return LLVMBuildMul (g->bld, l, r, "mul");
                case OP_DIV: return LLVMBuildSDiv(g->bld, l, r, "div");
                case OP_MOD: return LLVMBuildSRem(g->bld, l, r, "mod");
                case OP_EQ:  return LLVMBuildICmp(g->bld, LLVMIntEQ,  l, r, "eq");
                case OP_NEQ: return LLVMBuildICmp(g->bld, LLVMIntNE,  l, r, "neq");
                case OP_LT:  return LLVMBuildICmp(g->bld, LLVMIntSLT, l, r, "lt");
                case OP_LE:  return LLVMBuildICmp(g->bld, LLVMIntSLE, l, r, "le");
                case OP_GT:  return LLVMBuildICmp(g->bld, LLVMIntSGT, l, r, "gt");
                case OP_GE:  return LLVMBuildICmp(g->bld, LLVMIntSGE, l, r, "ge");
                default:
                    fprintf(stderr, "codegen: unknown binop %d\n", n->u.binop.op);
                    exit(1);
            }
        }

        case NK_UNOP: {
            LLVMValueRef v = emit_expr(g, n->u.unop.operand);
            switch (n->u.unop.op) {
                case OP_NEG: return LLVMBuildNeg(g->bld, v, "neg");
                case OP_NOT: return LLVMBuildNot(g->bld, v, "not");
                default:
                    fprintf(stderr, "codegen: unknown unop %d\n", n->u.unop.op);
                    exit(1);
            }
        }

        default:
            fprintf(stderr, "codegen: emit_expr unhandled kind %d\n", n->kind);
            exit(1);
    }
}

/* ── Statement emitter ──────────────────────────────────────── */
static void emit_stmt(CG *g, AstNode *n) {
    for (AstNode *curr = n; curr != NULL; curr = curr->next) {
        switch (curr->kind) {

            case NK_ASSIGN: {
                LLVMValueRef val  = emit_expr(g, curr->u.assign.expr);
                LLVMValueRef slot = lookup_slot(g, curr->u.assign.name);
                /* bool → i32 widening if needed */
                Symbol *sym = sym_lookup(g->syms, curr->u.assign.name);
                if (sym && sym->type == TY_INT &&
                    LLVMTypeOf(val) == ty_bool(g)) {
                    val = LLVMBuildZExt(g->bld, val, ty_int(g), "b2i");
                }
                LLVMBuildStore(g->bld, val, slot);
                break;
            }

            case NK_IF: {
                LLVMBasicBlockRef then_bb  = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "if.then");
                LLVMBasicBlockRef else_bb  = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "if.else");
                LLVMBasicBlockRef merge_bb = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "if.end");

                LLVMValueRef cond = emit_expr(g, curr->u.ifstmt.cond);
                /* ensure i1 */
                if (LLVMTypeOf(cond) != ty_bool(g))
                    cond = LLVMBuildICmp(g->bld, LLVMIntNE, cond, const_i32(g, 0), "cond");
                LLVMBuildCondBr(g->bld, cond, then_bb, else_bb);

                LLVMPositionBuilderAtEnd(g->bld, then_bb);
                emit_stmt(g, curr->u.ifstmt.then);
                if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(g->bld)))
                    LLVMBuildBr(g->bld, merge_bb);

                LLVMPositionBuilderAtEnd(g->bld, else_bb);
                if (curr->u.ifstmt.els)
                    emit_stmt(g, curr->u.ifstmt.els);
                if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(g->bld)))
                    LLVMBuildBr(g->bld, merge_bb);

                LLVMPositionBuilderAtEnd(g->bld, merge_bb);
                break;
            }

            case NK_WHILE: {
                LLVMBasicBlockRef cond_bb = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "while.cond");
                LLVMBasicBlockRef body_bb = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "while.body");
                LLVMBasicBlockRef end_bb  = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "while.end");

                LLVMBuildBr(g->bld, cond_bb);

                LLVMPositionBuilderAtEnd(g->bld, cond_bb);
                LLVMValueRef cond = emit_expr(g, curr->u.whilestmt.cond);
                if (LLVMTypeOf(cond) != ty_bool(g))
                    cond = LLVMBuildICmp(g->bld, LLVMIntNE, cond, const_i32(g, 0), "wcond");
                LLVMBuildCondBr(g->bld, cond, body_bb, end_bb);

                LLVMPositionBuilderAtEnd(g->bld, body_bb);
                emit_stmt(g, curr->u.whilestmt.body);
                if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(g->bld)))
                    LLVMBuildBr(g->bld, cond_bb);

                LLVMPositionBuilderAtEnd(g->bld, end_bb);
                break;
            }

            case NK_FOR: {
                /* for var := lo to/downto hi do body */
                Symbol *sym = sym_lookup(g->syms, curr->u.forstmt.var);
                if (!sym) { fprintf(stderr, "for: unknown var\n"); exit(1); }
                LLVMValueRef slot = sym->llvm_val;
                int downto = curr->u.forstmt.downto;

                LLVMValueRef lo = emit_expr(g, curr->u.forstmt.lo);
                LLVMValueRef hi = emit_expr(g, curr->u.forstmt.hi);
                LLVMBuildStore(g->bld, lo, slot);

                LLVMBasicBlockRef cond_bb = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "for.cond");
                LLVMBasicBlockRef body_bb = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "for.body");
                LLVMBasicBlockRef end_bb  = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "for.end");

                LLVMBuildBr(g->bld, cond_bb);
                LLVMPositionBuilderAtEnd(g->bld, cond_bb);
                LLVMValueRef cur_val = LLVMBuildLoad2(g->bld, ty_int(g), slot, "for_i");
                LLVMValueRef cond = downto
                    ? LLVMBuildICmp(g->bld, LLVMIntSGE, cur_val, hi, "for_cond")
                    : LLVMBuildICmp(g->bld, LLVMIntSLE, cur_val, hi, "for_cond");
                LLVMBuildCondBr(g->bld, cond, body_bb, end_bb);

                LLVMPositionBuilderAtEnd(g->bld, body_bb);
                emit_stmt(g, curr->u.forstmt.body);
                cur_val = LLVMBuildLoad2(g->bld, ty_int(g), slot, "for_i2");
                LLVMValueRef step = downto
                    ? LLVMBuildSub(g->bld, cur_val, const_i32(g, 1), "for_dec")
                    : LLVMBuildAdd(g->bld, cur_val, const_i32(g, 1), "for_inc");
                LLVMBuildStore(g->bld, step, slot);
                if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(g->bld)))
                    LLVMBuildBr(g->bld, cond_bb);

                LLVMPositionBuilderAtEnd(g->bld, end_bb);
                break;
            }

            case NK_WRITE: {
                /* writeln(true) → printf("true\n") etc. */
                int newline = curr->u.write.newline;
                AstNode *args = curr->u.write.args;

                if (!args) {
                    /* writeln with no args → just newline */
                    LLVMValueRef fmt = make_str(g, "\n", ".nl");
                    LLVMTypeRef printf_t = LLVMGlobalGetValueType(g->fn_printf);
                    LLVMBuildCall2(g->bld, printf_t, g->fn_printf, &fmt, 1, "");
                    break;
                }

                for (AstNode *a = args; a != NULL; a = a->next) {
                    LLVMValueRef val = emit_expr(g, a);
                    LLVMTypeRef  vt  = LLVMTypeOf(val);

                    if (vt == ty_bool(g)) {
                        /* print "true" or "false" */
                        LLVMBasicBlockRef true_bb  = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "wbool.t");
                        LLVMBasicBlockRef false_bb = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "wbool.f");
                        LLVMBasicBlockRef cont_bb  = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "wbool.end");
                        LLVMBuildCondBr(g->bld, val, true_bb, false_bb);

                        LLVMPositionBuilderAtEnd(g->bld, true_bb);
                        const char *tfmt = newline && !a->next ? "true\n" : "true";
                        LLVMValueRef ts = make_str(g, tfmt, ".strue");
                        LLVMTypeRef printf_t = LLVMGlobalGetValueType(g->fn_printf);
                        LLVMBuildCall2(g->bld, printf_t, g->fn_printf, &ts, 1, "");
                        LLVMBuildBr(g->bld, cont_bb);

                        LLVMPositionBuilderAtEnd(g->bld, false_bb);
                        const char *ffmt = newline && !a->next ? "false\n" : "false";
                        LLVMValueRef fs = make_str(g, ffmt, ".sfalse");
                        LLVMBuildCall2(g->bld, printf_t, g->fn_printf, &fs, 1, "");
                        LLVMBuildBr(g->bld, cont_bb);

                        LLVMPositionBuilderAtEnd(g->bld, cont_bb);

                    } else if (vt == ty_int(g)) {
                        const char *fmt_s = (newline && !a->next) ? "%d\n" : "%d ";
                        LLVMValueRef fmt = make_str(g, fmt_s, ".sint");
                        LLVMValueRef pargs[] = { fmt, val };
                        LLVMTypeRef printf_t = LLVMGlobalGetValueType(g->fn_printf);
                        LLVMBuildCall2(g->bld, printf_t, g->fn_printf, pargs, 2, "");

                    } else {
                        /* string literal (i8*) */
                        const char *fmt_s = newline && !a->next ? "%s\n" : "%s";
                        LLVMValueRef fmt = make_str(g, fmt_s, ".sstr");
                        LLVMValueRef pargs[] = { fmt, val };
                        LLVMTypeRef printf_t = LLVMGlobalGetValueType(g->fn_printf);
                        LLVMBuildCall2(g->bld, printf_t, g->fn_printf, pargs, 2, "");
                    }
                }
                /* trailing newline if writeln and last arg didn't include it */
                break;
            }

            case NK_CALL: {
                /* procedure call (result discarded) */
                const char *name = n->u.call.name;
                Symbol *sym = sym_lookup(g->syms, name);
                if (!sym) { fprintf(stderr, "codegen: unknown proc '%s'\n", name); exit(1); }
                LLVMValueRef fn = sym->llvm_val;
                LLVMValueRef call_args[64];
                unsigned nargs = 0;
                for (AstNode *a = curr->u.call.args; a && nargs < 64; a = a->next)
                    call_args[nargs++] = emit_expr(g, a);
                LLVMTypeRef fn_type = LLVMGlobalGetValueType(fn);
                LLVMBuildCall2(g->bld, fn_type, fn, call_args, nargs, "");
                break;
            }

            case NK_RETURN: {
                if (curr->u.ret.expr) {
                    LLVMValueRef val = emit_expr(g, curr->u.ret.expr);
                    LLVMBuildStore(g->bld, val, g->cur_fn_retslot);
                }
                /* actual ret is emitted at end of function */
                break;
            }

            case NK_BLOCK:
                emit_decls(g, curr->u.block.decls);
                emit_stmt(g, curr->u.block.stmts);
                break;

            case NK_SEQ:
                emit_stmt(g, curr);
                break;

            default:
                break;
        }
    }
}

/* ── Declaration emitter (var decls inside blocks) ──────────── */
static void emit_decls(CG *g, AstNode *n) {
    for (AstNode *d = n; d != NULL; d = d->next) {
        if (d->kind == NK_VAR_DECL) {
            LLVMTypeRef ty = pascal_to_llvm(g, d->u.var.vtype);
            LLVMValueRef slot = LLVMBuildAlloca(g->bld, ty, d->u.var.name);
            /* zero-initialize */
            LLVMBuildStore(g->bld, LLVMConstNull(ty), slot);
            Symbol *sym = sym_insert(g->syms, d->u.var.name, SYM_VAR, d->u.var.vtype);
            sym->llvm_val = slot;
        }
        /* proc/func decls are handled in cg_emit pre-pass */
    }
}

/* ── Proc/func forward declaration + body emit ──────────────── */
static void emit_proc(CG *g, AstNode *n) {
    int is_func = (n->kind == NK_FUNC_DECL);

    /* build parameter type list */
    LLVMTypeRef param_types[64];
    unsigned    nparams = 0;
    for (AstNode *p = n->u.proc.params; p && nparams < 64; p = p->next)
        param_types[nparams++] = pascal_to_llvm(g, p->u.var.vtype);

    LLVMTypeRef ret_ty = is_func ? pascal_to_llvm(g, n->u.proc.rettype) : ty_void(g);
    LLVMTypeRef fn_ty  = LLVMFunctionType(ret_ty, param_types, nparams, 0);
    LLVMValueRef fn    = LLVMAddFunction(g->mod, n->u.proc.name, fn_ty);

    /* register in symbol table */
    Symbol *sym = sym_insert(g->syms, n->u.proc.name,
                             is_func ? SYM_FUNC : SYM_PROC,
                             is_func ? n->u.proc.rettype : TY_VOID);
    sym->llvm_val = fn;

    /* save outer context */
    LLVMValueRef   outer_fn      = g->cur_fn;
    PascalType     outer_rettype = g->cur_fn_rettype;
    LLVMValueRef   outer_retslot = g->cur_fn_retslot;
    SymTable      *outer_syms    = g->syms;

    /* new scope */
    SymTable local_syms;
    sym_init(&local_syms);
    /* copy globals into local so lookups work */
    for (int i = 0; i < SYM_CAP; i++)
        if (outer_syms->slots[i].name)
            sym_insert(&local_syms, outer_syms->slots[i].name,
                       outer_syms->slots[i].kind, outer_syms->slots[i].type);
    /* copy llvm_val pointers */
    for (int i = 0; i < SYM_CAP; i++) {
        if (outer_syms->slots[i].name) {
            Symbol *ls = sym_lookup(&local_syms, outer_syms->slots[i].name);
            if (ls) ls->llvm_val = outer_syms->slots[i].llvm_val;
        }
    }
    g->syms = &local_syms;
    g->cur_fn = fn;
    g->cur_fn_rettype = is_func ? n->u.proc.rettype : TY_VOID;

    LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(g->ctx, fn, "entry");
    LLVMPositionBuilderAtEnd(g->bld, entry);

    /* alloca for function return value */
    if (is_func) {
        g->cur_fn_retslot = LLVMBuildAlloca(g->bld, ret_ty, "retval");
        LLVMBuildStore(g->bld, LLVMConstNull(ret_ty), g->cur_fn_retslot);
        /* register as assignable via function name */
        Symbol *rs = sym_insert(&local_syms, n->u.proc.name, SYM_FUNC, n->u.proc.rettype);
        rs->llvm_val = g->cur_fn_retslot;
    } else {
        g->cur_fn_retslot = NULL;
    }

    /* bind parameters */
    unsigned pi = 0;
    for (AstNode *p = n->u.proc.params; p && pi < nparams; p = p->next, pi++) {
        LLVMValueRef pval  = LLVMGetParam(fn, pi);
        LLVMTypeRef  pty   = pascal_to_llvm(g, p->u.var.vtype);
        LLVMValueRef slot  = LLVMBuildAlloca(g->bld, pty, p->u.var.name);
        LLVMBuildStore(g->bld, pval, slot);
        Symbol *ps = sym_insert(&local_syms, p->u.var.name, SYM_PARAM, p->u.var.vtype);
        ps->llvm_val = slot;
    }

    /* emit body */
    AstNode *body = n->u.proc.body;
    if (body->kind == NK_BLOCK) {
        emit_decls(g, body->u.block.decls);
        emit_stmt(g, body->u.block.stmts);
    } else {
        emit_stmt(g, body);
    }

    /* emit return */
    if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(g->bld))) {
        if (is_func) {
            LLVMValueRef rv = LLVMBuildLoad2(g->bld, ret_ty, g->cur_fn_retslot, "ret");
            LLVMBuildRet(g->bld, rv);
        } else {
            LLVMBuildRetVoid(g->bld);
        }
    }

    /* restore outer context */
    g->cur_fn      = outer_fn;
    g->cur_fn_rettype = outer_rettype;
    g->cur_fn_retslot = outer_retslot;
    g->syms        = outer_syms;
}

/* ── Top-level entry ────────────────────────────────────────── */
void cg_emit(CG *g, AstNode *root, SymTable *syms) {
    g->syms = syms;

    /* root must be NK_PROGRAM */
    if (!root || root->kind != NK_PROGRAM) {
        fprintf(stderr, "codegen: expected NK_PROGRAM\n"); exit(1);
    }
    AstNode *block = root->u.program.block;

    /* ── Build main(int argc, char **argv) ── */
    LLVMTypeRef i32       = ty_int(g);
    LLVMTypeRef i8p       = ty_i8p(g);
    LLVMTypeRef i8pp      = LLVMPointerType(i8p, 0);
    LLVMTypeRef main_args[2] = { i32, i8pp };
    LLVMTypeRef main_ty   = LLVMFunctionType(i32, main_args, 2, 0);
    LLVMValueRef main_fn  = LLVMAddFunction(g->mod, "main", main_ty);

    g->cur_fn         = main_fn;
    g->cur_fn_rettype = TY_INT;

    LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(g->ctx, main_fn, "entry");
    LLVMPositionBuilderAtEnd(g->bld, entry);

    /* store argc/argv for paramcount/paramstr */
    g->llvm_argc = LLVMGetParam(main_fn, 0);
    g->llvm_argv = LLVMGetParam(main_fn, 1);

    /* ── First pass: emit proc/func decls ── */
    for (AstNode *d = block->u.block.decls; d != NULL; d = d->next) {
        if (d->kind == NK_PROC_DECL || d->kind == NK_FUNC_DECL)
            emit_proc(g, d);
    }
    /* re-position after proc decls may have moved builder */
    LLVMPositionBuilderAtEnd(g->bld, entry);

    /* ── Emit global var decls ── */
    emit_decls(g, block->u.block.decls);

    /* ── Emit main body ── */
    emit_stmt(g, block->u.block.stmts);

    /* ── Return 0 ── */
    if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(g->bld)))
        LLVMBuildRet(g->bld, const_i32(g, 0));
}

/* ── Writing outputs ────────────────────────────────────────── */
int cg_write_ir(CG *cg, const char *path) {
    char *err = NULL;
    if (LLVMPrintModuleToFile(cg->mod, path, &err)) {
        fprintf(stderr, "IR write error: %s\n", err);
        LLVMDisposeMessage(err);
        return 1;
    }
    return 0;
}

int cg_write_obj(CG *cg, const char *path) {
    LLVMInitializeAllTargetInfos();
    LLVMInitializeAllTargets();
    LLVMInitializeAllTargetMCs();
    LLVMInitializeAllAsmPrinters();
    LLVMInitializeAllAsmParsers();

    char *triple = LLVMGetDefaultTargetTriple();
    LLVMTargetRef target;
    char *err = NULL;
    if (LLVMGetTargetFromTriple(triple, &target, &err)) {
        fprintf(stderr, "target error: %s\n", err);
        LLVMDisposeMessage(err); LLVMDisposeMessage(triple);
        return 1;
    }
    LLVMTargetMachineRef tm = LLVMCreateTargetMachine(
        target, triple, "generic", "",
        LLVMCodeGenLevelDefault, LLVMRelocPIC, LLVMCodeModelDefault);
    LLVMDisposeMessage(triple);

    LLVMSetModuleDataLayout(cg->mod, LLVMCreateTargetDataLayout(tm));
    LLVMSetTarget(cg->mod, LLVMGetDefaultTargetTriple());

    char *filename = strdup(path);
    if (LLVMTargetMachineEmitToFile(tm, cg->mod, filename, LLVMObjectFile, &err)) {
        fprintf(stderr, "obj write error: %s\n", err);
        LLVMDisposeMessage(err);
        free(filename);
        LLVMDisposeTargetMachine(tm);
        return 1;
    }
    LLVMDisposeTargetMachine(tm);
    free(filename);
    return 0;
}
