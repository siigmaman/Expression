#include <gtest/gtest.h>
#include "../../src/NODE.h"

using namespace ExpressionLibrary;

TEST(PowerNodeTest, Evaluate) {
    auto node = std::make_shared<PowerNode<double>>(
        std::make_shared<ConstNode<double>>(2.0),
        std::make_shared<ConstNode<double>>(3.0)
    );
    EXPECT_DOUBLE_EQ(node->evaluate({}), 8.0);
}

TEST(PowerNodeTest, ToString) {
    auto node = std::make_shared<PowerNode<double>>(
        std::make_shared<VarNode<double>>("x"),
        std::make_shared<ConstNode<double>>(2.0)
    );
    EXPECT_EQ(node->to_string(), "(x ^ 2)");
}

TEST(PowerNodeTest, Clone) {
    auto node = std::make_shared<PowerNode<double>>(
        std::make_shared<ConstNode<double>>(5.0),
        std::make_shared<VarNode<double>>("y")
    );
    auto clone = node->clone();
    EXPECT_EQ(clone->to_string(), "(5 ^ y)");
}

TEST(PowerNodeTest, Substitute) {
    auto node = std::make_shared<PowerNode<double>>(
        std::make_shared<VarNode<double>>("x"),
        std::make_shared<ConstNode<double>>(4.0)
    );
    auto substituted = node->substitute("x", 2.0);
    EXPECT_DOUBLE_EQ(substituted->evaluate({}), 16.0);
}
