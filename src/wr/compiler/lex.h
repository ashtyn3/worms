/*
 * Copyright (c) 2022 Ashtyn Morel-Blake
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
