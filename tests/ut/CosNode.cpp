#include <gtest/gtest.h>
#include "../../src/NODE.h"

using namespace ExpressionLibrary;

TEST(CosNodeTest, Evaluate) {
    auto arg = std::make_shared<ConstNode<double>>(0.0);
    CosNode<double> node(arg);
    EXPECT_DOUBLE_EQ(node.evaluate({}), 1.0);
}

TEST(CosNodeTest, Differentiate) {
    auto arg = std::make_shared<VarNode<double>>("x");
    CosNode<double> node(arg);
    auto derivative = node.differentiate("x");
    EXPECT_EQ(derivative->to_string(), "(-(sin(x)) * 1)");
}