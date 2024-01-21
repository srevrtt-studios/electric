#include <iostream>
#include <string>

#include "utils.h"
#include "analyzer.h"
#include "lexer.h"

int main(int argc, char *argv[]) {
  std::string src = Utils::readElectricSrcFile("../test.ectr");
  Lexer *lexer = new Lexer(src);
  std::vector<Token> tokens = lexer->getTokens();
  Analyzer *analyzer = new Analyzer(tokens);

  // for (auto &tkn : tokens) {
  //   std::cout << tkn.value << std::endl;
  // }

  // std::cout << "-----------" <<  std::endl;

  for (auto &analyzedToken : analyzer->getAnalyzedTokens()) {
    std::cout << analyzedToken.name << "    " << analyzedToken.value << std::endl;
  }

  return 0;
}
