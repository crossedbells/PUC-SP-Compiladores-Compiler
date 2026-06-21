/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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

#line 94 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LOWER_THAN_ELSE = 3,            /* LOWER_THAN_ELSE  */
  YYSYMBOL_TOK_PROGRAM = 4,                /* TOK_PROGRAM  */
  YYSYMBOL_TOK_BEGIN = 5,                  /* TOK_BEGIN  */
  YYSYMBOL_TOK_END = 6,                    /* TOK_END  */
  YYSYMBOL_TOK_VAR = 7,                    /* TOK_VAR  */
  YYSYMBOL_TOK_INTEGER = 8,                /* TOK_INTEGER  */
  YYSYMBOL_TOK_BOOLEAN = 9,                /* TOK_BOOLEAN  */
  YYSYMBOL_TOK_OF = 10,                    /* TOK_OF  */
  YYSYMBOL_TOK_IF = 11,                    /* TOK_IF  */
  YYSYMBOL_TOK_THEN = 12,                  /* TOK_THEN  */
  YYSYMBOL_TOK_ELSE = 13,                  /* TOK_ELSE  */
  YYSYMBOL_TOK_WHILE = 14,                 /* TOK_WHILE  */
  YYSYMBOL_TOK_DO = 15,                    /* TOK_DO  */
  YYSYMBOL_TOK_FOR = 16,                   /* TOK_FOR  */
  YYSYMBOL_TOK_TO = 17,                    /* TOK_TO  */
  YYSYMBOL_TOK_DOWNTO = 18,                /* TOK_DOWNTO  */
  YYSYMBOL_TOK_PROCEDURE = 19,             /* TOK_PROCEDURE  */
  YYSYMBOL_TOK_FUNCTION = 20,              /* TOK_FUNCTION  */
  YYSYMBOL_TOK_WRITE = 21,                 /* TOK_WRITE  */
  YYSYMBOL_TOK_WRITELN = 22,               /* TOK_WRITELN  */
  YYSYMBOL_TOK_AND = 23,                   /* TOK_AND  */
  YYSYMBOL_TOK_OR = 24,                    /* TOK_OR  */
  YYSYMBOL_TOK_NOT = 25,                   /* TOK_NOT  */
  YYSYMBOL_TOK_DIV = 26,                   /* TOK_DIV  */
  YYSYMBOL_TOK_MOD = 27,                   /* TOK_MOD  */
  YYSYMBOL_TOK_PARAMCOUNT = 28,            /* TOK_PARAMCOUNT  */
  YYSYMBOL_TOK_PARAMSTR = 29,              /* TOK_PARAMSTR  */
  YYSYMBOL_TOK_ASSIGN = 30,                /* TOK_ASSIGN  */
  YYSYMBOL_TOK_SEMI = 31,                  /* TOK_SEMI  */
  YYSYMBOL_TOK_COLON = 32,                 /* TOK_COLON  */
  YYSYMBOL_TOK_COMMA = 33,                 /* TOK_COMMA  */
  YYSYMBOL_TOK_DOT = 34,                   /* TOK_DOT  */
  YYSYMBOL_TOK_LPAREN = 35,                /* TOK_LPAREN  */
  YYSYMBOL_TOK_RPAREN = 36,                /* TOK_RPAREN  */
  YYSYMBOL_TOK_EQ = 37,                    /* TOK_EQ  */
  YYSYMBOL_TOK_NEQ = 38,                   /* TOK_NEQ  */
  YYSYMBOL_TOK_LT = 39,                    /* TOK_LT  */
  YYSYMBOL_TOK_LE = 40,                    /* TOK_LE  */
  YYSYMBOL_TOK_GT = 41,                    /* TOK_GT  */
  YYSYMBOL_TOK_GE = 42,                    /* TOK_GE  */
  YYSYMBOL_TOK_PLUS = 43,                  /* TOK_PLUS  */
  YYSYMBOL_TOK_MINUS = 44,                 /* TOK_MINUS  */
  YYSYMBOL_TOK_STAR = 45,                  /* TOK_STAR  */
  YYSYMBOL_TOK_SLASH = 46,                 /* TOK_SLASH  */
  YYSYMBOL_TOK_INT_LIT = 47,               /* TOK_INT_LIT  */
  YYSYMBOL_TOK_TRUE = 48,                  /* TOK_TRUE  */
  YYSYMBOL_TOK_FALSE = 49,                 /* TOK_FALSE  */
  YYSYMBOL_TOK_IDENT = 50,                 /* TOK_IDENT  */
  YYSYMBOL_TOK_STR_LIT = 51,               /* TOK_STR_LIT  */
  YYSYMBOL_UMINUS = 52,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_block = 55,                     /* block  */
  YYSYMBOL_var_decl_section = 56,          /* var_decl_section  */
  YYSYMBOL_var_decl_list = 57,             /* var_decl_list  */
  YYSYMBOL_var_decl = 58,                  /* var_decl  */
  YYSYMBOL_type_spec = 59,                 /* type_spec  */
  YYSYMBOL_proc_func_decls = 60,           /* proc_func_decls  */
  YYSYMBOL_proc_decl = 61,                 /* proc_decl  */
  YYSYMBOL_func_decl = 62,                 /* func_decl  */
  YYSYMBOL_param_section = 63,             /* param_section  */
  YYSYMBOL_param_list = 64,                /* param_list  */
  YYSYMBOL_param = 65,                     /* param  */
  YYSYMBOL_stmt_list = 66,                 /* stmt_list  */
  YYSYMBOL_inner_stmts = 67,               /* inner_stmts  */
  YYSYMBOL_stmt = 68,                      /* stmt  */
  YYSYMBOL_if_stmt = 69,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 70,                /* while_stmt  */
  YYSYMBOL_for_stmt = 71,                  /* for_stmt  */
  YYSYMBOL_for_dir = 72,                   /* for_dir  */
  YYSYMBOL_assign_stmt = 73,               /* assign_stmt  */
  YYSYMBOL_write_stmt = 74,                /* write_stmt  */
  YYSYMBOL_call_stmt = 75,                 /* call_stmt  */
  YYSYMBOL_expr_list = 76,                 /* expr_list  */
  YYSYMBOL_arg_list = 77,                  /* arg_list  */
  YYSYMBOL_expr = 78                       /* expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   368

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    80,    80,    91,   102,   103,   107,   108,   112,   122,
     123,   128,   129,   130,   134,   146,   158,   159,   163,   164,
     168,   179,   183,   184,   188,   189,   190,   191,   192,   193,
     194,   195,   201,   209,   220,   230,   243,   244,   248,   258,
     265,   275,   286,   287,   291,   295,   301,   307,   313,   319,
     325,   331,   337,   343,   349,   355,   361,   367,   373,   379,
     385,   391,   392,   398,   404,   410,   417,   424,   431,   437,
     444
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LOWER_THAN_ELSE",
  "TOK_PROGRAM", "TOK_BEGIN", "TOK_END", "TOK_VAR", "TOK_INTEGER",
  "TOK_BOOLEAN", "TOK_OF", "TOK_IF", "TOK_THEN", "TOK_ELSE", "TOK_WHILE",
  "TOK_DO", "TOK_FOR", "TOK_TO", "TOK_DOWNTO", "TOK_PROCEDURE",
  "TOK_FUNCTION", "TOK_WRITE", "TOK_WRITELN", "TOK_AND", "TOK_OR",
  "TOK_NOT", "TOK_DIV", "TOK_MOD", "TOK_PARAMCOUNT", "TOK_PARAMSTR",
  "TOK_ASSIGN", "TOK_SEMI", "TOK_COLON", "TOK_COMMA", "TOK_DOT",
  "TOK_LPAREN", "TOK_RPAREN", "TOK_EQ", "TOK_NEQ", "TOK_LT", "TOK_LE",
  "TOK_GT", "TOK_GE", "TOK_PLUS", "TOK_MINUS", "TOK_STAR", "TOK_SLASH",
  "TOK_INT_LIT", "TOK_TRUE", "TOK_FALSE", "TOK_IDENT", "TOK_STR_LIT",
  "UMINUS", "$accept", "program", "block", "var_decl_section",
  "var_decl_list", "var_decl", "type_spec", "proc_func_decls", "proc_decl",
  "func_decl", "param_section", "param_list", "param", "stmt_list",
  "inner_stmts", "stmt", "if_stmt", "while_stmt", "for_stmt", "for_dir",
  "assign_stmt", "write_stmt", "call_stmt", "expr_list", "arg_list",
  "expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-95)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       2,   -37,    17,    -4,   -95,    25,   -16,     3,   -95,     6,
     -16,   -95,   -95,    55,     7,   -95,    14,   -11,   -10,   -95,
     -95,   -95,   -95,   -95,    13,   192,   192,    12,    28,    30,
     -23,   -95,    -2,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
      31,    31,   -95,   192,   -95,    32,   192,   192,   -95,   -95,
     -95,    33,   -95,    59,    91,    39,   192,   192,   192,   192,
     -95,    14,    20,    42,    44,   301,   192,   208,   -95,   175,
      14,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,    14,   192,    45,    41,   256,
      43,   256,    51,   -95,    48,   -22,   -95,    25,     7,   232,
     -95,   -95,    52,    68,   301,   280,   -95,   -95,   322,   322,
     322,   322,   322,   322,    -3,    -3,   -95,   -95,   -95,   153,
     192,   -95,   -95,   -95,     7,    20,   -95,    58,    60,   -95,
     -95,    14,   -95,   -95,   192,   256,   -95,   -95,   -95,    25,
     -95,   123,    61,    14,   -95,   -95
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     5,     0,     0,    13,     0,
       4,     7,     2,     0,     0,     6,    31,     0,     0,    11,
      12,     3,     9,    10,     0,     0,     0,     0,     0,     0,
       0,    30,     0,    23,    25,    26,    27,    24,    28,    29,
      17,    17,     8,     0,    68,     0,     0,     0,    62,    63,
      64,    70,    65,     0,     0,     0,     0,     0,     0,     0,
      21,    31,     0,     0,     0,    47,     0,     0,    60,     0,
      31,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     0,    44,     0,    43,
       0,    38,     0,    22,     0,     0,    19,     5,     0,     0,
      61,    67,     0,    32,    46,    45,    58,    59,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    34,     0,
       0,    39,    40,    41,     0,     0,    16,     0,     0,    69,
      66,    31,    36,    37,     0,    42,    20,    18,    14,     5,
      33,     0,     0,    31,    15,    35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -95,   -95,   -94,   -95,   -95,    80,   -93,   -95,   -95,   -95,
      53,   -95,   -32,    94,   -95,   -59,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -49,   -25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     7,     8,    10,    11,    24,    13,    19,    20,
      63,    95,    96,    31,    32,    33,    34,    35,    36,   134,
      37,    38,    39,    87,    88,    89
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,    54,    93,   127,    60,   128,     1,    58,    90,   125,
      92,   103,    59,     3,   126,    22,    23,     4,    65,    16,
     102,    67,    68,    73,    74,    25,   118,     5,    26,    61,
      27,   136,     6,    91,     9,    28,    29,    12,    14,    40,
      41,    99,    83,    84,    42,   142,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
      16,   119,    55,    56,    30,    57,    62,    66,    69,    86,
      94,    70,   140,    97,    17,    18,    98,   121,   120,   122,
     124,   131,    71,    72,   145,    73,    74,   123,   130,   138,
      15,   139,   144,   137,    64,   135,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    21,     0,   141,
       0,     0,     0,     0,    71,    72,     0,    73,    74,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,   143,     0,
       0,     0,     0,     0,     0,     0,    71,    72,     0,    73,
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
     132,   133,     0,     0,     0,     0,    71,    72,     0,    73,
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      43,     0,     0,    44,    45,     0,     0,     0,     0,     0,
      46,   101,     0,     0,     0,     0,     0,    43,     0,    47,
      44,    45,    48,    49,    50,    51,    52,    46,     0,     0,
       0,    71,    72,     0,    73,    74,    47,     0,     0,    48,
      49,    50,    51,    52,   100,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    71,    72,     0,    73,    74,
       0,     0,     0,     0,     0,     0,     0,     0,   129,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    71,
      72,     0,    73,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    71,     0,     0,    73,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    73,    74,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    73,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84
};

static const yytype_int16 yycheck[] =
{
      25,    26,    61,    97,     6,    98,     4,    30,    57,    31,
      59,    70,    35,    50,    36,     8,     9,     0,    43,     5,
      69,    46,    47,    26,    27,    11,    85,    31,    14,    31,
      16,   124,     7,    58,    50,    21,    22,    34,    32,    50,
      50,    66,    45,    46,    31,   139,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
       5,    86,    50,    35,    50,    35,    35,    35,    35,    30,
      50,    12,   131,    31,    19,    20,    32,    36,    33,    36,
      32,    13,    23,    24,   143,    26,    27,    36,    36,    31,
      10,    31,    31,   125,    41,   120,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    15,    13,    -1,   134,
      -1,    -1,    -1,    -1,    23,    24,    -1,    26,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    26,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      17,    18,    -1,    -1,    -1,    -1,    23,    24,    -1,    26,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      25,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      35,    36,    -1,    -1,    -1,    -1,    -1,    25,    -1,    44,
      28,    29,    47,    48,    49,    50,    51,    35,    -1,    -1,
      -1,    23,    24,    -1,    26,    27,    44,    -1,    -1,    47,
      48,    49,    50,    51,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    23,    24,    -1,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    23,
      24,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    23,    -1,    -1,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    26,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,    54,    50,     0,    31,     7,    55,    56,    50,
      57,    58,    34,    60,    32,    58,     5,    19,    20,    61,
      62,    66,     8,     9,    59,    11,    14,    16,    21,    22,
      50,    66,    67,    68,    69,    70,    71,    73,    74,    75,
      50,    50,    31,    25,    28,    29,    35,    44,    47,    48,
      49,    50,    51,    78,    78,    50,    35,    35,    30,    35,
       6,    31,    35,    63,    63,    78,    35,    78,    78,    35,
      12,    23,    24,    26,    27,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    15,    30,    76,    77,    78,
      77,    78,    77,    68,    50,    64,    65,    31,    32,    78,
      36,    36,    77,    68,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    68,    78,
      33,    36,    36,    36,    32,    31,    36,    55,    59,    36,
      36,    13,    17,    18,    72,    78,    59,    65,    31,    31,
      68,    78,    55,    15,    31,    68
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    56,    56,    57,    57,    58,    59,
      59,    60,    60,    60,    61,    62,    63,    63,    64,    64,
      65,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    69,    70,    71,    72,    72,    73,    74,
      74,    75,    76,    76,    77,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     3,     2,     0,     2,     1,     4,     1,
       1,     2,     2,     0,     6,     8,     3,     0,     3,     1,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     6,     4,     8,     1,     1,     3,     4,
       4,     4,     3,     1,     1,     3,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     3,     1,     1,     1,     1,     4,     3,     1,     4,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: TOK_PROGRAM TOK_IDENT TOK_SEMI block TOK_DOT  */
