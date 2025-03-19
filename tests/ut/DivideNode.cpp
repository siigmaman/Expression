#include <gtest/gtest.h>
#include "../../src/NODE.h"

using namespace ExpressionLibrary;

TEST(DivideNodeTest, Evaluate) {
    auto left = std::make_shared<ConstNode<double>>(10.0);
auto right = std::make_shared<ConstNode<double>>(2.0);
    DivideNode<double> node(left, right);
    EXPECT_DOUBLE_EQ(node.evaluate({}), 5.0);
}

TEST(DivideNodeTest, Differentiate) {
    auto left = std::make_shared<VarNode<double>>("x");
    auto right = std::make_shared<ConstNode<double>>(2.0);
    DivideNode<double> node(left, right);
    auto derivative = node.differentiate("x");
    EXPECT_DOUBLE_EQ(derivative->evaluate({}), 0.5);
}