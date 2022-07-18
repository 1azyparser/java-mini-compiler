#ifndef MACHINE_H
#define MACHINE_H
#include "Program.h"
#include <stack>

class Instance;
class I32Array;

class GCObject;

enum class ObjectTag
{
  I32,
  I32ARRAY,
  INSTANCE,
  METHOD
};

class Object
{
public:
  ObjectTag tag;
  union
  {
    i32 i32_v;
    I32Array *arr_v;
    Instance *ins_v;
    Method *method_v;
  } u;
  Object() : tag{ObjectTag::I32} { u.i32_v = 0; }
  Object(i32 i32_v) : tag{ObjectTag::I32} { u.i32_v = i32_v; }
  Object(I32Array *arr_v) : tag{ObjectTag::I32ARRAY} { u.arr_v = arr_v; }
  Object(Instance *ins_v) : tag{ObjectTag::INSTANCE} { u.ins_v = ins_v; }
  Object(Method *method_v) : tag{ObjectTag::METHOD} { u.method_v = method_v; }
};

template <typename T>
struct ObjUtil
{
};
template <>
struct ObjUtil<i32>
{
  static i32 get(const Object &obj) { return obj.u.i32_v; }
};
template <>
struct ObjUtil<I32Array *>
{
  static I32Array *get(const Object &obj) { return obj.u.arr_v; }
};
template <>
struct ObjUtil<Instance *>
{
  static Instance *get(const Object &obj) { return obj.u.ins_v; }
};
template <>
struct ObjUtil<Method *>
{
  static Method *get(const Object &obj) { return obj.u.method_v; }
};

class GCObject
{
public:
  bool marked;
  GCObject *next;
  GCObject(bool marked, GCObject *next) : marked{marked}, next{next} {}
  virtual bool is_array() = 0;
};

class I32Array : public GCObject
{
public:
  vector<i32> integers;

  I32Array(size_t size, GCObject *next)
      : GCObject(false, next), integers(size, 0) {}
  bool is_array() override { return true; }
};

class Instance : public GCObject
{
public:
  Class *meta_class;
  vector<Object> fields;

  Instance(Class *meta_class, u16 n_fields, GCObject *next)
      : GCObject(false, next), meta_class{meta_class}, fields(n_fields) {}
  bool is_array() override { return false; }
};

class GC
{
public:
  GCObject *head;

  GC() : head{nullptr} {}

  Instance *new_instance(Class *meta_class, u16 n_fields)
  {
    auto obj = new Instance(meta_class, n_fields, head);
    head = obj;
    return obj;
  }

  I32Array *new_array(size_t size)
  {
    auto arr = new I32Array(size, head);
    head = arr;
    return arr;
  }

  void mark(vector<Object> &vm_stack, i32 sp);
  void sweep();
};

class Machine
{
public:
  Program &program;
  vector<Object> stack;
  Method *current_method;
  i32 fp;
  i32 sp;
  i32 pc;
  GC gc;

  Machine(Program &program, i32 stack_size)
      : program{program}, stack(stack_size),
        current_method{&(program.entry_point)}, fp{0}, sp{-1}, pc{0} {}

  u16 read_u16();
  i32 read_i32();
  void run();

  template <typename T>
  T stack_pop()
  {
    T value = ObjUtil<T>::get(stack[sp]);
    sp--;
    return value;
  }

  template <typename T>
  void stack_push(T value)
  {
    sp++;
    stack[sp] = value;
  }

  template <typename T>
  void do_return()
  {
    size_t start = static_cast<size_t>(fp + current_method->args +
                                       current_method->locals + 1);
    i32 last_fp = ObjUtil<i32>::get(stack.at(start));
    i32 last_pc = ObjUtil<i32>::get(stack.at(start + 1));
    Method *last_method = ObjUtil<Method *>::get(stack.at(start + 2));
    auto value = stack_pop<T>();

    pc = last_pc;
    sp = fp - 1;
    fp = last_fp;
    stack_push<T>(value);
    current_method = last_method;
  }

  template <typename T>
  void push_field()
  {
    u16 offset = read_u16();
    auto this_obj = stack_pop<Instance *>();
    auto value = ObjUtil<T>::get(this_obj->fields.at(offset));
    stack_push<T>(value);
  }

  template <typename T>
  void pop_field()
  {
    u16 offset = read_u16();
    auto this_obj = stack_pop<Instance *>();
    auto value = stack_pop<T>();

    this_obj->fields.at(offset) = value;
  }

  template <typename T>
  void push_local()
  {
    u16 offset = read_u16();
    stack_push<T>(ObjUtil<T>::get(stack.at(fp + offset)));
  }

  template <typename T>
  void pop_local()
  {
    u16 offset = read_u16();
    stack.at(fp + offset) = stack.at(sp);
    stack_pop<T>();
  }
};

void show_stack(vector<Object> &stack, i32 sp, i32 fp);

#endif // MACHINE_H