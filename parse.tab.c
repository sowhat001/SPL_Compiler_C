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
#define YYLAST   351

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  126
/* YYNRULES -- Number of states.  */
#define YYNSTATES  257

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
     119,   121,   126,   129,   132,   134,   136,   137,   142,   148,
     153,   157,   161,   162,   166,   168,   172,   176,   179,   181,
     183,   187,   191,   192,   196,   198,   200,   202,   204,   206,
     208,   210,   212,   214,   216,   220,   227,   233,   235,   240,
     242,   247,   252,   258,   261,   262,   267,   272,   281,   283,
     285,   291,   294,   296,   301,   306,   309,   313,   315,   319,
     323,   327,   331,   335,   339,   341,   345,   349,   353,   355,
     359,   363,   367,   371,   375,   377,   379,   384,   386,   391,
     393,   397,   400,   403,   408,   412,   416
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      62,     0,    -1,    63,    64,    16,    -1,    47,     3,    15,
      -1,    66,    94,    -1,    66,    94,    -1,    67,    68,    71,
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
      87,    -1,    85,    -1,    87,    -1,    -1,    86,    15,    65,
      15,    -1,    42,     3,    89,    14,    75,    -1,    88,    15,
      65,    15,    -1,    46,     3,    89,    -1,     8,    90,     9,
      -1,    -1,    90,    15,    91,    -1,    91,    -1,    92,    14,
      75,    -1,    93,    14,    75,    -1,    55,    80,    -1,    80,
      -1,    95,    -1,    34,    96,    40,    -1,    96,    97,    15,
      -1,    -1,     4,    14,    98,    -1,    98,    -1,    99,    -1,
     100,    -1,    95,    -1,   101,    -1,   103,    -1,   104,    -1,
     105,    -1,   107,    -1,   110,    -1,     3,    26,   112,    -1,
       3,    10,   112,    11,    26,   112,    -1,     3,    16,     3,
      26,   112,    -1,     3,    -1,     3,     8,   116,     9,    -1,
      59,    -1,    59,     8,   111,     9,    -1,    48,     8,   115,
       9,    -1,    44,   112,    51,    97,   102,    -1,    39,    97,
      -1,    -1,    50,    96,    54,   112,    -1,    56,   112,    37,
      97,    -1,    41,     3,    26,   112,   106,   112,    37,    97,
      -1,    52,    -1,    38,    -1,    35,   112,    45,   108,    40,
      -1,   108,   109,    -1,   109,    -1,    70,    14,    97,    15,
      -1,     3,    14,    97,    15,    -1,    43,     4,    -1,   111,
      13,   112,    -1,   112,    -1,   112,    25,   113,    -1,   112,
      24,   113,    -1,   112,    21,   113,    -1,   112,    20,   113,
      -1,   112,    22,   113,    -1,   112,    23,   113,    -1,   113,
      -1,   113,    17,   114,    -1,   113,    18,   114,    -1,   113,
      28,   114,    -1,   114,    -1,   114,    19,   115,    -1,   114,
      30,   115,    -1,   114,    31,   115,    -1,   114,    32,   115,
      -1,   114,    27,   115,    -1,   115,    -1,     3,    -1,     3,
       8,   116,     9,    -1,    58,    -1,    58,     8,   116,     9,
      -1,    70,    -1,     8,   112,     9,    -1,    29,   115,    -1,
      18,   115,    -1,     3,    10,   112,    11,    -1,     3,    16,
       3,    -1,   116,    13,   112,    -1,   112,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    39,    39,    41,    43,    45,    47,    49,    52,    53,
      55,    56,    58,    59,    60,    61,    62,    65,    66,    68,
      69,    71,    73,    74,    75,    77,    78,    79,    80,    81,
      84,    86,    88,    89,    91,    93,    94,    97,    98,   100,
     101,   103,   106,   107,   108,   109,   110,   112,   114,   116,
     118,   120,   121,   123,   124,   126,   127,   129,   131,   134,
     136,   138,   139,   141,   142,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   154,   155,   156,   158,   159,   160,
     161,   162,   164,   166,   167,   169,   171,   173,   175,   176,
     178,   180,   181,   183,   184,   186,   188,   189,   191,   192,
     193,   194,   195,   196,   197,   199,   200,   201,   202,   204,
     205,   206,   207,   208,   209,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   222,   223
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
  "function_decl", "function_head", "procedure_decl", "procedure_head",
  "parameters", "para_decl_list", "para_type_list", "var_para_list",
  "val_para_list", "routine_body", "compound_stmt", "stmt_list", "stmt",
  "non_label_stmt", "assign_stmt", "proc_stmt", "if_stmt", "else_clause",
  "repeat_stmt", "while_stmt", "for_stmt", "direction", "case_stmt",
  "case_expr_list", "case_expr", "goto_stmt", "expression_list",
  "expression", "expr", "term", "factor", "args_list", YY_NULL
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
      82,    83,    84,    84,    84,    84,    84,    85,    86,    87,
      88,    89,    89,    90,    90,    91,    91,    92,    93,    94,
      95,    96,    96,    97,    97,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    99,    99,    99,   100,   100,   100,
     100,   100,   101,   102,   102,   103,   104,   105,   106,   106,
     107,   108,   108,   109,   109,   110,   111,   111,   112,   112,
     112,   112,   112,   112,   112,   113,   113,   113,   113,   114,
     114,   114,   114,   114,   114,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   116,   116
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     2,     2,     5,     0,     2,     0,
       5,     4,     1,     1,     1,     1,     1,     2,     0,     2,
       1,     4,     1,     1,     1,     1,     1,     3,     3,     3,
       6,     3,     2,     1,     4,     3,     1,     2,     0,     2,
       1,     4,     2,     2,     1,     1,     0,     4,     5,     4,
       3,     3,     0,     3,     1,     3,     3,     2,     1,     1,
       3,     3,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     6,     5,     1,     4,     1,
       4,     4,     5,     2,     0,     4,     4,     8,     1,     1,
       5,     2,     1,     4,     4,     2,     3,     1,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     3,     1,     3,
       3,     3,     3,     3,     1,     1,     4,     1,     4,     1,
       3,     2,     2,     4,     3,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     7,     0,     1,     0,     0,     9,     3,
       2,    62,     4,    59,     0,    18,     0,     0,     8,     0,
      38,    77,     0,     0,    60,     0,     0,     0,     0,    62,
       0,    79,    67,     0,    64,    65,    66,    68,    69,    70,
      71,    72,    73,     0,     0,     0,    17,    20,     0,    46,
       0,     0,     0,     0,     0,   115,    12,    13,    14,    15,
       0,     0,     0,    16,   117,   119,     0,   104,   108,   114,
       0,    95,     0,     0,     0,     0,     0,    61,     0,     0,
       0,    19,    36,     0,    37,    40,     0,     0,     6,    44,
       0,    45,     0,   126,     0,     0,     0,    74,    63,     0,
       0,     0,     0,   122,   121,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97,    11,     0,
      26,     0,     0,     0,    25,     0,     0,    22,    23,    24,
       0,     0,    39,    52,    52,    42,    43,     7,     7,    78,
       0,     0,     0,     0,     0,   124,   120,     0,   101,   100,
     102,   103,    99,    98,     0,     0,     0,    92,   105,   106,
     107,   109,   113,   110,   111,   112,     0,    84,    81,    85,
      86,    80,     0,    10,     0,     0,     0,     0,    33,     0,
       0,    21,    35,     0,     0,     0,    50,     0,     0,     0,
     125,     0,    76,   116,   123,   118,     0,     0,    90,    91,
      89,    88,     0,     0,    82,    96,    29,    27,     0,    31,
      32,     0,    28,    41,     0,    58,     0,    54,     0,     0,
       0,    47,     5,    49,    75,     0,     0,     0,    83,     0,
       0,    57,    51,     0,     0,     0,    48,    94,    93,     0,
       0,    34,    53,    55,    56,    87,    30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,   197,   198,     8,    15,    18,    65,
      20,    46,    47,   136,   137,   138,   139,   187,   188,    83,
      49,    84,    85,    88,    89,    90,    91,    92,   195,   226,
     227,   228,   229,    12,    32,    16,    33,    34,    35,    36,
      37,   214,    38,    39,    40,   212,    41,   166,   167,    42,
     126,    93,    67,    68,    69,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -183
