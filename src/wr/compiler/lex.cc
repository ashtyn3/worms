// Copyright (c) 2022 Ashtyn Morel-Blake
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "lex.h"
#include <cctype>
#include <iostream>
#include <vector>

void Lexer::Lex() {
    while (index < (int)lines.size()) {
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
            while (isalnum(ch) || ch == '_') {
                name.push_back(ch);
                next_ch();
            }
            // next_ch();
            toks.push_back({.pos = {.start_col = start,
                                    .end_col = index,
                                    .line = line_num + 1},
                            .type = BUILTIN,
                            .token = name});
        } else if (ch == '@' && isalpha(peek())) {
            int start = index;
            next_ch();
            string name;
            name.push_back(ch);
            next_ch();
            while (isalnum(ch) || ch == '_') {
                name.push_back(ch);
                next_ch();
            }
            // next_ch();
            toks.push_back({.pos = {.start_col = start,
                                    .end_col = index,
                                    .line = line_num + 1},
                            .type = AT,
                            .token = name});
        } else if (isdigit(ch)) {
            int start = index;
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
            // next_ch();
            if (is_float) {
                toks.push_back({.pos = {.start_col = start,
                                        .end_col = index,
                                        .line = line_num + 1},
                                .type = FLOAT,
                                .token = digit});
                continue;
            }
            toks.push_back({.pos = {.start_col = start,
                                    .end_col = index,
                                    .line = line_num + 1},
                            .type = NUM,
                            .token = digit});
        } else if (isalpha(ch)) {
            int start = index;
            string name;
            name.push_back(ch);
            next_ch();
            while (1) {
                if (!isalnum(ch) || ch == '_') {
                    break;
                }
                name.push_back(ch);
                next_ch();
            }
            // cout << name << endl;
            if (name == "call" || name == "fn" || name == "end" ||
                name == "i32" || name == "i64" || name == "f32" ||
                name == "f64" || name == "ret") {
                toks.push_back({.pos = {.start_col = start,
                                        .end_col = index,
                                        .line = line_num + 1},
                                .type = BUILTIN,
                                .token = name});
                continue;
            }
            toks.push_back({.pos = {.start_col = start,
                                    .end_col = index,
                                    .line = line_num + 1},
                            .type = IDENT,
                            .token = name});
        } else if (ch == '(') {
            next_ch();
            toks.push_back({.pos = {.start_col = index,
                                    .end_col = index,
                                    .line = line_num + 1},
                            .type = L_PAREN,
                            .token = "("});
        } else if (ch == ')') {
            next_ch();
            toks.push_back({.pos = {.start_col = index,
                                    .end_col = index,
                                    .line = line_num + 1},
                            .type = R_PAREN,
                            .token = ")"});
        } else if (ch == ';') {
            next_ch();
            toks.push_back({.pos = {.start_col = index,
                                    .end_col = index,
                                    .line = line_num + 1},
                            .type = END,
                            .token = ";"});
        } else if (ch == ',') {
            next_ch();
            toks.push_back({.pos = {.start_col = index,
                                    .end_col = index,
                                    .line = line_num + 1},
                            .type = COMMA,
                            .token = ","});
        } else if (ch == '=') {
            next_ch();
            toks.push_back({.pos = {.start_col = index,
                                    .end_col = index,
                                    .line = line_num + 1},
                            .type = EQUAL,
                            .token = "="});
        } else {
            spdlog::critical("unknown token: {}", ch);
        }
    }
}
