%{
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
%}

%union {
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
}

%token PUBLIC
%token STATIC
%token VOID
%token MAIN
%token CLASS
%token EXTENDS
%token RETURN
%token TYPE_INT
%token TYPE_BOOLEAN
%token IF
%token ELSE
%token WHILE
%token PRINT_LINE
%token THIS
%token <token> LITERAL_BOOLEAN
%token NEW
%token LENGTH
%token STRING
%token OP_LOGICAL_AND

%token <token> IDENTIFIER
%token <token> LITERAL_INTEGER

%left OP_LOGICAL_AND
%nonassoc '<'
%left '+' '-' '*'
%right '='
%right '!'
%left '[' ']'
%left '(' ')'
%left '{' '}'
%left ','
%left '.'

%type <ast> E
%type <stmt> Statement
%type <stmt_list> StatementList
%type <node_list> ArgumentList
%type <method_decl> MainClass
%type <str> Type
%type <parameter_list> ParameterList
%type <method_list> MethodList
%type <method_decl> Method
%type <var_decl> Var
%type <var_list> VarList
%type <class_decl> ClassDecl
%type <class_list> ClassList

%start Program

%%
VarList
    : Var { $$ = new SLinkedList<VarDecl*>($1, nullptr); }
    | VarList Var { $$ = new SLinkedList<VarDecl*>($2, $1); }
    ;


Var
    : Type IDENTIFIER ';' { $$ = new VarDecl(*($1), $2->text); }
    ;


MethodList
    : Method { $$ = new SLinkedList<MethodDeclStatement*>($1, nullptr); }
    | MethodList Method { $$ = new SLinkedList<MethodDeclStatement*>($2, $1); }
    ;


Method
    : PUBLIC Type IDENTIFIER '(' ')' '{' StatementList RETURN E ';' '}'{
        $$ = new MethodDeclStatement(yylineno, $3->text, vector<ParameterDecl*>(), vector<VarDecl*>(),
            new BlockStatement(yylineno, singly_linked_list_to_vector($7)), $9, *($2));
    }
    | PUBLIC Type IDENTIFIER '(' ')' '{' RETURN E ';' '}'{
        $$ = new MethodDeclStatement(yylineno, $3->text, vector<ParameterDecl*>(), vector<VarDecl*>(),
            new BlockStatement(yylineno, vector<Statement*>()), $8, *($2));
    }
    | PUBLIC Type IDENTIFIER '(' ParameterList ')' '{' StatementList RETURN E ';' '}'{
        $$ = new MethodDeclStatement(yylineno, $3->text, singly_linked_list_to_vector($5), vector<VarDecl*>(),
            new BlockStatement(yylineno, singly_linked_list_to_vector($8)), $10, *($2));
    }
    | PUBLIC Type IDENTIFIER '(' ParameterList ')' '{' RETURN E ';' '}'{
        $$ = new MethodDeclStatement(yylineno, $3->text, singly_linked_list_to_vector($5), vector<VarDecl*>(),
            new BlockStatement(yylineno, vector<Statement*>()), $9, *($2));
    }
    | PUBLIC Type IDENTIFIER '(' ')' '{' VarList StatementList RETURN E ';' '}'{
        $$ = new MethodDeclStatement(yylineno, $3->text, vector<ParameterDecl*>(),
            singly_linked_list_to_vector($7),
            new BlockStatement(yylineno, singly_linked_list_to_vector($8)), $10, *($2));
    }
    | PUBLIC Type IDENTIFIER '(' ')' '{' VarList RETURN E ';' '}'{
        $$ = new MethodDeclStatement(yylineno, $3->text, vector<ParameterDecl*>(),
            singly_linked_list_to_vector($7), new BlockStatement(yylineno, vector<Statement*>()), $9, *($2));
    }
    | PUBLIC Type IDENTIFIER '(' ParameterList ')' '{' VarList StatementList RETURN E ';' '}'{
        $$ = new MethodDeclStatement(yylineno, $3->text,
            singly_linked_list_to_vector($5), singly_linked_list_to_vector($8),
            new BlockStatement(yylineno, singly_linked_list_to_vector($9)), $11, *($2));
    }
    | PUBLIC Type IDENTIFIER '(' ParameterList ')' '{' VarList RETURN E ';' '}' {
        $$ = new MethodDeclStatement(yylineno, $3->text,
            singly_linked_list_to_vector($5), singly_linked_list_to_vector($8),
            new BlockStatement(yylineno, vector<Statement*>()), $10, *($2));
    }
    ;


MainClass
    : CLASS IDENTIFIER '{'
        PUBLIC STATIC VOID MAIN '(' STRING '[' ']' IDENTIFIER ')' '{' StatementList '}' '}' {
            $$ = new MethodDeclStatement(yylineno, "main", vector<ParameterDecl*>(), vector<VarDecl*>(),
                                            new BlockStatement(yylineno, singly_linked_list_to_vector($15)),
                                            new ConstantExpression(yylineno, NodeType::INTEGER, "0"), "void");
        }
    ;


Program
    : MainClass {
        program = new Program($1, Table<string, ClassDeclStatement*>());
    }
    | MainClass ClassList {
        program = new Program($1, singly_linked_list_to_table($2));
    }
    ;


ClassList
    : ClassDecl { $$ = new SLinkedList<ClassDeclStatement*>($1, nullptr); }
    | ClassList ClassDecl { $$ = new SLinkedList<ClassDeclStatement*>($2, $1); }
    ;