static const yytype_int16 yypact[] =
{
     -16,    30,    46,  -183,    34,  -183,    48,    32,    31,  -183,
    -183,  -183,  -183,  -183,    75,    39,   114,    62,    96,   118,
      73,    85,   119,   253,  -183,   143,   146,   253,   144,  -183,
     253,   148,  -183,   136,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,   102,   138,   141,   118,  -183,   165,   -35,
     253,   253,   166,   253,   196,    72,  -183,  -183,  -183,  -183,
     253,   253,   253,  -183,   163,  -183,   252,     0,    95,  -183,
     149,  -183,   242,   253,   162,   263,   253,  -183,   157,   102,
      53,  -183,  -183,   128,   165,  -183,   171,   173,   -35,  -183,
     164,  -183,   169,   312,    25,   305,   151,   312,  -183,   253,
     253,   178,   299,  -183,  -183,   253,   253,   253,   253,   253,
     253,   253,    19,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   179,   176,   253,   179,    68,   312,  -183,   174,
     181,   165,   180,   165,  -183,   182,   183,  -183,  -183,  -183,
     185,    53,  -183,   187,   187,  -183,  -183,  -183,  -183,  -183,
     253,   160,   253,   106,   320,  -183,  -183,   107,     0,     0,
       0,     0,     0,     0,   186,   190,    47,  -183,    95,    95,
      95,  -183,  -183,  -183,  -183,  -183,   115,   170,  -183,   312,
    -183,  -183,   253,  -183,   205,   121,    37,     7,  -183,   131,
     102,  -183,  -183,   200,    10,   197,  -183,   202,    32,   204,
     312,   253,   312,  -183,  -183,  -183,   179,   179,  -183,  -183,
    -183,  -183,   253,   179,  -183,   312,  -183,  -183,   213,  -183,
    -183,    53,  -183,  -183,   165,   212,    20,  -183,   214,   218,
      37,  -183,  -183,  -183,   312,   211,   219,   281,  -183,   188,
     221,   212,  -183,    10,    37,    37,  -183,  -183,  -183,   179,
      53,  -183,  -183,  -183,  -183,  -183,  -183
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -183,  -183,  -183,  -183,    93,   239,  -183,  -183,  -183,   -43,
    -183,  -183,   199,  -138,  -182,  -183,  -183,  -183,    56,  -119,
    -183,  -183,   167,  -183,   159,  -183,   161,  -183,   104,  -183,
      11,  -183,  -183,    52,    -6,   224,  -117,   215,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,   112,  -183,
    -183,   -21,   240,   -94,   -46,   -14
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      78,    13,    66,   193,   218,   177,    72,    86,   180,    75,
      82,    87,   185,    82,   189,   103,   104,   113,   114,   168,
     169,   170,   164,    56,    57,    58,    59,   123,   115,   242,
      95,     1,    97,     4,   149,   243,   129,   135,   150,   102,
     130,    56,    57,    58,    59,   131,     5,   219,   246,     9,
     164,    56,    57,    58,    59,   127,   130,    56,    57,    58,
      59,   131,   253,   254,    10,   224,    11,    14,   189,   165,
     171,   172,   173,   174,   175,   225,    63,   181,    17,   154,
      99,   182,   100,   240,    43,   153,   132,   208,   101,   235,
     236,   157,    19,    50,    63,    51,   238,   134,   135,    44,
     176,    52,   133,   179,    63,   241,    56,    57,    58,    59,
      63,    53,   256,   134,   116,   203,   205,    21,    22,   150,
     150,    45,   117,   165,   225,   118,   119,   120,    48,   200,
     217,   202,   255,    54,   140,   106,   107,   108,   109,   110,
     111,   140,   141,   135,   140,   221,    70,   222,    11,    23,
      71,    77,    73,   210,    24,    25,    76,    26,    27,    63,
      79,   215,    28,    80,    29,    21,    22,   211,    82,    96,
      30,   105,   128,    31,   143,   121,   144,   152,   135,   147,
     234,   155,    21,    22,   148,   178,   201,   135,   192,   183,
     186,   237,    13,   184,   190,   194,    11,    23,   191,    21,
     206,   135,   135,    25,   207,    26,    27,   135,   216,   213,
      28,   230,    29,    11,    23,   223,   124,   231,    30,   233,
      25,    31,    26,    27,   239,   140,   247,    28,   244,    29,
      11,    23,   245,   250,   248,    30,   251,    25,    31,    26,
      27,   199,     7,   220,    28,    81,    29,   145,   196,   146,
     232,   142,    30,    74,   252,    31,    55,    56,    57,    58,
      59,    60,   106,   107,   108,   109,   110,   111,     0,    98,
       0,    61,   106,   107,   108,   109,   110,   111,   209,     0,
       0,     0,    62,   106,   107,   108,   109,   110,   111,     0,
       0,     0,     0,   122,     0,     0,     0,   112,     0,     0,
     125,   106,   107,   108,   109,   110,   111,     0,   156,     0,
      63,    64,     0,     0,     0,     0,   151,     0,   249,   106,
     107,   108,   109,   110,   111,   106,   107,   108,   109,   110,
     111,   204,   106,   107,   108,   109,   110,   111,     0,     0,
     106,   107,   108,   109,   110,   111,   158,   159,   160,   161,
     162,   163
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-183)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      43,     7,    23,   141,   186,   122,    27,    42,   125,    30,
       3,    46,   131,     3,   133,    61,    62,    17,    18,   113,
     114,   115,     3,     4,     5,     6,     7,    73,    28,     9,
      51,    47,    53,     3,     9,    15,    79,    80,    13,    60,
       3,     4,     5,     6,     7,     8,     0,    40,   230,    15,
       3,     4,     5,     6,     7,    76,     3,     4,     5,     6,
       7,     8,   244,   245,    16,    55,    34,    36,   187,   112,
     116,   117,   118,   119,   120,   194,    57,     9,     3,   100,
       8,    13,    10,   221,    22,    99,    33,    40,    16,   206,
     207,   105,    53,     8,    57,    10,   213,    60,   141,     3,
     121,    16,    49,   124,    57,   224,     4,     5,     6,     7,
      57,    26,   250,    60,    19,     9,     9,     3,     4,    13,
      13,     3,    27,   166,   243,    30,    31,    32,    55,   150,
       9,   152,   249,    14,    13,    20,    21,    22,    23,    24,
      25,    13,    14,   186,    13,    14,     3,   190,    34,    35,
       4,    15,     8,    38,    40,    41,     8,    43,    44,    57,
      22,   182,    48,    22,    50,     3,     4,    52,     3,     3,
      56,     8,    15,    59,     3,    26,     3,    26,   221,    15,
     201,     3,     3,     4,    15,     9,    26,   230,     3,    15,
      10,   212,   198,    12,    12,     8,    34,    35,    15,     3,
      14,   244,   245,    41,    14,    43,    44,   250,     3,    39,
      48,    14,    50,    34,    35,    15,    54,    15,    56,    15,
      41,    59,    43,    44,    11,    13,    15,    48,    14,    50,
      34,    35,    14,    45,    15,    56,    15,    41,    59,    43,
      44,   148,     3,   187,    48,    46,    50,    88,   144,    88,
     198,    84,    56,    29,   243,    59,     3,     4,     5,     6,
       7,     8,    20,    21,    22,    23,    24,    25,    -1,    54,
      -1,    18,    20,    21,    22,    23,    24,    25,   166,    -1,
      -1,    -1,    29,    20,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    45,    -1,    -1,
      37,    20,    21,    22,    23,    24,    25,    -1,     9,    -1,
      57,    58,    -1,    -1,    -1,    -1,    11,    -1,    37,    20,
      21,    22,    23,    24,    25,    20,    21,    22,    23,    24,
      25,    11,    20,    21,    22,    23,    24,    25,    -1,    -1,
      20,    21,    22,    23,    24,    25,   106,   107,   108,   109,
     110,   111
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    47,    62,    63,     3,     0,    64,    66,    67,    15,
      16,    34,    94,    95,    36,    68,    96,     3,    69,    53,
      71,     3,     4,    35,    40,    41,    43,    44,    48,    50,
      56,    59,    95,    97,    98,    99,   100,   101,   103,   104,
     105,   107,   110,    22,     3,     3,    72,    73,    55,    81,
       8,    10,    16,    26,    14,     3,     4,     5,     6,     7,
       8,    18,    29,    57,    58,    70,   112,   113,   114,   115,
       3,     4,   112,     8,    96,   112,     8,    15,    70,    22,
      22,    73,     3,    80,    82,    83,    42,    46,    84,    85,
      86,    87,    88,   112,   116,   112,     3,   112,    98,     8,
      10,    16,   112,   115,   115,     8,    20,    21,    22,    23,
      24,    25,    45,    17,    18,    28,    19,    27,    30,    31,
      32,    26,    51,   115,    54,    37,   111,   112,    15,    70,
       3,     8,    33,    49,    60,    70,    74,    75,    76,    77,
      13,    14,    83,     3,     3,    85,    87,    15,    15,     9,
      13,    11,    26,   116,   112,     3,     9,   116,   113,   113,
     113,   113,   113,   113,     3,    70,   108,   109,   114,   114,
     114,   115,   115,   115,   115,   115,   112,    97,     9,   112,
      97,     9,    13,    15,    12,    80,    10,    78,    79,    80,
      12,    15,     3,    74,     8,    89,    89,    65,    66,    65,
     112,    26,   112,     9,    11,     9,    14,    14,    40,   109,
      38,    52,   106,    39,   102,   112,     3,     9,    75,    40,
      79,    14,    70,    15,    55,    80,    90,    91,    92,    93,
      14,    15,    94,    15,   112,    97,    97,   112,    97,    11,
      74,    80,     9,    15,    14,    14,    75,    15,    15,    37,
      45,    15,    91,    75,    75,    97,    74
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
    { blocknumber++; outLevel[blocknumber]=curLevel; curLevel = blocknumber; curLevel=outLevel[curLevel]; (yyval) = makeRecord((yyvsp[(2) - (3)])); }
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
    { regVar((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));	 }
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

  case 51:
