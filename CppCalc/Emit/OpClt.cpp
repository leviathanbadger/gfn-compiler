#include "stdafx.h"
#include "Emit/OpClt.h"

OpClt::OpClt()
{
}
OpClt::~OpClt()
{
}

void OpClt::eval(EvalStack &stack) const
{
    int32_t lhs, rhs;
    std::tie(lhs, rhs) = stack.pop2();
    stack.push(lhs < rhs ? 1 : 0);
}
