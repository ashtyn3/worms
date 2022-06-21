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

#include "compiler/lex.h"
#include "compiler/parser.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    if (!argc) {
        cout << "usage: worms_wr <filename>" << endl;
        return 1;
    }
    string name;
    if (argv[1]) {
        name = argv[1];
    } else {
        cout << "usage: worms_wr <filename>" << endl;
        return 1;
    }
    cout << "compiling " << name << endl;
    string line;
    vector<string> lines;

    std::ifstream file(name);
    std::string str((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());

    vector<char> v(str.length());
    copy(str.begin(), str.end(), v.begin());

    Lexer l(v);

    l.Lex();
    Parser p(l.toks);
    vector<Parse_tok *> p_toks;
    // while (p.peek().token != "" || p.peek().pos.line != -1) {
    //   p_toks.push_back(p.run());
    // }
    p_toks = p.while_run();

    file.close();
    return 0;
}