/* Line 1792 of yacc.c  */
#line 120 "parse.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 121 "parse.y"
    { (yyval) = NULL; }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 123 "parse.y"
    { (yyval) = link((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 124 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 134 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 136 "parse.y"
    { (yyval) = makeBeginStmt((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 138 "parse.y"
    { (yyval) = link((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 139 "parse.y"
    { (yyval) = NULL; }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 141 "parse.y"
    { (yyval) = makeLabel((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 142 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 144 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 145 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 146 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 147 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 148 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 149 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 150 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 151 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 152 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 154 "parse.y"
    { (yyval) = makeAssign((yyvsp[(2) - (3)]), findId((yyvsp[(1) - (3)])), (yyvsp[(3) - (3)])); }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 155 "parse.y"
    { (yyval) = makeAssign((yyvsp[(5) - (6)]), arrayRef((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)])), (yyvsp[(6) - (6)])); }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 156 "parse.y"
    { (yyval) = makeAssign((yyvsp[(4) - (5)]), makeRecordMember((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)])), (yyvsp[(5) - (5)])); }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 158 "parse.y"
    { (yyval) = makeFuncall((yyvsp[(1) - (1)]), NULL, NULL); }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 159 "parse.y"
    { (yyval) = makeFuncall((yyvsp[(2) - (4)]), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 160 "parse.y"
    { (yyval) = NULL; }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 161 "parse.y"
    { (yyval) = makeFuncall((yyvsp[(2) - (4)]), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 162 "parse.y"
    { (yyval) = makeFuncall((yyvsp[(2) - (4)]), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 164 "parse.y"
    { (yyval) = makeIf((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])); }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 166 "parse.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 169 "parse.y"
    { (yyval) = makeRepeat((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)])); }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 171 "parse.y"
    { (yyval) = makeWhile((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)])); }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 173 "parse.y"
    { (yyval) = makeFor((yyvsp[(1) - (8)]), makeAssign((yyvsp[(3) - (8)]), (yyvsp[(2) - (8)]), (yyvsp[(4) - (8)])), (yyvsp[(5) - (8)]), (yyvsp[(6) - (8)]), (yyvsp[(7) - (8)]), (yyvsp[(8) - (8)])); }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 175 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 176 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 178 "parse.y"
    { (yyval) = makeCase((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)])); }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 180 "parse.y"
    { (yyval) = link((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 181 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 183 "parse.y"
    { (yyval) = makeSignalCase((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 184 "parse.y"
    { (yyval) = makeSignalCase(findId((yyvsp[(1) - (4)])), (yyvsp[(3) - (4)])); }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 186 "parse.y"
    { (yyval) = makeGoto((yyvsp[(2) - (2)])); }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 188 "parse.y"
    { (yyval) = link((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 189 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 191 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 192 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 193 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 194 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 195 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 196 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 197 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 199 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 200 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 201 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 202 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 204 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 205 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 206 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 207 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 208 "parse.y"
    { (yyval) = makeBinOp((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 209 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 211 "parse.y"
    { (yyval) = findId((yyvsp[(1) - (1)])); }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 212 "parse.y"
    { (yyval) = makeFuncall((yyvsp[(2) - (4)]), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 213 "parse.y"
    { (yyval) = NULL; }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 214 "parse.y"
    { (yyval) = makeFuncall((yyvsp[(2) - (4)]), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 215 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 216 "parse.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 217 "parse.y"
    { (yyval) = makeUnaryOp((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 218 "parse.y"
    { (yyval) = makeUnaryOp((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 219 "parse.y"
    { (yyval) = arrayRef((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 220 "parse.y"
    { (yyval) = makeRecordMember((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 222 "parse.y"
    { (yyval) = link((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 223 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;


/* Line 1792 of yacc.c  */
#line 2342 "parse.tab.c"
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

