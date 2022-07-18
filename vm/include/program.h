#ifndef PROGRAM_H
#define PROGRAM_H
#include <cstdint>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using std::ifstream;
using std::string;
using std::vector;
using Byte = uint8_t;
using u16 = uint16_t;
using i32 = int32_t;

using nlohmann::json;

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

class Method
{
public:
  u16 args;
  u16 locals;
  vector<Byte> code;
  Method() = default;
  Method(u16 args, u16 locals, vector<Byte> &&code)
      : args{args}, locals{locals}, code{code} {}
};

class Class
{
public:
  u16 n_fields;
  vector<Method> methods;
};

class Program
{
public:
  Method entry_point;
  vector<Class> classes;
};

class VMError
{
public:
  string msg;
  explicit VMError(string msg) : msg{msg} {}
};

Program load_program(string path);

u16 parse_u16(ifstream &stream, string error_msg);

Method load_method(ifstream &stream);

vector<Byte> read_bytes(ifstream &stream, u16 count);

Class load_class(ifstream &stream);

json program_to_json(Program &program);

json byte_code_to_json(vector<Byte> &code);

#endif // PROGRAM_H
