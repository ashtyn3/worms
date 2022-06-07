#include "parser.h"

#include <iostream>

void Parser::next_tok() {
  index++;
  tok = toks[index];
};
Lex_tok Parser::peek() {
  if (index + 1 < toks.size()) {
    return toks[index + 1];
  } else {
    return {};
  }
};

Parse_tok *Parser::parse_fn() {
  Parse_tok *p = new Parse_tok;
  p->line = tok.pos.line;

  Function *fn = new Function;
  // consume fn
  next_tok();
  fn->name = tok.token;

  // consume (
  next_tok();
  if (tok.type == L_PAREN) {
    next_tok();
  }
  if (peek().type != ARROW) {
    vector<Lex_tok> sub_tree;
    while (tok.type != R_PAREN) {
      sub_tree.push_back(tok);
      next_tok();
    }
    Parser p(sub_tree);
    while (p.index < sub_tree.size()) {
      fn->params.push_back(p.run());
    }
  }
  next_tok();

  p->function = fn;
  return p;
}
Parse_tok *Parser::parse_param() {
  Parse_tok *p = new Parse_tok;
  p->line = tok.pos.line;
  Param *param = new Param;

  param->name = tok.token;
  next_tok();
  param->type = tok.token;
  next_tok();

  p->param = param;
  return p;
}

Parse_tok *Parser::run() {
  Parse_tok *t;
  if (tok.token == "fn") {
    t = parse_fn();
  } else if (tok.type == IDENT && peek().type == BUILTIN) {
    t = parse_param();
  } else {
    cout << "unexpected lexer token (" << tok.pos.start_col << ":"
         << tok.pos.line << "): " << tok.token << endl;
    cout << "  token type: " << tok.type << endl;
    exit(1);
    return {};
  }

  next_tok();
  return t;
}
