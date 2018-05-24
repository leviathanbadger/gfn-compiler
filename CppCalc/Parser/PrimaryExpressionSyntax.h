#pragma once
#include "Parser/ExpressionSyntax.h"

enum class PrimaryExpressionType
{
    IntegerLiteral = 1,
    BooleanLiteral = 2
};

class PrimaryExpressionSyntax :
    public ExpressionSyntax
{
public:
    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

private:
    PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, PrimaryExpressionType type);
public:
    PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, uint64_t intLiteralValue);
    PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, bool booleanLiteralValue);
    ~PrimaryExpressionSyntax();

    PrimaryExpressionType type() const;

    uint64_t intLiteralValue() const;
    bool booleanLiteralValue() const;

    virtual bool tryResolveType() override;

    virtual void emit(MethodBuilder &mb) const override;

    virtual void repr(std::stringstream &stream) const;

private:
    PrimaryExpressionType m_type;
    uint64_t m_intLiteralValue;
};
