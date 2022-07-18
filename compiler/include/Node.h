#ifndef NODE_H
#define NODE_H
#include "Scope.h"
#include "Table.h"
#include <algorithm>
#include <magic_enum.hpp>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

using std::make_optional;
using std::optional;
using std::string;

enum class NodeType
{
  ADD,
  SUBTRACT,
  MULTIPLY,
  LESS_THAN,
  NOT,
  LOGICAL_AND,
  NEW,
  THIS,
  ARRAY_LENGTH,
  NAME,
  INTEGER,
  BOOLEAN,
  CALL,
  NEW_INTEGER_ARRAY,
  INDEX_ACCESS
};

enum class StatementType
{
  EXPRESSION_STATEMENT,
  IF_STATEMENT,
  WHILE_STATEMENT,
  BLOCK_STATEMENT,
  CLASS_STATEMENT,
  METHOD_STATEMENT,
  PRINT_LINE_STATEMENT,
  ASSIGN_STATEMENT,
  INDEX_ASSIGN_STATEMENT
};

class Statement
{
public:
  virtual int line() const = 0;
  virtual StatementType statement_type() const = 0;
};

class Expression : public Statement
{
public:
  virtual NodeType node_type() const = 0;
  StatementType statement_type() const override
  {
    return StatementType::EXPRESSION_STATEMENT;
  }
};

class BinaryExpression : public Expression
{
public:
  int _line;
  NodeType _node_type;
  Expression *left;
  Expression *right;

  BinaryExpression(int _line, NodeType _node_type, Expression *left,
                   Expression *right)
      : _line{_line}, _node_type{_node_type}, left{left}, right{right} {}
  int line() const override { return _line; }
  NodeType node_type() const override { return _node_type; }
};

class UnaryExpression : public Expression
{
public:
  int _line;
  NodeType _node_type;
  Expression *operand;

  UnaryExpression(int _line, NodeType _node_type, Expression *operand)
      : _line{_line}, _node_type{_node_type}, operand{operand} {}
  int line() const override { return _line; }
  NodeType node_type() const override { return _node_type; }
};

class IndexExpression : public Expression
{
public:
  int _line;
  Expression *array;
  Expression *index;

  IndexExpression(int _line, Expression *array, Expression *index)
      : _line{_line}, array{array}, index{index} {}
  int line() const override { return _line; }
  NodeType node_type() const override { return NodeType::INDEX_ACCESS; }
};

class IdentifierExpression : public Expression
{
public:
  int _line;
  string name;
  string type;

  IdentifierExpression(int _line, string name)
      : _line{_line}, name{name}, type() {}
  int line() const override { return _line; }
  NodeType node_type() const override { return NodeType::NAME; }
};

class ConstantExpression : public Expression
{
public:
  int _line;
  NodeType _node_type;
  string value;

  ConstantExpression(int _line, NodeType _node_type, string value)
      : _line{_line}, _node_type{_node_type}, value{value} {}
  int line() const override { return _line; }
  NodeType node_type() const override { return _node_type; }
};

class NewExpression : public Expression
{
public:
  int _line;
  string class_name;

  NewExpression(int _line, string class_name)
      : _line{_line}, class_name{class_name} {}
  int line() const override { return _line; }
  NodeType node_type() const override { return NodeType::NEW; }
};

class NewIntArrayExpression : public Expression
{
public:
  int _line;
  Expression *length;

  NewIntArrayExpression(int _line, Expression *length)
      : _line{_line}, length{length} {}
  int line() const override { return _line; }
  NodeType node_type() const override { return NodeType::NEW_INTEGER_ARRAY; }
};

class ThisExpression : public Expression
{
public:
  int _line;
  string class_name;

  ThisExpression(int _line) : _line{_line}, class_name() {}
  int line() const override { return _line; }
  NodeType node_type() const override { return NodeType::THIS; }
};

