/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 119 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
