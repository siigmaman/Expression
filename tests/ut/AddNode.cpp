#include <gtest/gtest.h>
#include "../../src/NODE.h"

using namespace ExpressionLibrary;

TEST(AddNodeTest, Evaluate) {
    auto node = std::make_shared<AddNode<double>>(
        std::make_shared<ConstNode<double>>(2.0),
        std::make_shared<ConstNode<double>>(3.0)
    );
    EXPECT_DOUBLE_EQ(node->evaluate({}), 5.0);
}

TEST(AddNodeTest, ToString) {
    auto node = std::make_shared<AddNode<double>>(
        std::make_shared<ConstNode<double>>(2.0),
        std::make_shared<VarNode<double>>("x")
    );
    EXPECT_EQ(node->to_string(), "(2 + x)");
}

TEST(AddNodeTest, Clone) {
    auto node = std::make_shared<AddNode<double>>(
        std::make_shared<ConstNode<double>>(1.0),
        std::make_shared<ConstNode<double>>(2.0)
    );
    auto clone = node->clone();
    EXPECT_EQ(clone->to_string(), "(1 + 2)");
}

TEST(AddNodeTest, Differentiate) {
    auto node = std::make_shared<AddNode<double>>(
        std::make_shared<VarNode<double>>("x"),
        std::make_shared<ConstNode<double>>(2.0)
    );
    auto derivative = node->differentiate("x");
    EXPECT_EQ(derivative->to_string(), "(1 + 0)");
}

TEST(AddNodeTest, Substitute) {
    auto node = std::make_shared<AddNode<double>>(
        std::make_shared<VarNode<double>>("x"),
        std::make_shared<ConstNode<double>>(4.0)
    );
    auto substituted = node->substitute("x", 3.0);
    EXPECT_DOUBLE_EQ(substituted->evaluate({}), 7.0);
}
