#include <gtest/gtest.h>
#include "../../src/NODE.h"

using namespace ExpressionLibrary;

TEST(SubtractNodeTest, Evaluate) {
    auto left = std::make_shared<ConstNode<double>>(10.0);
    auto right = std::make_shared<ConstNode<double>>(3.0);
    SubtractNode<double> node(left, right);
    EXPECT_DOUBLE_EQ(node.evaluate({}), 7.0);
}

TEST(SubtractNodeTest, Differentiate) {
    auto left = std::make_shared<VarNode<double>>("x");
    auto right = std::make_shared<ConstNode<double>>(4.0);
    SubtractNode<double> node(left, right);
    auto derivative = node.differentiate("x");
    EXPECT_DOUBLE_EQ(derivative->evaluate({}), 1.0);
}