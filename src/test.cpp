#include "EXPRESSION.cpp"
#include "NODE.h"
#include <iostream>

int main() {
    using namespace ExpressionLibrary;

    auto addExpr = Expression<double>::Parse("x + 2");
    auto addResult = addExpr.evaluate({ {"x", 3} });
    std::cout << "Addition Test: " << addExpr.ToString() << " with x=3 evaluates to " << addResult << " (expected: 5)" << std::endl;

    auto subExpr = Expression<double>::Parse("x - 2");
    auto subResult = subExpr.evaluate({ {"x", 5} });
    std::cout << "Subtraction Test: " << subExpr.ToString() << " with x=5 evaluates to " << subResult << " (expected: 3)" << std::endl;

    auto mulExpr = Expression<double>::Parse("x * 3");
    auto mulResult = mulExpr.evaluate({ {"x", 4} });
    std::cout << "Multiplication Test: " << mulExpr.ToString() << " with x=4 evaluates to " << mulResult << " (expected: 12)" << std::endl;

    auto divExpr = Expression<double>::Parse("x / 2");
    auto divResult = divExpr.evaluate({ {"x", 10} });
    std::cout << "Division Test: " << divExpr.ToString() << " with x=10 evaluates to " << divResult << " (expected: 5)" << std::endl;

    auto powExpr = Expression<double>::Parse("x ^ 2");
    auto powResult = powExpr.evaluate({ {"x", 3} });
    std::cout << "Power Test: " << powExpr.ToString() << " with x=3 evaluates to " << powResult << " (expected: 9)" << std::endl;

    auto sinExpr = Expression<double>::Parse("sin(x)");
    auto sinResult = sinExpr.evaluate({ {"x", 0} });
    std::cout << "Sin Test: " << sinExpr.ToString() << " with x=0 evaluates to " << sinResult << " (expected: 0)" << std::endl;

    auto cosExpr = Expression<double>::Parse("cos(x)");
    auto cosResult = cosExpr.evaluate({ {"x", 0} });
    std::cout << "Cos Test: " << cosExpr.ToString() << " with x=0 evaluates to " << cosResult << " (expected: 1)" << std::endl;

    auto lnExpr = Expression<double>::Parse("ln(x)");
    auto lnResult = lnExpr.evaluate({ {"x", 1} });
    std::cout << "Ln Test: " << lnExpr.ToString() << " with x=1 evaluates to " << lnResult << " (expected: 0)" << std::endl;

    auto expExpr = Expression<double>::Parse("exp(x)");
    auto expResult = expExpr.evaluate({ {"x", 0} });
    std::cout << "Exp Test: " << expExpr.ToString() << " with x=0 evaluates to " << expResult << " (expected: 1)" << std::endl;

    auto subExpr2 = Expression<double>::Parse("x + 2");
    auto substituted = subExpr2.substitute("x", 3);
    auto subResult2 = substituted.evaluate({});
    std::cout << "Substitute Test: " << subExpr2.ToString() << " after substituting x=3 evaluates to " << subResult2 << " (expected: 5)" << std::endl;

    auto diffExpr = Expression<double>::Parse("x^2 + 3*x + 2");
    auto deriv = diffExpr.differentiate("x");
    auto derivResult = deriv.evaluate({ {"x", 2} });
    std::cout << "Differentiate Test: " << diffExpr.ToString() << " differentiated w.r.t. x evaluates to " << derivResult << " at x=2 (expected: 7)" << std::endl;

    return 0;
}