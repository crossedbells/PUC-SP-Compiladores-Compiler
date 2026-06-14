#ifndef AST_H
#define AST_H

#include <stdint.h>

/* ── Types ─────────────────────────────────────────────────── */
typedef enum { TY_INT, TY_BOOL, TY_VOID } PascalType;

/* ── Node kinds ─────────────────────────────────────────────── */
typedef enum {
    NK_PROGRAM,      /* program Name; block */
    NK_BLOCK,        /* decl-list + stmt-list */
    NK_VAR_DECL,     /* var id : type */
    NK_ASSIGN,       /* id := expr */
    NK_IF,           /* if cond then s1 [else s2] */
    NK_WHILE,        /* while cond do body */
    NK_FOR,          /* for id := lo to hi do body */
    NK_WRITE,        /* write / writeln (expr-list) */
    NK_CALL,         /* proc/func call */
    NK_RETURN,       /* function return */
    NK_SEQ,          /* statement sequence (linked via ->next) */
    NK_BINOP,        /* binary operation */
    NK_UNOP,         /* unary operation */
    NK_INT_LIT,      /* integer literal */
    NK_BOOL_LIT,     /* boolean literal */
    NK_IDENT,        /* identifier reference */
    NK_PARAM,        /* formal parameter */
    NK_PROC_DECL,    /* procedure declaration */
    NK_FUNC_DECL,    /* function declaration */
    NK_ARG_LIST,     /* actual argument list */
} NodeKind;

/* ── Operators ──────────────────────────────────────────────── */
typedef enum {
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD,
    OP_EQ,  OP_NEQ, OP_LT,  OP_LE,  OP_GT, OP_GE,
    OP_AND, OP_OR,  OP_NOT, OP_NEG
} Op;

/* ── Forward declaration ────────────────────────────────────── */
typedef struct AstNode AstNode;

/* ── Node payload union ─────────────────────────────────────── */
struct AstNode {
    NodeKind kind;
    int      line;          /* source line for error reporting  */
    PascalType type;        /* resolved type (filled by sema)   */
    AstNode  *next;         /* sibling in sequence / arg list   */

    union {
        /* NK_PROGRAM */
        struct { char *name; AstNode *block; } program;

        /* NK_BLOCK */
        struct { AstNode *decls; AstNode *stmts; } block;

        /* NK_VAR_DECL / NK_PARAM */
        struct { char *name; PascalType vtype; } var;

        /* NK_ASSIGN */
        struct { char *name; AstNode *expr; } assign;

        /* NK_IF */
        struct { AstNode *cond; AstNode *then; AstNode *els; } ifstmt;

        /* NK_WHILE */
        struct { AstNode *cond; AstNode *body; } whilestmt;

        /* NK_FOR */
        struct { char *var; AstNode *lo; AstNode *hi; AstNode *body; int downto; } forstmt;

        /* NK_WRITE */
        struct { AstNode *args; int newline; } write;

        /* NK_CALL / NK_ARG_LIST */
        struct { char *name; AstNode *args; } call;

        /* NK_RETURN */
        struct { AstNode *expr; } ret;

        /* NK_BINOP */
        struct { Op op; AstNode *left; AstNode *right; } binop;

        /* NK_UNOP */
        struct { Op op; AstNode *operand; } unop;

        /* NK_INT_LIT */
        struct { int64_t value; } iliteral;

        /* NK_BOOL_LIT */
        struct { int value; } bliteral;  /* 0=false, 1=true */

        /* NK_IDENT */
        struct { char *name; } ident;

        /* NK_PROC_DECL / NK_FUNC_DECL */
        struct {
            char      *name;
            AstNode   *params;   /* linked NK_PARAM list */
            PascalType rettype;  /* TY_VOID for procedures */
            AstNode   *body;     /* NK_BLOCK */
        } proc;

    } u;
};

/* ── Symbol table (flat open-addressing hash map) ───────────── */
#define SYM_CAP 256  /* must be power of 2 */

typedef enum { SYM_VAR, SYM_PROC, SYM_FUNC, SYM_PARAM } SymKind;

typedef struct {
    char       *name;       /* NULL = empty slot              */
    SymKind     kind;
    PascalType  type;
    int         param_idx;  /* for SYM_PARAM: position index */
    /* codegen slot — filled during IR generation */
    void       *llvm_val;   /* LLVMValueRef, cast at use     */
} Symbol;

typedef struct {
    Symbol slots[SYM_CAP];
    int    count;
} SymTable;

/* ── AST allocator ──────────────────────────────────────────── */
AstNode  *ast_node(NodeKind kind, int line);
void      ast_free(AstNode *n);           /* recursive free    */

/* ── Symbol table API ───────────────────────────────────────── */
void      sym_init(SymTable *t);
Symbol   *sym_insert(SymTable *t, const char *name, SymKind k, PascalType ty);
Symbol   *sym_lookup(SymTable *t, const char *name);

#endif /* AST_H */
