/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_PROGRAM = 258,             /* TOK_PROGRAM  */
    TOK_BEGIN = 259,               /* TOK_BEGIN  */
    TOK_END = 260,                 /* TOK_END  */
    TOK_VAR = 261,                 /* TOK_VAR  */
    TOK_INTEGER = 262,             /* TOK_INTEGER  */
    TOK_BOOLEAN = 263,             /* TOK_BOOLEAN  */
    TOK_OF = 264,                  /* TOK_OF  */
    TOK_IF = 265,                  /* TOK_IF  */
    TOK_THEN = 266,                /* TOK_THEN  */
    TOK_ELSE = 267,                /* TOK_ELSE  */
    TOK_WHILE = 268,               /* TOK_WHILE  */
    TOK_DO = 269,                  /* TOK_DO  */
    TOK_FOR = 270,                 /* TOK_FOR  */
    TOK_TO = 271,                  /* TOK_TO  */
    TOK_DOWNTO = 272,              /* TOK_DOWNTO  */
    TOK_PROCEDURE = 273,           /* TOK_PROCEDURE  */
    TOK_FUNCTION = 274,            /* TOK_FUNCTION  */
    TOK_WRITE = 275,               /* TOK_WRITE  */
    TOK_WRITELN = 276,             /* TOK_WRITELN  */
    TOK_AND = 277,                 /* TOK_AND  */
    TOK_OR = 278,                  /* TOK_OR  */
    TOK_NOT = 279,                 /* TOK_NOT  */
    TOK_DIV = 280,                 /* TOK_DIV  */
    TOK_MOD = 281,                 /* TOK_MOD  */
    TOK_PARAMCOUNT = 282,          /* TOK_PARAMCOUNT  */
    TOK_PARAMSTR = 283,            /* TOK_PARAMSTR  */
    TOK_ASSIGN = 284,              /* TOK_ASSIGN  */
    TOK_SEMI = 285,                /* TOK_SEMI  */
    TOK_COLON = 286,               /* TOK_COLON  */
    TOK_COMMA = 287,               /* TOK_COMMA  */
    TOK_DOT = 288,                 /* TOK_DOT  */
    TOK_LPAREN = 289,              /* TOK_LPAREN  */
    TOK_RPAREN = 290,              /* TOK_RPAREN  */
    TOK_EQ = 291,                  /* TOK_EQ  */
    TOK_NEQ = 292,                 /* TOK_NEQ  */
    TOK_LT = 293,                  /* TOK_LT  */
    TOK_LE = 294,                  /* TOK_LE  */
    TOK_GT = 295,                  /* TOK_GT  */
    TOK_GE = 296,                  /* TOK_GE  */
    TOK_PLUS = 297,                /* TOK_PLUS  */
    TOK_MINUS = 298,               /* TOK_MINUS  */
    TOK_STAR = 299,                /* TOK_STAR  */
    TOK_SLASH = 300,               /* TOK_SLASH  */
    TOK_INT_LIT = 301,             /* TOK_INT_LIT  */
    TOK_TRUE = 302,                /* TOK_TRUE  */
    TOK_FALSE = 303,               /* TOK_FALSE  */
    TOK_IDENT = 304,               /* TOK_IDENT  */
    TOK_STR_LIT = 305,             /* TOK_STR_LIT  */
    UMINUS = 306                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 25 "parser.y"

    int     ival;
    char    *sval;
    AstNode *node;
    PascalType tyval;

#line 122 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
