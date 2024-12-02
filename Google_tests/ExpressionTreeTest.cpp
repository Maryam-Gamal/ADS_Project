#include <gtest/gtest.h>
#include <unordered_map>
#include "ExpressionTree.h"

class ExpressionTreeTest : public ::testing::Test {
protected:
    ExpressionTree expressionTree;
};

// Test Tokenization
TEST_F(ExpressionTreeTest, TokenizationTest) {
    // Test basic tokenization
    MyVector tokens1 = expressionTree.tokenize("( 5 + 3 ) * 2");
    EXPECT_EQ(tokens1.getSize(), 7);
    EXPECT_EQ(tokens1[0], "(");
    EXPECT_EQ(tokens1[1], "5");
    EXPECT_EQ(tokens1[2], "+");
    EXPECT_EQ(tokens1[3], "3");
    EXPECT_EQ(tokens1[4], ")");
    EXPECT_EQ(tokens1[5], "*");
    EXPECT_EQ(tokens1[6], "2");

    // Test tokenization with negative numbers
    MyVector tokens2 = expressionTree.tokenize("-5 + -3 * 2");
    EXPECT_EQ(tokens2.getSize(), 5);
    EXPECT_EQ(tokens2[0], "-5");
    EXPECT_EQ(tokens2[1], "+");
    EXPECT_EQ(tokens2[2], "-3");
    EXPECT_EQ(tokens2[3], "*");
    EXPECT_EQ(tokens2[4], "2");

    // Test tokenization with variables
    MyVector tokens3 = expressionTree.tokenize("AX * ( BX * CY )");
    EXPECT_EQ(tokens3.getSize(), 7);
    EXPECT_EQ(tokens3[0], "AX");
    EXPECT_EQ(tokens3[1], "*");
    EXPECT_EQ(tokens3[2], "(");
    EXPECT_EQ(tokens3[3], "BX");
    EXPECT_EQ(tokens3[4], "*");
    EXPECT_EQ(tokens3[5], "CY");
    EXPECT_EQ(tokens3[6], ")");
}

// Test Expression Type Detection
TEST_F(ExpressionTreeTest, ExpressionTypeDetectionTest) {
    // Infix expressions
    MyVector infixTokens1 = expressionTree.tokenize("5 + 3 * 2");
    EXPECT_EQ(expressionTree.determineExpressionType(infixTokens1), 1);

    // Prefix expressions
    MyVector prefixTokens1 = expressionTree.tokenize("+ 5 * 3 2");
    EXPECT_EQ(expressionTree.determineExpressionType(prefixTokens1), 2);

    // Postfix expressions
    MyVector postfixTokens1 = expressionTree.tokenize("5 3 2 * +");
    EXPECT_EQ(expressionTree.determineExpressionType(postfixTokens1), 3);
}

// Test Tree Building from Different Expression Types
TEST_F(ExpressionTreeTest, TreeBuildingTest) {
    // Infix Expression with Variables
    std::string infixExpr = "( AX * ( BX * ( ( ( CY + AY ) + BY ) * CX ) ) )";
    ExpressionTree::TreeNode* infixRoot = expressionTree.buildTreeFromInfix(infixExpr);
    EXPECT_NE(infixRoot, nullptr);

    std::string infixTraversal = expressionTree.inorder(infixRoot);
    EXPECT_FALSE(infixTraversal.empty());

    // Prefix Expression with Variables
    MyVector prefixTokens = expressionTree.tokenize("* AX * BX * + + CY AY BY CX");
    ExpressionTree::TreeNode* prefixRoot = expressionTree.buildTreeFromPrefix(prefixTokens);
    EXPECT_NE(prefixRoot, nullptr);

    std::string prefixTraversal = expressionTree.preorder(prefixRoot);
    EXPECT_FALSE(prefixTraversal.empty());

    // Postfix Expression with Variables
    MyVector postfixTokens = expressionTree.tokenize("AX BX CY AY + BY + CX * * *");
    ExpressionTree::TreeNode* postfixRoot = expressionTree.buildTreeFromPostfix(postfixTokens);
    EXPECT_NE(postfixRoot, nullptr);

    std::string postfixTraversal = expressionTree.postorder(postfixRoot);
    EXPECT_FALSE(postfixTraversal.empty());

    // Cleanup
    expressionTree.deleteTree(infixRoot);
    expressionTree.deleteTree(prefixRoot);
    expressionTree.deleteTree(postfixRoot);
}

