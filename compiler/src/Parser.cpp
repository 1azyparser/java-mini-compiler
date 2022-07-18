/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

#include "Token.h"
#include "Node.h"
#include "TypeChecker.h"
#include "Compiler.h"
#include "JsonVisitor.h"
#include <cxxopts.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

extern int yylineno;

int yylex();
void yyerror(string s);
void program_to_json(Program* program);
void view_ast(Expression* exp);

Program* program;

#line 96 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PUBLIC = 258,
    STATIC = 259,
    VOID = 260,
    MAIN = 261,
    CLASS = 262,
    EXTENDS = 263,
    RETURN = 264,
    TYPE_INT = 265,
    TYPE_BOOLEAN = 266,
    IF = 267,
    ELSE = 268,
    WHILE = 269,
    PRINT_LINE = 270,
    THIS = 271,
    LITERAL_BOOLEAN = 272,
    NEW = 273,
    LENGTH = 274,
    STRING = 275,
    OP_LOGICAL_AND = 276,
    IDENTIFIER = 277,
    LITERAL_INTEGER = 278
  };
#endif
/* Tokens.  */
#define PUBLIC 258
#define STATIC 259
#define VOID 260
#define MAIN 261
#define CLASS 262
#define EXTENDS 263
#define RETURN 264
#define TYPE_INT 265
#define TYPE_BOOLEAN 266
#define IF 267
#define ELSE 268
#define WHILE 269
#define PRINT_LINE 270
#define THIS 271
#define LITERAL_BOOLEAN 272
#define NEW 273
#define LENGTH 274
#define STRING 275
#define OP_LOGICAL_AND 276
#define IDENTIFIER 277
#define LITERAL_INTEGER 278

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "src/parser.y"

    Token* token;
    Expression* ast;
    Statement* stmt;
    SLinkedList<Statement*>* stmt_list;
    SLinkedList<Expression*>* node_list;
    SLinkedList<ParameterDecl*>* parameter_list;
    MethodDeclStatement* method_decl;
    SLinkedList<MethodDeclStatement*>* method_list;
    VarDecl* var_decl;
    SLinkedList<VarDecl*>* var_list;
    ClassDeclStatement* class_decl;
    SLinkedList<ClassDeclStatement*>* class_list;
    string* str;

#line 210 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   505

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  186

#define YYUNDEFTOK  2
#define YYMAXUTOK   278


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,     2,     2,     2,     2,     2,
      32,    33,    27,    25,    36,    26,    37,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    38,
      24,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    30,     2,    31,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,    35,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    95,    95,    96,   101,   106,   107,   112,   116,   120,
     124,   128,   133,   137,   142,   151,   161,   164,   171,   172,
     176,   180,   184,   188,   192,   196,   200,   204,   211,   214,
     221,   222,   223,   224,   225,   226,   227,   234,   235,   240,
     241,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     256,   257,   258,   259,   260,   261,   262,   263,   268,   269,
     270,   271
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PUBLIC", "STATIC", "VOID", "MAIN",
  "CLASS", "EXTENDS", "RETURN", "TYPE_INT", "TYPE_BOOLEAN", "IF", "ELSE",
  "WHILE", "PRINT_LINE", "THIS", "LITERAL_BOOLEAN", "NEW", "LENGTH",
  "STRING", "OP_LOGICAL_AND", "IDENTIFIER", "LITERAL_INTEGER", "'<'",
  "'+'", "'-'", "'*'", "'='", "'!'", "'['", "']'", "'('", "')'", "'{'",
  "'}'", "','", "'.'", "';'", "$accept", "VarList", "Var", "MethodList",
  "Method", "MainClass", "Program", "ClassList", "ClassDecl",
  "ParameterList", "Statement", "StatementList", "ArgumentList", "E",
  "Type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,    60,    43,    45,    42,    61,    33,
      91,    93,    40,    41,   123,   125,    44,    46,    59
};
# endif

