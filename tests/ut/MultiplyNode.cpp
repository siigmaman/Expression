#include <gtest/gtest.h>
#include "../../src/NODE.h"

using namespace ExpressionLibrary;

TEST(MultiplyNodeTest, Evaluate) {
    auto node = std::make_shared<MultiplyNode<double>>(
        std::make_shared<ConstNode<double>>(2.0),
        std::make_shared<ConstNode<double>>(3.0)
    );
    EXPECT_DOUBLE_EQ(node->evaluate({}), 6.0);
}

TEST(MultiplyNodeTest, ToString) {
    auto node = std::make_shared<MultiplyNode<double>>(
        std::make_shared<VarNode<double>>("x"),
        std::make_shared<ConstNode<double>>(4.0)
    );
    EXPECT_EQ(node->to_string(), "(x * 4)");
}

TEST(MultiplyNodeTest, Clone) {
    auto node = std::make_shared<MultiplyNode<double>>(
        std::make_shared<ConstNode<double>>(3.0),
        std::make_shared<VarNode<double>>("y")
    );
    auto clone = node->clone();
    EXPECT_EQ(clone->to_string(), "(3 * y)");
}

TEST(MultiplyNodeTest, Differentiate) {
    auto node = std::make_shared<MultiplyNode<double>>(
        std::make_shared<VarNode<double>>("x"),
        std::make_shared<ConstNode<double>>(2.0)
    );
auto derivative = node->differentiate("x");
    EXPECT_EQ(derivative->to_string(), "((1 * 2) + (x * 0))");
}

TEST(MultiplyNodeTest, Substitute) {
    auto node = std::make_shared<MultiplyNode<double>>(
        std::make_shared<VarNode<double>>("x"),
        std::make_shared<ConstNode<double>>(5.0)
    );
    auto substituted = node->substitute("x", 2.0);
    EXPECT_DOUBLE_EQ(substituted->evaluate({}), 10.0);
}