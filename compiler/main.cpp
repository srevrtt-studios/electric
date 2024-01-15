#include <iostream>
#include <string>

#include "utils.h"
#include "lexer.h"

int main(int argc, char *argv[]) {
  std::string src = Utils::readElectricSrcFile("../test.ectr");
  Lexer *lexer = new Lexer(src);
  std::vector<Token> tokens = lexer->getTokens();

  for (auto &tkn : tokens) {
    std::cout << tkn.name << ":" << tkn.value << std::endl;
  }

  return 0;
}
