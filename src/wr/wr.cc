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
  string name(argv[1]);
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
  while (p.peek().token != "") {
    p_toks.push_back(p.run());
  }

  file.close();
}