#define YYPACT_NINF (-80)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       8,     3,    13,    39,    12,    56,    13,   -80,   -80,    86,
      65,   -80,    97,    63,    69,    73,   118,     1,    91,    -9,
      98,   -80,   -80,    47,   -80,     9,   -80,   105,   123,   107,
      73,   -80,   109,   116,   -80,   -80,    19,   -80,   -80,   111,
     133,   120,    53,    35,   138,   -80,   -80,   -80,   136,   -80,
     -80,    37,   -80,   176,   141,   -80,   140,    29,   160,   158,
      82,   161,    -9,   -80,   172,   451,   164,   167,   170,    85,
     145,    96,   -80,   128,   110,   179,   173,   -80,   -80,    76,
     -80,   -80,   451,   451,   195,   451,   451,   451,   451,   451,
      85,   -80,   169,   451,   139,   451,   -80,   451,   124,   154,
     -80,   177,   180,   182,     6,   357,   451,   451,   451,   451,
     451,   451,    90,   183,   371,   385,   399,   210,   413,   -80,
     225,   451,   240,   255,   451,   163,   451,   193,   451,   184,
     -80,   452,   468,     6,     6,     6,   421,   -80,   191,   -80,
     193,   193,   186,   -80,   198,   194,   270,   203,   204,   285,
     451,   300,   178,   435,   -80,   -80,   317,   215,   -80,   -80,
     451,   -80,   206,   -80,   -80,   207,   327,   208,   209,   -80,
     -80,    81,   460,   193,   342,   -80,   -80,   218,   -80,   -80,
     -80,   451,   -80,   -80,   -80,   460
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    16,     0,     0,     0,    17,    18,     1,     0,
       0,    19,     0,     0,     0,     0,     0,     0,     0,     0,
      60,    59,    61,     0,     2,     0,     5,     0,     0,     0,
       0,    23,     0,     0,    22,     3,     0,    21,     6,     0,
       0,     0,     0,     0,     0,    58,    20,     4,     0,    27,
      26,     0,    25,     0,     0,    24,     0,     0,     0,     0,
       0,     0,     0,    28,     0,     0,     0,     0,     0,    61,
       0,     0,    37,     0,     0,     0,     0,    53,    51,     0,
      52,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    30,     0,     0,     0,     0,    38,     0,     0,     0,
      29,     0,     0,     0,    56,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,    41,    42,    43,    44,    45,     0,    47,     0,     8,
       0,     0,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    55,    46,     0,     0,    33,    34,
       0,    12,     0,     7,    10,     0,     0,     0,     0,    54,
      48,     0,    39,     0,     0,    11,    14,     0,     9,    15,
      49,     0,    32,    36,    13,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -80,   -19,   -18,   122,    23,   -80,   -80,   -80,   224,   -80,
     -73,   -37,   -80,   -79,    -2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    24,    25,    26,     2,     3,     6,     7,    57,
      72,    73,   171,    84,    27
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      96,    20,    21,   104,   105,    35,   114,   115,   116,   117,
     118,    42,    19,    22,   120,     1,   122,    32,   123,    96,
       5,    96,    19,    29,    35,     4,    96,   131,   132,   133,
     134,   135,   136,    92,    94,    30,   111,    99,    19,     8,
      19,    71,   146,   112,    37,   149,     9,   151,    38,   153,
      19,    58,    96,    35,    46,    98,    19,    20,    21,    38,
      75,   125,    61,    20,    21,    62,    38,   157,   158,    22,
      52,   166,    55,    13,    38,    22,    19,   172,    10,    96,
      35,   174,    34,    20,    21,    17,   102,    14,    50,    12,
     152,    65,    20,    21,    66,    22,    67,    68,   103,    15,
     182,    16,   185,    18,    69,    93,    20,    21,    66,   137,
      67,    68,   138,    88,   180,    89,    70,   181,    69,    97,
      20,    21,    66,    28,    67,    68,    31,    39,    33,    40,
      70,    44,    69,   124,    20,    21,    66,    95,    67,    68,
      66,    41,    67,    68,    70,    36,    69,    45,   121,    47,
      90,    66,    43,    67,    68,    49,    54,    66,    70,    67,
      68,    90,    70,   126,    51,    48,    66,    90,    67,    68,
      53,    59,   150,    70,    60,    66,    90,    67,    68,    70,
      91,    66,    63,    67,    68,    90,    20,    21,    70,    64,
      66,    90,    67,    68,    76,    74,    85,    70,    22,    86,
      90,   100,    87,    70,   119,    66,   101,    67,    68,    56,
     128,   127,    70,   168,   129,    90,   106,   154,   139,   107,
     108,   109,   110,   156,   159,   111,   160,    70,   173,   161,
      11,   106,   112,   113,   107,   108,   109,   110,   163,   164,
     111,   175,   176,   178,   179,     0,   106,   112,   143,   107,
     108,   109,   110,   184,     0,   111,     0,     0,     0,     0,
       0,   106,   112,   145,   107,   108,   109,   110,     0,     0,
     111,     0,     0,     0,     0,     0,   106,   112,   147,   107,
     108,   109,   110,     0,     0,   111,     0,     0,     0,     0,
       0,   106,   112,   148,   107,   108,   109,   110,     0,     0,
     111,     0,     0,     0,     0,     0,   106,   112,   162,   107,
     108,   109,   110,     0,     0,   111,     0,     0,     0,     0,
       0,   106,   112,   165,   107,   108,   109,   110,     0,     0,
     111,     0,     0,    77,    78,    79,     0,   112,   167,    80,
      81,     0,     0,     0,     0,     0,    82,     0,   106,    83,
     170,   107,   108,   109,   110,     0,     0,   111,     0,     0,
       0,     0,     0,   106,   112,   177,   107,   108,   109,   110,
       0,     0,   111,     0,     0,     0,     0,     0,   106,   112,
     183,   107,   108,   109,   110,     0,     0,   111,     0,     0,
     130,     0,   106,     0,   112,   107,   108,   109,   110,     0,
       0,   111,     0,     0,   140,     0,   106,     0,   112,   107,
     108,   109,   110,     0,     0,   111,     0,     0,   141,     0,
     106,     0,   112,   107,   108,   109,   110,     0,     0,   111,
       0,     0,   142,     0,   106,     0,   112,   107,   108,   109,
     110,     0,   106,   111,   144,   107,   108,   109,   110,     0,
     112,   111,   155,     0,     0,     0,   106,     0,   112,   107,
     108,   109,   110,     0,     0,   111,   169,    77,    78,    79,
       0,     0,   112,    80,    81,     0,   107,   108,   109,   110,
      82,   106,   111,    83,   107,   108,   109,   110,     0,   112,
     111,     0,    -1,   108,   109,   110,     0,   112,   111,     0,
       0,     0,     0,     0,     0,   112
};

