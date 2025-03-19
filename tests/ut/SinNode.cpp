#include <gtest/gtest.h>
#include "../../src/NODE.h"

using namespace ExpressionLibrary;

TEST(SinNodeTest, Evaluate) {
    auto arg = std::make_shared<ConstNode<double>>(0.0);
    SinNode<double> node(arg);
    EXPECT_DOUBLE_EQ(node.evaluate({}), 0.0);
}

TEST(SinNodeTest, Differentiate) {
    auto arg = std::make_shared<VarNode<double>>("x");
    SinNode<double> node(arg);
    auto derivative = node.differentiate("x");
    EXPECT_EQ(derivative->to_string(), "(cos(x) * 1)");
}