%{
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylineno;
extern int yylex(void);
void yyerror(const char *msg);

AstNode *parse_root = NULL;   /* root handed to main() */

/* helpers */
static AstNode *seq_append(AstNode *list, AstNode *node) {
    if (!list) return node;
    AstNode *cur = list;
    while (cur->next) cur = cur->next;
    cur->next = node;
    return list;
}
%}

/* ── Value union ────────────────────────────────────────────── */
%union {
    int     ival;
    char    *sval;
    AstNode *node;
    PascalType tyval;
}

%nonassoc LOWER_THAN_ELSE
%nonassoc TOK_ELSE

/* ── Tokens ─────────────────────────────────────────────────── */
%token TOK_PROGRAM TOK_BEGIN TOK_END
%token TOK_VAR TOK_INTEGER TOK_BOOLEAN TOK_OF
%token TOK_IF TOK_THEN TOK_ELSE
%token TOK_WHILE TOK_DO
%token TOK_FOR TOK_TO TOK_DOWNTO
%token TOK_PROCEDURE TOK_FUNCTION
%token TOK_WRITE TOK_WRITELN
%token TOK_AND TOK_OR TOK_NOT
%token TOK_DIV TOK_MOD
%token TOK_PARAMCOUNT TOK_PARAMSTR
%token TOK_ASSIGN TOK_SEMI TOK_COLON TOK_COMMA TOK_DOT
%token TOK_LPAREN TOK_RPAREN
%token TOK_EQ TOK_NEQ TOK_LT TOK_LE TOK_GT TOK_GE
%token TOK_PLUS TOK_MINUS TOK_STAR TOK_SLASH

%token <ival> TOK_INT_LIT TOK_TRUE TOK_FALSE
%token <sval> TOK_IDENT TOK_STR_LIT

/* ── Types ──────────────────────────────────────────────────── */
%type <node> program block
%type <node> var_decl_section var_decl_list var_decl
%type <node> proc_decl func_decl param_section param_list param
%type <node> stmt_list inner_stmts stmt
%type <node> assign_stmt if_stmt while_stmt for_stmt
%type <node> write_stmt call_stmt
%type <node> expr expr_list arg_list
%type <tyval> type_spec
%type <ival>  for_dir

/* ── Precedence (low → high) ────────────────────────────────── */
%left  TOK_OR
%left  TOK_AND
%right TOK_NOT
%nonassoc TOK_EQ TOK_NEQ TOK_LT TOK_LE TOK_GT TOK_GE
%left  TOK_PLUS TOK_MINUS
%left  TOK_STAR TOK_SLASH TOK_DIV TOK_MOD
%right UMINUS

%start program

%%

/* ── Top-level ──────────────────────────────────────────────── */
program
    : TOK_PROGRAM TOK_IDENT TOK_SEMI block TOK_DOT
        {
            AstNode *n = ast_node(NK_PROGRAM, yylineno);
            n->u.program.name  = $2;
            n->u.program.block = $4;
            parse_root = n;
            $$ = n;
        }
    ;

block
    : var_decl_section proc_func_decls stmt_list
        {
            AstNode *n = ast_node(NK_BLOCK, yylineno);
            n->u.block.decls = $1;
            n->u.block.stmts = $3;
            $$ = n;
        }
    ;

/* ── Variable declarations ──────────────────────────────────── */
var_decl_section
    : TOK_VAR var_decl_list   { $$ = $2; }
    | /* empty */             { $$ = NULL; }
    ;

var_decl_list
    : var_decl_list var_decl  { $$ = seq_append($1, $2); }
    | var_decl                { $$ = $1; }
    ;

var_decl
    : TOK_IDENT TOK_COLON type_spec TOK_SEMI
        {
            AstNode *n = ast_node(NK_VAR_DECL, yylineno);
            n->u.var.name  = $1;
            n->u.var.vtype = $3;
            $$ = n;
        }
    ;

type_spec
    : TOK_INTEGER  { $$ = TY_INT;  }
    | TOK_BOOLEAN  { $$ = TY_BOOL; }
    ;

/* ── Procedure / Function declarations ──────────────────────── */
proc_func_decls
    : proc_func_decls proc_decl  { parse_root = NULL; }
    | proc_func_decls func_decl  { }
    | /* empty */
    ;

