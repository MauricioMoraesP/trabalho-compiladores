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

#line 95 "syntax/header.tab.c"

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
  YYSYMBOL_ListaParametros = 47,           /* ListaParametros  */
  YYSYMBOL_ListaParametrosCont = 48,       /* ListaParametrosCont  */
  YYSYMBOL_Bloco = 49,                     /* Bloco  */
  YYSYMBOL_ListaDeclVar = 50,              /* ListaDeclVar  */
  YYSYMBOL_Tipo = 51,                      /* Tipo  */
  YYSYMBOL_ListaComando = 52,              /* ListaComando  */
  YYSYMBOL_Comando = 53,                   /* Comando  */
  YYSYMBOL_Expr = 54,                      /* Expr  */
  YYSYMBOL_OrExpr = 55,                    /* OrExpr  */
  YYSYMBOL_AndExpr = 56,                   /* AndExpr  */
  YYSYMBOL_EqExpr = 57,                    /* EqExpr  */
  YYSYMBOL_DesignExpr = 58,                /* DesignExpr  */
  YYSYMBOL_AddExpr = 59,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 60,                   /* MulExpr  */
  YYSYMBOL_UnExpr = 61,                    /* UnExpr  */
  YYSYMBOL_PrimExpr = 62,                  /* PrimExpr  */
  YYSYMBOL_ListExpr = 63                   /* ListExpr  */
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
#define YYLAST   144

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

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
       0,    62,    62,    82,   105,   128,   133,   138,   165,   170,
     186,   190,   197,   205,   216,   250,   254,   287,   288,   292,
     301,   313,   316,   319,   322,   330,   333,   341,   344,   347,
     350,   365,   370,   374,   386,   387,   391,   392,   396,   397,
     398,   402,   403,   404,   405,   406,   410,   411,   412,   416,
     417,   418,   422,   423,   424,   429,   451,   461,   466,   469,
     472,   476,   481
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
  "DeclFuncVar", "DeclProg", "DeclVar", "DeclFunc", "ListaParametros",
  "ListaParametrosCont", "Bloco", "ListaDeclVar", "Tipo", "ListaComando",
  "Comando", "Expr", "OrExpr", "AndExpr", "EqExpr", "DesignExpr",
  "AddExpr", "MulExpr", "UnExpr", "PrimExpr", "ListExpr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-35)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      37,   -35,   -35,    17,    24,    35,   -35,    -1,   -35,   -25,
      37,   -35,    37,    44,    20,    37,    47,    53,    34,   -35,
      66,    46,    37,   -35,    -8,   -35,   -35,    91,    72,    67,
      49,    57,    59,     5,   -35,    91,     5,   -35,     9,   -35,
      64,    62,    90,    29,    86,    42,    43,   -35,   -35,    46,
      -1,    68,   -35,   -35,    91,    87,    93,    94,    95,    99,
     -35,    91,    91,    85,   -35,    88,   -35,   -35,   -35,   -35,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,   105,   -35,    37,   -35,   -35,   -35,    -6,   -35,
     -35,   -35,   -35,    89,   106,   -35,    90,    29,    86,    86,
      42,    42,    42,    42,    43,    43,   -35,   -35,    37,   -35,
     -35,    91,   113,   120,   -35,   -35,    47,    47,   124,   -35,
      47,   -35
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,    18,    17,     0,     0,     0,     1,     0,     2,     8,
      15,     6,    10,     0,     0,     5,     0,     0,     0,    11,
       0,     8,     5,     4,    57,    59,    58,     0,     0,     0,
       0,     0,     0,     0,    21,     0,     0,    31,     0,    20,
       0,    32,    35,    37,    40,    45,    48,    51,    54,     8,
       0,    12,     7,     3,     0,     0,     0,     0,     0,     0,
      27,     0,     0,    57,    52,     0,    53,    14,    19,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,     0,    33,    56,    61,     0,    23,
      24,    26,    25,     0,     0,    60,    34,    36,    38,    39,
      41,    44,    42,    43,    46,    47,    49,    50,    15,    13,
      55,     0,     0,     0,    16,    62,     0,     0,    28,    30,
       0,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,   -35,     3,   -35,   -15,   -35,   -35,    60,    -2,    33,
     -10,   -35,   -34,   -26,   -35,    73,    71,     4,    58,    26,
      30,     6,   -35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     8,    14,    15,    18,    19,    37,    16,
       5,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    88
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      17,    56,    20,    59,    68,    11,    52,    12,    63,    65,
      25,    26,    24,    13,    25,    26,    54,     6,    23,    27,
      28,    29,    30,    31,    55,    53,    32,   110,    85,    87,
      33,     7,   111,    10,    82,    93,    94,    35,     9,    64,
      34,    35,    66,    10,    67,     1,     2,    21,    83,    36,
      24,    22,    25,    26,    72,    73,    49,    27,    28,    29,
      30,    31,    78,    79,    32,    80,    81,    50,    33,    51,
      24,    58,    25,    26,    20,    57,    98,    99,    34,    35,
      60,    10,   118,   119,    13,   115,   121,    36,    33,    61,
      24,    62,    25,    26,    24,    69,    25,    26,    17,    35,
      63,    70,    25,    26,   104,   105,    84,    36,    33,    71,
     106,   107,    33,    74,    75,    76,    77,    55,    33,    35,
      86,    95,   112,    35,    89,    90,    91,    36,   116,    35,
      92,    36,   100,   101,   102,   103,   108,    36,   117,   113,
     120,   114,    97,    96,   109
};

