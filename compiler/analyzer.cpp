#include <iostream>
#include <string>

#include "analyzer.h"

Analyzer::Analyzer(std::vector<Token> lexerTokens) {
  this->lexerTokens = lexerTokens;

  std::string currentFuncName = "";
  bool function = false;

  while (idx < lexerTokens.size() - 1) {
    Token currentTkn = lexerTokens[idx];

    if (currentTkn.value == "func") {
      currentFuncName = lexerTokens[idx + 1].value;

      // Entry point
      if (idx < lexerTokens.size() && lexerTokens[idx + 1].value == "main") {
        analyzedTokens.push_back(Token { "$AT_ENTRY_POINT_DECL", "" });
        analyzedTokens.push_back(Token { "$AT_FUNC_BODY_START", "" });
        currentFuncName = "";
      }

      function = true;
      idx++;

      continue;
    }

    if (currentFuncName != "" && currentTkn.value == "(") {
      std::string params = "";

      while (idx < lexerTokens.size() - 1 && lexerTokens[idx].value != ")") {
        params += lexerTokens[idx].value;
        idx++;
      }

      analyzedTokens.push_back(Token { "$AT_FUNCTION_DECL", currentFuncName + ":{" + params + "}" });
    }

    idx++;
  }
}

std::vector<Token> Analyzer::getAnalyzedTokens() {
  return analyzedTokens;
}
