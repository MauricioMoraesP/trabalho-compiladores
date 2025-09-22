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

#ifndef YY_YY_SYNTAX_HEADER_TAB_H_INCLUDED
# define YY_YY_SYNTAX_HEADER_TAB_H_INCLUDED
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
    ID_TOKEN = 258,                /* ID_TOKEN  */
    TSTRING_LITERAL = 259,         /* TSTRING_LITERAL  */
    INT_CONST = 260,               /* INT_CONST  */
    TCHAR_CONST = 261,             /* TCHAR_CONST  */
    TPROGRAM = 262,                /* TPROGRAM  */
    TCAR = 263,                    /* TCAR  */
    TINT = 264,                    /* TINT  */
    TRETURN = 265,                 /* TRETURN  */
    TREAD = 266,                   /* TREAD  */
    TWRITE = 267,                  /* TWRITE  */
    TNEWLINE = 268,                /* TNEWLINE  */
    TIF = 269,                     /* TIF  */
    TTHEN = 270,                   /* TTHEN  */
    TELSE = 271,                   /* TELSE  */
    TWHILE = 272,                  /* TWHILE  */
    TEXECUTE = 273,                /* TEXECUTE  */
    TAND = 274,                    /* TAND  */
    TPLUS = 275,                   /* TPLUS  */
    TMINUS = 276,                  /* TMINUS  */
    TTIMES = 277,                  /* TTIMES  */
    TDIVIDE = 278,                 /* TDIVIDE  */
    TASSIGN = 279,                 /* TASSIGN  */
    TEQ = 280,                     /* TEQ  */
    TNEQ = 281,                    /* TNEQ  */
    TLT = 282,                     /* TLT  */
    TLEQ = 283,                    /* TLEQ  */
    TGT = 284,                     /* TGT  */
    TGEQ = 285,                    /* TGEQ  */
    TSEMICOLON = 286,              /* TSEMICOLON  */
    TLPAREN = 287,                 /* TLPAREN  */
    TRPAREN = 288,                 /* TRPAREN  */
    TLBRACE = 289,                 /* TLBRACE  */
    TRBRACE = 290,                 /* TRBRACE  */
    TLBRACKET = 291,               /* TLBRACKET  */
    TRBRACKET = 292,               /* TRBRACKET  */
    TCOMMA = 293,                  /* TCOMMA  */
    TOR = 294,                     /* TOR  */
    TNEG = 295                     /* TNEG  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "syntax/header.y"

    int ival;
    char cval;
    char *str;

#line 110 "syntax/header.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SYNTAX_HEADER_TAB_H_INCLUDED  */
