/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "parse.y"

	#pragma warning(disable:4996)
	#define YYSTYPE TOKEN
	#include <stdio.h>
	#include <stdlib.h>
	#include <ctype.h>
	#include "token.h"
	#include "symtab.h"
	#include "utils.h"

	extern int lineCount;
	extern int curLevel;					/* current block level */
	extern int blocknumber;       			/* Totle number of blocks */
	extern int outLevel[MAXBLOCKS];			/* out layer */
	extern int blockoffs[MAXBLOCKS];  		/* Storage offsets for each block */
	extern int basicsizes[5];			
	extern int lineCount;					/* line count */

	TOKEN parseResult;

/* Line 371 of yacc.c  */
#line 89 "parse.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parse.tab.h".  */
#ifndef YY_YY_PARSE_TAB_H_INCLUDED
# define YY_YY_PARSE_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     INTEGER = 259,
     REAL = 260,
     CHAR = 261,
     STRING = 262,
     LP = 263,
     RP = 264,
     LB = 265,
     RB = 266,
     DOTDOT = 267,
     COMMA = 268,
     COLON = 269,
     SEMI = 270,
     DOT = 271,
     PLUS = 272,
     MINUS = 273,
     MUL = 274,
     LT = 275,
     LE = 276,
     EQ = 277,
     NE = 278,
     GT = 279,
     GE = 280,
     ASSIGN = 281,
     AND = 282,
     OR = 283,
     NOT = 284,
     DIV = 285,
     REAL_DIV = 286,
     MOD = 287,
     ARRAY = 288,
     BEGIN_ = 289,
     CASE = 290,
     CONST = 291,
     DO = 292,
     DOWNTO = 293,
     ELSE = 294,
     END = 295,
     FOR = 296,
     FUNCTION = 297,
     GOTO = 298,
     IF = 299,
     OF = 300,
     PROCEDURE = 301,
     PROGRAM = 302,
     READ = 303,
     RECORD = 304,
     REPEAT = 305,
     THEN = 306,
     TO = 307,
     TYPE = 308,
     UNTIL = 309,
     VAR = 310,
     WHILE = 311,
     SYS_CON = 312,
     SYS_FUNCT = 313,
     SYS_PROC = 314,
     SYS_TYPE = 315
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSE_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 215 "parse.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   335

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNRULES -- Number of states.  */
#define YYNSTATES  259

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   315

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    11,    14,    17,    23,    24,    27,
      28,    34,    39,    41,    43,    45,    47,    49,    52,    53,
      56,    58,    63,    65,    67,    69,    71,    73,    77,    81,
      85,    92,    96,    99,   101,   106,   110,   112,   115,   116,
     119,   121,   126,   129,   132,   134,   136,   137,   142,   143,
     150,   155,   156,   161,   165,   166,   170,   172,   176,   180,
     183,   185,   187,   191,   195,   196,   200,   202,   204,   206,
     208,   210,   212,   214,   216,   218,   220,   224,   231,   237,
     239,   244,   246,   251,   256,   262,   265,   266,   271,   276,
     285,   287,   289,   295,   298,   300,   305,   310,   313,   317,
     319,   323,   327,   331,   335,   339,   343,   345,   349,   353,
     357,   359,   363,   367,   371,   375,   379,   381,   383,   388,
     390,   395,   397,   401,   404,   407,   412,   416,   420
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      62,     0,    -1,    63,    64,    16,    -1,    47,     3,    15,
      -1,    66,    96,    -1,    66,    96,    -1,    67,    68,    71,
      81,    84,    -1,    -1,    36,    69,    -1,    -1,    69,     3,
      22,    70,    15,    -1,     3,    22,    70,    15,    -1,     4,
      -1,     5,    -1,     6,    -1,     7,    -1,    57,    -1,    53,
      72,    -1,    -1,    72,    73,    -1,    73,    -1,     3,    22,
      74,    15,    -1,    75,    -1,    76,    -1,    77,    -1,    60,
      -1,     3,    -1,     8,    80,     9,    -1,    70,    12,    70,
      -1,     3,    12,     3,    -1,    33,    10,    75,    11,    45,
      74,    -1,    49,    78,    40,    -1,    78,    79,    -1,    79,
      -1,    80,    14,    74,    15,    -1,    80,    13,     3,    -1,
       3,    -1,    55,    82,    -1,    -1,    82,    83,    -1,    83,
      -1,    80,    14,    74,    15,    -1,    84,    85,    -1,    84,
      88,    -1,    85,    -1,    88,    -1,    -1,    86,    15,    65,
      15,    -1,    -1,    42,    87,     3,    91,    14,    75,    -1,
      89,    15,    65,    15,    -1,    -1,    46,    90,     3,    91,
      -1,     8,    92,     9,    -1,    -1,    92,    15,    93,    -1,
      93,    -1,    94,    14,    75,    -1,    95,    14,    75,    -1,
      55,    80,    -1,    80,    -1,    97,    -1,    34,    98,    40,
      -1,    98,    99,    15,    -1,    -1,     4,    14,   100,    -1,
     100,    -1,   101,    -1,   102,    -1,    97,    -1,   103,    -1,
     105,    -1,   106,    -1,   107,    -1,   109,    -1,   112,    -1,
       3,    26,   114,    -1,     3,    10,   114,    11,    26,   114,
      -1,     3,    16,     3,    26,   114,    -1,     3,    -1,     3,
       8,   118,     9,    -1,    59,    -1,    59,     8,   113,     9,
      -1,    48,     8,   117,     9,    -1,    44,   114,    51,    99,
     104,    -1,    39,    99,    -1,    -1,    50,    98,    54,   114,
      -1,    56,   114,    37,    99,    -1,    41,     3,    26,   114,
     108,   114,    37,    99,    -1,    52,    -1,    38,    -1,    35,
     114,    45,   110,    40,    -1,   110,   111,    -1,   111,    -1,
      70,    14,    99,    15,    -1,     3,    14,    99,    15,    -1,
      43,     4,    -1,   113,    13,   114,    -1,   114,    -1,   114,
      25,   115,    -1,   114,    24,   115,    -1,   114,    21,   115,
      -1,   114,    20,   115,    -1,   114,    22,   115,    -1,   114,
      23,   115,    -1,   115,    -1,   115,    17,   116,    -1,   115,
      18,   116,    -1,   115,    28,   116,    -1,   116,    -1,   116,
      19,   117,    -1,   116,    30,   117,    -1,   116,    31,   117,
      -1,   116,    32,   117,    -1,   116,    27,   117,    -1,   117,
      -1,     3,    -1,     3,     8,   118,     9,    -1,    58,    -1,
      58,     8,   118,     9,    -1,    70,    -1,     8,   114,     9,
      -1,    29,   117,    -1,    18,   117,    -1,     3,    10,   114,
      11,    -1,     3,    16,     3,    -1,   118,    13,   114,    -1,
     114,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    39,    39,    41,    43,    45,    47,    49,    52,    53,
      55,    56,    58,    59,    60,    61,    62,    65,    66,    68,
      69,    71,    73,    74,    75,    77,    78,    79,    80,    81,
      84,    86,    88,    89,    91,    93,    94,    97,    98,   100,
     101,   103,   106,   107,   108,   109,   110,   112,   114,   114,
     116,   118,   118,   120,   121,   123,   124,   126,   127,   129,
     131,   134,   136,   138,   139,   141,   142,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   154,   155,   156,   158,
     159,   160,   161,   162,   164,   166,   167,   169,   171,   173,
     175,   176,   178,   180,   181,   183,   184,   186,   188,   189,
     191,   192,   193,   194,   195,   196,   197,   199,   200,   201,
     202,   204,   205,   206,   207,   208,   209,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   222,   223
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTEGER", "REAL", "CHAR",
  "STRING", "LP", "RP", "LB", "RB", "DOTDOT", "COMMA", "COLON", "SEMI",
  "DOT", "PLUS", "MINUS", "MUL", "LT", "LE", "EQ", "NE", "GT", "GE",
  "ASSIGN", "AND", "OR", "NOT", "DIV", "REAL_DIV", "MOD", "ARRAY",
  "BEGIN_", "CASE", "CONST", "DO", "DOWNTO", "ELSE", "END", "FOR",
  "FUNCTION", "GOTO", "IF", "OF", "PROCEDURE", "PROGRAM", "READ", "RECORD",
  "REPEAT", "THEN", "TO", "TYPE", "UNTIL", "VAR", "WHILE", "SYS_CON",
  "SYS_FUNCT", "SYS_PROC", "SYS_TYPE", "$accept", "program",
  "program_head", "routine", "sub_routine", "routine_head", "label_part",
  "const_part", "const_expr_list", "const_value", "type_part",
  "type_decl_list", "type_definition", "type_decl", "simple_type_decl",
  "array_type_decl", "record_type_decl", "field_decl_list", "field_decl",
  "id_list", "var_part", "var_decl_list", "var_decl", "routine_part",
  "function_decl", "function_head", "$@1", "procedure_decl",
  "procedure_head", "@2", "parameters", "para_decl_list", "para_type_list",
  "var_para_list", "val_para_list", "routine_body", "compound_stmt",
  "stmt_list", "stmt", "non_label_stmt", "assign_stmt", "proc_stmt",
  "if_stmt", "else_clause", "repeat_stmt", "while_stmt", "for_stmt",
  "direction", "case_stmt", "case_expr_list", "case_expr", "goto_stmt",
  "expression_list", "expression", "expr", "term", "factor", "args_list", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    63,    64,    65,    66,    67,    68,    68,
      69,    69,    70,    70,    70,    70,    70,    71,    71,    72,
      72,    73,    74,    74,    74,    75,    75,    75,    75,    75,
      76,    77,    78,    78,    79,    80,    80,    81,    81,    82,
      82,    83,    84,    84,    84,    84,    84,    85,    87,    86,
      88,    90,    89,    91,    91,    92,    92,    93,    93,    94,
      95,    96,    97,    98,    98,    99,    99,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   101,   101,   101,   102,
     102,   102,   102,   102,   103,   104,   104,   105,   106,   107,
     108,   108,   109,   110,   110,   111,   111,   112,   113,   113,
     114,   114,   114,   114,   114,   114,   114,   115,   115,   115,
     115,   116,   116,   116,   116,   116,   116,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   118,   118
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     2,     2,     5,     0,     2,     0,
       5,     4,     1,     1,     1,     1,     1,     2,     0,     2,
       1,     4,     1,     1,     1,     1,     1,     3,     3,     3,
       6,     3,     2,     1,     4,     3,     1,     2,     0,     2,
       1,     4,     2,     2,     1,     1,     0,     4,     0,     6,
       4,     0,     4,     3,     0,     3,     1,     3,     3,     2,
       1,     1,     3,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     6,     5,     1,
       4,     1,     4,     4,     5,     2,     0,     4,     4,     8,
       1,     1,     5,     2,     1,     4,     4,     2,     3,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     3,
       1,     3,     3,     3,     3,     3,     1,     1,     4,     1,
       4,     1,     3,     2,     2,     4,     3,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     7,     0,     1,     0,     0,     9,     3,
       2,    64,     4,    61,     0,    18,     0,     0,     8,     0,
      38,    79,     0,     0,    62,     0,     0,     0,     0,    64,
       0,    81,    69,     0,    66,    67,    68,    70,    71,    72,
      73,    74,    75,     0,     0,     0,    17,    20,     0,    46,
       0,     0,     0,     0,     0,   117,    12,    13,    14,    15,
       0,     0,     0,    16,   119,   121,     0,   106,   110,   116,
       0,    97,     0,     0,     0,     0,     0,    63,     0,     0,
       0,    19,    36,     0,    37,    40,    48,    51,     6,    44,
       0,    45,     0,   128,     0,     0,     0,    76,    65,     0,
       0,     0,     0,   124,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    99,    11,     0,
      26,     0,     0,     0,    25,     0,     0,    22,    23,    24,
       0,     0,    39,     0,     0,    42,    43,     7,     7,    80,
       0,     0,     0,     0,     0,   126,   122,     0,   103,   102,
     104,   105,   101,   100,     0,     0,     0,    94,   107,   108,
     109,   111,   115,   112,   113,   114,     0,    86,    83,    87,
      88,    82,     0,    10,     0,     0,     0,     0,    33,     0,
       0,    21,    35,     0,    54,    54,     0,     0,     0,   127,
       0,    78,   118,   125,   120,     0,     0,    92,    93,    91,
      90,     0,     0,    84,    98,    29,    27,     0,    31,    32,
       0,    28,    41,     0,     0,    52,    47,     5,    50,    77,
       0,     0,     0,    85,     0,     0,     0,    60,     0,    56,
       0,     0,     0,    96,    95,     0,     0,    34,    59,    53,
       0,     0,     0,    49,    89,    30,    55,    57,    58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,   196,   197,     8,    15,    18,    65,
      20,    46,    47,   136,   137,   138,   139,   187,   188,    83,
      49,    84,    85,    88,    89,    90,   143,    91,    92,   144,
     224,   238,   239,   240,   241,    12,    32,    16,    33,    34,
      35,    36,    37,   213,    38,    39,    40,   211,    41,   166,
     167,    42,   126,    93,    67,    68,    69,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -179
