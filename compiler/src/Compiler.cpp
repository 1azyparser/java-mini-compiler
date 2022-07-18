#include "Compiler.h"
#include <algorithm>

void Compiler::add_op(ByteCode &bytes, Op op)
{
  bytes.push_back(static_cast<Byte>(op));
}
void Compiler::add_u16(ByteCode &bytes, u16 value)
{
  bytes.push_back(value / 256);
  bytes.push_back(value % 256);
}
void Compiler::rewrite_u16(ByteCode &bytes, size_t index, u16 value)
{
  bytes.at(index) = value / 256;
  bytes.at(index + 1) = value % 256;
}
void Compiler::add_i32(ByteCode &bytes, i32 value)
{
  size_t start = bytes.size();
  for (int i = 0; i < 4; i++)
  {
    bytes.push_back(value % 256);
    value = value / 256;
  }
  std::reverse(bytes.begin() + start, bytes.end());
}

void Compiler::visit_binary(BinaryExpression *node, ByteCode &bytes,
                            Scope<u16> *scope)
{
  if (node->node_type() == NodeType::ADD)
  {
    visit(node->left, bytes, scope);
    visit(node->right, bytes, scope);
    add_op(bytes, Op::ADD);
  }
  else if (node->node_type() == NodeType::SUBTRACT)
  {
    visit(node->left, bytes, scope);
    visit(node->right, bytes, scope);
    add_op(bytes, Op::SUB);
  }
  else if (node->node_type() == NodeType::MULTIPLY)
  {
    visit(node->left, bytes, scope);
    visit(node->right, bytes, scope);
    add_op(bytes, Op::MUL);
  }
  else if (node->node_type() == NodeType::LESS_THAN)
  {
    visit(node->left, bytes, scope);
    visit(node->right, bytes, scope);
    add_op(bytes, Op::LESS_THAN);
  }
  else if (node->node_type() == NodeType::LOGICAL_AND)
  {
    // shortcut evaluation
    visit(node->left, bytes, scope);
    add_op(bytes, Op::GOTO_IF_FALSE);
    size_t index1 = bytes.size();
    add_u16(bytes, 0);
    visit(node->right, bytes, scope);
    add_op(bytes, Op::GOTO_IF_TRUE);
    size_t index2 = bytes.size();
    add_u16(bytes, 0);
    add_op(bytes, Op::PUSH_INT);
    add_i32(bytes, 0);
    rewrite_u16(bytes, index1, bytes.size());
    rewrite_u16(bytes, index2, bytes.size());
    add_op(bytes, Op::GOTO);
    add_u16(bytes, bytes.size() + 1 + 4);
    add_op(bytes, Op::PUSH_INT);
    add_i32(bytes, 1);
  }
  else
  {
    throw Error(node->line(),
                "not supported node type: '" +
                    string(magic_enum::enum_name<NodeType>(node->node_type())) +
                    "'");
  }
}

void Compiler::visit_unary(UnaryExpression *node, ByteCode &bytes,
                           Scope<u16> *scope)
{
  if (node->node_type() == NodeType::NOT)
  {
    visit(node->operand, bytes, scope);
    add_op(bytes, Op::NOT);
  }
  else if (node->node_type() == NodeType::ARRAY_LENGTH)
  {
    visit(node->operand, bytes, scope);
    add_op(bytes, Op::ARRAY_LENGTH);
  }
  else
  {
    throw Error(node->line(),
                "not supported node type: '" +
                    string(magic_enum::enum_name<NodeType>(node->node_type())) +
                    "'");
  }
}

void Compiler::visit_identifier(IdentifierExpression *node, ByteCode &bytes,
                                Scope<u16> *scope)
{
  if (auto index = scope->resolve(node->name))
  {
    if (node->type == "int")
    {
      add_op(bytes, Op::PUSH_LOCAL_INT);
      add_u16(bytes, index.value());
    }
    else if (node->type == "int[]")
    {
      add_op(bytes, Op::PUSH_LOCAL_INT_ARRAY);
      add_u16(bytes, index.value());
    }
    else
    {
      add_op(bytes, Op::PUSH_LOCAL_OBJECT);
      add_u16(bytes, index.value());
    }
  }
  else if (this_class->fields.has_key(node->name))
  {
    auto index = this_class->fields.get_index(node->name);
    push_this(bytes);
    if (node->type == "int" || node->type == "boolean")
    {
      add_op(bytes, Op::PUSH_FIELD_INT);
      add_u16(bytes, index);
    }
    else if (node->type == "int[]")
    {
      add_op(bytes, Op::PUSH_FIELD_INT_ARRAY);
      add_u16(bytes, index);
    }
    else
    {
      add_op(bytes, Op::PUSH_FIELD_OBJECT);
      add_u16(bytes, index);
    }
  }
  else
  {
    throw Error(node->line(), "undefined identifier '" + node->name + "'");
  }
}

