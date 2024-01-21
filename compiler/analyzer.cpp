#include <iostream>
#include <string>

#include "analyzer.h"

Analyzer::Analyzer(std::vector<Token> lexerTokens) {
  this->lexerTokens = lexerTokens;

  std::string currentFuncName = "";
  bool function = false;

  while (idx < lexerTokens.size()) {
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

    if (function) {
      if (currentTkn.value == "}") {
        analyzedTokens.push_back(Token { "$AT_FUNC_BODY_END", "" });
      }

      if (currentTkn.value == "." && idx > 1 && idx < lexerTokens.size() - 2) {
        bool lua = false;

        if (lexerTokens[idx - 1].value == "lua") {
          lua = true;
        }

        idx++;
        std::string funcCall = lexerTokens[idx].value + ":{";

        idx += 2;
        while (idx < lexerTokens.size() - 1 && lexerTokens[idx].value != ")") {
          if (lexerTokens[idx + 1].value == ")") {
            funcCall += lexerTokens[idx].value;
          } else {
            funcCall += lexerTokens[idx].value + ",";
          }

          idx++;
        }

        funcCall += "}";

        if (lua) {
          analyzedTokens.push_back(Token { "$AT_LUA_STD_CALL", funcCall });
        } else {
          analyzedTokens.push_back(Token { "$AT_STD_CALL", funcCall });
        }
      }
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
