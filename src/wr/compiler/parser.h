#pragma once
#include "lex.h"
#include "parse.h"

class Parser {
  int index = -1;
  Lex_tok tok;

public:
  vector<Lex_tok> toks;
  void next_tok();
  Lex_tok peek();
  Parse_tok *run();
  vector<Parse_tok *> while_run();
  Parse_tok *parse_fn();
  Parse_tok *parse_param();
  Parse_tok *parse_fn_call();
  Parse_tok *parse_ret();
  Parse_tok *parse_end();
  Parser(vector<Lex_tok> toks) : toks(toks) { next_tok(); }
};
