#pragma once

#include "lex.h"

class Parse_tok;
class Function {
public:
  vector<Parse_tok *> body;
  string name;
  vector<Parse_tok *> params;
};
class Param {
public:
  string name;
  string type;
};

class Parse_tok {
public:
  int line;
  Param *param;
  Function *function;
};
