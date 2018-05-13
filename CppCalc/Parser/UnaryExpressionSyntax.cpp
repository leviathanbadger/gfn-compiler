#include "stdafx.h"

#include "Parser/UnaryExpressionSyntax.h"

#include "Parser/PrimaryExpressionSyntax.h"
#include "Tokenizer/Token.h"
#include "Emit/OpLdcI4.h"
#include "Emit/OpNeg.h"

UnaryExpressionSyntax::UnaryExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *expr, const std::string op)
    : ExpressionSyntax(startIndex, length), m_expr(expr), m_op(op)
{
}
UnaryExpressionSyntax::~UnaryExpressionSyntax()
{
}

ExpressionSyntax *UnaryExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    if (cursor.current()->isOperator())
    {
        auto op = cursor.current()->op();
        if (op == "+" || op == "-")
        {
            auto beginIndex = cursor.snapshot();
            cursor.next();
            ExpressionSyntax *rhs = tryParseSyntax<UnaryExpressionSyntax>(cursor);
            if (rhs == nullptr) cursor.reset(beginIndex);
            else return new UnaryExpressionSyntax(beginIndex, cursor.snapshot() - beginIndex, rhs, op);
        }
    }

    return tryParseSyntax<PrimaryExpressionSyntax>(cursor);
}

ExpressionSyntax *UnaryExpressionSyntax::expr() const
{
    return this->m_expr;
}
const std::string UnaryExpressionSyntax::op() const
{
    return this->m_op;
}

void UnaryExpressionSyntax::emit(std::vector<Opcode*> &ops) const
{
    //Note: this top part is to handle the special case of having the minimum value for uint32_t
    if (this->op() == "-"s)
    {
        auto primaryExpr = dynamic_cast<PrimaryExpressionSyntax*>(this->expr());
        if (primaryExpr != nullptr && primaryExpr->type() == PrimaryExpressionType::IntegerLiteral && primaryExpr->intLiteralValue() == (uint64_t)-(int64_t)std::numeric_limits<int32_t>::min())
        {
            ops.push_back(new OpLdcI4(std::numeric_limits<int32_t>::min()));
            return;
        }
    }

    this->expr()->emit(ops);

    if (this->op() == "-"s) ops.push_back(new OpNeg());
    else if (this->op() == "+"s) { ; } //NOP
    else throw std::logic_error("Invalid unary expression operation: " + this->op());
}

void UnaryExpressionSyntax::repr(std::stringstream &stream) const
{
    stream << this->op() << this->expr();
}