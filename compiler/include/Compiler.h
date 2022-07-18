#ifndef COMPILER_H
#define COMPILER_H
#include "Node.h"
#include <cstdint>

using Byte = uint8_t;
using ByteCode = vector<Byte>;
using u16 = uint16_t;
using i32 = int32_t;

enum class Op
{
  GOTO_IF_TRUE,
  GOTO_IF_FALSE,
  GOTO,
  PUSH_LOCAL_INT,
  POP_LOCAL_INT,
  PUSH_LOCAL_INT_ARRAY,
  POP_LOCAL_INT_ARRAY,
  PUSH_LOCAL_OBJECT,
  POP_LOCAL_OBJECT,
  PUSH_FIELD_INT,
  POP_FIELD_INT,
  PUSH_FIELD_INT_ARRAY,
  POP_FIELD_INT_ARRAY,
  PUSH_FIELD_OBJECT,
  POP_FIELD_OBJECT,
  PRINT_LINE,
  LESS_THAN,
  ADD,
  SUB,
  MUL,
  NOT,
  ARRAY_LENGTH,
  METHOD_CALL,
  NEW_INT_ARRAY,
  NEW,
  PUSH_INT,
  PUSH_INT_ARRAY_ITEM,
  POP_INT_ARRAY_ITEM,
  RETURN_INT,
  RETURN_INT_ARRAY,
  RETURN_OBJECT,
  EXIT
};

class Compiler : public AstVisitor<void, void, ByteCode &, Scope<u16> *>
{
public:
  Program *program;
  ClassDeclStatement *this_class;

  explicit Compiler(Program *program)
      : program{program}, this_class{nullptr} {}

  void add_op(ByteCode &bytes, Op op);
  void add_u16(ByteCode &bytes, u16 value);
  void rewrite_u16(ByteCode &bytes, size_t index, u16 value);
  void add_i32(ByteCode &bytes, i32 value);

  void visit_binary(BinaryExpression *node, ByteCode &bytes,
                    Scope<u16> *scope) override;

  void visit_unary(UnaryExpression *node, ByteCode &bytes,
                   Scope<u16> *scope) override;

  void visit_identifier(IdentifierExpression *node, ByteCode &bytes,
                        Scope<u16> *scope) override;

  void visit_constant(ConstantExpression *node, ByteCode &bytes,
                      Scope<u16> *scope) override;

  void visit_this(ThisExpression *node, ByteCode &bytes,
                  Scope<u16> *scope) override;

  void visit_new(NewExpression *node, ByteCode &bytes,
                 Scope<u16> *scope) override;

  void visit_new_array(NewIntArrayExpression *node, ByteCode &bytes,
                       Scope<u16> *scope) override;

  void visit_index_access(IndexExpression *node, ByteCode &bytes,
                          Scope<u16> *scope) override;
  void visit_call(MethodCallExpression *node, ByteCode &bytes,
                  Scope<u16> *scope) override;

  void visit_block(BlockStatement *statement, ByteCode &bytes,
                   Scope<u16> *scope) override;

  void visit_if(IfStatement *statement, ByteCode &bytes,
                Scope<u16> *scope) override;

  void visit_while(WhileStatement *statement, ByteCode &bytes,
                   Scope<u16> *scope) override;

  void visit_index_assign(IndexAssignStatement *statement, ByteCode &bytes,
                          Scope<u16> *scope) override;

  void visit_assign(AssignStatement *statement, ByteCode &bytes,
                    Scope<u16> *scope) override;

  void visit_method_decl(MethodDeclStatement *statement, ByteCode &bytes,
                         Scope<u16> *scope) override;

  void visit_class_decl(ClassDeclStatement *statement, ByteCode &bytes,
                        Scope<u16> *scope) override;

  void visit_print_line(PrintLineStatement *statement, ByteCode &bytes,
                        Scope<u16> *scope) override;

  void node_to_statement(Expression *node, ByteCode &bytes,
                         Scope<u16> *scope) override;

  ByteCode compile();
  void push_this(ByteCode &bytes);
};
#endif // COMPILER_H
