#include "Machine.h"
#include <iostream>
#include <magic_enum.hpp>

using std::cout;
using std::endl;

u16 Machine::read_u16()
{
  auto &code = this->current_method->code;
  u16 value = (code.at(pc) << 8) + code.at(pc + 1);
  pc = pc + 2;
  return value;
}

i32 Machine::read_i32()
{
  auto &code = this->current_method->code;
  i32 value = (code.at(pc) << 24) + (code.at(pc + 1) << 16) +
              (code.at(pc + 2) << 8) + code.at(pc + 3);
  pc = pc + 4;
  return value;
}

void Machine::run()
{

  auto code_length = [this]() -> i32
  {
    auto &code = current_method->code;
    return static_cast<i32>(code.size());
  };

  while (pc < code_length())
  {
    auto code = &(current_method->code);
    Op op = magic_enum::enum_cast<Op>(static_cast<int>(code->at(pc))).value();
    // show_stack(stack, sp, fp);
    // cout << magic_enum::enum_name<Op>(op) << endl;
    // cout << "pc = " << pc << endl;
    // cout << "sp = " << sp << endl;
    pc++;
    switch (op)
    {
    case Op::GOTO_IF_TRUE:
    {
      u16 index = read_u16();
      if (ObjUtil<i32>::get(stack.at(sp)))
      {
        pc = index;
      }
      break;
    }
    case Op::GOTO_IF_FALSE:
    {
      u16 index = read_u16();
      if (!ObjUtil<i32>::get(stack.at(sp)))
      {
        pc = index;
      }
      break;
    }
    case Op::GOTO:
    {
      u16 index = read_u16();
      pc = index;
      break;
    }
    case Op::PUSH_LOCAL_INT:
    {
      push_local<i32>();
      break;
    }
    case Op::POP_LOCAL_INT:
    {
      pop_local<i32>();
      break;
    }
    case Op::PUSH_LOCAL_INT_ARRAY:
    {
      push_local<I32Array *>();
      break;
    }
    case Op::POP_LOCAL_INT_ARRAY:
    {
      pop_local<I32Array *>();
      break;
    }
    case Op::PUSH_LOCAL_OBJECT:
    {
      push_local<Instance *>();
      break;
    }
    case Op::POP_LOCAL_OBJECT:
    {
      pop_local<Instance *>();
      break;
    }
    case Op::PRINT_LINE:
    {
      cout << ObjUtil<i32>::get(stack[sp]) << endl;
      sp--;
      break;
    }
    case Op::ADD:
    {
      i32 right = stack_pop<i32>();
      i32 left = stack_pop<i32>();
      stack_push<i32>(left + right);
      break;
    }
    case Op::SUB:
    {
      i32 right = stack_pop<i32>();
      i32 left = stack_pop<i32>();
      stack_push<i32>(left - right);
      break;
    }
    case Op::MUL:
    {
      i32 right = stack_pop<i32>();
      i32 left = stack_pop<i32>();
      stack_push<i32>(left * right);
      break;
    }
    case Op::NOT:
    {
      i32 operand = stack_pop<i32>();
      stack_push<i32>(!operand);
      break;
    }
    case Op::PUSH_INT:
    {
      i32 value = read_i32();
      stack_push<i32>(value);
      break;
    }
    case Op::ARRAY_LENGTH:
    {
      auto int_arr = stack_pop<I32Array *>();
      stack_push<i32>(static_cast<i32>(int_arr->integers.size()));
      break;
    }
    case Op::NEW_INT_ARRAY:
    {
      i32 length = stack_pop<i32>();
      stack_push<I32Array *>(gc.new_array(length));
      break;
    }
    case Op::LESS_THAN:
    {
      i32 right = stack_pop<i32>();
      i32 left = stack_pop<i32>();
      stack_push<i32>(static_cast<i32>(left < right));
      break;
    }
    case Op::NEW:
    {
      u16 class_index = read_u16();
      auto &meta_class = program.classes.at(class_index);
      auto instance = gc.new_instance(&meta_class, meta_class.n_fields);
      stack_push<Instance *>(instance);
      break;
    }
    case Op::METHOD_CALL:
    {
      u16 class_index = read_u16();
      u16 method_index = read_u16();
      Method &method = program.classes.at(class_index).methods.at(method_index);
      i32 current_fp = fp;
      i32 current_pc = pc;
      fp = sp - method.args;
      sp = sp + method.locals;
      stack_push<i32>(current_fp);
      stack_push<i32>(current_pc);
      stack_push<Method *>(current_method);
      current_method = &method;
      pc = 0;
      break;
    }
    case Op::RETURN_INT:
    {
      do_return<i32>();
      break;
    }
    case Op::RETURN_INT_ARRAY:
    {
      do_return<I32Array *>();
      break;
    }
    case Op::RETURN_OBJECT:
    {
      do_return<Instance *>();
      break;
    }
    case Op::PUSH_FIELD_INT:
    {
      push_field<i32>();
      break;
    }
    case Op::PUSH_FIELD_INT_ARRAY:
    {
      push_field<I32Array *>();
      break;
    }
    case Op::PUSH_FIELD_OBJECT:
    {
      push_field<Instance *>();
      break;
    }
    case Op::POP_FIELD_INT:
    {
      pop_field<i32>();
      break;
    }
    case Op::POP_FIELD_INT_ARRAY:
    {
      pop_field<I32Array *>();
      break;
    }
    case Op::POP_FIELD_OBJECT:
    {
      pop_field<Instance *>();
      break;
    }
    case Op::PUSH_INT_ARRAY_ITEM:
    {
      i32 index = stack_pop<i32>();
      auto arr = stack_pop<I32Array *>();
      stack_push<i32>(arr->integers.at(static_cast<size_t>(index)));
      break;
    }
    case Op::POP_INT_ARRAY_ITEM:
    {
      i32 value = stack_pop<i32>();
      i32 index = stack_pop<i32>();
      auto arr = stack_pop<I32Array *>();
      arr->integers.at(static_cast<size_t>(index)) = value;
      break;
    }
    case Op::EXIT:
    {
      return;
    }
    default:
    {
      throw VMError("not implemented case: " +
                    string(magic_enum::enum_name(op)));
    }
    }
  }
}