class BlockStatement : public Statement
{
public:
  int _line;
  vector<Statement *> statements;

  BlockStatement(int _line, vector<Statement *> statements)
      : _line{_line}, statements{statements} {}
  int line() const override { return _line; }
  StatementType statement_type() const override
  {
    return StatementType::BLOCK_STATEMENT;
  }
};

class IfStatement : public Statement
{
public:
  int _line;
  Expression *condition;
  Statement *if_true;
  Statement *if_false;

  IfStatement(int _line, Expression *condition, Statement *if_true,
              Statement *if_false)
      : _line{_line}, condition{condition}, if_true{if_true}, if_false{
                                                                  if_false} {}
  int line() const override { return _line; }
  StatementType statement_type() const override
  {
    return StatementType::IF_STATEMENT;
  }
};

class WhileStatement : public Statement
{
public:
  int _line;
  Expression *condition;
  Statement *body;

  WhileStatement(int _line, Expression *condition, Statement *body)
      : _line{_line}, condition{condition}, body{body} {}
  int line() const override { return _line; }
  StatementType statement_type() const override
  {
    return StatementType::WHILE_STATEMENT;
  }
};

class IndexAssignStatement : public Statement
{
public:
  int _line;
  IdentifierExpression *identifier;
  Expression *index;
  Expression *value;

  IndexAssignStatement(int _line, IdentifierExpression *identifier,
                       Expression *index, Expression *value)
      : _line{_line}, identifier{identifier}, index{index}, value{value} {}
  int line() const override { return _line; }
  StatementType statement_type() const override
  {
    return StatementType::INDEX_ASSIGN_STATEMENT;
  }
};

class AssignStatement : public Statement
{
public:
  int _line;
  IdentifierExpression *identifier;
  Expression *value;
  string type;

  AssignStatement(int _line, IdentifierExpression *identifier,
                  Expression *value)
      : _line{_line}, identifier{identifier}, value{value} {}
  int line() const override { return _line; }
  StatementType statement_type() const override
  {
    return StatementType::ASSIGN_STATEMENT;
  }
};

class PrintLineStatement : public Statement
{
public:
  int _line;
  Expression *value;

  PrintLineStatement(int _line, Expression *value)
      : _line{_line}, value{value} {}
  int line() const override { return _line; }
  StatementType statement_type() const override
  {
    return StatementType::PRINT_LINE_STATEMENT;
  }
};

class MethodCallExpression : public Expression
{
public:
  int _line;
  Expression *object;
  string class_type;
  string method_name;
  vector<Expression *> arguments;

  MethodCallExpression(int _line, Expression *object, string method_name,
                       vector<Expression *> arguments)
      : _line{_line}, object{object},
        method_name{method_name}, arguments{arguments} {}
  int line() const override { return _line; }
  NodeType node_type() const override { return NodeType::CALL; }
};

class TypeAnnotation
{
public:
  string type;
  string _name;

  TypeAnnotation(string type, string name) : type{type}, _name{name} {}

  string name() const { return _name; }
};

using ParameterDecl = TypeAnnotation;
using VarDecl = TypeAnnotation;
using FieldDecl = TypeAnnotation;

class MethodDeclStatement : public Statement
{
public:
  int _line;
  string _name;
  vector<ParameterDecl *> parameters;
  vector<VarDecl *> local_vars;
  BlockStatement *body;
  Expression *return_exp;
  string return_type;

  MethodDeclStatement(int _line, string name,
                      vector<ParameterDecl *> parameters,
                      vector<VarDecl *> local_vars, BlockStatement *body,
                      Expression *return_exp, string return_type)
      : _line{_line}, _name{name}, parameters{parameters},
        local_vars{local_vars}, body{body}, return_exp{return_exp},
        return_type{return_type} {}
  int line() const override { return _line; }
  StatementType statement_type() const override
  {
    return StatementType::METHOD_STATEMENT;
  }
  string name() const { return _name; }
};

