#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

/* ── Helpers ────────────────────────────────────────────────── */
static LLVMTypeRef  ty_int(CG *g)  { return LLVMInt32TypeInContext(g->ctx); }
static LLVMTypeRef  ty_bool(CG *g) { return LLVMInt1TypeInContext(g->ctx);  }
static LLVMTypeRef  ty_i8p(CG *g)  { return LLVMPointerType(LLVMInt8TypeInContext(g->ctx), 0); }
static LLVMTypeRef  ty_void(CG *g) { return LLVMVoidTypeInContext(g->ctx);  }

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

/* Forward declarations */
static LLVMValueRef emit_expr(CG *g, AstNode *n);
static void         emit_stmt(CG *g, AstNode *n);

/* ── Extern declarations ────────────────────────────────────── */
static void declare_externs(CG *g) {
    LLVMTypeRef p_args[] = { ty_i8p(g) };
    LLVMTypeRef p_type = LLVMFunctionType(ty_int(g), p_args, 1, 1);
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

/* ── Symbol lookups ─────────────────────────────────────────── */
static LLVMValueRef lookup_slot(CG *g, const char *name) {
    if (!strcmp(name, "__paramcount")) {
        return LLVMBuildSub(g->bld, g->llvm_argc, const_i32(g, 1), "paramcount_val");
    }
    
    Symbol *sym = sym_lookup(g->syms, name); /* Corrigido de sym_find para sym_lookup */
    if (!sym) {
        if (g->cur_fn && !strcmp(name, LLVMGetValueName(g->cur_fn))) {
            return g->cur_fn_retslot;
        }
        fprintf(stderr, "codegen error: unresolved identifier '%s'\n", name);
        exit(1);
    }
    if (sym->kind == SYM_FUNC && g->cur_fn && !strcmp(name, LLVMGetValueName(g->cur_fn))) {
        return g->cur_fn_retslot;
    }
    return (LLVMValueRef)sym->llvm_val;
}

/* ── Expressions ────────────────────────────────────────────── */
static LLVMValueRef emit_expr(CG *g, AstNode *n) {
    if (!n) return NULL;
    switch (n->kind) {
        case NK_INT_LIT:
            return const_i32(g, n->u.iliteral.value);

        case NK_BOOL_LIT:
            return LLVMConstInt(ty_bool(g), n->u.bliteral.value, 0);

        case NK_IDENT: {
            if (!strcmp(n->u.ident.name, "__paramcount")) {
                return lookup_slot(g, "__paramcount");
            }
            LLVMValueRef slot = lookup_slot(g, n->u.ident.name);
            if (LLVMIsAAllocaInst(slot) || LLVMIsAGlobalVariable(slot)) {
                return LLVMBuildLoad2(g->bld, LLVMGetAllocatedType(slot) ? LLVMGetAllocatedType(slot) : ty_int(g), slot, "tmp_load");
            }
            return slot;
        }

        case NK_BINOP: {
            LLVMValueRef lhs = emit_expr(g, n->u.binop.left);
            LLVMValueRef rhs = emit_expr(g, n->u.binop.right);
            switch (n->u.binop.op) {
                case OP_ADD: return LLVMBuildAdd(g->bld, lhs, rhs, "addtmp");
                case OP_SUB: return LLVMBuildSub(g->bld, lhs, rhs, "subtmp");
                case OP_MUL: return LLVMBuildMul(g->bld, lhs, rhs, "multmp");
                case OP_DIV: return LLVMBuildSDiv(g->bld, lhs, rhs, "divtmp");
                case OP_MOD: return LLVMBuildSRem(g->bld, lhs, rhs, "modtmp");
                case OP_EQ:  return LLVMBuildICmp(g->bld, LLVMIntEQ,  lhs, rhs, "eqtmp");
                case OP_NEQ: return LLVMBuildICmp(g->bld, LLVMIntNE,  lhs, rhs, "neqtmp");
                case OP_LT:  return LLVMBuildICmp(g->bld, LLVMIntSLT, lhs, rhs, "lttmp");
                case OP_LE:  return LLVMBuildICmp(g->bld, LLVMIntSLE, lhs, rhs, "letmp");
                case OP_GT:  return LLVMBuildICmp(g->bld, LLVMIntSGT, lhs, rhs, "gttmp");
                case OP_GE:  return LLVMBuildICmp(g->bld, LLVMIntSGE, lhs, rhs, "getmp");
                case OP_AND: return LLVMBuildAnd(g->bld, lhs, rhs, "andtmp");
                case OP_OR:  return LLVMBuildOr(g->bld, lhs, rhs, "ortmp");
                default: break; /* Evita os avisos OP_NOT e OP_NEG do switch */
            }
            break;
        }

        case NK_UNOP: {
            LLVMValueRef opnd = emit_expr(g, n->u.unop.operand);
            if (n->u.unop.op == OP_NEG) return LLVMBuildNeg(g->bld, opnd, "negtmp");
            if (n->u.unop.op == OP_NOT) return LLVMBuildNot(g->bld, opnd, "nottmp");
            break;
        }

        case NK_CALL: {
            if (!strcmp(n->u.call.name, "__paramstr")) {
                LLVMValueRef idx_val = emit_expr(g, n->u.call.args);
                LLVMValueRef gep_args[] = { idx_val };
                LLVMValueRef str_ptr_slot = LLVMBuildGEP2(g->bld, ty_i8p(g), g->llvm_argv, gep_args, 1, "str_ptr_slot");
                LLVMValueRef str_ptr = LLVMBuildLoad2(g->bld, ty_i8p(g), str_ptr_slot, "str_ptr");
                
                LLVMTypeRef i8p_ty = ty_i8p(g); /* Corrigido lvalue required as unary '&' */
                LLVMTypeRef atoi_type = LLVMFunctionType(ty_int(g), &i8p_ty, 1, 0);
                return LLVMBuildCall2(g->bld, atoi_type, g->fn_atoi, &str_ptr, 1, "atoi_res");
            }

            Symbol *s = sym_lookup(g->syms, n->u.call.name); /* Corrigido para sym_lookup */
            if (!s || (s->kind != SYM_PROC && s->kind != SYM_FUNC)) {
                fprintf(stderr, "codegen error: '%s' is not a callable routine\n", n->u.call.name);
                exit(1);
            }
            LLVMValueRef target_fn = (LLVMValueRef)s->llvm_val;
            int count = 0;
            for (AstNode *a = n->u.call.args; a; a = a->next) count++;
            LLVMValueRef *args = malloc(sizeof(LLVMValueRef) * (count + 1));
            int i = 0;
            for (AstNode *a = n->u.call.args; a; a = a->next) {
                args[i++] = emit_expr(g, a);
            }
            LLVMTypeRef fn_type = LLVMGetCalledFunctionType(target_fn);
            if (!fn_type) {
                LLVMTypeRef *p_tys = malloc(sizeof(LLVMTypeRef)*count);
                for(int k=0; k<count; k++) p_tys[k] = ty_int(g);
                fn_type = LLVMFunctionType(pascal_to_llvm(g, s->type), p_tys, count, 0);
                free(p_tys);
            }
            LLVMValueRef call = LLVMBuildCall2(g->bld, fn_type, target_fn, args, count, s->kind == SYM_FUNC ? "calltmp" : "");
            free(args);
            return call;
        }

        default: break;
    }
    return NULL;
}

/* ── Statements ─────────────────────────────────────────────── */
static void emit_stmt(CG *g, AstNode *n) {
    if (!n) return;
    switch (n->kind) {
        case NK_ASSIGN: {
            LLVMValueRef val = emit_expr(g, n->u.assign.expr);
            LLVMValueRef slot = lookup_slot(g, n->u.assign.name);
            LLVMBuildStore(g->bld, val, slot);
            break;
        }

        case NK_WRITE: {
            LLVMValueRef first_print_g = LLVMGetNamedGlobal(g->mod, "_first_print");
            if (!first_print_g) {
                first_print_g = LLVMAddGlobal(g->mod, ty_int(g), "_first_print");
                LLVMSetInitializer(first_print_g, const_i32(g, 1));
            }

            for (AstNode *arg = n->u.write.args; arg; arg = arg->next) {
                LLVMValueRef v = emit_expr(g, arg);
                LLVMTypeRef v_type = LLVMTypeOf(v);
                LLVMValueRef pf_args[2];

                LLVMValueRef is_first = LLVMBuildLoad2(g->bld, ty_int(g), first_print_g, "load_first");
                LLVMValueRef cond_first = LLVMBuildICmp(g->bld, LLVMIntEQ, is_first, const_i32(g, 1), "cond_first");

                if (LLVMGetTypeKind(v_type) == LLVMIntegerTypeKind && LLVMGetIntTypeWidth(v_type) == 1) {
                    LLVMValueRef true_str  = LLVMBuildGlobalStringPtr(g->bld, "true", "t_str");
                    LLVMValueRef false_str = LLVMBuildGlobalStringPtr(g->bld, "false", "f_str");
                    LLVMValueRef bool_str  = LLVMBuildSelect(g->bld, v, true_str, false_str, "b_str");
                    
                    LLVMValueRef fmt_normal = LLVMBuildGlobalStringPtr(g->bld, "%s", "fmt_s");
                    LLVMValueRef fmt_space  = LLVMBuildGlobalStringPtr(g->bld, " %s", "fmt_s_sp");
                    
                    pf_args[0] = LLVMBuildSelect(g->bld, cond_first, fmt_normal, fmt_space, "select_fmt");
                    pf_args[1] = bool_str;
                } else {
                    LLVMValueRef fmt_normal = LLVMBuildGlobalStringPtr(g->bld, "%d", "fmt_d");
                    LLVMValueRef fmt_space  = LLVMBuildGlobalStringPtr(g->bld, " %d", "fmt_d_sp");
                    
                    pf_args[0] = LLVMBuildSelect(g->bld, cond_first, fmt_normal, fmt_space, "select_fmt");
                    pf_args[1] = v;
                }

                LLVMTypeRef i8p_ty = ty_i8p(g); /* Corrigido lvalue required as unary '&' */
                LLVMTypeRef pf_type = LLVMFunctionType(ty_int(g), &i8p_ty, 1, 1);
                LLVMBuildCall2(g->bld, pf_type, g->fn_printf, pf_args, 2, "");
                
                LLVMBuildStore(g->bld, const_i32(g, 0), first_print_g);
            }
            
            if (n->u.write.newline) {
                LLVMValueRef pf_args[1];
                pf_args[0] = LLVMBuildGlobalStringPtr(g->bld, "\n", "nlfmt");
                LLVMTypeRef i8p_ty = ty_i8p(g); /* Corrigido lvalue required as unary '&' */
                LLVMTypeRef pf_type = LLVMFunctionType(ty_int(g), &i8p_ty, 1, 1);
                LLVMBuildCall2(g->bld, pf_type, g->fn_printf, pf_args, 1, "");
                
                LLVMBuildStore(g->bld, const_i32(g, 1), first_print_g);
            }
            break;
        }

        case NK_IF: {
            LLVMValueRef cond = emit_expr(g, n->u.ifstmt.cond);
            LLVMBasicBlockRef then_bb = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "then");
            LLVMBasicBlockRef else_bb = n->u.ifstmt.els ? LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "else") : NULL;
            LLVMBasicBlockRef merge_bb = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "ifcont");

            LLVMBuildCondBr(g->bld, cond, then_bb, else_bb ? else_bb : merge_bb);

            LLVMPositionBuilderAtEnd(g->bld, then_bb);
            emit_stmt(g, n->u.ifstmt.then);
            if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(g->bld))) {
                LLVMBuildBr(g->bld, merge_bb);
            }

            if (else_bb) {
                LLVMPositionBuilderAtEnd(g->bld, else_bb);
                emit_stmt(g, n->u.ifstmt.els);
                if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(g->bld))) {
                    LLVMBuildBr(g->bld, merge_bb);
                }
            }

            LLVMPositionBuilderAtEnd(g->bld, merge_bb);
            break;
        }

        case NK_WHILE: {
            LLVMBasicBlockRef cond_bb = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "whilecond");
            LLVMBasicBlockRef body_bb = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "whilebody");
            LLVMBasicBlockRef end_bb  = LLVMAppendBasicBlockInContext(g->ctx, g->cur_fn, "whileend");

            LLVMBuildBr(g->bld, cond_bb);
            LLVMPositionBuilderAtEnd(g->bld, cond_bb);
            LLVMValueRef cond = emit_expr(g, n->u.whilestmt.cond);
            LLVMBuildCondBr(g->bld, cond, body_bb, end_bb);

            LLVMPositionBuilderAtEnd(g->bld, body_bb);
            emit_stmt(g, n->u.whilestmt.body);
            if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(g->bld))) {
                LLVMBuildBr(g->bld, cond_bb);
            }

            LLVMPositionBuilderAtEnd(g->bld, end_bb);
            break;
        }

        default: break;
    }
}

