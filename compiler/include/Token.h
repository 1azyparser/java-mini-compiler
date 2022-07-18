#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using std::string;

enum class TokenType
{
  INT,
  BOOLEAN,
  ID
};

class Token
{
public:
  int line;
  TokenType type;
  string text;
  Token(int line, TokenType type, string text)
      : line{line}, type{type}, text{text} {}
};
#endif // TOKEN_H