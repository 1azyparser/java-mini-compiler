#include "Program.h"
#include <magic_enum.hpp>

#include <iostream>
using std::cout;
using std::endl;

Program load_program(string path)
{
  ifstream stream(path, std::ios::binary);
  if (stream.fail())
  {
    throw VMError("the byte code file does not exists");
  }
  Program program;
  program.entry_point = load_method(stream);
  u16 n_classes = parse_u16(stream, "fail to read number of classes");

  for (size_t i = 0; i < n_classes; i++)
  {
    program.classes.push_back(load_class(stream));
  }
  return program;
}

u16 parse_u16(ifstream &stream, string error_msg)
{
  int b1 = stream.get();
  int b2 = stream.get();
  if (stream.fail())
  {
    throw VMError(error_msg);
  }
  else
  {
    return (b1 << 4) + b2;
  }
}

Method load_method(ifstream &stream)
{
  u16 args = parse_u16(stream, "fail to read argument count");
  u16 locals = parse_u16(stream, "fail to read local variable count");
  u16 n_bytes = parse_u16(stream, "fail to read method byte code size");

  return Method(args, locals, read_bytes(stream, n_bytes));
}

vector<Byte> read_bytes(ifstream &stream, u16 count)
{
  vector<Byte> bytes;
  bytes.reserve(count);
  for (size_t i = 0; i < count; i++)
  {
    bytes.push_back(stream.get());
    if (stream.fail())
    {
      throw VMError("fail to read method body byte code");
    }
  }
  return bytes;
}

Class load_class(ifstream &stream)
{
  u16 n_fields = parse_u16(stream, "fail to read number of fields");
  u16 n_methods = parse_u16(stream, "fail to read number of methods");

  Class _class;
  _class.n_fields = n_fields;
  for (size_t i = 0; i < n_methods; i++)
  {
    _class.methods.push_back(load_method(stream));
  }

  return _class;
}

json program_to_json(Program &program)
{
  json result;
  result["main_function"]["code"] = byte_code_to_json(program.entry_point.code);
  for (auto &_class : program.classes)
  {
    json class_json;
    class_json["n_fields"] = _class.n_fields;
    for (auto &method : _class.methods)
    {
      json method_json{{"code", byte_code_to_json(method.code)},
                       {"args", method.args},
                       {"locals", method.locals}};
      class_json["methods"].push_back(method_json);
    }
    result["classes"].push_back(class_json);
  }
  return result;
}

json byte_code_to_json(vector<Byte> &code)
{
  json result;
  size_t pc = 0;
  auto read_u16 = [&code, &pc]()
  {
    u16 value = (code.at(pc) << 8) + code.at(pc + 1);
    pc = pc + 2;
    return value;
  };
  auto read_i32 = [&code, &pc]()
  {
    i32 value = (code.at(pc) << 24) + (code.at(pc + 1) << 16) +
                (code.at(pc + 2) << 8) + code.at(pc + 3);
    pc = pc + 4;
    return value;
  };

  while (pc < code.size())
  {
    json row;
    auto opt = magic_enum::enum_cast<Op>(static_cast<int>(code.at(pc)));
    if (!opt.has_value())
    {
      throw VMError("fail to read operation code");
    }
    else
    {
      Op op = opt.value();
      row["operation"] = magic_enum::enum_name<Op>(op);
      row["program_counter"] = pc;
      pc++;
      switch (op)
      {
      case Op::GOTO_IF_TRUE:
      {
        row["next"] = read_u16();
        break;
      }
      case Op::GOTO_IF_FALSE:
      {
        row["next"] = read_u16();
        break;
      }
      case Op::GOTO:
      {
        row["next"] = read_u16();
        break;
      }
      case Op::PUSH_LOCAL_INT:
      {
        row["offset"] = read_u16();
        break;
      }
      case Op::POP_LOCAL_INT:
      {
        row["offset"] = read_u16();
        break;
      }
      case Op::PUSH_LOCAL_INT_ARRAY:
      {
        row["offset"] = read_u16();
        break;
      }
      case Op::POP_LOCAL_INT_ARRAY:
      {
        row["offset"] = read_u16();
        break;
      }
      case Op::PUSH_LOCAL_OBJECT:
      {
        row["offset"] = read_u16();
        break;
      }
      case Op::POP_LOCAL_OBJECT:
      {
        row["offset"] = read_u16();
        break;
      }
      case Op::PUSH_FIELD_INT:
      {
        row["offset"] = read_u16();
        break;
      }
      case Op::POP_FIELD_INT:
      {
        row["offset"] = read_u16();
        break;
      }
      case Op::PUSH_FIELD_INT_ARRAY:
      {
        row["offset"] = read_u16();
        break;
      }
      case Op::POP_FIELD_INT_ARRAY:
      {
        row["offset"] = read_u16();
        break;
      }
      case Op::PUSH_FIELD_OBJECT:
      {
        row["offset"] = read_u16();
        break;
      }
      case Op::POP_FIELD_OBJECT:
      {
        row["offset"] = read_u16();
        break;
      }
      case Op::PRINT_LINE:
      {
        break;
      }
      case Op::LESS_THAN:
      {
        break;
      }
      case Op::ADD:
      {
        break;
      }
      case Op::SUB:
      {
        break;
      }
      case Op::MUL:
      {
        break;
      }
      case Op::NOT:
      {
        break;
      }
      case Op::ARRAY_LENGTH:
      {
        break;
      }
      case Op::METHOD_CALL:
      {
        row["class_index"] = read_u16();
        row["method_index"] = read_u16();
        break;
      }
      case Op::NEW_INT_ARRAY:
      {
        break;
      }
      case Op::NEW:
      {
        row["class_index"] = read_u16();
        break;
      }
      case Op::PUSH_INT:
      {
        row["value"] = read_i32();
        break;
      }
      case Op::PUSH_INT_ARRAY_ITEM:
      {
        break;
      }
      case Op::POP_INT_ARRAY_ITEM:
      {
        break;
      }
      case Op::RETURN_INT:
      {
        break;
      }
      case Op::RETURN_INT_ARRAY:
      {
        break;
      }
      case Op::RETURN_OBJECT:
      {
        break;
      }
      case Op::EXIT:
      {
        break;
      }
      }
      result.push_back(row);
    }
  }
  return result;
}