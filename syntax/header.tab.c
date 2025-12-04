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
#line 1 "syntax/header.y"

#include "types.h"
#include "ast.h"
#include "syntax/header.tab.h"
#include "../semantic/semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Flex global functions and variables
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
extern int yydebug;

// Lexical analyzer function declaration
int yylex();

// Error handling function declaration
void yyerror(const char *s);
Node* root = NULL;
int error = 0;
SymbolTable *global=NULL;
SymbolTable *current=NULL;
int declaration_position = 0;
int sem_error = 0;

#line 99 "syntax/header.tab.c"

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

#include "header.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TID_TOKEN = 3,                  /* TID_TOKEN  */
  YYSYMBOL_TSTRING_LITERAL = 4,            /* TSTRING_LITERAL  */
  YYSYMBOL_TINT_CONST = 5,                 /* TINT_CONST  */
  YYSYMBOL_TCHAR_CONST = 6,                /* TCHAR_CONST  */
  YYSYMBOL_TPROGRAM = 7,                   /* TPROGRAM  */
  YYSYMBOL_TCAR = 8,                       /* TCAR  */
  YYSYMBOL_TINT = 9,                       /* TINT  */
  YYSYMBOL_TRETURN = 10,                   /* TRETURN  */
  YYSYMBOL_TREAD = 11,                     /* TREAD  */
  YYSYMBOL_TWRITE = 12,                    /* TWRITE  */
  YYSYMBOL_TNEWLINE = 13,                  /* TNEWLINE  */
  YYSYMBOL_TIF = 14,                       /* TIF  */
  YYSYMBOL_TTHEN = 15,                     /* TTHEN  */
  YYSYMBOL_TELSE = 16,                     /* TELSE  */
  YYSYMBOL_TWHILE = 17,                    /* TWHILE  */
  YYSYMBOL_TEXECUTE = 18,                  /* TEXECUTE  */
  YYSYMBOL_TAND = 19,                      /* TAND  */
  YYSYMBOL_TPLUS = 20,                     /* TPLUS  */
  YYSYMBOL_TMINUS = 21,                    /* TMINUS  */
  YYSYMBOL_TTIMES = 22,                    /* TTIMES  */
  YYSYMBOL_TDIVIDE = 23,                   /* TDIVIDE  */
  YYSYMBOL_TASSIGN = 24,                   /* TASSIGN  */
  YYSYMBOL_TEQ = 25,                       /* TEQ  */
  YYSYMBOL_TNEQ = 26,                      /* TNEQ  */
  YYSYMBOL_TLT = 27,                       /* TLT  */
  YYSYMBOL_TLEQ = 28,                      /* TLEQ  */
  YYSYMBOL_TGT = 29,                       /* TGT  */
  YYSYMBOL_TGEQ = 30,                      /* TGEQ  */
  YYSYMBOL_TSEMICOLON = 31,                /* TSEMICOLON  */
  YYSYMBOL_TLPAREN = 32,                   /* TLPAREN  */
  YYSYMBOL_TRPAREN = 33,                   /* TRPAREN  */
  YYSYMBOL_TLBRACE = 34,                   /* TLBRACE  */
  YYSYMBOL_TRBRACE = 35,                   /* TRBRACE  */
  YYSYMBOL_TLBRACKET = 36,                 /* TLBRACKET  */
  YYSYMBOL_TRBRACKET = 37,                 /* TRBRACKET  */
  YYSYMBOL_TCOMMA = 38,                    /* TCOMMA  */
  YYSYMBOL_TOR = 39,                       /* TOR  */
  YYSYMBOL_TNEG = 40,                      /* TNEG  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_Programa = 42,                  /* Programa  */
  YYSYMBOL_DeclFuncVar = 43,               /* DeclFuncVar  */
  YYSYMBOL_DeclProg = 44,                  /* DeclProg  */
  YYSYMBOL_DeclVar = 45,                   /* DeclVar  */
  YYSYMBOL_DeclFunc = 46,                  /* DeclFunc  */
  YYSYMBOL_47_1 = 47,                      /* $@1  */
  YYSYMBOL_ListaParametros = 48,           /* ListaParametros  */
  YYSYMBOL_ListaParametrosCont = 49,       /* ListaParametrosCont  */
  YYSYMBOL_Bloco = 50,                     /* Bloco  */
  YYSYMBOL_51_2 = 51,                      /* $@2  */
  YYSYMBOL_ListaDeclVar = 52,              /* ListaDeclVar  */
  YYSYMBOL_Tipo = 53,                      /* Tipo  */
  YYSYMBOL_ListaComando = 54,              /* ListaComando  */
  YYSYMBOL_Comando = 55,                   /* Comando  */
  YYSYMBOL_Expr = 56,                      /* Expr  */
  YYSYMBOL_OrExpr = 57,                    /* OrExpr  */
  YYSYMBOL_AndExpr = 58,                   /* AndExpr  */
  YYSYMBOL_EqExpr = 59,                    /* EqExpr  */
  YYSYMBOL_DesignExpr = 60,                /* DesignExpr  */
  YYSYMBOL_AddExpr = 61,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 62,                   /* MulExpr  */
  YYSYMBOL_UnExpr = 63,                    /* UnExpr  */
  YYSYMBOL_PrimExpr = 64,                  /* PrimExpr  */
  YYSYMBOL_ListExpr = 65                   /* ListExpr  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   146

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  124

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    66,    66,    77,    87,   114,   120,   125,   132,   137,
     137,   154,   158,   164,   171,   183,   182,   200,   204,   236,
     237,   241,   250,   264,   267,   270,   273,   279,   282,   288,
     291,   294,   297,   311,   316,   320,   328,   329,   333,   334,
     338,   339,   340,   344,   345,   346,   347,   348,   352,   353,
     354,   358,   359,   360,   364,   365,   366,   371,   379,   385,
     388,   391,   394,   398,   403
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
  "\"end of file\"", "error", "\"invalid token\"", "TID_TOKEN",
  "TSTRING_LITERAL", "TINT_CONST", "TCHAR_CONST", "TPROGRAM", "TCAR",
  "TINT", "TRETURN", "TREAD", "TWRITE", "TNEWLINE", "TIF", "TTHEN",
  "TELSE", "TWHILE", "TEXECUTE", "TAND", "TPLUS", "TMINUS", "TTIMES",
  "TDIVIDE", "TASSIGN", "TEQ", "TNEQ", "TLT", "TLEQ", "TGT", "TGEQ",
  "TSEMICOLON", "TLPAREN", "TRPAREN", "TLBRACE", "TRBRACE", "TLBRACKET",
  "TRBRACKET", "TCOMMA", "TOR", "TNEG", "$accept", "Programa",
  "DeclFuncVar", "DeclProg", "DeclVar", "DeclFunc", "$@1",
  "ListaParametros", "ListaParametrosCont", "Bloco", "$@2", "ListaDeclVar",
  "Tipo", "ListaComando", "Comando", "Expr", "OrExpr", "AndExpr", "EqExpr",
  "DesignExpr", "AddExpr", "MulExpr", "UnExpr", "PrimExpr", "ListExpr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-40)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       0,   -40,   -40,    24,    31,    54,   -40,    40,   -40,   -15,
     -40,   -40,   -40,    82,    57,     0,     0,     0,    59,     0,
     -40,    55,   110,    84,   -40,   115,   -40,   -40,   -17,   -40,
     -40,    50,   116,    41,    89,    90,    91,    27,   -40,    50,
      27,   -40,     8,   -40,    95,    85,   102,    11,    73,    29,
      69,   -40,   -40,    59,    40,    92,    50,    72,    96,    97,
      98,   100,   -40,    50,    50,   103,   -40,    99,   -40,   -40,
     -40,   -40,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,   105,   -40,     0,   -40,   -40,   -40,
      -7,   -40,   -40,   -40,   -40,   101,   104,   -40,   102,    11,
      73,    73,    29,    29,    29,    29,    69,    69,   -40,   -40,
       0,   -40,   -40,    50,   123,   121,   -40,   -40,    55,    55,
     124,   -40,    55,   -40
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,    20,    19,     0,     0,     0,     1,     0,     2,     8,
      15,     6,     9,     0,     0,     5,    17,    11,     8,     5,
       4,     0,     0,     0,    12,     0,     7,     3,    59,    61,
      60,     0,     0,     0,     0,     0,     0,     0,    23,     0,
       0,    33,     0,    22,     0,    34,    37,    39,    42,    47,
      50,    53,    56,     8,     0,    13,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    59,    54,     0,    55,    16,
      21,    24,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    10,     0,    35,    58,    63,
       0,    25,    26,    28,    27,     0,     0,    62,    36,    38,
      40,    41,    43,    46,    44,    45,    48,    49,    51,    52,
      17,    14,    57,     0,     0,     0,    18,    64,     0,     0,
      30,    32,     0,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,    -3,   -40,   -12,   -40,   -40,   -40,    56,    -2,
     -40,    33,   -16,   -40,   -39,   -29,   -40,    74,    68,   -11,
      30,    35,    28,    14,   -40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     8,    14,    15,    17,    23,    24,    41,
      16,    21,     5,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    90
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      22,    25,    58,    70,    61,    11,    26,    56,     1,     2,
      67,    28,    20,    29,    30,    57,    27,    12,    31,    32,
      33,    34,    35,    13,     6,    36,   112,    87,    89,    37,
      65,   113,    29,    30,    95,    96,    74,    75,     7,    38,
      39,    84,    10,    69,    28,    60,    29,    30,    40,    80,
      81,    66,    85,    28,    68,    29,    30,     9,    28,    39,
      29,    30,    37,   100,   101,    31,    32,    33,    34,    35,
      25,    37,    36,    39,    10,    28,    37,    29,    30,   120,
     121,    40,    39,   123,   117,    18,    38,    39,    19,    10,
      40,    82,    83,    37,    22,    40,    65,    13,    29,    30,
      76,    77,    78,    79,    39,    88,   102,   103,   104,   105,
     108,   109,    40,    53,    37,   106,   107,    54,    55,    59,
      62,    73,    63,    64,    72,    39,    71,    91,    92,    93,
      86,    94,    97,    40,   114,    57,   110,   115,   118,   119,
     122,    99,   111,   116,     0,     0,    98
};

static const yytype_int8 yycheck[] =
{
      16,    17,    31,    42,    33,     7,    18,    24,     8,     9,
      39,     3,    15,     5,     6,    32,    19,    32,    10,    11,
      12,    13,    14,    38,     0,    17,    33,    56,    57,    21,
       3,    38,     5,     6,    63,    64,    25,    26,     7,    31,
      32,    53,    34,    35,     3,     4,     5,     6,    40,    20,
      21,    37,    54,     3,    40,     5,     6,     3,     3,    32,
       5,     6,    21,    74,    75,    10,    11,    12,    13,    14,
      86,    21,    17,    32,    34,     3,    21,     5,     6,   118,
     119,    40,    32,   122,   113,     3,    31,    32,    31,    34,
      40,    22,    23,    21,   110,    40,     3,    38,     5,     6,
      27,    28,    29,    30,    32,    33,    76,    77,    78,    79,
      82,    83,    40,     3,    21,    80,    81,    33,     3,     3,
      31,    19,    32,    32,    39,    32,    31,    31,    31,    31,
      38,    31,    33,    40,    33,    32,    31,    33,    15,    18,
      16,    73,    86,   110,    -1,    -1,    72
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,     9,    42,    43,    53,     0,     7,    44,     3,
      34,    50,    32,    38,    45,    46,    51,    47,     3,    31,
      43,    52,    53,    48,    49,    53,    45,    43,     3,     5,
       6,    10,    11,    12,    13,    14,    17,    21,    31,    32,
      40,    50,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,     3,    33,     3,    24,    32,    56,     3,
       4,    56,    31,    32,    32,     3,    64,    56,    64,    35,
      55,    31,    39,    19,    25,    26,    27,    28,    29,    30,
      20,    21,    22,    23,    45,    50,    38,    56,    33,    56,
      65,    31,    31,    31,    31,    56,    56,    33,    58,    59,
      60,    60,    61,    61,    61,    61,    62,    62,    63,    63,
      31,    49,    33,    38,    33,    33,    52,    56,    15,    18,
      55,    55,    16,    55
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    43,    44,    45,    45,    47,
      46,    48,    48,    49,    49,    51,    50,    52,    52,    53,
      53,    54,    54,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    56,    56,    57,    57,    58,    58,
      59,    59,    59,    60,    60,    60,    60,    60,    61,    61,
      61,    62,    62,    62,    63,    63,    63,    64,    64,    64,
      64,    64,    64,    65,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     5,     4,     0,     2,     3,     0,     0,
       5,     0,     1,     2,     4,     0,     5,     0,     5,     1,
       1,     2,     1,     1,     2,     3,     3,     3,     3,     2,
       6,     8,     6,     1,     1,     3,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     2,     2,     1,     4,     3,     1,
       1,     1,     3,     1,     3
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
  case 2: /* Programa: DeclFuncVar DeclProg  */