class ClassDeclStatement : public Statement
{
public:
  int _line;
  string _name;
  optional<string> super_class_name;
  Table<string, FieldDecl *> fields;
  Table<string, MethodDeclStatement *> methods;

  ClassDeclStatement(int _line, string name, optional<string> super_class_name,
                     Table<string, FieldDecl *> fields,
                     Table<string, MethodDeclStatement *> methods)
      : _line{_line}, _name{name},
        super_class_name{super_class_name}, fields{fields}, methods{methods} {}
  int line() const override { return _line; }
  StatementType statement_type() const override
  {
    return StatementType::CLASS_STATEMENT;
  }
  string name() const { return _name; }
};

class Program
{
public:
  MethodDeclStatement *entry_point;
  Table<string, ClassDeclStatement *> classes;

  Program(MethodDeclStatement *entry_point,
          Table<string, ClassDeclStatement *> classes)
      : entry_point{entry_point}, classes{classes} {}
};

class Error
{
public:
  int line;
  string msg;
  Error() : line{0}, msg{""} {}
  Error(int line, string msg) : line{line}, msg{msg} {}
};

/* singly linked list */
template <typename T>
class SLinkedList
{
public:
  T value;
  SLinkedList<T> *next;
  SLinkedList(T value, SLinkedList<T> *next) : value{value}, next{next} {}
};

template <typename T>
vector<T> singly_linked_list_to_vector(SLinkedList<T> *head)
{
  auto current = head;
  vector<T> result;
  while (current != nullptr)
  {
    result.push_back(current->value);
    current = current->next;
  }
  std::reverse(result.begin(), result.end());
  free_singly_linked_list(head);
  return result;
}

template <typename T>
Table<string, T> singly_linked_list_to_table(SLinkedList<T> *head)
{
  vector<T> vec = singly_linked_list_to_vector(head);
  Table<string, T> table;
  for (auto item : vec)
  {
    table.add(item->name(), item);
  }
  return table;
}

template <typename T>
void free_singly_linked_list(SLinkedList<T> *head)
{
  auto cur = head;
  while (cur != nullptr)
  {
    auto next = cur->next;
    delete cur;
    cur = next;
  }
}

template <typename NodeReturnType, typename StatementReturnType,
          typename... Arguments>
class AstVisitor
{
public:
  virtual NodeReturnType visit(Expression *node, Arguments... args)
  {
    switch (node->node_type())
    {
    case NodeType::ADD:
    case NodeType::SUBTRACT:
    case NodeType::MULTIPLY:
    case NodeType::LESS_THAN:
    case NodeType::LOGICAL_AND:
    {
      return visit_binary(dynamic_cast<BinaryExpression *>(node), args...);
    }
    case NodeType::INTEGER:
    case NodeType::BOOLEAN:
    {
      return visit_constant(dynamic_cast<ConstantExpression *>(node), args...);
    }
    case NodeType::ARRAY_LENGTH:
    case NodeType::NOT:
    {
      return visit_unary(dynamic_cast<UnaryExpression *>(node), args...);
    }
    case NodeType::THIS:
    {
      return visit_this(dynamic_cast<ThisExpression *>(node), args...);
    }
    case NodeType::NAME:
    {
      return visit_identifier(dynamic_cast<IdentifierExpression *>(node),
                              args...);
    }
    case NodeType::NEW:
    {
      return visit_new(dynamic_cast<NewExpression *>(node), args...);
    }
    case NodeType::NEW_INTEGER_ARRAY:
    {
      return visit_new_array(dynamic_cast<NewIntArrayExpression *>(node),
                             args...);
    }
    case NodeType::CALL:
    {
      return visit_call(dynamic_cast<MethodCallExpression *>(node), args...);
    }
    case NodeType::INDEX_ACCESS:
    {
      return visit_index_access(dynamic_cast<IndexExpression *>(node), args...);
    }
    default:
    {
      throw Error(node->line(),
                  "not supported node type: " +
                      string(magic_enum::enum_name(node->node_type())));
    }
    }
  }

