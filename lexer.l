%{
#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "parser.tab.h"   /* Bison-generated token definitions */

int yyline = 1;
%}

/* CORREÇÃO: Removidos 'nounput' e 'noinput' e forçada a geração deles */
%option noyywrap
%option input unput
%option yylineno

/* ── Primitives ─────────────────────────────────────────────── */
DIGIT       [0-9]
ALPHA       [a-zA-Z_]
ALNUM       [a-zA-Z0-9_]
INT_LIT     {DIGIT}+
IDENT       {ALPHA}{ALNUM}*

/* ── Comment patterns ───────────────────────────────────────── */
%x COMMENT_BRACE
%x COMMENT_PAREN

%%

 /* ── Whitespace ─────────────────────────────────────────────── */
[ \t\r]+            { /* skip */ }
\n                  { /* yylineno handles count */ }

 /* ── Block comments { ... } ─────────────────────────────────── */
"{"                 { BEGIN(COMMENT_BRACE); }
<COMMENT_BRACE>"}"  { BEGIN(INITIAL); }
<COMMENT_BRACE>\n   { /* consume */ }
<COMMENT_BRACE>.    { /* consume */ }

 /* ── Block comments (* ... *) ───────────────────────────────── */
"(*"                { BEGIN(COMMENT_PAREN); }
<COMMENT_PAREN>"*)" { BEGIN(INITIAL); }
<COMMENT_PAREN>\n   { /* consume */ }
<COMMENT_PAREN>.    { /* consume */ }

 /* ── Keywords (case-insensitive via (?i:...) modifier) ─────── */
(?i:"program")      { return TOK_PROGRAM; }
(?i:"begin")        { return TOK_BEGIN; }
(?i:"end")          { return TOK_END; }
(?i:"var")          { return TOK_VAR; }
(?i:"integer")      { return TOK_INTEGER; }
(?i:"boolean")      { return TOK_BOOLEAN; }
(?i:"of")           { return TOK_OF; }
(?i:"if")           { return TOK_IF; }
(?i:"then")         { return TOK_THEN; }
(?i:"else")         { return TOK_ELSE; }
(?i:"while")        { return TOK_WHILE; }
(?i:"do")           { return TOK_DO; }
(?i:"for")          { return TOK_FOR; }
(?i:"to")           { return TOK_TO; }
(?i:"downto")       { return TOK_DOWNTO; }
(?i:"procedure")    { return TOK_PROCEDURE; }
(?i:"function")     { return TOK_FUNCTION; }
(?i:"write")        { return TOK_WRITE; }
(?i:"writeln")      { return TOK_WRITELN; }
(?i:"and")          { return TOK_AND; }
(?i:"or")           { return TOK_OR; }
(?i:"not")          { return TOK_NOT; }
(?i:"div")          { return TOK_DIV; }
(?i:"mod")          { return TOK_MOD; }
(?i:"true")         { return TOK_TRUE; }
(?i:"false")        { return TOK_FALSE; }
(?i:"paramcount")   { return TOK_PARAMCOUNT; }
(?i:"paramstr")     { return TOK_PARAMSTR; }

 /* ── String literal ──────────────────────────────────────────── */
"'"                 {
                      char s[1024];
                      int si = 0;
                      /* CORREÇÃO: Removida a variável 'i' não utilizada para sanar o warning */
                      
                      /* read until closing quote, handling escaped single quotes */
                      while (1) {
                          char c = input();
                          if (c == '\0' || c == EOF) {
                              fprintf(stderr, "lexer: unclosed string literal\n");
                              exit(1);
                          }
                          if (c == '\'') {
                              char next = input();
                              if (next == '\'') {
                                  s[si++] = '\'';
                              } else {
                                  if (next != '\0' && next != EOF) {
                                      unput(next);
                                  }
                                  break;
                              }
                          } else if (c == '\n') {
                              s[si++] = '\n';
                          } else {
                              s[si++] = c;
                          }
                      }
                      s[si] = '\0';
                      yylval.sval = strdup(s);
                      return TOK_STR_LIT;
                    }

 /* ── Integer literal ─────────────────────────────────────────── */
{INT_LIT}           { yylval.ival = atol(yytext); return TOK_INT_LIT; }

 /* ── Identifier ─────────────────────────────────────────────── */
{IDENT}             { yylval.sval = strdup(yytext); return TOK_IDENT; }

 /* ── Operators & punctuation ─────────────────────────────────── */
":="                { return TOK_ASSIGN; }
"<>"                { return TOK_NEQ;    }
"<="                { return TOK_LE;     }
">="                { return TOK_GE;     }
"<"                 { return TOK_LT;     }
">"                 { return TOK_GT;     }
"="                 { return TOK_EQ;     }
"+"                 { return TOK_PLUS;   }
"-"                 { return TOK_MINUS;  }
"*"                 { return TOK_STAR;   }
"/"                 { return TOK_SLASH;  }
"("                 { return TOK_LPAREN; }
")"                 { return TOK_RPAREN; }
";"                 { return TOK_SEMI;   }
":"                 { return TOK_COLON;  }
","                 { return TOK_COMMA;  }
"."                 { return TOK_DOT;    }

 /* ── Catch-all ───────────────────────────────────────────────── */
.                   {
                      fprintf(stderr, "lexer: unknown char '%s' at line %d\n",
                              yytext, yylineno);
                      exit(1);
                    }

%%