#include "stdafx.h"

#include <iostream>

#include "CppCalc.h"

int32_t main(uint32_t argc, char **argv)
{
    CppCalc calc;

    auto expr = "+1 * 2 + 3 / -4 - (25)"s;

    std::cout << expr << " = "s << calc.eval(expr) << std::endl;

    int val;
    std::cin >> val;

    return 0;
}
