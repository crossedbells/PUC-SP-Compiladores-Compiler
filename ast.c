#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ast.h"

/* ── AST allocator ──────────────────────────────────────────── */
AstNode *ast_node(NodeKind kind, int line) {
    AstNode *n = calloc(1, sizeof(AstNode));
    if (!n) { fputs("OOM\n", stderr); exit(1); }
    n->kind = kind;
    n->line = line;
    n->type = TY_VOID;
    return n;
}

/* Post-order recursive free — does NOT free char* names
   (those point into Flex's string pool / strdup'd in parser) */
void ast_free(AstNode *n) {
    if (!n) return;
    ast_free(n->next);
    switch (n->kind) {
        case NK_PROGRAM:   free(n->u.program.name);
                           ast_free(n->u.program.block);          break;
        case NK_BLOCK:     ast_free(n->u.block.decls);
                           ast_free(n->u.block.stmts);            break;
        case NK_VAR_DECL:
        case NK_PARAM:     free(n->u.var.name);                   break;
        case NK_ASSIGN:    free(n->u.assign.name);
                           ast_free(n->u.assign.expr);            break;
        case NK_IF:        ast_free(n->u.ifstmt.cond);
                           ast_free(n->u.ifstmt.then);
                           ast_free(n->u.ifstmt.els);             break;
        case NK_WHILE:     ast_free(n->u.whilestmt.cond);
                           ast_free(n->u.whilestmt.body);         break;
        case NK_FOR:       free(n->u.forstmt.var);
                           ast_free(n->u.forstmt.lo);
                           ast_free(n->u.forstmt.hi);
                           ast_free(n->u.forstmt.body);           break;
        case NK_WRITE:     ast_free(n->u.write.args);             break;
        case NK_CALL:
        case NK_ARG_LIST:  free(n->u.call.name);
                           ast_free(n->u.call.args);              break;
        case NK_RETURN:    ast_free(n->u.ret.expr);               break;
        case NK_BINOP:     ast_free(n->u.binop.left);
                           ast_free(n->u.binop.right);            break;
        case NK_UNOP:      ast_free(n->u.unop.operand);           break;
        case NK_IDENT:     free(n->u.ident.name);                 break;
        case NK_PROC_DECL:
        case NK_FUNC_DECL: free(n->u.proc.name);
                           ast_free(n->u.proc.params);
                           ast_free(n->u.proc.body);              break;
        case NK_SEQ:       /* children linked via ->next */        break;
        default:                                                   break;
    }
    free(n);
}

/* ── Symbol table ───────────────────────────────────────────── */
/* FNV-1a 32-bit */
static uint32_t fnv1a(const char *s) {
    uint32_t h = 2166136261u;
    while (*s) { h ^= (uint8_t)*s++; h *= 16777619u; }
    return h;
}

void sym_init(SymTable *t) {
    memset(t, 0, sizeof(SymTable));
}

Symbol *sym_insert(SymTable *t, const char *name, SymKind k, PascalType ty) {
    if (t->count >= SYM_CAP * 3 / 4) {
        fputs("symbol table full\n", stderr); exit(1);
    }
    uint32_t idx = fnv1a(name) & (SYM_CAP - 1);
    while (t->slots[idx].name) {
        if (!strcmp(t->slots[idx].name, name)) return &t->slots[idx]; /* update */
        idx = (idx + 1) & (SYM_CAP - 1);
    }
    t->slots[idx].name = strdup(name);
    t->slots[idx].kind = k;
    t->slots[idx].type = ty;
    t->count++;
    return &t->slots[idx];
}

Symbol *sym_lookup(SymTable *t, const char *name) {
    uint32_t idx = fnv1a(name) & (SYM_CAP - 1);
    while (t->slots[idx].name) {
        if (!strcmp(t->slots[idx].name, name)) return &t->slots[idx];
        idx = (idx + 1) & (SYM_CAP - 1);
    }
    return NULL;
}