void Compiler::visit_constant(ConstantExpression *node, ByteCode &bytes,
                              Scope<u16> *scope)
{
  if (node->node_type() == NodeType::BOOLEAN)
  {
    if (node->value == "true")
    {
      add_op(bytes, Op::PUSH_INT);
      add_i32(bytes, 1);
    }
    else if (node->value == "false")
    {
      add_op(bytes, Op::PUSH_INT);
      add_i32(bytes, 0);
    }
    else
    {
      throw Error(node->line(), "the boolean value must be 'true' or 'false'");
    }
  }
  else if (node->node_type() == NodeType::INTEGER)
  {
    i32 value = std::stoi(node->value);
    add_op(bytes, Op::PUSH_INT);
    add_i32(bytes, value);
  }
  else
  {
    throw Error(node->line(), "not supported constant type");
  }
}

void Compiler::visit_this(ThisExpression *node, ByteCode &bytes,
                          Scope<u16> *scope)
{
  push_this(bytes);
}

void Compiler::visit_new(NewExpression *node, ByteCode &bytes,
                         Scope<u16> *scope)
{
  add_op(bytes, Op::NEW);
  add_u16(bytes, program->classes.get_index(node->class_name));
}

void Compiler::visit_new_array(NewIntArrayExpression *node, ByteCode &bytes,
                               Scope<u16> *scope)
{
  visit(node->length, bytes, scope);
  add_op(bytes, Op::NEW_INT_ARRAY);
}

void Compiler::visit_index_access(IndexExpression *node, ByteCode &bytes,
                                  Scope<u16> *scope)
{
  visit(node->array, bytes, scope);
  visit(node->index, bytes, scope);
  add_op(bytes, Op::PUSH_INT_ARRAY_ITEM);
}
void Compiler::visit_call(MethodCallExpression *node, ByteCode &bytes,
                          Scope<u16> *scope)
{
  visit(node->object, bytes, scope);
  for (auto arg : node->arguments)
  {
    visit(arg, bytes, scope);
  }

  add_op(bytes, Op::METHOD_CALL);
  add_u16(bytes, program->classes.get_index(node->class_type));
  auto _class = program->classes.find_by_key(node->class_type);
  add_u16(bytes, _class->methods.get_index(node->method_name));
}

void Compiler::visit_block(BlockStatement *statement, ByteCode &bytes,
                           Scope<u16> *scope)
{
  for (auto stmt : statement->statements)
  {
    visit_statement(stmt, bytes, scope);
  }
}

void Compiler::visit_if(IfStatement *statement, ByteCode &bytes,
                        Scope<u16> *scope)
{
  visit_statement(statement->condition, bytes, scope);
  add_op(bytes, Op::GOTO_IF_FALSE);
  size_t index1 = bytes.size();
  add_u16(bytes, 0);

  visit_statement(statement->if_true, bytes, scope);
  add_op(bytes, Op::GOTO);
  size_t index2 = bytes.size();
  add_u16(bytes, 0);

  rewrite_u16(bytes, index1, bytes.size());
  visit_statement(statement->if_false, bytes, scope);
  rewrite_u16(bytes, index2, bytes.size());
}

void Compiler::visit_while(WhileStatement *statement, ByteCode &bytes,
                           Scope<u16> *scope)
{
  size_t start = bytes.size();
  visit(statement->condition, bytes, scope);
  add_op(bytes, Op::GOTO_IF_FALSE);
  size_t index = bytes.size();
  add_u16(bytes, 0);

  visit_statement(statement->body, bytes, scope);
  add_op(bytes, Op::GOTO);
  add_u16(bytes, start);

  rewrite_u16(bytes, index, bytes.size());
}

void Compiler::visit_index_assign(IndexAssignStatement *statement,
                                  ByteCode &bytes, Scope<u16> *scope)
{
  visit(statement->identifier, bytes, scope);
  visit(statement->index, bytes, scope);
  visit(statement->value, bytes, scope);
  add_op(bytes, Op::POP_INT_ARRAY_ITEM);
}

