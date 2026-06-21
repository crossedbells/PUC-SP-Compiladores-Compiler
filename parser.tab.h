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
    LOWER_THAN_ELSE = 258,         /* LOWER_THAN_ELSE  */
    TOK_PROGRAM = 259,             /* TOK_PROGRAM  */
    TOK_BEGIN = 260,               /* TOK_BEGIN  */
    TOK_END = 261,                 /* TOK_END  */
    TOK_VAR = 262,                 /* TOK_VAR  */
    TOK_INTEGER = 263,             /* TOK_INTEGER  */
    TOK_BOOLEAN = 264,             /* TOK_BOOLEAN  */
    TOK_OF = 265,                  /* TOK_OF  */
    TOK_IF = 266,                  /* TOK_IF  */
    TOK_THEN = 267,                /* TOK_THEN  */
    TOK_ELSE = 268,                /* TOK_ELSE  */
    TOK_WHILE = 269,               /* TOK_WHILE  */
    TOK_DO = 270,                  /* TOK_DO  */
    TOK_FOR = 271,                 /* TOK_FOR  */
    TOK_TO = 272,                  /* TOK_TO  */
    TOK_DOWNTO = 273,              /* TOK_DOWNTO  */
    TOK_PROCEDURE = 274,           /* TOK_PROCEDURE  */
    TOK_FUNCTION = 275,            /* TOK_FUNCTION  */
    TOK_WRITE = 276,               /* TOK_WRITE  */
    TOK_WRITELN = 277,             /* TOK_WRITELN  */
    TOK_AND = 278,                 /* TOK_AND  */
    TOK_OR = 279,                  /* TOK_OR  */
    TOK_NOT = 280,                 /* TOK_NOT  */
    TOK_DIV = 281,                 /* TOK_DIV  */
    TOK_MOD = 282,                 /* TOK_MOD  */
    TOK_PARAMCOUNT = 283,          /* TOK_PARAMCOUNT  */
    TOK_PARAMSTR = 284,            /* TOK_PARAMSTR  */
    TOK_ASSIGN = 285,              /* TOK_ASSIGN  */
    TOK_SEMI = 286,                /* TOK_SEMI  */
    TOK_COLON = 287,               /* TOK_COLON  */
    TOK_COMMA = 288,               /* TOK_COMMA  */
    TOK_DOT = 289,                 /* TOK_DOT  */
    TOK_LPAREN = 290,              /* TOK_LPAREN  */
    TOK_RPAREN = 291,              /* TOK_RPAREN  */
    TOK_EQ = 292,                  /* TOK_EQ  */
    TOK_NEQ = 293,                 /* TOK_NEQ  */
    TOK_LT = 294,                  /* TOK_LT  */
    TOK_LE = 295,                  /* TOK_LE  */
    TOK_GT = 296,                  /* TOK_GT  */
    TOK_GE = 297,                  /* TOK_GE  */
    TOK_PLUS = 298,                /* TOK_PLUS  */
    TOK_MINUS = 299,               /* TOK_MINUS  */
    TOK_STAR = 300,                /* TOK_STAR  */
    TOK_SLASH = 301,               /* TOK_SLASH  */
    TOK_INT_LIT = 302,             /* TOK_INT_LIT  */
    TOK_TRUE = 303,                /* TOK_TRUE  */
    TOK_FALSE = 304,               /* TOK_FALSE  */
    TOK_IDENT = 305,               /* TOK_IDENT  */
    TOK_STR_LIT = 306,             /* TOK_STR_LIT  */
    UMINUS = 307                   /* UMINUS  */
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

#line 123 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
