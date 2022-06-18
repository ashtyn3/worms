#pragma once

#ifndef MODULE_H
#define MODULE_H
#include "../lib/inst.h"
#include "val.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

enum value_t {
  snailer_int64_t,
  snailer_int32_t,
  snailer_int16_t,
  snailer_int8_t,
  snailer_float64_t,
  snailer_null_t,
  snailer_pointer_t,
};
enum block_t {
  snailer_fn_block_t,
  snailer_fn_call_block_t,
};

class Fn_block;
class Fn_call_block;
// class Value;
// class Param;

class Block {

  Fn_block *fn;
  Fn_call_block *call;

public:
  word p_size = IWORD_8(0);
  virtual ~Block() = default;
  // int get_pointer_to();
  virtual Inst raw_instruction(){};
  virtual string produce(){};
  block_t type;
  // virtual int make_local(string name, value_t type) = 0;
  // virtual void add_block(Block *b) = 0;
};

class Module {
public:
  vector<Block *> blocks;
  Fn_block *make_fn(string, value_t);
};

class Value : public Block {

public:
  value_t type;

  Ptr ptr;
  Int integer;
  Float s_float;

  Ptr set_ptr(int ref);

  Int set_Integer(int64_t i);
  Int set_Integer32(int32_t i);
  Int set_Integer16(int16_t i);
  Int set_Integer8(int8_t i);

  Float set_float(float f);

  string produce();
  Inst raw_instruction();
};
class Param : public Block {
public:
  string name;
  value_t val_t;
  Param(string name, value_t vt) : name(name), val_t(vt){};
  string produce();
};

class Fn_block : public Block {
protected:
  map<string, value_t> heap_model;

public:
  Fn_block(string name) : name(name){};
  string name;
  value_t return_t;
  vector<Param *> params;
  vector<Block *> body;
  int make_local(string name, value_t type);
  void add_block(Block *b);
  void add_param_sig(string n, value_t vt);
  string produce();
};

class Fn_call_block : public Block {
public:
  string name;
  bool is_builtin;
  vector<Value *> params;
  Fn_call_block(string name, bool builtin) : name(name), is_builtin(builtin) {
    type = snailer_fn_call_block_t;
  };
  string produce();
  Inst raw_instruction();
  void add_param(Value *p);
};
#endif