  virtual StatementReturnType node_to_statement(Expression *node,
                                                Arguments... args) = 0;

  virtual StatementReturnType visit_statement(Statement *statement,
                                              Arguments... args)
  {
    switch (statement->statement_type())
    {
    case StatementType::EXPRESSION_STATEMENT:
    {
      return node_to_statement(dynamic_cast<Expression *>(statement), args...);
    }
    case StatementType::IF_STATEMENT:
    {
      return visit_if(dynamic_cast<IfStatement *>(statement), args...);
    }
    case StatementType::WHILE_STATEMENT:
    {
      return visit_while(dynamic_cast<WhileStatement *>(statement), args...);
    }
    case StatementType::BLOCK_STATEMENT:
    {
      return visit_block(dynamic_cast<BlockStatement *>(statement), args...);
    }
    case StatementType::CLASS_STATEMENT:
    {
      return visit_class_decl(dynamic_cast<ClassDeclStatement *>(statement),
                              args...);
    }
    case StatementType::METHOD_STATEMENT:
    {
      return visit_method_decl(dynamic_cast<MethodDeclStatement *>(statement),
                               args...);
    }
    case StatementType::PRINT_LINE_STATEMENT:
    {
      return visit_print_line(dynamic_cast<PrintLineStatement *>(statement),
                              args...);
    }
    case StatementType::ASSIGN_STATEMENT:
    {
      return visit_assign(dynamic_cast<AssignStatement *>(statement), args...);
    }
    case StatementType::INDEX_ASSIGN_STATEMENT:
    {
      return visit_index_assign(dynamic_cast<IndexAssignStatement *>(statement),
                                args...);
    }
    default:
    {
      throw Error(statement->line(), "not supported statement type: " +
                                         string(magic_enum::enum_name(
                                             statement->statement_type())));
    }
    }
  }

  virtual NodeReturnType visit_binary(BinaryExpression *node,
                                      Arguments... args) = 0;

  virtual NodeReturnType visit_unary(UnaryExpression *node,
                                     Arguments... args) = 0;

  virtual NodeReturnType visit_identifier(IdentifierExpression *node,
                                          Arguments... args) = 0;

  virtual NodeReturnType visit_constant(ConstantExpression *node,
                                        Arguments... args) = 0;

  virtual NodeReturnType visit_this(ThisExpression *node,
                                    Arguments... args) = 0;

  virtual NodeReturnType visit_new(NewExpression *node, Arguments... args) = 0;

  virtual NodeReturnType visit_new_array(NewIntArrayExpression *node,
                                         Arguments... args) = 0;

  virtual NodeReturnType visit_index_access(IndexExpression *node,
                                            Arguments... args) = 0;
  virtual NodeReturnType visit_call(MethodCallExpression *node,
                                    Arguments... args) = 0;
  virtual StatementReturnType visit_block(BlockStatement *statement,
                                          Arguments... args) = 0;

  virtual StatementReturnType visit_if(IfStatement *statement,
                                       Arguments... args) = 0;

  virtual StatementReturnType visit_while(WhileStatement *statement,
                                          Arguments... args) = 0;

  virtual StatementReturnType
  visit_index_assign(IndexAssignStatement *statement, Arguments... args) = 0;

  virtual StatementReturnType visit_assign(AssignStatement *statement,
                                           Arguments... args) = 0;

  virtual StatementReturnType visit_method_decl(MethodDeclStatement *statement,
                                                Arguments... args) = 0;

  virtual StatementReturnType visit_class_decl(ClassDeclStatement *statement,
                                               Arguments... args) = 0;

  virtual StatementReturnType visit_print_line(PrintLineStatement *statement,
                                               Arguments... args) = 0;
};

#endif // NODE_H