#line 81 "parser.y"
        {
            AstNode *n = ast_node(NK_PROGRAM, yylineno);
            n->u.program.name  = (yyvsp[-3].sval);
            n->u.program.block = (yyvsp[-1].node);
            parse_root = n;
            (yyval.node) = n;
        }
#line 1309 "parser.tab.c"
    break;

  case 3: /* block: var_decl_section proc_func_decls stmt_list  */
#line 92 "parser.y"
        {
            AstNode *n = ast_node(NK_BLOCK, yylineno);
            n->u.block.decls = (yyvsp[-2].node);
            n->u.block.stmts = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1320 "parser.tab.c"
    break;

  case 4: /* var_decl_section: TOK_VAR var_decl_list  */
#line 102 "parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1326 "parser.tab.c"
    break;

  case 5: /* var_decl_section: %empty  */
#line 103 "parser.y"
                              { (yyval.node) = NULL; }
#line 1332 "parser.tab.c"
    break;

  case 6: /* var_decl_list: var_decl_list var_decl  */
#line 107 "parser.y"
                              { (yyval.node) = seq_append((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1338 "parser.tab.c"
    break;

  case 7: /* var_decl_list: var_decl  */
#line 108 "parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1344 "parser.tab.c"
    break;

  case 8: /* var_decl: TOK_IDENT TOK_COLON type_spec TOK_SEMI  */
#line 113 "parser.y"
        {
            AstNode *n = ast_node(NK_VAR_DECL, yylineno);
            n->u.var.name  = (yyvsp[-3].sval);
            n->u.var.vtype = (yyvsp[-1].tyval);
            (yyval.node) = n;
        }
#line 1355 "parser.tab.c"
    break;

  case 9: /* type_spec: TOK_INTEGER  */
#line 122 "parser.y"
                   { (yyval.tyval) = TY_INT;  }
#line 1361 "parser.tab.c"
    break;

  case 10: /* type_spec: TOK_BOOLEAN  */
#line 123 "parser.y"
                   { (yyval.tyval) = TY_BOOL; }
#line 1367 "parser.tab.c"
    break;

  case 11: /* proc_func_decls: proc_func_decls proc_decl  */
#line 128 "parser.y"
                                 { parse_root = NULL; }
#line 1373 "parser.tab.c"
    break;

  case 12: /* proc_func_decls: proc_func_decls func_decl  */
#line 129 "parser.y"
                                 { }
#line 1379 "parser.tab.c"
    break;

  case 14: /* proc_decl: TOK_PROCEDURE TOK_IDENT param_section TOK_SEMI block TOK_SEMI  */
#line 135 "parser.y"
        {
            AstNode *n = ast_node(NK_PROC_DECL, yylineno);
            n->u.proc.name    = (yyvsp[-4].sval);
            n->u.proc.params  = (yyvsp[-3].node);
            n->u.proc.rettype = TY_VOID;
            n->u.proc.body    = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1392 "parser.tab.c"
    break;

  case 15: /* func_decl: TOK_FUNCTION TOK_IDENT param_section TOK_COLON type_spec TOK_SEMI block TOK_SEMI  */
#line 147 "parser.y"
        {
            AstNode *n = ast_node(NK_FUNC_DECL, yylineno);
            n->u.proc.name    = (yyvsp[-6].sval);
            n->u.proc.params  = (yyvsp[-5].node);
            n->u.proc.rettype = (yyvsp[-3].tyval);
            n->u.proc.body    = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1405 "parser.tab.c"
    break;

  case 16: /* param_section: TOK_LPAREN param_list TOK_RPAREN  */
#line 158 "parser.y"
                                        { (yyval.node) = (yyvsp[-1].node); }
#line 1411 "parser.tab.c"
    break;

  case 17: /* param_section: %empty  */
#line 159 "parser.y"
                                        { (yyval.node) = NULL; }
#line 1417 "parser.tab.c"
    break;

  case 18: /* param_list: param_list TOK_SEMI param  */
#line 163 "parser.y"
                                 { (yyval.node) = seq_append((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1423 "parser.tab.c"
    break;

  case 19: /* param_list: param  */
#line 164 "parser.y"
                                 { (yyval.node) = (yyvsp[0].node); }
#line 1429 "parser.tab.c"
    break;

  case 20: /* param: TOK_IDENT TOK_COLON type_spec  */
#line 169 "parser.y"
        {
            AstNode *n = ast_node(NK_PARAM, yylineno);
            n->u.var.name  = (yyvsp[-2].sval);
            n->u.var.vtype = (yyvsp[0].tyval);
            (yyval.node) = n;
        }
#line 1440 "parser.tab.c"
    break;

  case 21: /* stmt_list: TOK_BEGIN inner_stmts TOK_END  */
#line 179 "parser.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 1446 "parser.tab.c"
    break;

  case 22: /* inner_stmts: inner_stmts TOK_SEMI stmt  */
#line 183 "parser.y"
                                 { (yyval.node) = seq_append((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1452 "parser.tab.c"
    break;

  case 23: /* inner_stmts: stmt  */
#line 184 "parser.y"
                                 { (yyval.node) = (yyvsp[0].node); }
#line 1458 "parser.tab.c"
    break;

  case 24: /* stmt: assign_stmt  */
#line 188 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1464 "parser.tab.c"
    break;

  case 25: /* stmt: if_stmt  */
#line 189 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1470 "parser.tab.c"
    break;

  case 26: /* stmt: while_stmt  */
#line 190 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1476 "parser.tab.c"
    break;

  case 27: /* stmt: for_stmt  */
#line 191 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1482 "parser.tab.c"
    break;

  case 28: /* stmt: write_stmt  */
#line 192 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1488 "parser.tab.c"
    break;

  case 29: /* stmt: call_stmt  */
#line 193 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1494 "parser.tab.c"
    break;

  case 30: /* stmt: stmt_list  */
#line 194 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1500 "parser.tab.c"
    break;

  case 31: /* stmt: %empty  */
#line 195 "parser.y"
                    { (yyval.node) = NULL; }
#line 1506 "parser.tab.c"
    break;

  case 32: /* if_stmt: TOK_IF expr TOK_THEN stmt  */
#line 202 "parser.y"
        {
            AstNode *n = ast_node(NK_IF, yylineno);
            n->u.ifstmt.cond = (yyvsp[-2].node);
            n->u.ifstmt.then = (yyvsp[0].node);
            n->u.ifstmt.els  = NULL;
            (yyval.node) = n;
        }
#line 1518 "parser.tab.c"
    break;

  case 33: /* if_stmt: TOK_IF expr TOK_THEN stmt TOK_ELSE stmt  */
#line 210 "parser.y"
        {
            AstNode *n = ast_node(NK_IF, yylineno);
            n->u.ifstmt.cond = (yyvsp[-4].node);
            n->u.ifstmt.then = (yyvsp[-2].node);
            n->u.ifstmt.els  = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1530 "parser.tab.c"
    break;

  case 34: /* while_stmt: TOK_WHILE expr TOK_DO stmt  */
#line 221 "parser.y"
        {
            AstNode *n = ast_node(NK_WHILE, yylineno);
            n->u.whilestmt.cond = (yyvsp[-2].node);
            n->u.whilestmt.body = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1541 "parser.tab.c"
    break;

  case 35: /* for_stmt: TOK_FOR TOK_IDENT TOK_ASSIGN expr for_dir expr TOK_DO stmt  */
#line 231 "parser.y"
        {
            AstNode *n = ast_node(NK_FOR, yylineno);
            n->u.forstmt.var    = (yyvsp[-6].sval);
            n->u.forstmt.lo     = (yyvsp[-4].node);
            n->u.forstmt.downto = (yyvsp[-3].ival);
            n->u.forstmt.hi     = (yyvsp[-2].node);
            n->u.forstmt.body   = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1555 "parser.tab.c"
    break;

  case 36: /* for_dir: TOK_TO  */
#line 243 "parser.y"
                  { (yyval.ival) = 1; }
#line 1561 "parser.tab.c"
    break;

  case 37: /* for_dir: TOK_DOWNTO  */
#line 244 "parser.y"
                  { (yyval.ival) = 0; }
#line 1567 "parser.tab.c"
    break;

  case 38: /* assign_stmt: TOK_IDENT TOK_ASSIGN expr  */
#line 249 "parser.y"
        {
            AstNode *n = ast_node(NK_ASSIGN, yylineno);
            n->u.assign.name = (yyvsp[-2].sval);
            n->u.assign.expr = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1578 "parser.tab.c"
    break;

  case 39: /* write_stmt: TOK_WRITE TOK_LPAREN arg_list TOK_RPAREN  */
#line 259 "parser.y"
        {
            AstNode *n = ast_node(NK_WRITE, yylineno);
            n->u.write.args = (yyvsp[-1].node);
            n->u.write.newline = 0;
            (yyval.node) = n;
        }
#line 1589 "parser.tab.c"
    break;

  case 40: /* write_stmt: TOK_WRITELN TOK_LPAREN arg_list TOK_RPAREN  */
#line 266 "parser.y"
        {
            AstNode *n = ast_node(NK_WRITE, yylineno);
            n->u.write.args = (yyvsp[-1].node);
            n->u.write.newline = 1;
            (yyval.node) = n;
        }
#line 1600 "parser.tab.c"
    break;

  case 41: /* call_stmt: TOK_IDENT TOK_LPAREN arg_list TOK_RPAREN  */
#line 276 "parser.y"
        {
            AstNode *n = ast_node(NK_CALL, yylineno);
            n->u.call.name = (yyvsp[-3].sval);
            n->u.call.args = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1611 "parser.tab.c"
    break;

  case 42: /* expr_list: expr_list TOK_COMMA expr  */
#line 286 "parser.y"
                                { (yyval.node) = seq_append((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1617 "parser.tab.c"
    break;

  case 43: /* expr_list: expr  */
#line 287 "parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1623 "parser.tab.c"
    break;

  case 44: /* arg_list: expr_list  */
#line 291 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1629 "parser.tab.c"
    break;

  case 45: /* expr: expr TOK_OR expr  */
#line 296 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_OR; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1639 "parser.tab.c"
    break;

  case 46: /* expr: expr TOK_AND expr  */
#line 302 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_AND; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1649 "parser.tab.c"
    break;

  case 47: /* expr: TOK_NOT expr  */
#line 308 "parser.y"
        {
            AstNode *n = ast_node(NK_UNOP, yylineno);
            n->u.unop.op = OP_NOT; n->u.unop.operand = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1659 "parser.tab.c"
    break;

  case 48: /* expr: expr TOK_EQ expr  */
#line 314 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_EQ; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1669 "parser.tab.c"
    break;

  case 49: /* expr: expr TOK_NEQ expr  */
#line 320 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_NEQ; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1679 "parser.tab.c"
    break;

  case 50: /* expr: expr TOK_LT expr  */
#line 326 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_LT; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1689 "parser.tab.c"
    break;

  case 51: /* expr: expr TOK_LE expr  */
#line 332 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_LE; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1699 "parser.tab.c"
    break;

  case 52: /* expr: expr TOK_GT expr  */
#line 338 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_GT; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1709 "parser.tab.c"
    break;

  case 53: /* expr: expr TOK_GE expr  */
#line 344 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_GE; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1719 "parser.tab.c"
    break;

  case 54: /* expr: expr TOK_PLUS expr  */
#line 350 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_ADD; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1729 "parser.tab.c"
    break;

  case 55: /* expr: expr TOK_MINUS expr  */
#line 356 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_SUB; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1739 "parser.tab.c"
    break;

  case 56: /* expr: expr TOK_STAR expr  */
#line 362 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_MUL; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1749 "parser.tab.c"
    break;

  case 57: /* expr: expr TOK_SLASH expr  */
#line 368 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_DIV; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1759 "parser.tab.c"
    break;

  case 58: /* expr: expr TOK_DIV expr  */
#line 374 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_DIV; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1769 "parser.tab.c"
    break;

  case 59: /* expr: expr TOK_MOD expr  */
#line 380 "parser.y"
        {
            AstNode *n = ast_node(NK_BINOP, yylineno);
            n->u.binop.op = OP_MOD; n->u.binop.left = (yyvsp[-2].node); n->u.binop.right = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1779 "parser.tab.c"
    break;

  case 60: /* expr: TOK_MINUS expr  */
#line 386 "parser.y"
        {
            AstNode *n = ast_node(NK_UNOP, yylineno);
            n->u.unop.op = OP_NEG; n->u.unop.operand = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1789 "parser.tab.c"
    break;

  case 61: /* expr: TOK_LPAREN expr TOK_RPAREN  */
#line 391 "parser.y"
                                  { (yyval.node) = (yyvsp[-1].node); }
#line 1795 "parser.tab.c"
    break;

  case 62: /* expr: TOK_INT_LIT  */
#line 393 "parser.y"
        {
            AstNode *n = ast_node(NK_INT_LIT, yylineno);
            n->u.iliteral.value = (yyvsp[0].ival);
            (yyval.node) = n;
        }
#line 1805 "parser.tab.c"
    break;

  case 63: /* expr: TOK_TRUE  */
#line 399 "parser.y"
        {
            AstNode *n = ast_node(NK_BOOL_LIT, yylineno);
            n->u.bliteral.value = 1;
            (yyval.node) = n;
        }
#line 1815 "parser.tab.c"
    break;

  case 64: /* expr: TOK_FALSE  */
#line 405 "parser.y"
        {
            AstNode *n = ast_node(NK_BOOL_LIT, yylineno);
            n->u.bliteral.value = 0;
            (yyval.node) = n;
        }
#line 1825 "parser.tab.c"
    break;

  case 65: /* expr: TOK_STR_LIT  */
#line 411 "parser.y"
        {
            AstNode *n = ast_node(NK_IDENT, yylineno);
            n->u.ident.name = (yyvsp[0].sval);
            n->type = TY_VOID;
            (yyval.node) = n;
        }
#line 1836 "parser.tab.c"
    break;

  case 66: /* expr: TOK_IDENT TOK_LPAREN arg_list TOK_RPAREN  */
#line 418 "parser.y"
        {
            AstNode *n = ast_node(NK_CALL, yylineno);
            n->u.call.name = (yyvsp[-3].sval);
            n->u.call.args = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1847 "parser.tab.c"
    break;

  case 67: /* expr: TOK_IDENT TOK_LPAREN TOK_RPAREN  */
#line 425 "parser.y"
        {
            AstNode *n = ast_node(NK_CALL, yylineno);
            n->u.call.name = (yyvsp[-2].sval);
            n->u.call.args = NULL;
            (yyval.node) = n;
        }
#line 1858 "parser.tab.c"
    break;

  case 68: /* expr: TOK_PARAMCOUNT  */
#line 432 "parser.y"
        {
            AstNode *n = ast_node(NK_IDENT, yylineno);
            n->u.ident.name = strdup("__paramcount");
            (yyval.node) = n;
        }
#line 1868 "parser.tab.c"
    break;

  case 69: /* expr: TOK_PARAMSTR TOK_LPAREN expr TOK_RPAREN  */
#line 438 "parser.y"
        {
            AstNode *n = ast_node(NK_CALL, yylineno);
            n->u.call.name = strdup("__paramstr");
            n->u.call.args = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1879 "parser.tab.c"
    break;

  case 70: /* expr: TOK_IDENT  */
#line 445 "parser.y"
        {
            AstNode *n = ast_node(NK_IDENT, yylineno);
            n->u.ident.name = (yyvsp[0].sval);
            (yyval.node) = n;
        }
#line 1889 "parser.tab.c"
    break;


#line 1893 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 452 "parser.y"


void yyerror(const char *msg) {
    fprintf(stderr, "parse error at line %d: %s\n", yylineno, msg);
}
