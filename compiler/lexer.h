#pragma once

#include <string>
#include <vector>

struct Token {
  std::string name;
  std::string value;
};

class Lexer {
private:
  std::vector<Token> tokens;
  std::string src{};
  int idx{};

  void skipWhitespace();
  std::string tokenizeLetters();
  std::string tokenizeString();
  void tokenizeSymbol();
public:
  Lexer(std::string src);
  std::vector<Token> getTokens();
};