static const yytype_int16 yycheck[] =
{
      73,    10,    11,    82,    83,    23,    85,    86,    87,    88,
      89,    30,     3,    22,    93,     7,    95,    19,    97,    92,
       7,    94,     3,    22,    42,    22,    99,   106,   107,   108,
     109,   110,   111,    70,    71,    34,    30,    74,     3,     0,
       3,    60,   121,    37,    35,   124,    34,   126,    25,   128,
       3,    53,   125,    71,    35,    74,     3,    10,    11,    36,
      62,    98,    33,    10,    11,    36,    43,   140,   141,    22,
      35,   150,    35,     8,    51,    22,     3,   156,    22,   152,
      98,   160,    35,    10,    11,    22,    10,    22,    35,     3,
     127,     9,    10,    11,    12,    22,    14,    15,    22,    34,
     173,     4,   181,    34,    22,     9,    10,    11,    12,    19,
      14,    15,    22,    28,    33,    30,    34,    36,    22,     9,
      10,    11,    12,     5,    14,    15,    35,    22,    30,     6,
      34,    22,    22,     9,    10,    11,    12,     9,    14,    15,
      12,    34,    14,    15,    34,    23,    22,    31,     9,    38,
      22,    12,    30,    14,    15,    35,    20,    12,    34,    14,
      15,    22,    34,     9,    42,    32,    12,    22,    14,    15,
      32,    30,     9,    34,    34,    12,    22,    14,    15,    34,
      35,    12,    22,    14,    15,    22,    10,    11,    34,    31,
      12,    22,    14,    15,    22,    34,    32,    34,    22,    32,
      22,    22,    32,    34,    35,    12,    33,    14,    15,    33,
      30,    34,    34,    35,    32,    22,    21,    33,    35,    24,
      25,    26,    27,    32,    38,    30,    28,    34,    13,    35,
       6,    21,    37,    38,    24,    25,    26,    27,    35,    35,
      30,    35,    35,    35,    35,    -1,    21,    37,    38,    24,
      25,    26,    27,    35,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    21,    37,    38,    24,    25,    26,    27,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    21,    37,    38,    24,
      25,    26,    27,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    21,    37,    38,    24,    25,    26,    27,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    21,    37,    38,    24,
      25,    26,    27,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    21,    37,    38,    24,    25,    26,    27,    -1,    -1,
      30,    -1,    -1,    16,    17,    18,    -1,    37,    38,    22,
      23,    -1,    -1,    -1,    -1,    -1,    29,    -1,    21,    32,
      33,    24,    25,    26,    27,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    21,    37,    38,    24,    25,    26,    27,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    21,    37,
      38,    24,    25,    26,    27,    -1,    -1,    30,    -1,    -1,
      33,    -1,    21,    -1,    37,    24,    25,    26,    27,    -1,
      -1,    30,    -1,    -1,    33,    -1,    21,    -1,    37,    24,
      25,    26,    27,    -1,    -1,    30,    -1,    -1,    33,    -1,
      21,    -1,    37,    24,    25,    26,    27,    -1,    -1,    30,
      -1,    -1,    33,    -1,    21,    -1,    37,    24,    25,    26,
      27,    -1,    21,    30,    31,    24,    25,    26,    27,    -1,
      37,    30,    31,    -1,    -1,    -1,    21,    -1,    37,    24,
      25,    26,    27,    -1,    -1,    30,    31,    16,    17,    18,
      -1,    -1,    37,    22,    23,    -1,    24,    25,    26,    27,
      29,    21,    30,    32,    24,    25,    26,    27,    -1,    37,
      30,    -1,    24,    25,    26,    27,    -1,    37,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    44,    45,    22,     7,    46,    47,     0,    34,
      22,    47,     3,     8,    22,    34,     4,    22,    34,     3,
      10,    11,    22,    40,    41,    42,    43,    53,     5,    22,
      34,    35,    53,    30,    35,    41,    42,    35,    43,    22,
       6,    34,    40,    42,    22,    31,    35,    38,    32,    35,
      35,    42,    35,    32,    20,    35,    33,    48,    53,    30,
      34,    33,    36,    22,    31,     9,    12,    14,    15,    22,
      34,    40,    49,    50,    34,    53,    22,    16,    17,    18,
      22,    23,    29,    32,    52,    32,    32,    32,    28,    30,
      22,    35,    50,     9,    50,     9,    49,     9,    40,    50,
      22,    33,    10,    22,    52,    52,    21,    24,    25,    26,
      27,    30,    37,    38,    52,    52,    52,    52,    52,    35,
      52,     9,    52,    52,     9,    50,     9,    34,    30,    32,
      33,    52,    52,    52,    52,    52,    52,    19,    22,    35,
      33,    33,    33,    38,    31,    38,    52,    38,    38,    52,
       9,    52,    50,    52,    33,    31,    32,    49,    49,    38,
      28,    35,    38,    35,    35,    38,    52,    38,    35,    31,
      33,    51,    52,    13,    52,    35,    35,    38,    35,    35,
      33,    36,    49,    38,    35,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    40,    41,    42,    42,    43,    43,    43,
      43,    43,    43,    43,    43,    44,    45,    45,    46,    46,
      47,    47,    47,    47,    47,    47,    47,    47,    48,    48,
      49,    49,    49,    49,    49,    49,    49,    50,    50,    51,
      51,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    53,    53,
      53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     3,     1,     2,    11,    10,    12,
      11,    12,    11,    13,    12,    17,     1,     2,     1,     2,
       6,     5,     5,     5,     8,     7,     7,     7,     2,     4,
       2,     3,     7,     5,     5,     4,     7,     1,     2,     1,
       3,     3,     3,     3,     3,     3,     4,     3,     5,     6,
       1,     1,     1,     1,     5,     4,     2,     3,     3,     1,
       1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
  case 2:
#line 95 "src/parser.y"
          { (yyval.var_list) = new SLinkedList<VarDecl*>((yyvsp[0].var_decl), nullptr); }
#line 1558 "y.tab.c"
    break;

  case 3:
#line 96 "src/parser.y"
                  { (yyval.var_list) = new SLinkedList<VarDecl*>((yyvsp[0].var_decl), (yyvsp[-1].var_list)); }
#line 1564 "y.tab.c"
    break;

  case 4:
#line 101 "src/parser.y"
                          { (yyval.var_decl) = new VarDecl(*((yyvsp[-2].str)), (yyvsp[-1].token)->text); }
#line 1570 "y.tab.c"
    break;

  case 5:
#line 106 "src/parser.y"
             { (yyval.method_list) = new SLinkedList<MethodDeclStatement*>((yyvsp[0].method_decl), nullptr); }
#line 1576 "y.tab.c"
    break;

  case 6:
#line 107 "src/parser.y"
                        { (yyval.method_list) = new SLinkedList<MethodDeclStatement*>((yyvsp[0].method_decl), (yyvsp[-1].method_list)); }
#line 1582 "y.tab.c"
    break;

  case 7:
#line 112 "src/parser.y"
                                                                       {
        (yyval.method_decl) = new MethodDeclStatement(yylineno, (yyvsp[-8].token)->text, vector<ParameterDecl*>(), vector<VarDecl*>(),
            new BlockStatement(yylineno, singly_linked_list_to_vector((yyvsp[-4].stmt_list))), (yyvsp[-2].ast), *((yyvsp[-9].str)));
    }
#line 1591 "y.tab.c"
    break;

  case 8:
#line 116 "src/parser.y"
                                                         {
        (yyval.method_decl) = new MethodDeclStatement(yylineno, (yyvsp[-7].token)->text, vector<ParameterDecl*>(), vector<VarDecl*>(),
            new BlockStatement(yylineno, vector<Statement*>()), (yyvsp[-2].ast), *((yyvsp[-8].str)));
    }
#line 1600 "y.tab.c"
    break;

  case 9:
#line 120 "src/parser.y"
                                                                                     {
        (yyval.method_decl) = new MethodDeclStatement(yylineno, (yyvsp[-9].token)->text, singly_linked_list_to_vector((yyvsp[-7].parameter_list)), vector<VarDecl*>(),
            new BlockStatement(yylineno, singly_linked_list_to_vector((yyvsp[-4].stmt_list))), (yyvsp[-2].ast), *((yyvsp[-10].str)));
    }
#line 1609 "y.tab.c"
    break;

  case 10:
#line 124 "src/parser.y"
                                                                       {
        (yyval.method_decl) = new MethodDeclStatement(yylineno, (yyvsp[-8].token)->text, singly_linked_list_to_vector((yyvsp[-6].parameter_list)), vector<VarDecl*>(),
            new BlockStatement(yylineno, vector<Statement*>()), (yyvsp[-2].ast), *((yyvsp[-9].str)));
    }
#line 1618 "y.tab.c"
    break;

  case 11:
#line 128 "src/parser.y"
                                                                               {
        (yyval.method_decl) = new MethodDeclStatement(yylineno, (yyvsp[-9].token)->text, vector<ParameterDecl*>(),
            singly_linked_list_to_vector((yyvsp[-5].var_list)),
            new BlockStatement(yylineno, singly_linked_list_to_vector((yyvsp[-4].stmt_list))), (yyvsp[-2].ast), *((yyvsp[-10].str)));
    }
#line 1628 "y.tab.c"
    break;

  case 12:
#line 133 "src/parser.y"
                                                                 {
        (yyval.method_decl) = new MethodDeclStatement(yylineno, (yyvsp[-8].token)->text, vector<ParameterDecl*>(),
            singly_linked_list_to_vector((yyvsp[-4].var_list)), new BlockStatement(yylineno, vector<Statement*>()), (yyvsp[-2].ast), *((yyvsp[-9].str)));
    }
#line 1637 "y.tab.c"
    break;

  case 13:
#line 137 "src/parser.y"
                                                                                             {
        (yyval.method_decl) = new MethodDeclStatement(yylineno, (yyvsp[-10].token)->text,
            singly_linked_list_to_vector((yyvsp[-8].parameter_list)), singly_linked_list_to_vector((yyvsp[-5].var_list)),
            new BlockStatement(yylineno, singly_linked_list_to_vector((yyvsp[-4].stmt_list))), (yyvsp[-2].ast), *((yyvsp[-11].str)));
    }
#line 1647 "y.tab.c"
    break;

  case 14:
#line 142 "src/parser.y"
                                                                                {
        (yyval.method_decl) = new MethodDeclStatement(yylineno, (yyvsp[-9].token)->text,
            singly_linked_list_to_vector((yyvsp[-7].parameter_list)), singly_linked_list_to_vector((yyvsp[-4].var_list)),
            new BlockStatement(yylineno, vector<Statement*>()), (yyvsp[-2].ast), *((yyvsp[-10].str)));
    }
#line 1657 "y.tab.c"
    break;

  case 15:
#line 152 "src/parser.y"
                                                                                            {
            (yyval.method_decl) = new MethodDeclStatement(yylineno, "main", vector<ParameterDecl*>(), vector<VarDecl*>(),
                                            new BlockStatement(yylineno, singly_linked_list_to_vector((yyvsp[-2].stmt_list))),
                                            new ConstantExpression(yylineno, NodeType::INTEGER, "0"), "void");
        }
#line 1667 "y.tab.c"
    break;

  case 16:
#line 161 "src/parser.y"
                {
        program = new Program((yyvsp[0].method_decl), Table<string, ClassDeclStatement*>());
    }
#line 1675 "y.tab.c"
    break;

  case 17:
#line 164 "src/parser.y"
                          {
        program = new Program((yyvsp[-1].method_decl), singly_linked_list_to_table((yyvsp[0].class_list)));
    }
#line 1683 "y.tab.c"
    break;

  case 18:
#line 171 "src/parser.y"
                { (yyval.class_list) = new SLinkedList<ClassDeclStatement*>((yyvsp[0].class_decl), nullptr); }
#line 1689 "y.tab.c"
    break;

  case 19:
#line 172 "src/parser.y"
                          { (yyval.class_list) = new SLinkedList<ClassDeclStatement*>((yyvsp[0].class_decl), (yyvsp[-1].class_list)); }
#line 1695 "y.tab.c"
    break;

  case 20:
#line 176 "src/parser.y"
                                                  {
        (yyval.class_decl) = new ClassDeclStatement(yylineno, (yyvsp[-4].token)->text, optional<string>(),
            singly_linked_list_to_table((yyvsp[-2].var_list)), singly_linked_list_to_table((yyvsp[-1].method_list)));
    }
#line 1704 "y.tab.c"
    break;

  case 21:
#line 180 "src/parser.y"
                                          {
        (yyval.class_decl) = new ClassDeclStatement(yylineno, (yyvsp[-3].token)->text, optional<string>(),
            Table<string, FieldDecl*>(), singly_linked_list_to_table((yyvsp[-1].method_list)));
    }
#line 1713 "y.tab.c"
    break;

  case 22:
#line 184 "src/parser.y"
                                       {
        (yyval.class_decl) = new ClassDeclStatement(yylineno, (yyvsp[-3].token)->text, optional<string>(),
            singly_linked_list_to_table((yyvsp[-1].var_list)), Table<string, MethodDeclStatement*>());
    }
#line 1722 "y.tab.c"
    break;

  case 23:
#line 188 "src/parser.y"
                                          {
        (yyval.class_decl) = new ClassDeclStatement(yylineno, (yyvsp[-3].token)->text, optional<string>(),
            Table<string, VarDecl*>(), Table<string, MethodDeclStatement*>());
    }
#line 1731 "y.tab.c"
    break;

  case 24:
#line 192 "src/parser.y"
                                                                     {
        (yyval.class_decl) = new ClassDeclStatement(yylineno, (yyvsp[-6].token)->text, (yyvsp[-4].token)->text,
            singly_linked_list_to_table((yyvsp[-2].var_list)), singly_linked_list_to_table((yyvsp[-1].method_list)));
    }
#line 1740 "y.tab.c"
    break;

  case 25:
#line 196 "src/parser.y"
                                                             {
        (yyval.class_decl) = new ClassDeclStatement(yylineno, (yyvsp[-5].token)->text, (yyvsp[-3].token)->text,
            Table<string, FieldDecl*>(), singly_linked_list_to_table((yyvsp[-1].method_list)));
    }
#line 1749 "y.tab.c"
    break;

  case 26:
#line 200 "src/parser.y"
                                                          {
        (yyval.class_decl) = new ClassDeclStatement(yylineno, (yyvsp[-5].token)->text, optional<string>(),
            singly_linked_list_to_table((yyvsp[-1].var_list)), Table<string, MethodDeclStatement*>());
    }
#line 1758 "y.tab.c"
    break;

  case 27:
#line 204 "src/parser.y"
                                                             {
        (yyval.class_decl) = new ClassDeclStatement(yylineno, (yyvsp[-5].token)->text, (yyvsp[-3].token)->text,
            Table<string, VarDecl*>(), Table<string, MethodDeclStatement*>());
    }
#line 1767 "y.tab.c"
    break;

  case 28:
#line 211 "src/parser.y"
                    {
        (yyval.parameter_list) = new SLinkedList<ParameterDecl*>(new ParameterDecl(*((yyvsp[-1].str)), (yyvsp[0].token)->text), nullptr);
    }
#line 1775 "y.tab.c"
    break;

  case 29:
#line 214 "src/parser.y"
                                        {
        (yyval.parameter_list) = new SLinkedList<ParameterDecl*>(new ParameterDecl(*((yyvsp[-1].str)), (yyvsp[0].token)->text), (yyvsp[-3].parameter_list));
    }
#line 1783 "y.tab.c"
    break;

  case 30:
#line 221 "src/parser.y"
              { (yyval.stmt) = new BlockStatement(yylineno, vector<Statement*>()); }
#line 1789 "y.tab.c"
    break;

  case 31:
#line 222 "src/parser.y"
                            { (yyval.stmt) = new BlockStatement(yylineno, singly_linked_list_to_vector((yyvsp[-1].stmt_list))); }
#line 1795 "y.tab.c"
    break;

  case 32:
#line 223 "src/parser.y"
                                            { (yyval.stmt) = new IfStatement(yylineno, (yyvsp[-4].ast), (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 1801 "y.tab.c"
    break;

  case 33:
#line 224 "src/parser.y"
                                { (yyval.stmt) = new WhileStatement(yylineno, (yyvsp[-2].ast), (yyvsp[0].stmt)); }
#line 1807 "y.tab.c"
    break;

  case 34:
#line 225 "src/parser.y"
                               { (yyval.stmt) = new PrintLineStatement(yylineno, (yyvsp[-2].ast)); }
#line 1813 "y.tab.c"
    break;

  case 35:
#line 226 "src/parser.y"
                           { (yyval.stmt) = new AssignStatement(yylineno, new IdentifierExpression(yylineno, (yyvsp[-3].token)->text), (yyvsp[-1].ast)); }
#line 1819 "y.tab.c"
    break;

  case 36:
#line 227 "src/parser.y"
                                     {
        (yyval.stmt) = new IndexAssignStatement(yylineno, new IdentifierExpression(yylineno, (yyvsp[-6].token)->text), (yyvsp[-4].ast), (yyvsp[-1].ast));
    }
#line 1827 "y.tab.c"
    break;

  case 37:
#line 234 "src/parser.y"
                { (yyval.stmt_list) = new SLinkedList<Statement*>((yyvsp[0].stmt), nullptr); }
#line 1833 "y.tab.c"
    break;

  case 38:
#line 235 "src/parser.y"
                              { (yyval.stmt_list) = new SLinkedList<Statement*>((yyvsp[0].stmt), (yyvsp[-1].stmt_list)); }
#line 1839 "y.tab.c"
    break;

  case 39:
#line 240 "src/parser.y"
      { (yyval.node_list) = new SLinkedList<Expression*>((yyvsp[0].ast), nullptr); }
#line 1845 "y.tab.c"
    break;

  case 40:
#line 241 "src/parser.y"
                         { (yyval.node_list) = new SLinkedList<Expression*>((yyvsp[0].ast), (yyvsp[-2].node_list)); }
#line 1851 "y.tab.c"
    break;

  case 41:
#line 245 "src/parser.y"
                         { (yyval.ast) = new BinaryExpression(yylineno, NodeType::LOGICAL_AND, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1857 "y.tab.c"
    break;

  case 42:
#line 246 "src/parser.y"
              { view_ast((yyvsp[-2].ast)); view_ast((yyvsp[0].ast)); (yyval.ast) = new BinaryExpression(yylineno, NodeType::LESS_THAN, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1863 "y.tab.c"
    break;

  case 43:
#line 247 "src/parser.y"
              { (yyval.ast) = new BinaryExpression(yylineno, NodeType::ADD, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1869 "y.tab.c"
    break;

  case 44:
#line 248 "src/parser.y"
              { (yyval.ast) = new BinaryExpression(yylineno, NodeType::SUBTRACT, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1875 "y.tab.c"
    break;

  case 45:
#line 249 "src/parser.y"
              { (yyval.ast) = new BinaryExpression(yylineno, NodeType::MULTIPLY, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1881 "y.tab.c"
    break;

  case 46:
#line 250 "src/parser.y"
                  { (yyval.ast) = new IndexExpression(yylineno, (yyvsp[-3].ast), (yyvsp[-1].ast)); }
#line 1887 "y.tab.c"
    break;

  case 47:
#line 251 "src/parser.y"
                   { view_ast((yyvsp[-2].ast)); (yyval.ast) = new UnaryExpression(yylineno, NodeType::ARRAY_LENGTH, (yyvsp[-2].ast)); }
#line 1893 "y.tab.c"
    break;

  case 48:
#line 252 "src/parser.y"
                               { (yyval.ast) = new MethodCallExpression(yylineno, (yyvsp[-4].ast), (yyvsp[-2].token)->text, vector<Expression*>()); }
#line 1899 "y.tab.c"
    break;

  case 49:
#line 253 "src/parser.y"
                                            {
        (yyval.ast) = new MethodCallExpression(yylineno, (yyvsp[-5].ast), (yyvsp[-3].token)->text, singly_linked_list_to_vector((yyvsp[-1].node_list)));
    }
#line 1907 "y.tab.c"
    break;

  case 50:
#line 256 "src/parser.y"
                      { (yyval.ast) = new ConstantExpression(yylineno, NodeType::INTEGER, (yyvsp[0].token)->text); }
#line 1913 "y.tab.c"
    break;

  case 51:
#line 257 "src/parser.y"
                      { (yyval.ast) = new ConstantExpression(yylineno, NodeType::BOOLEAN, (yyvsp[0].token)->text); }
#line 1919 "y.tab.c"
    break;

  case 52:
#line 258 "src/parser.y"
                 { (yyval.ast) = new IdentifierExpression(yylineno, (yyvsp[0].token)->text); }
#line 1925 "y.tab.c"
    break;

  case 53:
#line 259 "src/parser.y"
           { (yyval.ast) = new ThisExpression(yylineno); }
#line 1931 "y.tab.c"
    break;

  case 54:
#line 260 "src/parser.y"
                             { (yyval.ast) = new NewIntArrayExpression(yylineno, (yyvsp[-1].ast)); }
#line 1937 "y.tab.c"
    break;

  case 55:
#line 261 "src/parser.y"
                             { (yyval.ast) = new NewExpression(yylineno, (yyvsp[-2].token)->text); }
#line 1943 "y.tab.c"
    break;

  case 56:
#line 262 "src/parser.y"
            { (yyval.ast) = new UnaryExpression(yylineno, NodeType::NOT, (yyvsp[0].ast)); }
#line 1949 "y.tab.c"
    break;

  case 57:
#line 263 "src/parser.y"
                { (yyval.ast) = (yyvsp[-1].ast); }
#line 1955 "y.tab.c"
    break;

  case 58:
#line 268 "src/parser.y"
                       { (yyval.str) = new string("int[]"); }
#line 1961 "y.tab.c"
    break;

  case 59:
#line 269 "src/parser.y"
                   { (yyval.str) = new string("boolean"); }
#line 1967 "y.tab.c"
    break;

  case 60:
#line 270 "src/parser.y"
               { (yyval.str) = new string("int"); }
#line 1973 "y.tab.c"
    break;

  case 61:
#line 271 "src/parser.y"
                 { (yyval.str) = new string((yyvsp[0].token)->text); }
#line 1979 "y.tab.c"
    break;


#line 1983 "y.tab.c"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 272 "src/parser.y"


void yyerror(string s) {
    cerr << "line " << yylineno << ": " << s << endl;
}

void program_to_json(Program* program) {
    JsonVisitor json_visitor;
    json json_obj = json_visitor.visit_program(program);
    cout << std::setw(4) << json_obj << endl;
}

void view_ast(Expression* exp) {
    JsonVisitor json_visitor;
    cout << std::setw(4) << json_visitor.visit(exp) << endl;
}

void write_byte_code(string path, const vector<Byte>& bytes) {
    std::ofstream stream(path, std::ofstream::binary);
    stream.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    if (stream.fail()) {
        throw Error(-1, "fail to write all the byte code into a binary file");
    }
}

string parse_args(int argc, char** argv) {
    cxxopts::Options options("minijava compiler", "It compiles minijava program to byte code");
    options.add_options()
            ("o,out", "Output path", cxxopts::value<std::string>())
            ("h,help", "Print usage");
    auto result = options.parse(argc, argv);
    if (result.count("help")) {
      cout << options.help() << endl;
      exit(0);
    } else {
        if (result.count("out")) {
            return result["out"].as<string>();
        } else {
            cout << "output path argument is required" << endl;
            exit(0);
        }
    }
}

int main(int argc, char** argv) {
    string output_path = parse_args(argc, argv);
    yyparse();

    try {
        TypeChecker type_checker(program);
        type_checker.check_program();
        program_to_json(program);
        Compiler compiler(program);
        auto bytes = compiler.compile();
        write_byte_code(output_path, bytes);
    } catch (Error& err) {
        cout << err.msg << endl;
    }
    return 0;
}