#line 66 "syntax/header.y"
                         {
        Node *program = create_nnary_node(NOPROGRAMA, yylineno, TYVOID);
        nnary_merge_children(program, (yyvsp[-1].n));
        if ((yyvsp[0].n))
            nnary_add_child(program, (yyvsp[0].n));
        (yyval.n) = program;
        root = program;
    }
#line 1243 "syntax/header.tab.c"
    break;

  case 3: /* DeclFuncVar: Tipo TID_TOKEN DeclVar TSEMICOLON DeclFuncVar  */
#line 77 "syntax/header.y"
                                                  {
        Node *decl = create_nnary_node(NODECL_VAR, yylineno, (yyvsp[-4].type));
        Node *id = create_leaf_node(NOIDENTIFICADOR, yylineno, (yyvsp[-4].type), (yyvsp[-3].str), 0, 0);
        nnary_add_child(decl, id);
        insert_variable(current, (yyvsp[-3].str), (yyvsp[-4].type), declaration_position);
        nnary_merge_children(decl, (yyvsp[-2].n));
        Node *list = ((yyvsp[0].n) ? (yyvsp[0].n) : create_nnary_node(NOLISTA_DECL, yylineno, TYVOID));
        nnary_add_child(list, decl);
        (yyval.n) = list;
    }
