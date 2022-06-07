#pragma once

#include <string>
#include <vector>

using namespace std;

struct Tok_pos {
  int start_col;
  int end_col;
  int line;
};

struct Lex_tok {
  Tok_pos pos;
  int type;
  string token;
};

enum Lex_tok_type {
  IDENT = 0,
  BUILTIN,
  NUM,
  FLOAT,
  ARROW,
  R_PAREN,
  L_PAREN,
  END,
  COMMA
};

class Lexer {
  int index = -1;
  char ch;
  vector<char> lines;
  int line_num = 0;
  void next_ch() {
    index++;
    ch = lines[index];
  };
  char peek() {
    if (index + 1 < lines.size()) {
      return lines[index + 1];
    } else {
      return -1;
    }
  };

public:
  vector<Lex_tok> toks;
  Lexer(vector<char> file) : lines(file) { next_ch(); }
  void Lex();
};
