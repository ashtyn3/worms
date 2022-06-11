#include "parser.h"

#include <iostream>

void Parser::next_tok() {
  if (index >= (int)toks.size()) {
    tok = {.pos = {.start_col = -1, .end_col = -1, .line = -1},
           .type = END,
           .token = "EOF"};
    return;
  }
  index++;
  tok = toks[index];
};
Lex_tok Parser::peek() {
  if (index + 1 < (int)toks.size()) {
    return toks[index + 1];
  } else {
    return {};
  }
};

Parse_tok *Parser::parse_fn() {
  Parse_tok *p = new Parse_tok;
  p->line = tok.pos.line;
  p->type = function_t;

  Function *fn = new Function;
  // consume fn
  next_tok();
  fn->name = tok.token;
  int curr_line = tok.pos.line;

  next_tok();
  // consume (
  if (tok.type == L_PAREN) {
    next_tok();
  }
  if (peek().type != ARROW && peek().pos.line == curr_line &&
      tok.type != ARROW) {
    vector<Lex_tok> sub_tree;
    while (tok.type != R_PAREN) {
      sub_tree.push_back(tok);
      next_tok();
    }
    Parser p(sub_tree);
    // while (p.index < sub_tree.size()) {
    //   fn->params.push_back(p.run());
    // }
    fn->params = p.while_run();
  }
  if (tok.type == R_PAREN) {
    next_tok();
  }
  if (tok.type == ARROW) {
    next_tok();
    fn->ret_type = tok.token;
    next_tok();
  } else {
    if (tok.pos.line == curr_line || tok.pos.line < curr_line) {
      cout << "broken syntax (" << tok.pos.start_col << ":" << tok.pos.line
           << "): expected -> or newline" << endl;
      exit(1);
    }
  }

  vector<Lex_tok> sub_tree;
  while (tok.token != "end" && peek().token != fn->name) {
    sub_tree.push_back(tok);
    next_tok();
  }
  next_tok();
  Parser bod_p(sub_tree);
  // while (bod_p.index < sub_tree.size()) {
  //   fn->params.push_back(bod_p.run());
  // }
  fn->body = bod_p.while_run();

  p->function = fn;
  next_tok();
  return p;
}
Parse_tok *Parser::parse_param() {
  Parse_tok *p = new Parse_tok;
  p->line = tok.pos.line;
  p->type = param_t;
  Param *param = new Param;

  int curr_line = tok.pos.line;
  param->name = tok.token;

  next_tok();

  if (tok.type != BUILTIN || tok.pos.line != curr_line) {
    cout << "broken syntax (" << tok.pos.start_col << ":" << tok.pos.line
         << "): expected param type" << endl;
    exit(1);
  } else {
    param->type = tok.token;
    next_tok();
    // if (tok.type == END) {
    // next_tok();
    // }
  }

  p->param = param;
  return p;
}

Parse_tok *Parser::parse_fn_call() {
  Parse_tok *p = new Parse_tok;
  p->line = tok.pos.line;
  p->type = function_c_t;
  Function_call *fn_call = new Function_call;

  // consume call;
  next_tok();

  fn_call->name = tok.token;

  next_tok();

  if (tok.type != END) {
    vector<Lex_tok> sub_tree;
    while (1) {
      sub_tree.push_back(tok);
      if (tok.type == END) {
        break;
      }
      next_tok();
    }
    next_tok();
    Parser bod_p(sub_tree);
    // while (bod_p.index < (int)sub_tree.size()) {
    //   if (bod_p.tok.pos.line == -1) {
    //     break;
    //   }
    //   fn_call->params.push_back(bod_p.run());
    // }
    fn_call->params = bod_p.while_run();
  }
  p->fn_call = fn_call;
  return p;
}

Parse_tok *Parser::parse_ret() {
  // consume ret
  next_tok();
  // consume ;
  next_tok();

  Parse_tok *p = new Parse_tok;
  p->line = tok.pos.line;
  p->type = function_r_t;

  Return *r = new Return;
  r->is = true;

  p->fn_return = r;
  next_tok();
  return p;
}
Parse_tok *Parser::parse_end() {
  Parse_tok *p = new Parse_tok;
  p->line = tok.pos.line;
  p->type = function_r_t;

  Return *r = new Return;
  r->is = true;

  p->fn_return = r;

  return p;
}
Parse_tok *Parser::run() {
  Parse_tok *t;
  if (tok.token == ";") {
    t = parse_end();
    next_tok();
  } else if (tok.token == "fn") {
    t = parse_fn();
  } else if ((tok.type == IDENT || tok.type == NUM || tok.type == FLOAT) &&
             peek().type == BUILTIN) {
    t = parse_param();
  } else if (tok.token == "call") {
    t = parse_fn_call();
  } else if (tok.token == "ret") {
    t = parse_ret();
  } else {
    cout << "unexpected lexer token (" << tok.pos.start_col << ":"
         << tok.pos.line << "): " << tok.token << endl;
    cout << "  token type: " << tok.type << endl;
    exit(1);
    return {};
  }

  return t;
}

vector<Parse_tok *> Parser::while_run() {
  vector<Parse_tok *> TOKS;
  while (tok.pos.line != -1 && index < (int)toks.size() && tok.token != ";") {
    TOKS.push_back(run());
  }
  return TOKS;
}
