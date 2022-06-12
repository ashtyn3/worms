#include "module.h"
#include <iostream>
#include <random>

int Fn_block::make_local(string name, value_t type) {
  heap_model[name] = type;
  return 0;
}

string t_string(value_t t) {
  switch (t) {
  case snailer_null_t:
    return "nullptr";
  case snailer_pointer_t:
    return "ref";
  case snailer_int64_t:
    return "i64";
  case snailer_float64_t:
    return "f64";
  }
}

string Fn_block::produce() {
  string str;
  str.append("fn ");
  str.append(name);
  if (params.empty() == false) {
    str.append("(");
    for (int i = 0; i < (int)params.size(); i++) {
      if (i > 0) {
        str.append(params[i]->produce() + ", ");
        continue;
      }
      str.append(params[i]->produce());
    }
    str.append(")");
  }

  if (return_t != snailer_null_t) {
    str.append(" -> ");
    str.append(t_string(return_t));
    str.append(" \n");
  }
  if (body.empty() == false) {
    for (int i = 0; i < (int)body.size(); i++) {
      str.append("\t" + body[i]->produce() + "\n");
    }
  }
  str.append("end ");
  str.append(name + ";\n");
  return str;
}

Float Value::set_float(float f) {
  type = snailer_float64_t;
  s_float = {.value = f, .size = 64};
  return s_float;
}

Int Value::set_Integer(int i) {
  type = snailer_int64_t;
  integer = {.value = i, .size = 64};
  return integer;
}

string Value::produce() {
  string str;
  str.append(" ");
  switch (type) {
  case snailer_int64_t:
    str.append(to_string(integer.value));
    str.append(" i" + to_string(integer.size));
    break;
  case snailer_float64_t:
    str.append(to_string(s_float.value));
    str.append(" f" + to_string(s_float.size));
    break;
  case snailer_pointer_t:
    str.append(to_string(ptr.value));
    str.append(" ref");
    break;
  }
  return str;
}

void Fn_call_block::add_param(Value *p) { params.push_back(p); }

void Fn_block::add_param_sig(string n, value_t vt) {
  heap_model[n] = vt;
  params.push_back(new Param(n, vt));
}

string Fn_call_block::produce() {
  string str;
  str.append("call ");
  if (is_builtin) {
    str.append("&");
  }
  str.append(name);
  if (params.empty() == false) {
    for (int i = 0; i < (int)params.size(); i++) {
      str.append(params[i]->produce());
    }
  }
  str.append(";");
  return str;
}

Fn_block *Module::make_fn(string name, value_t ret_t) {
  Fn_block *fn = new Fn_block(name);
  fn->name = name;
  fn->return_t = ret_t;
  blocks[0] = fn;
  return fn;
}

void Fn_block::add_block(Block *b) { body.push_back(b); }

string Param::produce() {
  string str;
  str.append(name + " ");
  str.append(t_string(val_t));
  return str;
}