/* ── Declarations & Scopes ──────────────────────────────────── */
static void emit_proc(CG *g, AstNode *n) {
    int pcount = 0;
    for (AstNode *p = n->u.proc.params; p; p = p->next) pcount++;
    LLVMTypeRef *p_types = malloc(sizeof(LLVMTypeRef) * (pcount + 1));
    for (int i = 0; i < pcount; i++) p_types[i] = ty_int(g);

    LLVMTypeRef ret_t = pascal_to_llvm(g, n->u.proc.rettype);
    LLVMTypeRef fn_t = LLVMFunctionType(ret_t, p_types, pcount, 0);
    LLVMValueRef fn = LLVMAddFunction(g->mod, n->u.proc.name, fn_t);

    Symbol *fsym = sym_insert(g->syms, n->u.proc.name, n->kind == NK_FUNC_DECL ? SYM_FUNC : SYM_PROC, n->u.proc.rettype);
    fsym->llvm_val = fn;

    LLVMValueRef old_fn = g->cur_fn;
    PascalType old_rt  = g->cur_fn_rettype;
    LLVMValueRef old_slot = g->cur_fn_retslot;

    g->cur_fn = fn;
    g->cur_fn_rettype = n->u.proc.rettype;

    LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(g->ctx, fn, "entry");
    LLVMBuilderRef b = g->bld;
    LLVMPositionBuilderAtEnd(b, entry);

    if (n->kind == NK_FUNC_DECL) {
        g->cur_fn_retslot = LLVMBuildAlloca(b, ret_t, "ret_slot");
    }

    int idx = 0;
    for (AstNode *p = n->u.proc.params; p; p = p->next) {
        LLVMValueRef p_alloc = LLVMBuildAlloca(b, ty_int(g), p->u.var.name);
        LLVMBuildStore(b, LLVMGetParam(fn, idx), p_alloc);
        Symbol *psym = sym_insert(g->syms, p->u.var.name, SYM_PARAM, p->u.var.vtype);
        psym->llvm_val = p_alloc;
        idx++;
    }

    AstNode *block = n->u.proc.body;
    for (AstNode *d = block->u.block.decls; d; d = d->next) {
        if (d->kind == NK_VAR_DECL) {
            LLVMValueRef v_alloc = LLVMBuildAlloca(b, pascal_to_llvm(g, d->u.var.vtype), d->u.var.name);
            Symbol *vsym = sym_insert(g->syms, d->u.var.name, SYM_VAR, d->u.var.vtype);
            vsym->llvm_val = v_alloc;
        }
    }

    for (AstNode *s = block->u.block.stmts; s; s = s->next) {
        emit_stmt(g, s);
    }

    if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(b))) {
        if (n->kind == NK_FUNC_DECL) {
            LLVMValueRef final_ret = LLVMBuildLoad2(b, ret_t, g->cur_fn_retslot, "retval");
            LLVMBuildRet(b, final_ret);
        } else {
            LLVMBuildRetVoid(b);
        }
    }

    g->cur_fn = old_fn;
    g->cur_fn_rettype = old_rt;
    g->cur_fn_retslot = old_slot;
    free(p_types);
}

