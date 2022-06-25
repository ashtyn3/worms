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

#include "../include/argparse.hpp"
#include "../snailer/byte_gen.h"
#include "../version.h"
#include "compiler/gen.h"
#include "compiler/lex.h"
#include "compiler/parser.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("worms_wr", WR_VERSION);
    program.add_argument("filename")
        .help("The text bytecode filename ending in \".wors\".")
        .required();
    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    string name = program.get<string>("filename");

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

    code_gen *c = new code_gen(p_toks);
    auto blocks = c->while_gen();
    auto fn = (Fn_block *)blocks[0];

    auto gen = new snailer_byte_generator(c->mod);
    gen->proc_module();
    gen->write("worms.out");

    file.close();
    return 0;
}