ClassDecl
    : CLASS IDENTIFIER '{' VarList MethodList '}' {
        $$ = new ClassDeclStatement(yylineno, $2->text, optional<string>(),
            singly_linked_list_to_table($4), singly_linked_list_to_table($5));
    }
    | CLASS IDENTIFIER '{' MethodList '}' {
        $$ = new ClassDeclStatement(yylineno, $2->text, optional<string>(),
            Table<string, FieldDecl*>(), singly_linked_list_to_table($4));
    }
    | CLASS IDENTIFIER '{' VarList '}' {
        $$ = new ClassDeclStatement(yylineno, $2->text, optional<string>(),
            singly_linked_list_to_table($4), Table<string, MethodDeclStatement*>());
    }
    | CLASS IDENTIFIER IDENTIFIER '{' '}' {
        $$ = new ClassDeclStatement(yylineno, $2->text, optional<string>(),
            Table<string, VarDecl*>(), Table<string, MethodDeclStatement*>());
    }
    | CLASS IDENTIFIER EXTENDS IDENTIFIER '{' VarList MethodList '}' {
        $$ = new ClassDeclStatement(yylineno, $2->text, $4->text,
            singly_linked_list_to_table($6), singly_linked_list_to_table($7));
    }
    | CLASS IDENTIFIER EXTENDS IDENTIFIER '{' MethodList '}' {
        $$ = new ClassDeclStatement(yylineno, $2->text, $4->text,
            Table<string, FieldDecl*>(), singly_linked_list_to_table($6));
    }
    | CLASS IDENTIFIER EXTENDS IDENTIFIER '{' VarList '}' {
        $$ = new ClassDeclStatement(yylineno, $2->text, optional<string>(),
            singly_linked_list_to_table($6), Table<string, MethodDeclStatement*>());
    }
    | CLASS IDENTIFIER EXTENDS IDENTIFIER IDENTIFIER '{' '}' {
        $$ = new ClassDeclStatement(yylineno, $2->text, $4->text,
            Table<string, VarDecl*>(), Table<string, MethodDeclStatement*>());
    }
    ;

ParameterList:
    Type IDENTIFIER {
        $$ = new SLinkedList<ParameterDecl*>(new ParameterDecl(*($1), $2->text), nullptr);
    }
    | ParameterList ',' Type IDENTIFIER {
        $$ = new SLinkedList<ParameterDecl*>(new ParameterDecl(*($3), $4->text), $1);
    }
    ;


Statement
    : '{' '}' { $$ = new BlockStatement(yylineno, vector<Statement*>()); }
    | '{' StatementList '}' { $$ = new BlockStatement(yylineno, singly_linked_list_to_vector($2)); }
    | IF '(' E ')' Statement ELSE Statement { $$ = new IfStatement(yylineno, $3, $5, $7); }
    | WHILE '(' E ')' Statement { $$ = new WhileStatement(yylineno, $3, $5); }
    | PRINT_LINE '(' E ')' ';' { $$ = new PrintLineStatement(yylineno, $3); }
    | IDENTIFIER '=' E ';' { $$ = new AssignStatement(yylineno, new IdentifierExpression(yylineno, $1->text), $3); }
    | IDENTIFIER '[' E ']' '=' E ';' {
        $$ = new IndexAssignStatement(yylineno, new IdentifierExpression(yylineno, $1->text), $3, $6);
    }
    ;


StatementList
    : Statement { $$ = new SLinkedList<Statement*>($1, nullptr); }
    | StatementList Statement { $$ = new SLinkedList<Statement*>($2, $1); }
    ;


ArgumentList:
    E { $$ = new SLinkedList<Expression*>($1, nullptr); }
    | ArgumentList ',' E { $$ = new SLinkedList<Expression*>($3, $1); }
    ;

E
    : E OP_LOGICAL_AND E { $$ = new BinaryExpression(yylineno, NodeType::LOGICAL_AND, $1, $3); }
    | E '<' E { view_ast($1); view_ast($3); $$ = new BinaryExpression(yylineno, NodeType::LESS_THAN, $1, $3); }
    | E '+' E { $$ = new BinaryExpression(yylineno, NodeType::ADD, $1, $3); }
    | E '-' E { $$ = new BinaryExpression(yylineno, NodeType::SUBTRACT, $1, $3); }
    | E '*' E { $$ = new BinaryExpression(yylineno, NodeType::MULTIPLY, $1, $3); }
    | E '[' E ']' { $$ = new IndexExpression(yylineno, $1, $3); }
    | E '.' LENGTH { view_ast($1); $$ = new UnaryExpression(yylineno, NodeType::ARRAY_LENGTH, $1); }
    | E '.' IDENTIFIER '(' ')' { $$ = new MethodCallExpression(yylineno, $1, $3->text, vector<Expression*>()); }
    | E '.' IDENTIFIER '(' ArgumentList ')' {
        $$ = new MethodCallExpression(yylineno, $1, $3->text, singly_linked_list_to_vector($5));
    }
    | LITERAL_INTEGER { $$ = new ConstantExpression(yylineno, NodeType::INTEGER, $1->text); }
    | LITERAL_BOOLEAN { $$ = new ConstantExpression(yylineno, NodeType::BOOLEAN, $1->text); }
    | IDENTIFIER { $$ = new IdentifierExpression(yylineno, $1->text); }
    | THIS { $$ = new ThisExpression(yylineno); }
    | NEW TYPE_INT '[' E ']' { $$ = new NewIntArrayExpression(yylineno, $4); }
    | NEW IDENTIFIER '(' ')' { $$ = new NewExpression(yylineno, $2->text); }
    | '!' E { $$ = new UnaryExpression(yylineno, NodeType::NOT, $2); }
    | '(' E ')' { $$ = $2; }
    ;


Type
    : TYPE_INT '[' ']' { $$ = new string("int[]"); }
    | TYPE_BOOLEAN { $$ = new string("boolean"); }
    | TYPE_INT { $$ = new string("int"); }
    | IDENTIFIER { $$ = new string($1->text); }
%%

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