#line 1258 "syntax/header.tab.c"
    break;

  case 4: /* DeclFuncVar: Tipo TID_TOKEN DeclFunc DeclFuncVar  */
#line 87 "syntax/header.y"
                                             {
        Node *func = create_nnary_node(NODECL_FUNCAO, yylineno, (yyvsp[-3].type));
        Node *id = create_leaf_node(NOIDENTIFICADOR, yylineno, (yyvsp[-3].type), (yyvsp[-2].str), 0, 0);
        nnary_add_child(func, id);

        Node *params_node = ((yyvsp[-1].n) && (yyvsp[-1].n)->data.nnary.first) ? (yyvsp[-1].n)->data.nnary.first : NULL;
        int num_params = 0;
        DataType *param_types = NULL;
        if (params_node && params_node->data.nnary.first) {
            Node *p = params_node->data.nnary.first;
            while (p) { num_params++; p = p->next; }
            param_types = malloc(sizeof(DataType) * num_params);
            int i = 0;
            p = params_node->data.nnary.first;
            while (p) {
                param_types[i++] = (p->type == TYINT ? INT_TYPE : CAR_TYPE);
                p = p->next;
            }
        }
        if (global) insert_function(global, (yyvsp[-2].str), ((yyvsp[-3].type) == TYINT ? INT_TYPE : CAR_TYPE),num_params, param_types);
        else  insert_function(current ? current : global, (yyvsp[-2].str), ((yyvsp[-3].type) == TYINT ? INT_TYPE : CAR_TYPE), num_params, param_types);
    
        nnary_merge_children(func, (yyvsp[-1].n));
        Node *list = (yyvsp[0].n) ? (yyvsp[0].n) : create_nnary_node(NOLISTA_DECL, yylineno, TYVOID);
        nnary_add_child(list, func);
        (yyval.n) = list;
    }
