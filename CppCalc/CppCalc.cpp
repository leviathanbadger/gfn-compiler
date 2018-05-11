#include "stdafx.h"

#include "CppCalc.h"

#include "Tokenizer.h"
#include "SyntaxTreeParser.h"

CppCalc::CppCalc()
{
}

CppCalc::~CppCalc()
{
}

int64_t CppCalc::Calculate(const std::string &src)
{
    Tokenizer tokenizer;
    auto tokens = tokenizer.tokenize(src);

    SyntaxTreeParser parser;
    //auto expr = parser.parse(tokens);

    throw std::logic_error("Not implemented");
}
