#pragma once
#include "val.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

enum value_t {
  snailer_null_t,
  snailer_pointer_t,
  snailer_int64_t,
  snailer_float64_t
};

class Fn_block;
class Fn_call_block;
// class Value;
// class Param;

class Block {

  Fn_block *fn;
  Fn_call_block *call;

public:
  virtual ~Block() = default;
  // int get_pointer_to();
  // int get_size();
  // int set_size();
  virtual string produce(){};
  // virtual int make_local(string name, value_t type) = 0;
  // virtual void add_block(Block *b) = 0;
};

class Module {
public:
  map<int, Block *> blocks;
  Fn_block *make_fn(string, value_t);
};

class Value : public Block {

public:
  value_t type;

  Ptr ptr;
  Int integer;
  Float s_float;

  Ptr set_ptr(int ref);
  Int set_Integer(int i);
  Float set_float(float f);

  string produce();
};
class Param : public Block {
  string name;
  value_t val_t;

public:
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
  Fn_call_block(string name, bool builtin) : name(name), is_builtin(builtin){};
  string produce();
  void add_param(Value *p);
};