#line 1290 "syntax/header.tab.c"
    break;

  case 5: /* DeclFuncVar: %empty  */
#line 114 "syntax/header.y"
                     { (yyval.n) = NULL; }
#line 1296 "syntax/header.tab.c"
    break;

  case 6: /* DeclProg: TPROGRAM Bloco  */
#line 120 "syntax/header.y"
                   { (yyval.n) = (yyvsp[0].n); }
#line 1302 "syntax/header.tab.c"
    break;

  case 7: /* DeclVar: TCOMMA TID_TOKEN DeclVar  */
#line 125 "syntax/header.y"
                             {
        Node *id_node = create_leaf_node(NOIDENTIFICADOR, yylineno, TYVOID, (yyvsp[-1].str), 0, 0);
        Node *list = create_nnary_node(NOLISTA_DECL, yylineno, TYVOID);
        nnary_add_child(list, id_node);
        nnary_merge_children(list, (yyvsp[0].n));
        (yyval.n) = list;
    }
#line 1314 "syntax/header.tab.c"
    break;

  case 8: /* DeclVar: %empty  */
#line 132 "syntax/header.y"
                    { (yyval.n) = NULL; }
#line 1320 "syntax/header.tab.c"
    break;

  case 9: /* $@1: %empty  */
#line 137 "syntax/header.y"
            { create_new_scope(&current); declaration_position = 0; }
#line 1326 "syntax/header.tab.c"
    break;

  case 10: /* DeclFunc: TLPAREN $@1 ListaParametros TRPAREN Bloco  */
#line 139 "syntax/header.y"
    { 
        Node *wrap = create_nnary_node(NOFUNC_COMPONENTS, yylineno, TYVOID);
        Node *params = (yyvsp[-2].n); 
        if (!params) params = create_nnary_node(NOLISTA_PARAMS, yylineno, TYVOID);
        nnary_add_child(wrap, params);
        nnary_add_child(wrap, (yyvsp[0].n));  
        remove_current_scope(&current);
        (yyval.n) = wrap;
    }
#line 1340 "syntax/header.tab.c"
    break;

  case 11: /* ListaParametros: %empty  */
#line 154 "syntax/header.y"
                   {
         (yyval.n) = create_nnary_node(NOLISTA_PARAMS, yylineno, TYVOID);
     }
#line 1348 "syntax/header.tab.c"
    break;

  case 12: /* ListaParametros: ListaParametrosCont  */
