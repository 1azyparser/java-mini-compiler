#ifndef JSON_VISITOR_H
#define JSON_VISITOR_H
#include "Node.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonVisitor : public AstVisitor<json, json>
{
public:
  json visit_binary(BinaryExpression *node) override;

  json visit_unary(UnaryExpression *node) override;

  json visit_identifier(IdentifierExpression *node) override;

  json visit_constant(ConstantExpression *node) override;

  json visit_this(ThisExpression *node) override;

  json visit_new(NewExpression *node) override;

  json visit_call(MethodCallExpression *node) override;

  json visit_index_access(IndexExpression *node) override;

  json visit_block(BlockStatement *statement) override;

  json visit_if(IfStatement *statement) override;

  json visit_while(WhileStatement *statement) override;

  json visit_method_decl(MethodDeclStatement *statement) override;

  json visit_class_decl(ClassDeclStatement *statement) override;

  json visit_type_annotation(TypeAnnotation *type_annotation);

  json node_to_statement(Expression *node) override;

  json visit_new_array(NewIntArrayExpression *node) override;

  json visit_index_assign(IndexAssignStatement *statement) override;

  json visit_assign(AssignStatement *statement) override;

  json visit_print_line(PrintLineStatement *statement) override;

  json visit_program(Program *program);
};
#endif // JSON_VISITOR_H