proc_decl
    : TOK_PROCEDURE TOK_IDENT param_section TOK_SEMI block TOK_SEMI
        {
            AstNode *n = ast_node(NK_PROC_DECL, yylineno);
            n->u.proc.name    = $2;
            n->u.proc.params  = $3;
            n->u.proc.rettype = TY_VOID;
            n->u.proc.body    = $5;
            $$ = n;
        }
    ;

func_decl
    : TOK_FUNCTION TOK_IDENT param_section TOK_COLON type_spec TOK_SEMI block TOK_SEMI
        {
            AstNode *n = ast_node(NK_FUNC_DECL, yylineno);
            n->u.proc.name    = $2;
            n->u.proc.params  = $3;
            n->u.proc.rettype = $5;
            n->u.proc.body    = $7;
            $$ = n;
        }
    ;

param_section
    : TOK_LPAREN param_list TOK_RPAREN  { $$ = $2; }
    | /* empty */                       { $$ = NULL; }
    ;

param_list
    : param_list TOK_SEMI param  { $$ = seq_append($1, $3); }
    | param                      { $$ = $1; }
    ;

param
    : TOK_IDENT TOK_COLON type_spec
        {
            AstNode *n = ast_node(NK_PARAM, yylineno);
            n->u.var.name  = $1;
            n->u.var.vtype = $3;
            $$ = n;
        }
    ;

/* ── Statement list ─────────────────────────────────────────── */
stmt_list
    : TOK_BEGIN inner_stmts TOK_END  { $$ = $2; }
    ;

inner_stmts
    : inner_stmts TOK_SEMI stmt  { $$ = seq_append($1, $3); }
    | stmt                       { $$ = $1; }
    ;

stmt
    : assign_stmt   { $$ = $1; }
    | if_stmt       { $$ = $1; }
    | while_stmt    { $$ = $1; }
    | for_stmt      { $$ = $1; }
    | write_stmt    { $$ = $1; }
    | call_stmt     { $$ = $1; }
    | stmt_list     { $$ = $1; }
    | /* empty */   { $$ = NULL; }
    ;

/* ── Sentenças (Statements) ─────────────────────────────────── */

if_stmt
    : TOK_IF expr TOK_THEN stmt %prec LOWER_THAN_ELSE
        {
            AstNode *n = ast_node(NK_IF, yylineno);
            n->u.ifstmt.cond = $2;
            n->u.ifstmt.then = $4;
            n->u.ifstmt.els  = NULL;
            $$ = n;
        }
    | TOK_IF expr TOK_THEN stmt TOK_ELSE stmt
        {
            AstNode *n = ast_node(NK_IF, yylineno);
            n->u.ifstmt.cond = $2;
            n->u.ifstmt.then = $4;
            n->u.ifstmt.els  = $6;
            $$ = n;
        }
    ;

while_stmt
    : TOK_WHILE expr TOK_DO stmt
        {
            AstNode *n = ast_node(NK_WHILE, yylineno);
            n->u.whilestmt.cond = $2;
            n->u.whilestmt.body = $4;
            $$ = n;
        }
    ;

for_stmt
    : TOK_FOR TOK_IDENT TOK_ASSIGN expr for_dir expr TOK_DO stmt
        {
            AstNode *n = ast_node(NK_FOR, yylineno);
            n->u.forstmt.var    = $2;
            n->u.forstmt.lo     = $4;
            n->u.forstmt.downto = $5;
            n->u.forstmt.hi     = $6;
            n->u.forstmt.body   = $8;
            $$ = n;
        }
    ;

for_dir
    : TOK_TO      { $$ = 1; }
    | TOK_DOWNTO  { $$ = 0; }
    ;

assign_stmt
    : TOK_IDENT TOK_ASSIGN expr
        {
            AstNode *n = ast_node(NK_ASSIGN, yylineno);
            n->u.assign.name = $1;
            n->u.assign.expr = $3;
            $$ = n;
        }
    ;

