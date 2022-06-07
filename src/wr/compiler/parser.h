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
  Parse_tok *parse_fn();
  Parse_tok *parse_param();
  Parser(vector<Lex_tok> toks) : toks(toks) { next_tok(); }
};
