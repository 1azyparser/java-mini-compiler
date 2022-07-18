#ifndef TYPE_CHECKER_H
#define TYPE_CHECKER_H
#include "Node.h"
#include <functional>
#include <unordered_set>

using std::unordered_set;

class TypeChecker : public AstVisitor<string, void, Scope<string> *>
{
public:
  Program *program;
  ClassDeclStatement *this_class;

  explicit TypeChecker(Program *program)
      : program{program}, this_class{nullptr} {}

  string visit_binary(BinaryExpression *node, Scope<string> *scope) override;

  string visit_unary(UnaryExpression *node, Scope<string> *scope) override;

  string visit_identifier(IdentifierExpression *node,
                          Scope<string> *scope) override;

  string visit_constant(ConstantExpression *node,
                        Scope<string> *scope) override;

  string visit_this(ThisExpression *node, Scope<string> *scope) override;

  string visit_new(NewExpression *node, Scope<string> *scope) override;

  string visit_new_array(NewIntArrayExpression *node,
                         Scope<string> *scope) override;

  string visit_index_access(IndexExpression *node,
                            Scope<string> *scope) override;

  string visit_call(MethodCallExpression *node, Scope<string> *scope) override;

  void visit_block(BlockStatement *statement, Scope<string> *scope) override;

  void visit_if(IfStatement *statement, Scope<string> *scope) override;

  void visit_while(WhileStatement *statement, Scope<string> *scope) override;

  void visit_index_assign(IndexAssignStatement *statement,
                          Scope<string> *scope) override;

  void visit_assign(AssignStatement *statement, Scope<string> *scope) override;

  void visit_method_decl(MethodDeclStatement *statement,
                         Scope<string> *scope) override;

  void visit_class_decl(ClassDeclStatement *statement,
                        Scope<string> *scope) override;

  void visit_print_line(PrintLineStatement *statement,
                        Scope<string> *scope) override;

  void node_to_statement(Expression *node, Scope<string> *scope) override;

  void collect_super_classes(ClassDeclStatement *current,
                             vector<ClassDeclStatement *> &super_classes,
                             unordered_set<ClassDeclStatement *> &visited);

  void fix_class_inheritance();

  void check_program();
};

#endif // TYPE_CHECKER_H