#include <gtest/gtest.h>
#include "../../src/NODE.h"

using namespace ExpressionLibrary;

TEST(NegateNodeTest, Evaluate) {
    auto arg = std::make_shared<ConstNode<double>>(3.0);
    NegateNode<double> node(arg);
    EXPECT_DOUBLE_EQ(node.evaluate({}), -3.0);
}

TEST(NegateNodeTest, Differentiate) {
    auto arg = std::make_shared<VarNode<double>>("x");
    NegateNode<double> node(arg);
    auto derivative = node.differentiate("x");
    EXPECT_EQ(derivative->to_string(), "-(1)");
}