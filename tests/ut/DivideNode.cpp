#include <gtest/gtest.h>
#include "../../src/NODE.h"

using namespace ExpressionLibrary;

TEST(DivideNodeTest, Evaluate) {
    auto left = std::make_shared<ConstNode<double>>(10.0);
auto right = std::make_shared<ConstNode<double>>(2.0);
    DivideNode<double> node(left, right);
    EXPECT_DOUBLE_EQ(node.evaluate({}), 5.0);
}