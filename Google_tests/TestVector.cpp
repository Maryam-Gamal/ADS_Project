#include "gtest/gtest.h"
#include "MyVector.h"

// Test fixture for MyVector
class TestVector : public ::testing::Test {
protected:
    MyVector vec;
};
#include <gtest/gtest.h>

// Main function to run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


// Test 1: Check if a new MyVector is initially empty
TEST_F(TestVector, IsEmptyInitially) {
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.getSize(), 0);
}

// Test 2: Test push_back and at functions
TEST_F(TestVector, PushBackAndAt) {
    vec.push_back("Apple");
    vec.push_back("Banana");

    EXPECT_EQ(vec.getSize(), 2);
    EXPECT_EQ(vec.at(0), "Apple");
    EXPECT_EQ(vec.at(1), "Banana");
}

// Test 3: Test out-of-bounds access with at()
TEST_F(TestVector, AtOutOfBoundsThrowsException) {
    vec.push_back("Cherry");

    EXPECT_THROW(vec.at(1), std::out_of_range);
    EXPECT_THROW(vec.at(-1), std::out_of_range);
}

// Test 4: Test pop_back
TEST_F(TestVector, PopBack) {
    vec.push_back("Durian");
    vec.push_back("Elderberry");

    vec.pop_back();
    EXPECT_EQ(vec.getSize(), 1);
    EXPECT_EQ(vec.at(0), "Durian");

    vec.pop_back();
    EXPECT_TRUE(vec.empty());
}

// Test 5: Test operator[] for reading and writing
TEST_F(TestVector, OperatorBracket) {
    vec.push_back("Fig");
    vec.push_back("Grape");

    vec[0] = "Guava";
    EXPECT_EQ(vec[0], "Guava");
    EXPECT_EQ(vec[1], "Grape");
}

// Test 6: Test clear function
TEST_F(TestVector, Clear) {
    vec.push_back("Honeydew");
    vec.push_back("Jackfruit");

    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.getSize(), 0);
}

// Test 7: Test iterators
TEST_F(TestVector, Iterators) {
    vec.push_back("Kiwi");
    vec.push_back("Lemon");
    vec.push_back("Mango");

    MyVector::iterator it = vec.begin();
    EXPECT_EQ(*it, "Kiwi");

    ++it;
    EXPECT_EQ(*it, "Lemon");

    ++it;
    EXPECT_EQ(*it, "Mango");

    MyVector::iterator rit = vec.rbegin();
    EXPECT_EQ(*rit, "Mango");
    --rit;
    EXPECT_EQ(*rit, "Lemon");
    --rit;
    EXPECT_EQ(*rit, "Kiwi");
}
