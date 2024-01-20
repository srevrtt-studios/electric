#pragma once
#include "lexer.h"

class Analyzer {
private:
  std::vector<Token> analyzedTokens{};
  std::vector<Token> lexerTokens{};
  int idx{};
public:
  Analyzer(std::vector<Token> lexerTokens);
  std::vector<Token> getAnalyzedTokens();
};