#line 158 "syntax/header.y"
                         {
         (yyval.n) = (yyvsp[0].n);
     }
#line 1356 "syntax/header.tab.c"
    break;

  case 13: /* ListaParametrosCont: Tipo TID_TOKEN  */
#line 164 "syntax/header.y"
                    {
         Node *list = create_nnary_node(NOLISTA_PARAMS, yylineno, TYVOID);
         Node *param = create_leaf_node(NOIDENTIFICADOR, yylineno, (yyvsp[-1].type), (yyvsp[0].str), 0, 0);
         nnary_add_child(list, param);
         if (current)  insert_parameter(current, (yyvsp[0].str),((yyvsp[-1].type) == TYINT ? INT_TYPE : CAR_TYPE), declaration_position++);
         (yyval.n) = list;
     }
#line 1368 "syntax/header.tab.c"
    break;

  case 14: /* ListaParametrosCont: Tipo TID_TOKEN TCOMMA ListaParametrosCont  */
#line 171 "syntax/header.y"
                                                {

         Node *list = (yyvsp[0].n);
         Node *param = create_leaf_node(NOIDENTIFICADOR, yylineno, (yyvsp[-3].type), (yyvsp[-2].str), 0, 0);
         nnary_add_child(list, param);
         if (current) insert_parameter(current, (yyvsp[-2].str),((yyvsp[-3].type) == TYINT ? INT_TYPE : CAR_TYPE),declaration_position++);
         (yyval.n) = list;
     }
#line 1381 "syntax/header.tab.c"
    break;

  case 15: /* $@2: %empty  */
#line 183 "syntax/header.y"
    {
        create_new_scope(&current);
        declaration_position = 0;
    }
#line 1390 "syntax/header.tab.c"
    break;

  case 16: /* Bloco: TLBRACE $@2 ListaDeclVar ListaComando TRBRACE  */
#line 190 "syntax/header.y"
    {
        remove_current_scope(&current);
        Node *bloco = create_nnary_node(NOBLOCO, yylineno, TYVOID);
        nnary_merge_children(bloco, (yyvsp[-2].n));
        nnary_merge_children(bloco, (yyvsp[-1].n));
        (yyval.n) = bloco;
    }
#line 1402 "syntax/header.tab.c"
    break;

  case 17: /* ListaDeclVar: %empty  */
#line 200 "syntax/header.y"
                  {
        (yyval.n) = create_nnary_node(NOLISTA_DECL, yylineno, TYVOID);
    }
#line 1410 "syntax/header.tab.c"
    break;

  case 18: /* ListaDeclVar: Tipo TID_TOKEN DeclVar TSEMICOLON ListaDeclVar  */
#line 205 "syntax/header.y"
    {
        Node *decl = create_nnary_node(NODECL_VAR, yylineno, (yyvsp[-4].type));
        Node *id = create_leaf_node(NOIDENTIFICADOR, yylineno, (yyvsp[-4].type), (yyvsp[-3].str), 0, 0);
        nnary_add_child(decl, id);
        if (current) insert_variable(current,(yyvsp[-3].str), ((yyvsp[-4].type) == TYINT ? INT_TYPE : CAR_TYPE),declaration_position++);
        if ((yyvsp[-2].n) && (yyvsp[-2].n)->data.nnary.first) {
            Node *child = (yyvsp[-2].n)->data.nnary.first;
            while (child) {
                Node *next = child->next;
                child->type = (yyvsp[-4].type);
                if (current && child->data.leaf.lexeme) {
                    insert_variable(
                        current,
                        child->data.leaf.lexeme,
                        ((yyvsp[-4].type) == TYINT ? INT_TYPE : CAR_TYPE),
                        declaration_position++
                    );
                }
                nnary_add_child(decl, child);
                child = next;
            }
        }
        Node *acc = (yyvsp[0].n) ? (yyvsp[0].n) : create_nnary_node(NOLISTA_DECL, yylineno, TYVOID);
        nnary_add_child(acc, decl);
        (yyval.n) = acc;
    }
#line 1441 "syntax/header.tab.c"
    break;

  case 19: /* Tipo: TINT  */
#line 236 "syntax/header.y"
         { (yyval.type) = TYINT; }
#line 1447 "syntax/header.tab.c"
    break;

  case 20: /* Tipo: TCAR  */
#line 237 "syntax/header.y"
           { (yyval.type) = TYCAR; }
#line 1453 "syntax/header.tab.c"
    break;

  case 21: /* ListaComando: ListaComando Comando  */