// Test Traversal Methods
TEST_F(ExpressionTreeTest, TraversalMethodsTest) {
    std::string infixExpr = "( 5 + 3 ) * 2";
    ExpressionTree::TreeNode* root = expressionTree.buildTreeFromInfix(infixExpr);

    std::string inorderResult = expressionTree.inorder(root);
    EXPECT_EQ(inorderResult, "( ( 5 + 3 ) * 2 )");

    std::string preorderResult = expressionTree.preorder(root);
    EXPECT_EQ(preorderResult, "* + 5 3 2");

    std::string postorderResult = expressionTree.postorder(root);
    EXPECT_EQ(postorderResult, "5 3 + 2 *");

    expressionTree.deleteTree(root);
}

// Test Evaluation with multi-Variables
TEST_F(ExpressionTreeTest, EvaluationTest) {
    // Test with multiple variables
    std::string expr = "( AX * ( BX * ( ( ( CY + AY ) + BY ) * CX ) ) )";
    ExpressionTree::TreeNode* root = expressionTree.buildTreeFromInfix(expr);

    std::unordered_map<std::string, double> variables = {
        {"AX", 2.0}, {"BX", 3.0},
        {"CY", 1.0}, {"AY", 4.0},
        {"BY", 5.0}, {"CX", 2.0}
    };

    EXPECT_NO_THROW({
        long double result = expressionTree.evaluate(root, variables);
        EXPECT_NEAR(result, 120.0, 1e-9);
    });

    expressionTree.deleteTree(root);
}

// Test Arithmetic Expression with Various Operators
TEST_F(ExpressionTreeTest, ComplexArithmeticTest) {
    std::string expr = "123 - 4 * 5 + 33 / 11 - 2 ^ 3 + 45 * 2";
    ExpressionTree::TreeNode* root = expressionTree.buildTreeFromInfix(expr);

    std::unordered_map<std::string, double> emptyVars;
    long double result = expressionTree.evaluate(root, emptyVars);
    EXPECT_NEAR(result, 188.0, 1e-9);

    expressionTree.deleteTree(root);
}

// Error Handling Tests
TEST_F(ExpressionTreeTest, ErrorHandlingTest) {
    // Test invalid parentheses
    EXPECT_THROW({
        expressionTree.buildTreeFromInfix("( 5 + 3 ) )");
    }, std::runtime_error);

    // Test division by zero
    std::string divByZeroExpr = "10 / 0";
    ExpressionTree::TreeNode* root = expressionTree.buildTreeFromInfix(divByZeroExpr);
    std::unordered_map<std::string, double> emptyVars;

    EXPECT_THROW({
        expressionTree.evaluate(root, emptyVars);
    }, std::runtime_error);

    if (root) expressionTree.deleteTree(root);

    // Test unbalanced expression
    EXPECT_THROW({
        expressionTree.validateExpressionStructure(expressionTree.tokenize("5 + * 3"));
    }, std::runtime_error);
}

// Validation Type Tests
TEST_F(ExpressionTreeTest, ValidationTests) {
    // Valid infix expression
    MyVector infixTokens = expressionTree.tokenize("5 + 3 * 2");
    EXPECT_NO_THROW({
        expressionTree.validateExpressionType(infixTokens, 1);
    });

    // Invalid type throws runtime_error
    MyVector prefixTokens = expressionTree.tokenize("+ 5 * 3 2");
    EXPECT_THROW({
        expressionTree.validateExpressionType(prefixTokens, 1);
    }, std::runtime_error);
}

// Additional Complex Expressions Test
TEST_F(ExpressionTreeTest, ComplexExpressionsTest) {
    std::string complexInfix = "( ( H * ( ( ( ( A + ( ( B + C ) * D ) ) * F ) * G ) * E ) ) + J )";
    ExpressionTree::TreeNode* root = expressionTree.buildTreeFromInfix(complexInfix);

    std::unordered_map<std::string, double> variables = {
        {"H", 2.0}, {"A", 3.0}, {"B", 4.0},
        {"C", 1.0}, {"D", 2.0}, {"F", 3.0},
        {"G", 2.0}, {"E", 1.0}, {"J", 5.0}
    };

    EXPECT_NO_THROW({
        long double result = expressionTree.evaluate(root, variables);
        EXPECT_TRUE(result != 0);  // Just ensuring a non-zero result
    });

    expressionTree.deleteTree(root);
}

