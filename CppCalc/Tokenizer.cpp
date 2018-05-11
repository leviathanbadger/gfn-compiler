#include "stdafx.h"
#include <cctype>

#include "Tokenizer.h"

#include "Cursor.h"
#include "IntegerLiteralToken.h"
#include "OperatorToken.h"
#include "EndOfFileToken.h"

Tokenizer::Tokenizer()
{
}

Tokenizer::~Tokenizer()
{
}

std::vector<Token*> *Tokenizer::tokenize(const std::string &src)
{
    auto vec = new std::vector<Token*>();
    Cursor<char> cursor(src);

    Token *nextToken;
    while (true)
    {
        this->collectWhitespace(cursor);

        if (cursor.isDone())
        {
            vec->push_back(new EndOfFileToken(cursor.snapshot()));
            break;
        }

        nextToken = this->tryCollectToken(cursor);
        if (nextToken == nullptr)
        {
            auto idx = cursor.snapshot();
            throw std::invalid_argument("Invalid source. Failed to parse token starting with character '"s + src.at(idx) + "' at index "s + std::to_string(idx));
        }

        vec->push_back(nextToken);
    }

    return vec;
}

void Tokenizer::collectWhitespace(Cursor<char> &cursor)
{
    while (!cursor.isDone() && std::isspace(cursor.current()))
    {
        cursor.next();
    }
}

Token *Tokenizer::tryCollectToken(Cursor<char> &cursor)
{
    if (cursor.isDone()) return nullptr;

    auto nextChar = cursor.current();
    if (std::isdigit(nextChar)) return this->tryCollectIntegerLiteralToken(cursor);
    else return this->tryCollectOperatorToken(cursor);
}

IntegerLiteralToken *Tokenizer::tryCollectIntegerLiteralToken(Cursor<char> &cursor)
{
    assert(!cursor.isDone());
    assert(std::isdigit(cursor.current()));

    thread_local static std::stringstream buffer;
    buffer.clear();

    auto beginIndex = cursor.snapshot();

    if (cursor.current() == '0')
    {
        cursor.next();
        if (!cursor.isDone() && std::isdigit(cursor.current()))
        {
            cursor.reset(beginIndex);
            return nullptr;
        }
        return new IntegerLiteralToken(beginIndex, 1, 0);
    }

    while (!cursor.isDone() && std::isdigit(cursor.current()))
    {
        buffer << cursor.current();
        cursor.next();
    }

    uint64_t value;
    buffer >> value;
    return new IntegerLiteralToken(beginIndex, cursor.snapshot() - beginIndex, value);
}

OperatorToken *Tokenizer::tryCollectOperatorToken(Cursor<char> &cursor)
{
    assert(!cursor.isDone());

    auto beginIndex = cursor.snapshot();
    char nextChar = cursor.current();

    switch (nextChar)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
        cursor.next();
        return new OperatorToken(beginIndex, 1, std::string(&nextChar, 1));
    }

    return nullptr;
}