#line 241 "syntax/header.y"
                         {
        if ((yyvsp[0].n) == NULL) { (yyval.n) = (yyvsp[-1].n); } 
        else if ((yyvsp[-1].n) != NULL) { nnary_add_child((yyvsp[-1].n), (yyvsp[0].n)); (yyval.n) = (yyvsp[-1].n); } 
        else { 
            Node *l = create_nnary_node(NOLISTA_COMANDOS, yylineno, TYVOID); 
            nnary_add_child(l, (yyvsp[0].n)); 
            (yyval.n) = l; 
        }
    }
#line 1467 "syntax/header.tab.c"
    break;

  case 22: /* ListaComando: Comando  */
#line 250 "syntax/header.y"
              {
        if ((yyvsp[0].n) != NULL) { 
            Node *l = create_nnary_node(NOLISTA_COMANDOS, yylineno, TYVOID); 
            nnary_add_child(l, (yyvsp[0].n)); 
            (yyval.n) = l; 
        }
        else (yyval.n) = NULL;

        
    }
#line 1482 "syntax/header.tab.c"
    break;

  case 23: /* Comando: TSEMICOLON  */
#line 265 "syntax/header.y"
        { (yyval.n) = NULL; }
#line 1488 "syntax/header.tab.c"
    break;

  case 24: /* Comando: Expr TSEMICOLON  */
#line 268 "syntax/header.y"
        { (yyval.n) = (yyvsp[-1].n); }
#line 1494 "syntax/header.tab.c"
    break;

  case 25: /* Comando: TRETURN Expr TSEMICOLON  */
#line 271 "syntax/header.y"
        { (yyval.n) = create_unary_node(NORETURN, yylineno, TYVOID, (yyvsp[-1].n)); }
#line 1500 "syntax/header.tab.c"
    break;

  case 26: /* Comando: TREAD TID_TOKEN TSEMICOLON  */
#line 274 "syntax/header.y"
        {
            Node *id = create_leaf_node(NOIDENTIFICADOR, yylineno, TYVOID, (yyvsp[-1].str), 0, 0);            
            (yyval.n) = create_unary_node(NOREAD, yylineno, TYVOID, id);
        }
#line 1509 "syntax/header.tab.c"
    break;

  case 27: /* Comando: TWRITE Expr TSEMICOLON  */
#line 280 "syntax/header.y"
        { (yyval.n) = create_unary_node(NOWRITE, yylineno, TYVOID, (yyvsp[-1].n)); }
#line 1515 "syntax/header.tab.c"
    break;

  case 28: /* Comando: TWRITE TSTRING_LITERAL TSEMICOLON  */
#line 283 "syntax/header.y"
        {
            Node *str = create_leaf_node(NOSTRING_LITERAL, yylineno, TYVOID, (yyvsp[-1].str), 0, 0);            
            (yyval.n) = create_unary_node(NOWRITE_LITERAL, yylineno, TYVOID, str);
        }
#line 1524 "syntax/header.tab.c"
    break;

  case 29: /* Comando: TNEWLINE TSEMICOLON  */
#line 289 "syntax/header.y"
        { (yyval.n) = create_nnary_node(NONEWLINE, yylineno, TYVOID); }
#line 1530 "syntax/header.tab.c"
    break;

  case 30: /* Comando: TIF TLPAREN Expr TRPAREN TTHEN Comando  */
#line 292 "syntax/header.y"
        { (yyval.n) = create_binary_node(NOIF, yylineno, TYVOID, (yyvsp[-3].n), (yyvsp[0].n)); }
#line 1536 "syntax/header.tab.c"
    break;

  case 31: /* Comando: TIF TLPAREN Expr TRPAREN TTHEN Comando TELSE Comando  */
