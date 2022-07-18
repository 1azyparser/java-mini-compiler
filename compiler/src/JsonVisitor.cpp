#include "JsonVisitor.h"

json JsonVisitor::visit_binary(BinaryExpression *node)
{
  json obj;
  obj["Line"] = node->line();
  obj["Node Type"] = magic_enum::enum_name<NodeType>(node->node_type());
  obj["Left"] = visit(node->left);
  obj["Right"] = visit(node->right);
  return obj;
}

json JsonVisitor::visit_unary(UnaryExpression *node)
{
  json obj;
  obj["Line"] = node->line();
  obj["Node Type"] = magic_enum::enum_name<NodeType>(node->node_type());
  obj["Operand"] = visit(node->operand);
  return obj;
}

json JsonVisitor::visit_identifier(IdentifierExpression *node)
{
  json obj;
  obj["Line"] = node->line();
  obj["Node Type"] = magic_enum::enum_name<NodeType>(node->node_type());
  obj["Name"] = node->name;
  return obj;
}

json JsonVisitor::visit_constant(ConstantExpression *node)
{
  json obj;
  obj["Line"] = node->line();
  obj["Node Type"] = magic_enum::enum_name<NodeType>(node->node_type());
  obj["Value"] = node->value;
  return obj;
}

json JsonVisitor::visit_this(ThisExpression *node)
{
  json obj;
  obj["Line"] = node->line();
  obj["Node Type"] = magic_enum::enum_name<NodeType>(node->node_type());
  return obj;
}

json JsonVisitor::visit_new(NewExpression *node)
{
  json obj;
  obj["Line"] = node->line();
  obj["Node Type"] = magic_enum::enum_name<NodeType>(node->node_type());
  obj["Class Name"] = node->class_name;
  return obj;
}

json JsonVisitor::visit_call(MethodCallExpression *node)
{
  json obj;
  vector<json> args;
  obj["Line"] = node->line();
  obj["Node Type"] = magic_enum::enum_name<NodeType>(node->node_type());
  obj["Object"] = visit(node->object);
  for (auto arg : node->arguments)
  {
    args.push_back(visit(arg));
  }
  obj["Arguments"] = args;
  return obj;
}

json JsonVisitor::visit_index_access(IndexExpression *node)
{
  json obj;
  obj["Line"] = node->line();
  obj["Node Type"] = magic_enum::enum_name<NodeType>(node->node_type());
  obj["Array"] = visit(node->array);
  obj["Index"] = visit(node->index);
  return obj;
}

json JsonVisitor::visit_block(BlockStatement *statement)
{
  json obj;
  vector<json> statements;
  obj["Line"] = statement->line();
  obj["Statement Type"] =
      magic_enum::enum_name<StatementType>(statement->statement_type());
  for (auto stmt : statement->statements)
  {
    statements.push_back(visit_statement(stmt));
  }
  obj["Statements"] = statements;
  return obj;
}

json JsonVisitor::visit_if(IfStatement *statement)
{
  json obj;
  obj["Line"] = statement->line();
  obj["Statement Type"] =
      magic_enum::enum_name<StatementType>(statement->statement_type());
  obj["Condition"] = visit_statement(statement->condition);
  obj["If True"] = visit_statement(statement->if_true);
  obj["If False"] = visit_statement(statement->if_false);
  return obj;
}

json JsonVisitor::visit_while(WhileStatement *statement)
{
  json obj;
  obj["Line"] = statement->line();
  obj["Statement Type"] =
      magic_enum::enum_name<StatementType>(statement->statement_type());
  obj["Condition"] = visit(statement->condition);
  obj["Body"] = visit_statement(statement->body);
  return obj;
}

json JsonVisitor::visit_method_decl(MethodDeclStatement *statement)
{
  json obj;
  vector<json> parameters;
  vector<json> local_vars;

  obj["Line"] = statement->line();
  obj["Statement Type"] =
      magic_enum::enum_name<StatementType>(statement->statement_type());
  for (auto parameter : statement->parameters)
  {
    parameters.push_back(visit_type_annotation(parameter));
  }
  obj["Parameters"] = parameters;
  for (auto var : statement->local_vars)
  {
    local_vars.push_back(visit_type_annotation(var));
  }
  obj["Local Variables"] = local_vars;
  obj["Body"] = visit_statement(statement->body);
  obj["Return Expression"] = visit(statement->return_exp);
  obj["Return Type"] = statement->return_type;

  return obj;
}

json JsonVisitor::visit_class_decl(ClassDeclStatement *statement)
{
  vector<json> fields;
  vector<json> methods;

  for (auto field : statement->fields.values)
  {
    fields.push_back(visit_type_annotation(field));
  }
  for (auto method : statement->methods.values)
  {
    methods.push_back(visit_method_decl(method));
  }

  json obj;
  obj["Line"] = statement->line();
  obj["Name"] = statement->_name;
  if (statement->super_class_name.has_value())
  {
    obj["Super Class"] = statement->super_class_name.value();
  }
  obj["Fields"] = fields;
  obj["Methods"] = methods;
  return obj;
}

json JsonVisitor::visit_type_annotation(TypeAnnotation *type_annotation)
{
  json obj;
  obj["Type"] = type_annotation->type;
  obj["Name"] = type_annotation->_name;
  return obj;
}

json JsonVisitor::node_to_statement(Expression *node) { return visit(node); }

json JsonVisitor::visit_new_array(NewIntArrayExpression *node)
{
  json obj;
  obj["Line"] = node->line();
  obj["Node Type"] = magic_enum::enum_name<NodeType>(node->node_type());
  obj["Length"] = visit(node->length);
  return obj;
}

json JsonVisitor::visit_index_assign(IndexAssignStatement *statement)
{
  json obj;
  obj["Line"] = statement->line();
  obj["Statement Type"] =
      magic_enum::enum_name<StatementType>(statement->statement_type());
  obj["Identifier"] = visit(statement->identifier);
  obj["Index"] = visit(statement->index);
  obj["Value"] = visit(statement->value);
  return obj;
}

json JsonVisitor::visit_assign(AssignStatement *statement)
{
  json obj;
  obj["Line"] = statement->line();
  obj["Statement Type"] =
      magic_enum::enum_name<StatementType>(statement->statement_type());
  obj["Identifier"] = visit(statement->identifier);
  obj["Value"] = visit(statement->value);
  return obj;
}

json JsonVisitor::visit_print_line(PrintLineStatement *statement)
{
  json obj;
  obj["Line"] = statement->line();
  obj["Statement Type"] =
      magic_enum::enum_name<StatementType>(statement->statement_type());
  obj["Value"] = visit(statement->value);
  return obj;
}

json JsonVisitor::visit_program(Program *program)
{
  json json_obj;
  json_obj.push_back(visit_method_decl(program->entry_point));
  for (auto _class : program->classes.values)
  {
    json_obj.push_back(visit_statement(_class));
  }
  return json_obj;
}