static void emit_main(CG *g, AstNode *block) {
    LLVMTypeRef main_args[] = { ty_int(g), LLVMPointerType(ty_i8p(g), 0) };
    LLVMTypeRef main_type = LLVMFunctionType(ty_int(g), main_args, 2, 0);
    LLVMValueRef main_fn = LLVMAddFunction(g->mod, "main", main_type);

    g->cur_fn = main_fn;
    g->cur_fn_rettype = TY_INT;

    LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(g->ctx, main_fn, "entry");
    LLVMPositionBuilderAtEnd(g->bld, entry);

    g->llvm_argc = LLVMGetParam(main_fn, 0);
    g->llvm_argv = LLVMGetParam(main_fn, 1);

    for (AstNode *d = block->u.block.decls; d; d = d->next) {
        if (d->kind == NK_VAR_DECL) {
            LLVMValueRef v_alloc = LLVMBuildAlloca(g->bld, pascal_to_llvm(g, d->u.var.vtype), d->u.var.name);
            Symbol *vsym = sym_insert(g->syms, d->u.var.name, SYM_VAR, d->u.var.vtype);
            vsym->llvm_val = v_alloc;
        }
    }

    for (AstNode *s = block->u.block.stmts; s; s = s->next) {
        emit_stmt(g, s);
    }

    if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(g->bld))) {
        LLVMBuildRet(g->bld, const_i32(g, 0));
    }
}

void cg_emit(CG *g, AstNode *root, SymTable *syms) {
    if (!root || root->kind != NK_PROGRAM) return;
    g->syms = syms;

    AstNode *block = root->u.program.block;
    for (AstNode *d = block->u.block.decls; d; d = d->next) {
        if (d->kind == NK_PROC_DECL || d->kind == NK_FUNC_DECL)
            emit_proc(g, d);
    }

    emit_main(g, block);
}

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
        LLVMCodeGenLevelDefault, LLVMRelocDefault, LLVMCodeModelDefault);
    LLVMDisposeMessage(triple);

    LLVMSetModuleDataLayout(cg->mod, LLVMCreateTargetDataLayout(tm));
    LLVMSetTarget(cg->mod, triple);

    char *filename = strdup(path);
    if (LLVMTargetMachineEmitToFile(tm, cg->mod, filename, LLVMObjectFile, &err)) {
        fprintf(stderr, "obj write error: %s\n", err);
        LLVMDisposeMessage(err); free(filename); LLVMDisposeTargetMachine(tm);
        return 1;
    }

    free(filename);
    LLVMDisposeTargetMachine(tm);
    return 0;
}
