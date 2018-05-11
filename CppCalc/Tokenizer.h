#pragma once

#include <string>

#include "Cursor.h"

class Token;
class IntegerLiteralToken;
class OperatorToken;

class Tokenizer
{
public:
    Tokenizer();
    ~Tokenizer();

    std::vector<Token*> *tokenize(const std::string &src);

private:
    void collectWhitespace(Cursor<char> &cursor);
    Token *tryCollectToken(Cursor<char> &cursor);
    IntegerLiteralToken *tryCollectIntegerLiteralToken(Cursor<char> &cursor);
    OperatorToken *tryCollectOperatorToken(Cursor<char> &cursor);
};