void GC::mark(vector<Object> &vm_stack, i32 sp)
{
  auto cur = head;
  while (cur != nullptr)
  {
    cur->marked = false;
    cur = cur->next;
  }
  std::stack<GCObject *> stack;
  for (i32 i = 0; i < sp; i++)
  {
    if (vm_stack[i].tag == ObjectTag::INSTANCE)
    {
      stack.push(ObjUtil<Instance *>::get(vm_stack[i]));
    }
    else if (vm_stack[i].tag == ObjectTag::I32ARRAY)
    {
      stack.push(ObjUtil<I32Array *>::get(vm_stack[i]));
    }
  }
  while (!stack.empty())
  {
    auto obj = stack.top();
    stack.pop();
    obj->marked = true;
    if (!obj->is_array())
    {
      for (const auto &field : dynamic_cast<Instance *>(obj)->fields)
      {
        if (field.tag == ObjectTag::INSTANCE)
        {
          stack.push(ObjUtil<Instance *>::get(field));
        }
        else if (field.tag == ObjectTag::I32ARRAY)
        {
          stack.push(ObjUtil<I32Array *>::get(field));
        }
      }
    }
  }
}

void GC::sweep()
{
  while (head != nullptr)
  {
    if (head->marked == false)
    {
      auto next = head->next;
      delete head;
      head = next;
    }
  }
  auto cur = head;
  while (cur != nullptr)
  {
    auto next = cur->next;
    if (next != nullptr)
    {
      if (next->marked == false)
      {
        auto next_next = next->next;
        delete next;
        cur->next = next_next;
      }
      else
      {
        cur = next;
      }
    }
  }
}

void show_stack(vector<Object> &stack, i32 sp, i32 fp)
{
  cout << "stack: " << endl;
  for (int i = 0; i <= sp; i++)
  {
    auto &obj = stack.at(static_cast<size_t>(i));
    if (i == fp)
    {
      cout << "\tfp >> offset: " << i << ", ";
    }
    else
    {
      cout << "\toffset: " << i << ", ";
    }
    if (obj.tag == ObjectTag::I32)
    {
      cout << "type: int, value: " << ObjUtil<I32Array *>::get(obj) << endl;
    }
    else if (obj.tag == ObjectTag::I32ARRAY)
    {
      cout << "type: int[]" << endl;
    }
    else if (obj.tag == ObjectTag::INSTANCE)
    {
      cout << "type: object" << endl;
    }
    else
    {
      cout << "type: method pointer" << endl;
    }
  }
}