static const yytype_int16 yypact[] =
{
     -30,    30,    35,  -179,    34,  -179,    54,    22,    55,  -179,
    -179,  -179,  -179,  -179,    90,    61,    98,    87,   122,   132,
      75,    32,   123,   237,  -179,   152,   156,   237,   154,  -179,
     237,   160,  -179,   149,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,    56,   148,   150,   132,  -179,   170,    25,
     237,   237,   172,   237,   180,   118,  -179,  -179,  -179,  -179,
     237,   237,   237,  -179,   168,  -179,   236,    88,    80,  -179,
     155,  -179,   226,   237,   115,   247,   237,  -179,   165,    56,
       8,  -179,  -179,    64,   170,  -179,  -179,  -179,    25,  -179,
     167,  -179,   177,   296,    77,   289,   169,   296,  -179,   237,
     237,   175,   283,  -179,  -179,   237,   237,   237,   237,   237,
     237,   237,    47,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   163,   184,   237,   163,    83,   296,  -179,   179,
     188,   170,   186,   170,  -179,   189,   190,  -179,  -179,  -179,
     207,     8,  -179,   209,   214,  -179,  -179,  -179,  -179,  -179,
     237,   192,   237,   108,   304,  -179,  -179,   111,    88,    88,
      88,    88,    88,    88,   206,   211,    40,  -179,    80,    80,
      80,  -179,  -179,  -179,  -179,  -179,   164,   187,  -179,   296,
    -179,  -179,   237,  -179,   228,   127,    15,    26,  -179,   131,
      56,  -179,  -179,   212,   221,   221,   217,    22,   218,   296,
     237,   296,  -179,  -179,  -179,   163,   163,  -179,  -179,  -179,
    -179,   237,   163,  -179,   296,  -179,  -179,   223,  -179,  -179,
       8,  -179,  -179,    21,   238,  -179,  -179,  -179,  -179,   296,
     220,   222,   265,  -179,   193,   239,   170,   240,    16,  -179,
     248,   249,    15,  -179,  -179,   163,     8,  -179,   240,  -179,
      21,    15,    15,  -179,  -179,  -179,  -179,  -179,  -179
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -179,  -179,  -179,  -179,   116,   262,  -179,  -179,  -179,   -43,
    -179,  -179,   227,  -131,  -178,  -179,  -179,  -179,    89,  -128,
    -179,  -179,   191,  -179,   194,  -179,  -179,   195,  -179,  -179,
      79,  -179,    28,  -179,  -179,    82,    -6,   251,  -118,   242,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
     125,  -179,  -179,   -21,   224,    38,   -35,   -71
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      78,    13,    66,   185,   177,   189,    72,   180,   217,    75,
     193,   130,    56,    57,    58,    59,   131,     1,   130,    56,
      57,    58,    59,   131,    82,   249,   103,   104,   153,    82,
      95,   250,    97,     4,   157,     5,   129,   135,   123,   102,
      50,   132,    51,   164,    56,    57,    58,    59,    52,     9,
     164,    56,    57,    58,    59,   127,    11,   133,    53,   189,
      56,    57,    58,    59,   253,    63,   218,    86,   134,   165,
      10,    87,    63,   257,   258,   134,   236,   140,   141,   154,
     207,   171,   172,   173,   174,   175,   149,   230,   231,   235,
     150,    14,   181,    17,   233,   237,   182,    63,   135,   116,
     176,    21,    22,   179,    63,   113,   114,   117,   248,    43,
     118,   119,   120,    63,    19,   255,   115,   202,    21,    22,
     204,   150,   237,   165,   150,    44,    99,   254,   100,   199,
      48,   201,    11,    23,   101,    45,   216,    54,    24,    25,
     140,    26,    27,   135,   140,   220,    28,   221,    29,    11,
      23,   168,   169,   170,    30,    70,    25,    31,    26,    27,
      71,   214,    73,    28,    77,    29,    21,    22,    76,   124,
      79,    30,    80,    82,    31,    96,   105,   135,   155,   229,
     128,   121,   147,    21,   106,   107,   108,   109,   110,   111,
     232,    13,   148,   178,   183,   152,   186,    11,    23,   135,
     184,   190,   209,   135,    25,   191,    26,    27,   135,   135,
     192,    28,   194,    29,    11,    23,   210,   195,   200,    30,
     205,    25,    31,    26,    27,   206,   212,   222,    28,   223,
      29,   215,   226,   228,   234,   243,    30,   244,   246,    31,
      55,    56,    57,    58,    59,    60,   106,   107,   108,   109,
     110,   111,   242,   140,   247,    61,   106,   107,   108,   109,
     110,   111,   251,   252,   198,     7,    62,   106,   107,   108,
     109,   110,   111,    81,   225,   142,   219,   122,   256,   227,
      74,   112,   145,   146,   125,   106,   107,   108,   109,   110,
     111,   208,   156,     0,    63,    64,    98,     0,     0,     0,
     151,     0,   245,   106,   107,   108,   109,   110,   111,   106,
     107,   108,   109,   110,   111,   203,   106,   107,   108,   109,
     110,   111,     0,     0,   106,   107,   108,   109,   110,   111,
     158,   159,   160,   161,   162,   163
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-179)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      43,     7,    23,   131,   122,   133,    27,   125,   186,    30,
     141,     3,     4,     5,     6,     7,     8,    47,     3,     4,
       5,     6,     7,     8,     3,     9,    61,    62,    99,     3,
      51,    15,    53,     3,   105,     0,    79,    80,    73,    60,
       8,    33,    10,     3,     4,     5,     6,     7,    16,    15,
       3,     4,     5,     6,     7,    76,    34,    49,    26,   187,
       4,     5,     6,     7,   242,    57,    40,    42,    60,   112,
      16,    46,    57,   251,   252,    60,    55,    13,    14,   100,
      40,   116,   117,   118,   119,   120,     9,   205,   206,   220,
      13,    36,     9,     3,   212,   223,    13,    57,   141,    19,
     121,     3,     4,   124,    57,    17,    18,    27,   236,    22,
      30,    31,    32,    57,    53,   246,    28,     9,     3,     4,
       9,    13,   250,   166,    13,     3,     8,   245,    10,   150,
      55,   152,    34,    35,    16,     3,     9,    14,    40,    41,
      13,    43,    44,   186,    13,    14,    48,   190,    50,    34,
      35,   113,   114,   115,    56,     3,    41,    59,    43,    44,
       4,   182,     8,    48,    15,    50,     3,     4,     8,    54,
      22,    56,    22,     3,    59,     3,     8,   220,     3,   200,
      15,    26,    15,     3,    20,    21,    22,    23,    24,    25,
     211,   197,    15,     9,    15,    26,    10,    34,    35,   242,
      12,    12,    38,   246,    41,    15,    43,    44,   251,   252,
       3,    48,     3,    50,    34,    35,    52,     3,    26,    56,
      14,    41,    59,    43,    44,    14,    39,    15,    48,     8,
      50,     3,    15,    15,    11,    15,    56,    15,    45,    59,
       3,     4,     5,     6,     7,     8,    20,    21,    22,    23,
      24,    25,    14,    13,    15,    18,    20,    21,    22,    23,
      24,    25,    14,    14,   148,     3,    29,    20,    21,    22,
      23,    24,    25,    46,   195,    84,   187,    51,   250,   197,
      29,    45,    88,    88,    37,    20,    21,    22,    23,    24,
      25,   166,     9,    -1,    57,    58,    54,    -1,    -1,    -1,
      11,    -1,    37,    20,    21,    22,    23,    24,    25,    20,
      21,    22,    23,    24,    25,    11,    20,    21,    22,    23,
      24,    25,    -1,    -1,    20,    21,    22,    23,    24,    25,
     106,   107,   108,   109,   110,   111
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    47,    62,    63,     3,     0,    64,    66,    67,    15,
      16,    34,    96,    97,    36,    68,    98,     3,    69,    53,
      71,     3,     4,    35,    40,    41,    43,    44,    48,    50,
      56,    59,    97,    99,   100,   101,   102,   103,   105,   106,
     107,   109,   112,    22,     3,     3,    72,    73,    55,    81,
       8,    10,    16,    26,    14,     3,     4,     5,     6,     7,
       8,    18,    29,    57,    58,    70,   114,   115,   116,   117,
       3,     4,   114,     8,    98,   114,     8,    15,    70,    22,
      22,    73,     3,    80,    82,    83,    42,    46,    84,    85,
      86,    88,    89,   114,   118,   114,     3,   114,   100,     8,
      10,    16,   114,   117,   117,     8,    20,    21,    22,    23,
      24,    25,    45,    17,    18,    28,    19,    27,    30,    31,
      32,    26,    51,   117,    54,    37,   113,   114,    15,    70,
       3,     8,    33,    49,    60,    70,    74,    75,    76,    77,
      13,    14,    83,    87,    90,    85,    88,    15,    15,     9,
      13,    11,    26,   118,   114,     3,     9,   118,   115,   115,
     115,   115,   115,   115,     3,    70,   110,   111,   116,   116,
     116,   117,   117,   117,   117,   117,   114,    99,     9,   114,
      99,     9,    13,    15,    12,    80,    10,    78,    79,    80,
      12,    15,     3,    74,     3,     3,    65,    66,    65,   114,
      26,   114,     9,    11,     9,    14,    14,    40,   111,    38,
      52,   108,    39,   104,   114,     3,     9,    75,    40,    79,
      14,    70,    15,     8,    91,    91,    15,    96,    15,   114,
      99,    99,   114,    99,    11,    74,    55,    80,    92,    93,
      94,    95,    14,    15,    15,    37,    45,    15,    80,     9,
      15,    14,    14,    75,    99,    74,    93,    75,    75
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 39 "parse.y"
    { parseResult = makeProgram((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 41 "parse.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 43 "parse.y"
    { (yyval) = link((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 45 "parse.y"
    { (yyval) = link((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 47 "parse.y"
    { (yyval) = endDecl((yyvsp[(5) - (5)])); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 52 "parse.y"
    { (yyval) = NULL;}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 55 "parse.y"
    { regConst((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 56 "parse.y"
    { regConst((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 58 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 59 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 60 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 61 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 62 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 65 "parse.y"
    { (yyval) = NULL; }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 68 "parse.y"
    { (yyval) = NULL; }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 69 "parse.y"
    { (yyval) = NULL; }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 71 "parse.y"
    { regType((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 73 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 74 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 75 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 77 "parse.y"
    { (yyval) = getType((yyvsp[(1) - (1)])); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 78 "parse.y"
    { (yyval) = getType((yyvsp[(1) - (1)])); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 79 "parse.y"
    { (yyval) = makeEnum((yyvsp[(2) - (3)])); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 80 "parse.y"
    { (yyval) = makeSubrange((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 81 "parse.y"
    { (yyval) = makeSubrange((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 84 "parse.y"
    { (yyval) = makeArray((yyvsp[(3) - (6)]), (yyvsp[(6) - (6)])); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 86 "parse.y"
    { (yyval) = makeRecord((yyvsp[(2) - (3)])); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 88 "parse.y"
    { (yyval) = link((yyvsp[(1) - (2)]),(yyvsp[(2) - (2)])); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 89 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 91 "parse.y"
    { (yyval) = makeField((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 93 "parse.y"
    { (yyval) = link((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));  }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 94 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 97 "parse.y"
    { (yyval) = NULL; }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 98 "parse.y"
    { (yyval) = NULL; }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 100 "parse.y"
    { (yyval) = NULL; }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 101 "parse.y"
    { (yyval) = NULL; }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 103 "parse.y"
    { regVar((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), 2);	 }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 106 "parse.y"
    { (yyval) = link((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 107 "parse.y"
    { (yyval) = link((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 108 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 109 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 110 "parse.y"
    { (yyval) = NULL; }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 112 "parse.y"
    { (yyval) = makeFunDcl((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 114 "parse.y"
    { upLevel(); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 114 "parse.y"
    { (yyval) = makeFunHead((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)])); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 116 "parse.y"
    { (yyval) = makeFunDcl((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 118 "parse.y"
    { upLevel(); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 118 "parse.y"
    { (yyval) = makeFunHead((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), NULL);}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 120 "parse.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 121 "parse.y"
    { (yyval) = NULL; }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 123 "parse.y"
    { (yyval) = link((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 124 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 126 "parse.y"
    { (yyval) = (yyvsp[(1) - (3)]); regVar((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 1); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 127 "parse.y"
    { (yyval) = (yyvsp[(1) - (3)]); regVar((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), 0); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 129 "parse.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 131 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 134 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 136 "parse.y"
    { (yyval) = makeBeginStmt((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 138 "parse.y"
    { (yyval) = link((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 139 "parse.y"
    { (yyval) = NULL; }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 141 "parse.y"
    { (yyval) = makeLabel((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 142 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 144 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 145 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 146 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 147 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 148 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 149 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 150 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 151 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 152 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 154 "parse.y"
    { (yyval) = makeAssign((yyvsp[(2) - (3)]), findId((yyvsp[(1) - (3)])), (yyvsp[(3) - (3)])); }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 155 "parse.y"
    { (yyval) = makeAssign((yyvsp[(5) - (6)]), arrayRef((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)])), (yyvsp[(6) - (6)])); }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 156 "parse.y"
    { (yyval) = makeAssign((yyvsp[(4) - (5)]), makeRecordMember((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)])), (yyvsp[(5) - (5)])); }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 158 "parse.y"
    { (yyval) = makeFuncall((yyvsp[(1) - (1)]), NULL, NULL); }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 159 "parse.y"
    { (yyval) = makeFuncall((yyvsp[(2) - (4)]), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 160 "parse.y"
    { (yyval) = NULL; }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 161 "parse.y"
    { (yyval) = makeFuncall((yyvsp[(2) - (4)]), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 162 "parse.y"
    { (yyval) = makeFuncall((yyvsp[(2) - (4)]), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 164 "parse.y"
    { (yyval) = makeIf((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])); }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 166 "parse.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 169 "parse.y"
    { (yyval) = makeRepeat((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)])); }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 171 "parse.y"
    { (yyval) = makeWhile((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)])); }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 173 "parse.y"
    { (yyval) = makeFor((yyvsp[(1) - (8)]), makeAssign((yyvsp[(3) - (8)]), findId((yyvsp[(2) - (8)])), (yyvsp[(4) - (8)])), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]), (yyvsp[(8) - (8)])); }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 175 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 176 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 178 "parse.y"
    { (yyval) = makeCase((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 180 "parse.y"
    { (yyval) = link((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 181 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 183 "parse.y"
    { (yyval) = makeSignalCase((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 184 "parse.y"
    { (yyval) = makeSignalCase(findId((yyvsp[(1) - (4)])), (yyvsp[(3) - (4)])); }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 186 "parse.y"
    { (yyval) = makeGoto((yyvsp[(2) - (2)])); }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 188 "parse.y"
    { (yyval) = link((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 189 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 191 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 192 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 193 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 194 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 195 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 196 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 197 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 199 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 200 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 201 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 202 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 204 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 205 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 206 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 207 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 208 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 209 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 211 "parse.y"
    { (yyval) = findId((yyvsp[(1) - (1)])); }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 212 "parse.y"
    { (yyval) = makeFuncall((yyvsp[(2) - (4)]), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 213 "parse.y"
    { (yyval) = NULL; }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 214 "parse.y"
    { (yyval) = makeFuncall((yyvsp[(2) - (4)]), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 215 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 216 "parse.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 217 "parse.y"
    { (yyval) = makeUnaryOp((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 218 "parse.y"
    { (yyval) = makeUnaryOp((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 219 "parse.y"
    { (yyval) = arrayRef((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 220 "parse.y"
    { (yyval) = makeRecordMember((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 222 "parse.y"
    { (yyval) = link((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 223 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;


/* Line 1792 of yacc.c  */
#line 2399 "parse.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 224 "parse.y"