#line 295 "syntax/header.y"
        { (yyval.n) = create_if_else_node(NOIF_ELSE, yylineno, TYVOID, (yyvsp[-5].n), (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1542 "syntax/header.tab.c"
    break;

  case 32: /* Comando: TWHILE TLPAREN Expr TRPAREN TEXECUTE Comando  */
#line 298 "syntax/header.y"
{
        Node *body;
        if ((yyvsp[0].n)->species == NOBLOCO) {
            body = (yyvsp[0].n);
        } else {
            body = create_nnary_node(NOBLOCO, yylineno, TYVOID);
            nnary_add_child(body, (yyvsp[0].n));
        }

        (yyval.n) = create_binary_node(NOWHILE, yylineno, TYVOID, (yyvsp[-3].n), body);
    }
#line 1558 "syntax/header.tab.c"
    break;

  case 33: /* Comando: Bloco  */
#line 312 "syntax/header.y"
        { (yyval.n) = (yyvsp[0].n); }
#line 1564 "syntax/header.tab.c"
    break;

  case 34: /* Expr: OrExpr  */
#line 317 "syntax/header.y"
        {
            (yyval.n) = (yyvsp[0].n);
        }
#line 1572 "syntax/header.tab.c"
    break;

  case 35: /* Expr: TID_TOKEN TASSIGN Expr  */
#line 321 "syntax/header.y"
        {
            (yyval.n) = create_binary_node(NOATRIBUICAO, yylineno, TYVOID, create_leaf_node(NOIDENTIFICADOR, yylineno, TYVOID, (yyvsp[-2].str), 0, 0), (yyvsp[0].n));            
        }
#line 1580 "syntax/header.tab.c"
    break;

  case 36: /* OrExpr: OrExpr TOR AndExpr  */
#line 328 "syntax/header.y"
                       { (yyval.n) = create_binary_node(NOOR, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1586 "syntax/header.tab.c"
    break;

  case 37: /* OrExpr: AndExpr  */
#line 329 "syntax/header.y"
              { (yyval.n) = (yyvsp[0].n); }
#line 1592 "syntax/header.tab.c"
    break;

  case 38: /* AndExpr: AndExpr TAND EqExpr  */
#line 333 "syntax/header.y"
                        { (yyval.n) = create_binary_node(NOAND, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1598 "syntax/header.tab.c"
    break;

  case 39: /* AndExpr: EqExpr  */
#line 334 "syntax/header.y"
             { (yyval.n) = (yyvsp[0].n); }
#line 1604 "syntax/header.tab.c"
    break;

  case 40: /* EqExpr: EqExpr TEQ DesignExpr  */
#line 338 "syntax/header.y"
                          { (yyval.n) = create_binary_node(NOIGUAL, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1610 "syntax/header.tab.c"
    break;

  case 41: /* EqExpr: EqExpr TNEQ DesignExpr  */
#line 339 "syntax/header.y"
                             { (yyval.n) = create_binary_node(NODIFERENTE, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1616 "syntax/header.tab.c"
    break;

  case 42: /* EqExpr: DesignExpr  */
#line 340 "syntax/header.y"
                 { (yyval.n) = (yyvsp[0].n); }
#line 1622 "syntax/header.tab.c"
    break;

  case 43: /* DesignExpr: DesignExpr TLT AddExpr  */
#line 344 "syntax/header.y"
                           { (yyval.n) = create_binary_node(NOMENOR, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1628 "syntax/header.tab.c"
    break;

  case 44: /* DesignExpr: DesignExpr TGT AddExpr  */
#line 345 "syntax/header.y"
                             { (yyval.n) = create_binary_node(NOMAIOR, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1634 "syntax/header.tab.c"
    break;

  case 45: /* DesignExpr: DesignExpr TGEQ AddExpr  */
#line 346 "syntax/header.y"
                              { (yyval.n) = create_binary_node(NOMAIOR_IGUAL, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1640 "syntax/header.tab.c"
    break;

  case 46: /* DesignExpr: DesignExpr TLEQ AddExpr  */
#line 347 "syntax/header.y"
                              { (yyval.n) = create_binary_node(NOMENOR_IGUAL, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1646 "syntax/header.tab.c"
    break;

  case 47: /* DesignExpr: AddExpr  */
#line 348 "syntax/header.y"
              { (yyval.n) = (yyvsp[0].n); }
#line 1652 "syntax/header.tab.c"
    break;

  case 48: /* AddExpr: AddExpr TPLUS MulExpr  */
#line 352 "syntax/header.y"
                          { (yyval.n) = create_binary_node(NOSOMA, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1658 "syntax/header.tab.c"
    break;

  case 49: /* AddExpr: AddExpr TMINUS MulExpr  */
#line 353 "syntax/header.y"
                             { (yyval.n) = create_binary_node(NOSUBTRACAO, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1664 "syntax/header.tab.c"
    break;

  case 50: /* AddExpr: MulExpr  */
#line 354 "syntax/header.y"
              { (yyval.n) = (yyvsp[0].n); }
#line 1670 "syntax/header.tab.c"
    break;

  case 51: /* MulExpr: MulExpr TTIMES UnExpr  */
#line 358 "syntax/header.y"
                          { (yyval.n) = create_binary_node(NOMULTIPLICACAO, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1676 "syntax/header.tab.c"
    break;

  case 52: /* MulExpr: MulExpr TDIVIDE UnExpr  */
#line 359 "syntax/header.y"
                             { (yyval.n) = create_binary_node(NODIVISAO, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1682 "syntax/header.tab.c"
    break;

  case 53: /* MulExpr: UnExpr  */
#line 360 "syntax/header.y"
             { (yyval.n) = (yyvsp[0].n); }
#line 1688 "syntax/header.tab.c"
    break;

  case 54: /* UnExpr: TMINUS PrimExpr  */
#line 364 "syntax/header.y"
                    { (yyval.n) = create_unary_node(NOMENOS_UNARIO, yylineno, TYINT, (yyvsp[0].n)); }
#line 1694 "syntax/header.tab.c"
    break;

  case 55: /* UnExpr: TNEG PrimExpr  */
#line 365 "syntax/header.y"
                    { (yyval.n) = create_unary_node(NONEGACAO, yylineno, TYINT, (yyvsp[0].n)); }
#line 1700 "syntax/header.tab.c"
    break;

  case 56: /* UnExpr: PrimExpr  */
#line 366 "syntax/header.y"
               { (yyval.n) = (yyvsp[0].n); }
#line 1706 "syntax/header.tab.c"
    break;

  case 57: /* PrimExpr: TID_TOKEN TLPAREN ListExpr TRPAREN  */
#line 371 "syntax/header.y"
                                       {
    Node *call = create_nnary_node(NOCHAMADA_FUNCAO, yylineno, TYVOID);
    Node *id = create_leaf_node(NOIDENTIFICADOR, yylineno, TYVOID, (yyvsp[-3].str), 0, 0);
    nnary_add_child(call, id);    
    nnary_merge_children(call, (yyvsp[-1].n));
    (yyval.n) = call;
}
#line 1718 "syntax/header.tab.c"
    break;

  case 58: /* PrimExpr: TID_TOKEN TLPAREN TRPAREN  */
#line 379 "syntax/header.y"
                                {
        Node *call = create_nnary_node(NOCHAMADA_FUNCAO, yylineno, TYVOID);
        Node *id = create_leaf_node(NOIDENTIFICADOR, yylineno, TYVOID, (yyvsp[-2].str), 0, 0);
        nnary_add_child(call, id);
        (yyval.n) = call;
      }
#line 1729 "syntax/header.tab.c"
    break;

  case 59: /* PrimExpr: TID_TOKEN  */
#line 385 "syntax/header.y"
                {
        (yyval.n) = create_leaf_node(NOIDENTIFICADOR, yylineno, TYVOID, (yyvsp[0].str), 0, 0);        
      }
#line 1737 "syntax/header.tab.c"
    break;

  case 60: /* PrimExpr: TCHAR_CONST  */
#line 388 "syntax/header.y"
                  {
        (yyval.n) = create_leaf_node(NOCAR_CONST, yylineno, TYCAR, NULL, 0, (yyvsp[0].cval));
      }
#line 1745 "syntax/header.tab.c"
    break;

  case 61: /* PrimExpr: TINT_CONST  */
#line 391 "syntax/header.y"
                 {
        (yyval.n) = create_leaf_node(NOINT_CONST, yylineno, TYINT, NULL, (yyvsp[0].ival), 0);
      }
#line 1753 "syntax/header.tab.c"
    break;

  case 62: /* PrimExpr: TLPAREN Expr TRPAREN  */
#line 394 "syntax/header.y"
                           { (yyval.n) = (yyvsp[-1].n); }
#line 1759 "syntax/header.tab.c"
    break;

  case 63: /* ListExpr: Expr  */
#line 398 "syntax/header.y"
         {
        Node *l = create_nnary_node(NOLISTA_EXPR, yylineno, TYVOID);
        nnary_add_child(l, (yyvsp[0].n));
        (yyval.n) = l;
      }
#line 1769 "syntax/header.tab.c"
    break;

  case 64: /* ListExpr: ListExpr TCOMMA Expr  */
#line 403 "syntax/header.y"
                           {
        nnary_add_child((yyvsp[-2].n), (yyvsp[0].n));
        (yyval.n) = (yyvsp[-2].n);
      }
#line 1778 "syntax/header.tab.c"
    break;


#line 1782 "syntax/header.tab.c"

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

#line 410 "syntax/header.y"


void yyerror(const char *s) {
    error = 1;
    fprintf(stderr, "Erro: Erro lexico  na linha %d na linha '%s'\n", yylineno, yytext);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Erro: argumento ausente.\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Erro: não foi possível abrir o arquivo '%s'.\n", argv[1]);
        return 1;
    }

    initialize_symbol_table(&global);
    current = global;
    declaration_position = 0;

    yyparse(); 
    fclose(yyin);
    analyze_program(root, global);

    if (error) {
        if (root) {
            free_ast(root);
            root = NULL;
        }
        return 1;
    }

   
    if (sem_error) {
        fprintf(stderr,
                "Sucesso: analise foi concluida, mas foram encontrados erros SEMANTICOS.\n");
        return 1;
    }

    printf("Sucesso: análise concluída com sucesso, livre de erros semanticos e de erros sintaticos.\n");
    return 0;
}