void Compiler::visit_assign(AssignStatement *statement, ByteCode &bytes,
                            Scope<u16> *scope)
{
  visit(statement->value, bytes, scope);
  if (auto id = scope->resolve(statement->identifier->name))
  {
    if (statement->type == "int" || statement->type == "boolean")
    {
      add_op(bytes, Op::POP_LOCAL_INT);
    }
    else if (statement->type == "int[]")
    {
      add_op(bytes, Op::POP_LOCAL_INT_ARRAY);
    }
    else
    {
      add_op(bytes, Op::POP_LOCAL_OBJECT);
    }
    add_u16(bytes, id.value());
  }
  else if (this_class->fields.has_key(statement->identifier->name))
  {
    push_this(bytes);
    auto index = this_class->fields.get_index(statement->identifier->name);
    if (statement->type == "int" || statement->type == "boolean")
    {
      add_op(bytes, Op::POP_FIELD_INT);
    }
    else if (statement->type == "int[]")
    {
      add_op(bytes, Op::POP_FIELD_INT_ARRAY);
    }
    else
    {
      add_op(bytes, Op::POP_FIELD_OBJECT);
    }
    add_u16(bytes, index);
  }
  else
  {
    throw Error(statement->line(),
                "undefined identifier '" + statement->identifier->name + "'");
  }
}

void Compiler::visit_method_decl(MethodDeclStatement *statement,
                                 ByteCode &bytes, Scope<u16> *scope)
{
  add_u16(bytes, statement->parameters.size());
  add_u16(bytes, statement->local_vars.size());
  Scope<u16> new_scope(scope);
  if (statement->name() == "main")
  {
    size_t index = 0;
    for (auto local_var : statement->local_vars)
    {
      new_scope.put(local_var->name(), index);
      index++;
    }
  }
  else
  {
    new_scope.put("this", 0);
    size_t index = 1;
    for (auto parameter : statement->parameters)
    {
      new_scope.put(parameter->name(), index);
      index++;
    }
    for (auto local_var : statement->local_vars)
    {
      new_scope.put(local_var->name(), index);
      index++;
    }
  }
  ByteCode function_bytes;
  visit_statement(statement->body, function_bytes, &new_scope);
  // process return expression
  if (statement->return_type == "int" || statement->return_type == "boolean")
  {
    visit(statement->return_exp, function_bytes, &new_scope);
    add_op(function_bytes, Op::RETURN_INT);
  }
  else if (statement->return_type == "int[]")
  {
    visit(statement->return_exp, function_bytes, &new_scope);
    add_op(function_bytes, Op::RETURN_INT_ARRAY);
  }
  else if (statement->return_type == "void")
  {
    add_op(function_bytes, Op::EXIT);
  }
  else
  {
    visit(statement->return_exp, function_bytes, &new_scope);
    add_op(function_bytes, Op::RETURN_OBJECT);
  }
  // merge
  add_u16(bytes, function_bytes.size());
  for (auto b : function_bytes)
  {
    bytes.push_back(b);
  }
}

void Compiler::visit_class_decl(ClassDeclStatement *statement, ByteCode &bytes,
                                Scope<u16> *scope)
{
  this_class = statement;
  add_u16(bytes, statement->fields.values.size());
  add_u16(bytes, statement->methods.values.size());
  for (auto method : statement->methods.values)
  {
    visit_method_decl(method, bytes, scope);
  }
}

void Compiler::visit_print_line(PrintLineStatement *statement, ByteCode &bytes,
                                Scope<u16> *scope)
{
  visit(statement->value, bytes, scope);
  add_op(bytes, Op::PRINT_LINE);
}

void Compiler::node_to_statement(Expression *node, ByteCode &bytes,
                                 Scope<u16> *scope)
{
  visit(node, bytes, scope);
}

ByteCode Compiler::compile()
{
  ByteCode bytes;
  Scope<u16> scope;
  visit_method_decl(program->entry_point, bytes, &scope);
  add_u16(bytes, program->classes.values.size());
  for (auto _class : program->classes.values)
  {
    visit_class_decl(_class, bytes, &scope);
  }
  return bytes;
}
void Compiler::push_this(ByteCode &bytes)
{
  add_op(bytes, Op::PUSH_LOCAL_OBJECT);
  add_u16(bytes, 0); // first parameter
}