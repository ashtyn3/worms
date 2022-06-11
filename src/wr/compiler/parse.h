#pragma once

#include "lex.h"

class Parse_tok;
class Function {
public:
  vector<Parse_tok *> body;
  string name;
  string ret_type;
  vector<Parse_tok *> params;
};

class Function_call {
public:
  string name;
  string ret_type;
  vector<Parse_tok *> params;
};
class Return {
public:
  bool is;
};
class Param {
public:
  string name;
  string type;
};
class End {
public:
  bool is;
};

enum Parse_type { param_t, function_t, function_c_t, function_r_t, end_t };
class Parse_tok {
public:
  int line;
  int type;
  Param *param;
  Function *function;
  Function_call *fn_call;
  Return *fn_return;
  End end;
};
