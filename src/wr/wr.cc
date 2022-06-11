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
  cout << p_toks[0]->function->ret_type << endl;

  file.close();
  return 0;
}
