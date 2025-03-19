#include <gtest/gtest.h>
#include "../../src/NODE.h"

using namespace ExpressionLibrary;

TEST(ConstNodeTest, Evaluate) {
    ConstNode<double> node(5.0);
    EXPECT_DOUBLE_EQ(node.evaluate({}), 5.0);
}

TEST(ConstNodeTest, ToString) {
    ConstNode<double> node(3.14);
    EXPECT_EQ(node.to_string(), "3.14");
}

TEST(ConstNodeTest, Clone) {
    auto node = std::make_shared<ConstNode<double>>(7.0);
    auto clone = node->clone();
    EXPECT_DOUBLE_EQ(clone->evaluate({}), 7.0);
}

TEST(ConstNodeTest, Differentiate) {
    ConstNode<double> node(4.0);
    auto derivative = node.differentiate("x");
    EXPECT_DOUBLE_EQ(derivative->evaluate({}), 0.0);
}

TEST(ConstNodeTest, Substitute) {
    ConstNode<double> node(2.5);
    auto substituted = node.substitute("x", 10.0);
    EXPECT_DOUBLE_EQ(substituted->evaluate({}), 2.5);
}