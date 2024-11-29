#include "MyStack.h"
#include <gtest/gtest.h>
#include <string>

class TestStack : public ::testing::Test {
};

TEST_F(TestStack, TestPushAndTop) {
    MyStack<int> stack;
    stack.push(10);
    EXPECT_EQ(stack.top(), 10);
    stack.push(20);
    EXPECT_EQ(stack.top(), 20);
}

TEST_F(TestStack, TestPop) {
    MyStack<int> stack;
    stack.push(5);
    stack.push(15);
    stack.pop();
    EXPECT_EQ(stack.top(), 5);
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST_F(TestStack, TestEmpty) {
    MyStack<int> stack;
    EXPECT_TRUE(stack.empty());
    stack.push(7);
    EXPECT_FALSE(stack.empty());
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST_F(TestStack, TestSize) {
    MyStack<int> stack;
    EXPECT_EQ(stack.size(), 0);
    stack.push(10);
    EXPECT_EQ(stack.size(), 1);
    stack.push(20);
    EXPECT_EQ(stack.size(), 2);
    stack.pop();
    EXPECT_EQ(stack.size(), 1);
}

TEST_F(TestStack, TestClear) {
    MyStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    EXPECT_EQ(stack.size(), 3);
    stack.clear();
    EXPECT_EQ(stack.size(), 0);
    EXPECT_TRUE(stack.empty());
}

TEST_F(TestStack, TestCopyConstructor) {
    MyStack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    MyStack<int> stack2(stack1); // Use copy constructor
    EXPECT_EQ(stack2.size(), 3);
    EXPECT_EQ(stack2.top(), 3);

    stack2.pop();
    EXPECT_EQ(stack2.top(), 2);
    EXPECT_EQ(stack1.top(), 3); // Ensure stack1 is unchanged
}

TEST_F(TestStack, TestAssignmentOperator) {
    MyStack<int> stack1;
    stack1.push(1);
    stack1.push(2);

    MyStack<int> stack2;
    stack2 = stack1; // Use assignment operator

    EXPECT_EQ(stack2.size(), 2);
    EXPECT_EQ(stack2.top(), 2);

    stack2.pop();
    EXPECT_EQ(stack2.top(), 1);
    EXPECT_EQ(stack1.top(), 2); // Ensure stack1 is unchanged
}

TEST_F(TestStack, TestTopException) {
    MyStack<int> stack;
    EXPECT_THROW(stack.top(), std::runtime_error);
}

TEST_F(TestStack, TestPopException) {
    MyStack<int> stack;
    EXPECT_THROW(stack.pop(), std::runtime_error);
}

TEST_F(TestStack, TestConstTop) {
    MyStack<int> stack;
    stack.push(42);

    const MyStack<int>& constStack = stack;
    EXPECT_EQ(constStack.top(), 42);
}
