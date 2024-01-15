#include <iostream>
#include <string>

#include "lexer.h"

void Lexer::skipWhitespace() {
  while (isspace(src[idx])) {
    idx++;
  }
}

std::string Lexer::tokenizeLetters() {
  std::string letters{};

  while (isalpha(src[idx])) {
    letters += src[idx];
    idx++;
  }

  return letters;
}

std::string Lexer::tokenizeString() {
  std::string str = "\"";
  idx++;

  while (idx < src.length() - 1 && src[idx] != '"') {
    str += src[idx];
    idx++;
  }

  str += "\"";
  idx++;

  return str;
}

void Lexer::tokenizeSymbol() {
  Token tkn{};
  tkn.value = src[idx];

  if (src[idx] == '(' || src[idx] == ')') {
    tkn.name = "$T_PAREN";
  } else if (src[idx] == '{' || src[idx] == '}') {
    tkn.name = "$T_BRACE";
  }

  if (src[idx] == '=') {
    tkn.name = "$T_EQUALS";
  } else if (src[idx] == ';') {
    tkn.name = "$T_SEMICOLON";
  } else if (src[idx] == '.') {
    tkn.name = "$T_PERIOD";
  }

  tokens.push_back(tkn);
}

Lexer::Lexer(std::string src) {
  this->src = src;
  skipWhitespace();

  while (idx < src.length() - 1) {
    std::string letters = tokenizeLetters();

    if (letters.length() > 0) {
      tokens.push_back(Token { "$T_LETTERS", letters });

      skipWhitespace();
      continue;
    }

    if (src[idx] == '"') {
      std::string str = tokenizeString();

      if (str.length() > 0) {
        tokens.push_back(Token { "$T_STRING", str });

        skipWhitespace();
        continue;
      } 
    }

    tokenizeSymbol();

    idx++;
    skipWhitespace();
  }
}

std::vector<Token> Lexer::getTokens() {
  return tokens;
}
