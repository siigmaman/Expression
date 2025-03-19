#include <gtest/gtest.h>
#include "../../src/NODE.h"

using namespace ExpressionLibrary;

TEST(ExpNodeTest, Evaluate) {
    auto arg = std::make_shared<ConstNode<double>>(1.0);
    ExpNode<double> node(arg);
    EXPECT_DOUBLE_EQ(node.evaluate({}), std::exp(1.0));
}

TEST(ExpNodeTest, Differentiate) {
    auto arg = std::make_shared<VarNode<double>>("x");
    ExpNode<double> node(arg);
    auto derivative = node.differentiate("x");
    EXPECT_EQ(derivative->to_string(), "(exp(x) * 1)");
}