write_stmt
    : TOK_WRITE TOK_LPAREN arg_list TOK_RPAREN
        {
            AstNode *n = ast_node(NK_WRITE, yylineno);
            n->u.write.args = $3;
            n->u.write.newline = 0;
            $$ = n;
        }
    | TOK_WRITELN TOK_LPAREN arg_list TOK_RPAREN
        {
            AstNode *n = ast_node(NK_WRITE, yylineno);
            n->u.write.args = $3;
            n->u.write.newline = 1;
            $$ = n;
        }
    ;

call_stmt
    : TOK_IDENT TOK_LPAREN arg_list TOK_RPAREN
        {
            AstNode *n = ast_node(NK_CALL, yylineno);
            n->u.call.name = $1;
            n->u.call.args = $3;
            $$ = n;
        }
    ;

/* ── Expressions ────────────────────────────────────────────── */
expr_list
    : expr_list TOK_COMMA expr  { $$ = seq_append($1, $3); }
    | expr                      { $$ = $1; }
    ;

arg_list
    : expr_list  { $$ = $1; }
    ;

expr
    : expr TOK_OR expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_OR; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | expr TOK_AND expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_AND; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | TOK_NOT expr
        {
            AstNode *n = ast_node(NK_UNOP, yylineno);
            n->u.unop.op = OP_NOT; n->u.unop.operand = $2;
            $$ = n;
        }
    | expr TOK_EQ  expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_EQ; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | expr TOK_NEQ expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_NEQ; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | expr TOK_LT  expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_LT; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | expr TOK_LE  expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_LE; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | expr TOK_GT  expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_GT; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | expr TOK_GE  expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_GE; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | expr TOK_PLUS  expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_ADD; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | expr TOK_MINUS expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_SUB; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | expr TOK_STAR  expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_MUL; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | expr TOK_SLASH expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_DIV; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | expr TOK_DIV   expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_DIV; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | expr TOK_MOD   expr
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_MOD; n->u.binop.left = $1; n->u.binop.right = $3;
            $$ = n;
        }
    | TOK_MINUS expr %prec UMINUS
        {
            AstNode *n = ast_node(NK_UNOP, yylineno);
            n->u.unop.op = OP_NEG; n->u.unop.operand = $2;
            $$ = n;
        }
    | TOK_LPAREN expr TOK_RPAREN  { $$ = $2; }
    | TOK_INT_LIT
        {
            AstNode *n = ast_node(NK_INT_LIT, yylineno);
            n->u.iliteral.value = $1;
            $$ = n;
        }
    | TOK_TRUE
        {
            AstNode *n = ast_node(NK_BOOL_LIT, yylineno);
            n->u.bliteral.value = 1;
            $$ = n;
        }
    | TOK_FALSE
        {
            AstNode *n = ast_node(NK_BOOL_LIT, yylineno);
            n->u.bliteral.value = 0;
            $$ = n;
        }
    | TOK_STR_LIT
        {
            AstNode *n = ast_node(NK_IDENT, yylineno);
            n->u.ident.name = $1;
            n->type = TY_VOID;
            $$ = n;
        }
    | TOK_IDENT TOK_LPAREN arg_list TOK_RPAREN
        {
            AstNode *n = ast_node(NK_CALL, yylineno);
            n->u.call.name = $1;
            n->u.call.args = $3;
            $$ = n;
        }
    | TOK_IDENT TOK_LPAREN TOK_RPAREN
        {
            AstNode *n = ast_node(NK_CALL, yylineno);
            n->u.call.name = $1;
            n->u.call.args = NULL;
            $$ = n;
        }
    | TOK_PARAMCOUNT
        {
            AstNode *n = ast_node(NK_IDENT, yylineno);
            n->u.ident.name = strdup("__paramcount");
            $$ = n;
        }
    | TOK_PARAMSTR TOK_LPAREN expr TOK_RPAREN
        {
            AstNode *n = ast_node(NK_CALL, yylineno);
            n->u.call.name = strdup("__paramstr");
            n->u.call.args = $3;
            $$ = n;
        }
    | TOK_IDENT
        {
            AstNode *n = ast_node(NK_IDENT, yylineno);
            n->u.ident.name = $1;
            $$ = n;
        }
    ;

%%

void yyerror(const char *msg) {
    fprintf(stderr, "parse error at line %d: %s\n", yylineno, msg);
}
