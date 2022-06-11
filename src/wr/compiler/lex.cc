#include "lex.h"
#include <cctype>
#include <iostream>
#include <vector>

void Lexer::Lex() {
  while (index < lines.size()) {
    if (ch == '\n') {
      line_num++;
      next_ch();
    } else if (ch == ' ') {
      next_ch();
    } else if (ch == '-' && peek() == '>') {
      next_ch();
      next_ch();
      toks.push_back({.pos = {.start_col = index - 1,
                              .end_col = index,
                              .line = line_num + 1},
                      .type = ARROW,
                      .token = "->"});
    } else if (ch == '&' && isalpha(peek())) {
      int start = index;
      next_ch();
      string name;
      name.push_back(ch);
      next_ch();
      while (isalnum(ch)) {
        name.push_back(ch);
        next_ch();
      }
      next_ch();
      toks.push_back(
          {.pos = {.start_col = start, .end_col = index, .line = line_num + 1},
           .type = BUILTIN,
           .token = name});
    } else if (isdigit(ch)) {
      int start = index;
      next_ch();
      string digit;
      digit.push_back(ch);
      next_ch();
      bool is_float;
      while (isdigit(ch) || ch == '.') {
        if (ch == '.') {
          is_float = true;
        }
        digit.push_back(ch);
        next_ch();
      }
      next_ch();
      if (is_float) {
        toks.push_back({.pos = {.start_col = start,
                                .end_col = index,
                                .line = line_num + 1},
                        .type = FLOAT,
                        .token = digit});
        continue;
      }
      toks.push_back(
          {.pos = {.start_col = start, .end_col = index, .line = line_num + 1},
           .type = NUM,
           .token = digit});
    } else if (isalpha(ch)) {
      int start = index;
      string name;
      name.push_back(ch);
      next_ch();
      while (isalnum(ch)) {
        name.push_back(ch);
        next_ch();
      }
      if (name == "call" || name == "fn" || name == "end" || name == "i32" ||
          name == "i64" || name == "f32" || name == "f64" || name == "ret") {
        toks.push_back({.pos = {.start_col = start,
                                .end_col = index,
                                .line = line_num + 1},
                        .type = BUILTIN,
                        .token = name});
        continue;
      }
      toks.push_back(
          {.pos = {.start_col = start, .end_col = index, .line = line_num + 1},
           .type = IDENT,
           .token = name});
    } else if (ch == '(') {
      next_ch();
      toks.push_back(
          {.pos = {.start_col = index, .end_col = index, .line = line_num + 1},
           .type = L_PAREN,
           .token = "("});
    } else if (ch == ')') {
      next_ch();
      toks.push_back(
          {.pos = {.start_col = index, .end_col = index, .line = line_num + 1},
           .type = R_PAREN,
           .token = ")"});
    } else if (ch == ';') {
      next_ch();
      toks.push_back(
          {.pos = {.start_col = index, .end_col = index, .line = line_num + 1},
           .type = END,
           .token = ";"});
    } else if (ch == ',') {
      next_ch();
      toks.push_back(
          {.pos = {.start_col = index, .end_col = index, .line = line_num + 1},
           .type = COMMA,
           .token = ","});
    }
  }
}
