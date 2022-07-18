#include "TypeChecker.h"

string TypeChecker::visit_binary(BinaryExpression *node, Scope<string> *scope)
{
  auto left = visit(node->left, scope);
  auto right = visit(node->right, scope);
  switch (node->node_type())
  {
  case NodeType::ADD:
  case NodeType::SUBTRACT:
  case NodeType::MULTIPLY:
  {
    if (left == "int" && right == "int")
    {
      return "int";
    }
    else
    {
      throw Error(node->line(), "binary expression (+ - *) type error");
    }
  }
  case NodeType::LESS_THAN:
  {
    if (left == "int" && right == "int")
    {
      return "boolean";
    }
    else
    {
      throw Error(node->line(), "binary expression (<) type error");
    }
  }
  case NodeType::LOGICAL_AND:
  {
    if (left == "boolean" && right == "boolean")
    {
      return "boolean";
    }
    else
    {
      throw Error(node->line(), "binary expression (&&) type error");
    }
  }
  default:
  {
    throw Error(node->line(), "wrong node type for the binary expression");
  }
  }
}

string TypeChecker::visit_unary(UnaryExpression *node, Scope<string> *scope)
{
  auto operand = visit(node->operand, scope);
  if (node->node_type() == NodeType::NOT)
  {
    if (operand == "boolean")
    {
      return "boolean";
    }
    else
    {
      throw Error(node->line(), "not expression (!) only takes boolean type");
    }
  }
  else if (node->node_type() == NodeType::ARRAY_LENGTH)
  {
    if (operand == "int[]")
    {
      return "int";
    }
    else
    {
      throw Error(node->line(),
                  "array length operation can only be done for an array");
    }
  }
  else
  {
    throw Error(node->line(), "not supported node type for unary expression");
  }
}

string TypeChecker::visit_identifier(IdentifierExpression *node,
                                     Scope<string> *scope)
{
  if (auto id_type = scope->resolve(node->name))
  {
    node->type = id_type.value();
    return id_type.value();
  }
  else
  {
    throw Error(node->line(), "undefined identifier '" + node->name + "'");
  }
}

string TypeChecker::visit_constant(ConstantExpression *node,
                                   Scope<string> *scope)
{
  switch (node->node_type())
  {
  case NodeType::INTEGER:
  {
    return "int";
  }
  case NodeType::BOOLEAN:
  {
    return "boolean";
  }
  default:
  {
    throw Error(node->line(), "unsupported constant node type");
  }
  }
}

string TypeChecker::visit_this(ThisExpression *node, Scope<string> *scope)
{
  return this_class->name();
}

string TypeChecker::visit_new(NewExpression *node, Scope<string> *scope)
{
  return node->class_name;
}

string TypeChecker::visit_new_array(NewIntArrayExpression *node,
                                    Scope<string> *scope)
{
  if (visit(node->length, scope) == "int")
  {
    return "int[]";
  }
  else
  {
    throw Error(node->line(), "array length should be integer type");
  }
}

string TypeChecker::visit_index_access(IndexExpression *node,
                                       Scope<string> *scope)
{
  auto array = visit(node->array, scope);
  auto index = visit(node->index, scope);
  if (array == "int[]" && index == "int")
  {
    return "int";
  }
  else
  {
    throw Error(node->line(), "array index access type mismatch");
  }
}

string TypeChecker::visit_call(MethodCallExpression *node,
                               Scope<string> *scope)
{
  auto obj_type = visit(node->object, scope);
  node->class_type = obj_type;
  if (program->classes.has_key(obj_type))
  {
    auto _class = program->classes.find_by_key(obj_type);
    if (_class->methods.has_key(node->method_name))
    {
      auto method = _class->methods.find_by_key(node->method_name);
      if (node->arguments.size() == method->parameters.size())
      {
        for (size_t i = 0; i < node->arguments.size(); i++)
        {
          auto arg_type = visit(node->arguments[i], scope);
          if (arg_type != method->parameters[i]->type)
          {
            throw Error(node->line(), "method call argument type mismatch");
          }
        }
        return method->return_type;
      }
      else
      {
        throw Error(node->line(), "method call argument count mismatch");
      }
    }
    else
    {
      throw Error(node->line(), "undefined method '" + node->method_name + "'");
    }
  }
  else
  {
    throw Error(node->line(), "undefined class '" + obj_type + "'");
  }
}

void TypeChecker::visit_block(BlockStatement *statement, Scope<string> *scope)
{
  for (auto stmt : statement->statements)
  {
    visit_statement(stmt, scope);
  }
}

void TypeChecker::visit_if(IfStatement *statement, Scope<string> *scope)
{
  if (visit(statement->condition, scope) == "boolean")
  {
    visit_statement(statement->if_true, scope);
    visit_statement(statement->if_false, scope);
  }
  else
  {
    throw Error(statement->line(),
                "the condition of the if statement must return boolean type");
  }
}

