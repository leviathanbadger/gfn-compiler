#include "stdafx.h"

#include "CppCalc.h"

#include "Tokenizer/Tokenizer.h"
#include "Tokenizer/Token.h"
#include "Parser/SyntaxTreeParser.h"
#include "Parser/ExpressionSyntax.h"
#include "Eval/ExpressionEvaluator.h"
#include "Runtime/RuntimeType.h"

CppCalc::CppCalc()
{
    RuntimeType::prepareRuntimeTypes();
}
CppCalc::~CppCalc()
{
}

int32_t CppCalc::eval(const std::string &src)
{
    Tokenizer tokenizer;
    auto tokens = tokenizer.tokenize(src);

    SyntaxTreeParser parser;
    auto expr = parser.parseExpression(*tokens);

    if (!expr->tryResolveType()) throw std::logic_error("Failed to resolve expression type."s);

    ExpressionEvaluator evaluator;
    auto result = evaluator.eval(expr);

    for (auto iter = tokens->begin(); iter != tokens->end(); iter++)
    {
        delete *iter;
    }
    tokens->clear();
    delete tokens;
    delete expr;

    return result;
}