static const yytype_int8 yycheck[] =
{
      10,    27,    12,    29,    38,     7,    21,    32,     3,    35,
       5,     6,     3,    38,     5,     6,    24,     0,    15,    10,
      11,    12,    13,    14,    32,    22,    17,    33,    54,    55,
      21,     7,    38,    34,    49,    61,    62,    32,     3,    33,
      31,    32,    36,    34,    35,     8,     9,     3,    50,    40,
       3,    31,     5,     6,    25,    26,     3,    10,    11,    12,
      13,    14,    20,    21,    17,    22,    23,    33,    21,     3,
       3,     4,     5,     6,    84,     3,    72,    73,    31,    32,
      31,    34,   116,   117,    38,   111,   120,    40,    21,    32,
       3,    32,     5,     6,     3,    31,     5,     6,   108,    32,
       3,    39,     5,     6,    78,    79,    38,    40,    21,    19,
      80,    81,    21,    27,    28,    29,    30,    32,    21,    32,
      33,    33,    33,    32,    31,    31,    31,    40,    15,    32,
      31,    40,    74,    75,    76,    77,    31,    40,    18,    33,
      16,   108,    71,    70,    84
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,     9,    42,    43,    51,     0,     7,    44,     3,
      34,    49,    32,    38,    45,    46,    50,    51,    47,    48,
      51,     3,    31,    43,     3,     5,     6,    10,    11,    12,
      13,    14,    17,    21,    31,    32,    40,    49,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,     3,
      33,     3,    45,    43,    24,    32,    54,     3,     4,    54,
      31,    32,    32,     3,    62,    54,    62,    35,    53,    31,
      39,    19,    25,    26,    27,    28,    29,    30,    20,    21,
      22,    23,    45,    49,    38,    54,    33,    54,    63,    31,
      31,    31,    31,    54,    54,    33,    56,    57,    58,    58,
      59,    59,    59,    59,    60,    60,    61,    61,    31,    48,
      33,    38,    33,    33,    50,    54,    15,    18,    53,    53,
      16,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    43,    44,    45,    45,    46,
      47,    47,    48,    48,    49,    50,    50,    51,    51,    52,
      52,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    54,    54,    55,    55,    56,    56,    57,    57,
      57,    58,    58,    58,    58,    58,    59,    59,    59,    60,
      60,    60,    61,    61,    61,    62,    62,    62,    62,    62,
      62,    63,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     5,     4,     0,     2,     3,     0,     4,
       0,     1,     2,     4,     4,     0,     5,     1,     1,     2,
       1,     1,     2,     3,     3,     3,     3,     2,     6,     8,
       6,     1,     1,     3,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     2,     2,     1,     4,     3,     1,     1,     1,
       3,     1,     3
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
#line 62 "syntax/header.y"
                         {
        Node *program = createNnaryNode(NOPROGRAMA, yylineno, TYVOID);
        if ((yyvsp[-1].n) && (yyvsp[-1].n)->data.nnary.first) {
            Node *child = (yyvsp[-1].n)->data.nnary.first;
            while (child) {
                Node *next = child->next;
                nnaryAddChild(program, child);
                child = next;
            }
        }
        if ((yyvsp[-1].n)) free((yyvsp[-1].n));

        if ((yyvsp[0].n))
            nnaryAddChild(program, (yyvsp[0].n));
        (yyval.n) = program;
        root = program;
    }
#line 1246 "syntax/header.tab.c"
    break;

  case 3: /* DeclFuncVar: Tipo TID_TOKEN DeclVar TSEMICOLON DeclFuncVar  */
#line 82 "syntax/header.y"
                                                  {
        Node *decl = createNnaryNode(NODECL_VAR, yylineno, (yyvsp[-4].type));
        Node *id = createLeafNode(NOIDENTIFICADOR, yylineno, (yyvsp[-4].type), (yyvsp[-3].str), 0, 0);
        nnaryAddChild(decl, id);

        /* se houver lista de identificadores vindos de DeclVar, movê-los com segurança */
        if ((yyvsp[-2].n) && (yyvsp[-2].n)->data.nnary.first) {
            Node *child = (yyvsp[-2].n)->data.nnary.first;
            while (child) {
                Node *next = child->next; 
                nnaryAddChild(decl, child);
                child = next;
            }
        }
        /* CORREÇÃO 1: Libera o nó container $3 (DeclVar) */
        if ((yyvsp[-2].n)) free((yyvsp[-2].n));
        /* CORREÇÃO 4: Libera o lexema $2 */
        free((yyvsp[-3].str));

        Node *list = ((yyvsp[0].n) ? (yyvsp[0].n) : createNnaryNode(NOLISTA_DECL, yylineno, TYVOID));
        nnaryAddChild(list, decl);
        (yyval.n) = list;
    }
#line 1274 "syntax/header.tab.c"
    break;

  case 4: /* DeclFuncVar: Tipo TID_TOKEN DeclFunc DeclFuncVar  */
#line 105 "syntax/header.y"
                                          {
        Node *func = createNnaryNode(NODECL_FUNCAO, yylineno, (yyvsp[-3].type));
        Node *id = createLeafNode(NOIDENTIFICADOR, yylineno, (yyvsp[-3].type), (yyvsp[-2].str), 0, 0);

        nnaryAddChild(func, id);
        
        /* CORREÇÃO 4: Libera o lexema $2 */
        free((yyvsp[-2].str));

        Node *child = (yyvsp[-1].n)->data.nnary.first;
        while (child) {
            Node *next = child->next;
            nnaryAddChild(func, child);
            child = next;
        }

        /* CORREÇÃO 2: Libera o nó container $3 (DeclFunc/NOFUNC_COMPONENTS) */
        if ((yyvsp[-1].n)) free((yyvsp[-1].n));

        Node *list = (yyvsp[0].n) ? (yyvsp[0].n) : createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
        nnaryAddChild(list, func);
        (yyval.n) = list;
    }
#line 1302 "syntax/header.tab.c"
    break;

  case 5: /* DeclFuncVar: %empty  */
#line 128 "syntax/header.y"
             { (yyval.n) = NULL; }
#line 1308 "syntax/header.tab.c"
    break;

  case 6: /* DeclProg: TPROGRAM Bloco  */
#line 133 "syntax/header.y"
                   { (yyval.n) = (yyvsp[0].n); }
#line 1314 "syntax/header.tab.c"
    break;

  case 7: /* DeclVar: TCOMMA TID_TOKEN DeclVar  */
#line 138 "syntax/header.y"
                             {
        Node *id_node = createLeafNode(NOIDENTIFICADOR, yylineno, TYVOID, (yyvsp[-1].str), 0, 0);
        /* CORREÇÃO 4: Libera o lexema $2 */
        free((yyvsp[-1].str));

        /* criar nova lista com o id atual em primeiro */
        Node *list = createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
        nnaryAddChild(list, id_node);

        /* anexar (mover) os filhos de $3, se existirem, após o id atual */
        if ((yyvsp[0].n) && (yyvsp[0].n)->data.nnary.first) {
            Node *child = (yyvsp[0].n)->data.nnary.first;
            while (child) {
                Node *next = child->next;
                /* desconectar antes de anexar */
                child->next = NULL;
                nnaryAddChild(list, child);
                child = next;
            }
        }

        /* liberar o container antigo para evitar vazamento */
        if ((yyvsp[0].n))
            free((yyvsp[0].n));

        (yyval.n) = list;
    }
#line 1346 "syntax/header.tab.c"
    break;

  case 8: /* DeclVar: %empty  */
#line 165 "syntax/header.y"
             { (yyval.n) = NULL; }
#line 1352 "syntax/header.tab.c"
    break;

  case 9: /* DeclFunc: TLPAREN ListaParametros TRPAREN Bloco  */
#line 170 "syntax/header.y"
                                          { 
        Node *wrap = createNnaryNode(NOFUNC_COMPONENTS, yylineno, TYVOID);
        
        Node *params = (yyvsp[-2].n); 
        if (!params) {
             params = createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
        }
        
        nnaryAddChild(wrap, params);
        nnaryAddChild(wrap, (yyvsp[0].n));
        (yyval.n) = wrap;
    }
#line 1369 "syntax/header.tab.c"
    break;

  case 10: /* ListaParametros: %empty  */
#line 186 "syntax/header.y"
            {
         (yyval.n) = createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
     }
#line 1377 "syntax/header.tab.c"
    break;

  case 11: /* ListaParametros: ListaParametrosCont  */
#line 190 "syntax/header.y"
                         {
         (yyval.n) = (yyvsp[0].n);
     }
#line 1385 "syntax/header.tab.c"
    break;

  case 12: /* ListaParametrosCont: Tipo TID_TOKEN  */
#line 197 "syntax/header.y"
                    {
         Node *list = createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
         Node *param = createLeafNode(NOIDENTIFICADOR, yylineno, (yyvsp[-1].type), (yyvsp[0].str), 0, 0);
         nnaryAddChild(list, param);
         /* CORREÇÃO 4: Libera o lexema $2 */
         free((yyvsp[0].str));
         (yyval.n) = list;
     }
#line 1398 "syntax/header.tab.c"
    break;

  case 13: /* ListaParametrosCont: Tipo TID_TOKEN TCOMMA ListaParametrosCont  */
#line 205 "syntax/header.y"
                                                {
         Node *list = (yyvsp[0].n) ? (yyvsp[0].n) : createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
         Node *param = createLeafNode(NOIDENTIFICADOR, yylineno, (yyvsp[-3].type), (yyvsp[-2].str), 0, 0);
         nnaryAddChild(list, param);
         /* CORREÇÃO 4: Libera o lexema $2 */
         free((yyvsp[-2].str));
         (yyval.n) = list;
     }
#line 1411 "syntax/header.tab.c"
    break;

  case 14: /* Bloco: TLBRACE ListaDeclVar ListaComando TRBRACE  */
#line 216 "syntax/header.y"
                                              {
        Node *bloco = createNnaryNode(NOBLOCO, yylineno, TYVOID);
        /* ------ Mover declarações ($2) ------ */
        if ((yyvsp[-2].n)) {
            Node *child = (yyvsp[-2].n)->data.nnary.first;
            while (child) {
                Node *next = child->next;
                child->next = NULL;
                nnaryAddChild(bloco, child);
                child = next;
            }
            free((yyvsp[-2].n));   /* libera o contêiner */
            (yyvsp[-2].n) = NULL;
        }

        /* ------ Mover comandos ($3) ------ */
        if ((yyvsp[-1].n)) {
            Node *child = (yyvsp[-1].n)->data.nnary.first;
            while (child) {
                Node *next = child->next;
                child->next = NULL;
                nnaryAddChild(bloco, child);
                child = next;
            }
            free((yyvsp[-1].n));  
            (yyvsp[-1].n) = NULL;
        }
        (yyval.n) = bloco;
    }
#line 1445 "syntax/header.tab.c"
    break;

  case 15: /* ListaDeclVar: %empty  */
#line 250 "syntax/header.y"
           {
        (yyval.n) = createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
    }
#line 1453 "syntax/header.tab.c"
    break;

  case 16: /* ListaDeclVar: Tipo TID_TOKEN DeclVar TSEMICOLON ListaDeclVar  */
#line 254 "syntax/header.y"
                                                   {

        /* Declaração individual */
        Node *decl = createNnaryNode(NODECL_VAR, yylineno, (yyvsp[-4].type));
        Node *id = createLeafNode(NOIDENTIFICADOR, yylineno, (yyvsp[-4].type), (yyvsp[-3].str), 0, 0);
        nnaryAddChild(decl, id);
        
        /* CORREÇÃO 4: Libera o lexema $2 */
        free((yyvsp[-3].str));

        /* Adiciona ids separados por vírgula */
        if ((yyvsp[-2].n) && (yyvsp[-2].n)->data.nnary.first) {
            Node *child = (yyvsp[-2].n)->data.nnary.first;
            while (child) {
                Node *next = child->next;
                nnaryAddChild(decl, child);
                child = next;
            }
        }
        /* Libera o container de IDs DeclVar ($3) se ele existe */
        if ((yyvsp[-2].n)) free((yyvsp[-2].n));


        /* $5 é a ListaDeclVar recursiva (à direita) */
        Node *acc = (yyvsp[0].n) ? (yyvsp[0].n) : createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
        nnaryAddChild(acc, decl);

        (yyval.n) = acc;
    }
#line 1487 "syntax/header.tab.c"
    break;

  case 17: /* Tipo: TINT  */
#line 287 "syntax/header.y"
         { (yyval.type) = TYINT; }
#line 1493 "syntax/header.tab.c"
    break;

  case 18: /* Tipo: TCAR  */
#line 288 "syntax/header.y"
           { (yyval.type) = TYCAR; }
#line 1499 "syntax/header.tab.c"
    break;

  case 19: /* ListaComando: ListaComando Comando  */
#line 292 "syntax/header.y"
                         {
        if ((yyvsp[0].n) == NULL) { (yyval.n) = (yyvsp[-1].n); } 
        else if ((yyvsp[-1].n) != NULL) { nnaryAddChild((yyvsp[-1].n), (yyvsp[0].n)); (yyval.n) = (yyvsp[-1].n); } 
        else { 
            Node *l = createNnaryNode(NOLISTA_COMANDOS, yylineno, TYVOID); 
            nnaryAddChild(l, (yyvsp[0].n)); 
            (yyval.n) = l; 
        }
    }
#line 1513 "syntax/header.tab.c"
    break;

  case 20: /* ListaComando: Comando  */
#line 301 "syntax/header.y"
              {
        if ((yyvsp[0].n) != NULL) { 
            Node *l = createNnaryNode(NOLISTA_COMANDOS, yylineno, TYVOID); 
            nnaryAddChild(l, (yyvsp[0].n)); 
            (yyval.n) = l; 
        }
        else { (yyval.n) = NULL; } // Comando nulo, retorna NULL. OK.
    }
#line 1526 "syntax/header.tab.c"
    break;

  case 21: /* Comando: TSEMICOLON  */
#line 314 "syntax/header.y"
        { (yyval.n) = NULL; }
#line 1532 "syntax/header.tab.c"
    break;

  case 22: /* Comando: Expr TSEMICOLON  */
#line 317 "syntax/header.y"
        { (yyval.n) = (yyvsp[-1].n); }
#line 1538 "syntax/header.tab.c"
    break;

  case 23: /* Comando: TRETURN Expr TSEMICOLON  */
#line 320 "syntax/header.y"
        { (yyval.n) = createUnaryNode(NORETURN, yylineno, TYVOID, (yyvsp[-1].n)); }
#line 1544 "syntax/header.tab.c"
    break;

  case 24: /* Comando: TREAD TID_TOKEN TSEMICOLON  */
#line 323 "syntax/header.y"
        {
            Node *id = createLeafNode(NOIDENTIFICADOR, yylineno, TYVOID, (yyvsp[-1].str), 0, 0);
            /* CORREÇÃO 4: Libera o lexema $2 */
            free((yyvsp[-1].str));
            (yyval.n) = createUnaryNode(NOREAD, yylineno, TYVOID, id);
        }
#line 1555 "syntax/header.tab.c"
    break;

  case 25: /* Comando: TWRITE Expr TSEMICOLON  */
#line 331 "syntax/header.y"
        { (yyval.n) = createUnaryNode(NOWRITE, yylineno, TYVOID, (yyvsp[-1].n)); }
#line 1561 "syntax/header.tab.c"
    break;

  case 26: /* Comando: TWRITE TSTRING_LITERAL TSEMICOLON  */
#line 334 "syntax/header.y"
        {
            Node *str = createLeafNode(NOSTRING_LITERAL, yylineno, TYVOID, (yyvsp[-1].str), 0, 0);
            /* CORREÇÃO 4: Libera o lexema $2 */
            free((yyvsp[-1].str));
            (yyval.n) = createUnaryNode(NOWRITE_LITERAL, yylineno, TYVOID, str);
        }
#line 1572 "syntax/header.tab.c"
    break;

  case 27: /* Comando: TNEWLINE TSEMICOLON  */
#line 342 "syntax/header.y"
        { (yyval.n) = createNnaryNode(NONEWLINE, yylineno, TYVOID); }
#line 1578 "syntax/header.tab.c"
    break;

  case 28: /* Comando: TIF TLPAREN Expr TRPAREN TTHEN Comando  */
#line 345 "syntax/header.y"
        { (yyval.n) = createBinaryNode(NOIF, yylineno, TYVOID, (yyvsp[-3].n), (yyvsp[0].n)); }
#line 1584 "syntax/header.tab.c"
    break;

  case 29: /* Comando: TIF TLPAREN Expr TRPAREN TTHEN Comando TELSE Comando  */
#line 348 "syntax/header.y"
        { (yyval.n) = createIfElseNode(NOIF_ELSE, yylineno, TYVOID, (yyvsp[-5].n), (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1590 "syntax/header.tab.c"
    break;

  case 30: /* Comando: TWHILE TLPAREN Expr TRPAREN TEXECUTE Comando  */
#line 351 "syntax/header.y"
{
        Node *body;

        if ((yyvsp[0].n)->species == NOBLOCO) {
            body = (yyvsp[0].n);
        } else {
            body = createNnaryNode(NOBLOCO, yylineno, TYVOID);
            nnaryAddChild(body, (yyvsp[0].n));
        }

        (yyval.n) = createBinaryNode(NOWHILE, yylineno, TYVOID, (yyvsp[-3].n), body);
    }
#line 1607 "syntax/header.tab.c"
    break;

  case 31: /* Comando: Bloco  */
#line 366 "syntax/header.y"
        { (yyval.n) = (yyvsp[0].n); }
#line 1613 "syntax/header.tab.c"
    break;

  case 32: /* Expr: OrExpr  */
#line 371 "syntax/header.y"
        {
            (yyval.n) = (yyvsp[0].n);
        }
#line 1621 "syntax/header.tab.c"
    break;

  case 33: /* Expr: TID_TOKEN TASSIGN Expr  */
#line 375 "syntax/header.y"
        {
            (yyval.n) = createBinaryNode(NOATRIBUICAO, yylineno, TYVOID,
                                     createLeafNode(NOIDENTIFICADOR, yylineno, TYVOID, (yyvsp[-2].str), 0, 0),
                                     (yyvsp[0].n));
            /* CORREÇÃO 4: Libera o lexema $1 */
            free((yyvsp[-2].str));
        }
#line 1633 "syntax/header.tab.c"
    break;

  case 34: /* OrExpr: OrExpr TOR AndExpr  */
#line 386 "syntax/header.y"
                       { (yyval.n) = createBinaryNode(NOOR, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1639 "syntax/header.tab.c"
    break;

  case 35: /* OrExpr: AndExpr  */
#line 387 "syntax/header.y"
              { (yyval.n) = (yyvsp[0].n); }
#line 1645 "syntax/header.tab.c"
    break;

  case 36: /* AndExpr: AndExpr TAND EqExpr  */
#line 391 "syntax/header.y"
                        { (yyval.n) = createBinaryNode(NOAND, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1651 "syntax/header.tab.c"
    break;

  case 37: /* AndExpr: EqExpr  */
#line 392 "syntax/header.y"
             { (yyval.n) = (yyvsp[0].n); }
#line 1657 "syntax/header.tab.c"
    break;

  case 38: /* EqExpr: EqExpr TEQ DesignExpr  */
#line 396 "syntax/header.y"
                          { (yyval.n) = createBinaryNode(NOIGUAL, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1663 "syntax/header.tab.c"
    break;

  case 39: /* EqExpr: EqExpr TNEQ DesignExpr  */
#line 397 "syntax/header.y"
                             { (yyval.n) = createBinaryNode(NODIFERENTE, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1669 "syntax/header.tab.c"
    break;

  case 40: /* EqExpr: DesignExpr  */
#line 398 "syntax/header.y"
                 { (yyval.n) = (yyvsp[0].n); }
#line 1675 "syntax/header.tab.c"
    break;

  case 41: /* DesignExpr: DesignExpr TLT AddExpr  */
#line 402 "syntax/header.y"
                           { (yyval.n) = createBinaryNode(NOMENOR, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1681 "syntax/header.tab.c"
    break;

  case 42: /* DesignExpr: DesignExpr TGT AddExpr  */
#line 403 "syntax/header.y"
                             { (yyval.n) = createBinaryNode(NOMAIOR, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1687 "syntax/header.tab.c"
    break;

  case 43: /* DesignExpr: DesignExpr TGEQ AddExpr  */
#line 404 "syntax/header.y"
                              { (yyval.n) = createBinaryNode(NOMAIOR_IGUAL, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1693 "syntax/header.tab.c"
    break;

  case 44: /* DesignExpr: DesignExpr TLEQ AddExpr  */
#line 405 "syntax/header.y"
                              { (yyval.n) = createBinaryNode(NOMENOR_IGUAL, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1699 "syntax/header.tab.c"
    break;

  case 45: /* DesignExpr: AddExpr  */
#line 406 "syntax/header.y"
              { (yyval.n) = (yyvsp[0].n); }
#line 1705 "syntax/header.tab.c"
    break;

  case 46: /* AddExpr: AddExpr TPLUS MulExpr  */
#line 410 "syntax/header.y"
                          { (yyval.n) = createBinaryNode(NOSOMA, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1711 "syntax/header.tab.c"
    break;

  case 47: /* AddExpr: AddExpr TMINUS MulExpr  */
#line 411 "syntax/header.y"
                             { (yyval.n) = createBinaryNode(NOSUBTRACAO, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1717 "syntax/header.tab.c"
    break;

  case 48: /* AddExpr: MulExpr  */
#line 412 "syntax/header.y"
              { (yyval.n) = (yyvsp[0].n); }
#line 1723 "syntax/header.tab.c"
    break;

  case 49: /* MulExpr: MulExpr TTIMES UnExpr  */
#line 416 "syntax/header.y"
                          { (yyval.n) = createBinaryNode(NOMULTIPLICACAO, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1729 "syntax/header.tab.c"
    break;

  case 50: /* MulExpr: MulExpr TDIVIDE UnExpr  */
#line 417 "syntax/header.y"
                             { (yyval.n) = createBinaryNode(NODIVISAO, yylineno, TYINT, (yyvsp[-2].n), (yyvsp[0].n)); }
#line 1735 "syntax/header.tab.c"
    break;

  case 51: /* MulExpr: UnExpr  */
#line 418 "syntax/header.y"
             { (yyval.n) = (yyvsp[0].n); }
#line 1741 "syntax/header.tab.c"
    break;

  case 52: /* UnExpr: TMINUS PrimExpr  */
#line 422 "syntax/header.y"
                    { (yyval.n) = createUnaryNode(NOMENOS_UNARIO, yylineno, TYINT, (yyvsp[0].n)); }
#line 1747 "syntax/header.tab.c"
    break;

  case 53: /* UnExpr: TNEG PrimExpr  */
#line 423 "syntax/header.y"
                    { (yyval.n) = createUnaryNode(NONEGACAO, yylineno, TYINT, (yyvsp[0].n)); }
#line 1753 "syntax/header.tab.c"
    break;

  case 54: /* UnExpr: PrimExpr  */
#line 424 "syntax/header.y"
               { (yyval.n) = (yyvsp[0].n); }
#line 1759 "syntax/header.tab.c"
    break;

  case 55: /* PrimExpr: TID_TOKEN TLPAREN ListExpr TRPAREN  */
#line 429 "syntax/header.y"
                                       {
    Node *call = createNnaryNode(NOCHAMADA_FUNCAO, yylineno, TYVOID);
    Node *id = createLeafNode(NOIDENTIFICADOR, yylineno, TYVOID, (yyvsp[-3].str), 0, 0);
    nnaryAddChild(call, id);
    /* CORREÇÃO 4: Libera o lexema $1 */
    free((yyvsp[-3].str));
    
    if ((yyvsp[-1].n) && (yyvsp[-1].n)->data.nnary.first) {
        Node *child = (yyvsp[-1].n)->data.nnary.first;
        while (child) {
            Node *next = child->next;
            nnaryAddChild(call, child);
            child = next;
        }
    }

    /* free do container ListExpr: já movemos os filhos */
    if ((yyvsp[-1].n)) free((yyvsp[-1].n));

    (yyval.n) = call;
}
#line 1785 "syntax/header.tab.c"
    break;

  case 56: /* PrimExpr: TID_TOKEN TLPAREN TRPAREN  */
#line 451 "syntax/header.y"
                                {
        Node *call = createNnaryNode(NOCHAMADA_FUNCAO, yylineno, TYVOID);
        Node *id = createLeafNode(NOIDENTIFICADOR, yylineno, TYVOID, (yyvsp[-2].str), 0, 0);
        nnaryAddChild(call, id);
        
        /* CORREÇÃO 4: Libera o lexema $1 */
        free((yyvsp[-2].str));

        (yyval.n) = call;
      }
#line 1800 "syntax/header.tab.c"
    break;

  case 57: /* PrimExpr: TID_TOKEN  */
#line 461 "syntax/header.y"
                {
        (yyval.n) = createLeafNode(NOIDENTIFICADOR, yylineno, TYVOID, (yyvsp[0].str), 0, 0);
        /* CORREÇÃO 4: Libera o lexema $1 */
        free((yyvsp[0].str));
      }
#line 1810 "syntax/header.tab.c"
    break;

  case 58: /* PrimExpr: TCHAR_CONST  */
#line 466 "syntax/header.y"
                  {
        (yyval.n) = createLeafNode(NOCAR_CONST, yylineno, TYCAR, NULL, 0, (yyvsp[0].cval));
      }
#line 1818 "syntax/header.tab.c"
    break;

  case 59: /* PrimExpr: TINT_CONST  */
#line 469 "syntax/header.y"
                 {
        (yyval.n) = createLeafNode(NOINT_CONST, yylineno, TYINT, NULL, (yyvsp[0].ival), 0);
      }
#line 1826 "syntax/header.tab.c"
    break;

  case 60: /* PrimExpr: TLPAREN Expr TRPAREN  */
#line 472 "syntax/header.y"
                           { (yyval.n) = (yyvsp[-1].n); }
#line 1832 "syntax/header.tab.c"
    break;

  case 61: /* ListExpr: Expr  */
#line 476 "syntax/header.y"
         {
        Node *l = createNnaryNode(NOLISTA_EXPR, yylineno, TYVOID);
        nnaryAddChild(l, (yyvsp[0].n));
        (yyval.n) = l;
      }
#line 1842 "syntax/header.tab.c"
    break;

  case 62: /* ListExpr: ListExpr TCOMMA Expr  */
#line 481 "syntax/header.y"
                           {
        nnaryAddChild((yyvsp[-2].n), (yyvsp[0].n));
        (yyval.n) = (yyvsp[-2].n);
      }
#line 1851 "syntax/header.tab.c"
    break;


#line 1855 "syntax/header.tab.c"

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

#line 488 "syntax/header.y"


/* User C Code */

// Error handling function
void yyerror(const char *s) {
    error = 1;
    fprintf(stderr, "Erro: Erro sintático na linha %d, próximo a '%s'\n", yylineno, yytext);
}

// Main function to start the analyzer
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

    /* preparar tabela de símbolos */
    //SymbolTable *table = NULL;
   // initialize_symbol_table(&table);
    
    // 💡 Salva o ponteiro para o escopo RAIZ (Nível 0).
   // SymbolTable *table_root = table; 
    
    // 'table' passa a apontar para o escopo interno/atual (Nível 1)
   // create_new_scope(&table); 

    /* PARSE */
    // Assumindo que 'root' é uma variável global que recebe o nó raiz da AST
    yyparse(); 
    printAST(root, 0);
    fclose(yyin);

    /* Se houve erro sintático, liberar tudo e encerrar */
    if (error) {
        if (root) {
            freeAST(root);
            root = NULL;
        }
        // 🛑 Usa a raiz para destruir todos os escopos.
       /* if (table_root) { 
            destroy_symbol_table(table_root);
            table_root = NULL;
        }*/
        fprintf(stderr, "Falha: foram encontrados erros sintáticos.\n");
        return 1;
    }

    /* Sem erros sintáticos → executar análise semântica */
    // Note: analyze_semantic deve usar e restaurar os escopos corretamente.
    //analyze_semantic(root, table); 

    /* Liberar recursos SEMPRE */
    // 🌳 Libera a Árvore Sintática Abstrata
    if (root) {
        freeAST(root);
        root = NULL;
    }

    // 📚 Libera a Tabela de Símbolos, usando o ponteiro RAIZ.
   /* if (table_root) {
        destroy_symbol_table(table_root);
        table_root = NULL;
    }*/

    /* Resultado final */
    if (error) {
        fprintf(stderr,
                "Sucesso: análise foi concluída, mas foram encontrados erros semânticos.\n");
        return 1;
    }

    printf("Sucesso: análise concluída com sucesso.\n");
    return 0;
}