void TypeChecker::visit_while(WhileStatement *statement, Scope<string> *scope)
{
  if (visit(statement->condition, scope) == "boolean")
  {
    visit_statement(statement->body, scope);
  }
  else
  {
    throw Error(statement->line(),
                "while loop condition must return boolean type");
  }
}

void TypeChecker::visit_index_assign(IndexAssignStatement *statement,
                                     Scope<string> *scope)
{
  auto array = visit(statement->identifier, scope);
  auto index = visit(statement->index, scope);
  auto value = visit(statement->value, scope);
  if (array == "int[]" && index == "int" && value == "int")
  {
  }
  else
  {
    throw Error(statement->line(), "array index assign type mismatch");
  }
}

void TypeChecker::visit_assign(AssignStatement *statement,
                               Scope<string> *scope)
{
  auto id = visit(statement->identifier, scope);
  auto value = visit(statement->value, scope);
  if (id != value)
  {
    throw Error(statement->line(), "assign type mismatch");
  }
  else
  {
    statement->type = value;
  }
}

void TypeChecker::visit_method_decl(MethodDeclStatement *statement,
                                    Scope<string> *scope)
{
  Scope new_scope{scope};
  for (auto local_var : statement->local_vars)
  {
    new_scope.put(local_var->_name, local_var->type);
  }
  for (auto parameter : statement->parameters)
  {
    new_scope.put(parameter->_name, parameter->type);
  }
  visit_statement(statement->body, &new_scope);
  if (statement->return_type != "void")
  {
    visit_statement(statement->return_exp, &new_scope);
  }
}

void TypeChecker::visit_class_decl(ClassDeclStatement *statement,
                                   Scope<string> *scope)
{
  Scope new_scope{scope};
  this_class = statement;
  for (auto field : statement->fields.values)
  {
    new_scope.put(field->_name, field->type);
  }
  for (auto method : statement->methods.values)
  {
    visit_method_decl(method, &new_scope);
  }
}

void TypeChecker::visit_print_line(PrintLineStatement *statement,
                                   Scope<string> *scope)
{
  auto value = visit(statement->value, scope);
  if (value != "int")
  {
    throw Error(statement->line(), "minijava can only print int value");
  }
}

void TypeChecker::node_to_statement(Expression *node, Scope<string> *scope)
{
  visit(node, scope);
}

void TypeChecker::collect_super_classes(
    ClassDeclStatement *current, vector<ClassDeclStatement *> &super_classes,
    unordered_set<ClassDeclStatement *> &visited)
{
  if (visited.count(current))
  {
    throw Error(current->line(), "a class cannot inherit its dervied class '" +
                                     current->name() + "' or itself");
  }
  else if (current->super_class_name.has_value())
  {
    auto next_class_name = current->super_class_name.value();
    if (program->classes.has_key(next_class_name))
    {
      auto next_class = program->classes.find_by_key(next_class_name);
      super_classes.push_back(next_class);
      collect_super_classes(next_class, super_classes, visited);
    }
    else
    {
      throw Error(current->line(),
                  "cannot find super class '" + next_class_name + "'");
    }
  }
  else
  {
    // pass
  }
}
void TypeChecker::fix_class_inheritance()
{
  unordered_map<ClassDeclStatement *, Table<string, FieldDecl *>> field_map;
  unordered_map<ClassDeclStatement *, Table<string, MethodDeclStatement *>>
      method_map;
  for (auto class_decl : program->classes.values)
  {
    vector<ClassDeclStatement *> super_classes;
    unordered_set<ClassDeclStatement *> visited;
    collect_super_classes(class_decl, super_classes, visited);
    std::reverse(super_classes.begin(), super_classes.end());
    for (auto super_class : super_classes)
    {
      for (auto field : super_class->fields.values)
      {
        field_map[class_decl].add(field->name(), field);
      }
      for (auto method : super_class->methods.values)
      {
        method_map[class_decl].add(method->name(), method);
      }
    }
    for (auto field : class_decl->fields.values)
    {
      field_map[class_decl].add(field->name(), field);
    }
    for (auto method : class_decl->methods.values)
    {
      method_map[class_decl].add(method->name(), method);
    }
  }

  for (auto class_decl : program->classes.values)
  {
    class_decl->fields = field_map[class_decl];
    class_decl->methods = method_map[class_decl];
  }
}

void TypeChecker::check_program()
{
  fix_class_inheritance();
  Scope<string> scope;
  for (auto _class : program->classes.values)
  {
    visit_class_decl(_class, &scope);
  }
  visit_method_decl(program->entry_point, &scope);
}