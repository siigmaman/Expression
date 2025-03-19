#include <gtest/gtest.h>
#include "../../src/NODE.h"

using namespace ExpressionLibrary;

TEST(LnNodeTest, Evaluate) {
    auto arg = std::make_shared<ConstNode<double>>(std::exp(1.0));
    LnNode<double> node(arg);
    EXPECT_DOUBLE_EQ(node.evaluate({}), 1.0);
}

TEST(LnNodeTest, Differentiate) {
    auto arg = std::make_shared<VarNode<double>>("x");
    LnNode<double> node(arg);
    auto derivative = node.differentiate("x");
    EXPECT_EQ(derivative->to_string(), "(1 / x)");
}