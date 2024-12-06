//implemented by Fatima Nageh
#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <string>
#include "MyVector.h"
#include <unordered_map>

class ExpressionTree {
public:
    // Represents a node in the expression tree
    struct TreeNode {
        std::string value;  // Stores the value of the node (operator, number, or variable)
        TreeNode* left;   // Pointer to the left child node
        TreeNode* right;  // Pointer to the right child node

        // Constructor to initialize a node with a given value
        TreeNode(const std::string& val) : value(val), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;  // Root of the expression tree

    // Helper functions
    bool isOperator(const std::string& token) const;  // Checks if a token is a mathematical operator
    bool isValidParentheses(const std::string& expression) const;  // Validates parentheses balance
    bool isNumber(const std::string& str) const; // Checks if a string is a valid number
    static bool isVariable(const std::string& token); // Checks if a token is a valid variable name
    static int precedence(const std::string& op);   // Determines operator precedence
    void deleteTree(TreeNode* node);  // Recursively deletes tree nodes to prevent memory leaks

    // Constructors and destructors
    ExpressionTree();
    ~ExpressionTree();

    // Tree building functions for different expression formats
    TreeNode* buildTreeFromInfix(const std::string& infix);
    TreeNode* buildTreeFromPrefix(const MyVector& tokens);
    TreeNode* buildTreeFromPostfix(const MyVector& tokens);

    // Traversal functions
    std::string inorder(TreeNode* root) const; // Gives infix expression
    std::string preorder(TreeNode* root) const; // Gives prefix expression
    std::string postorder(TreeNode* root) const; // Gives postfix expression

    // Evaluation and tokenization functions
    long double evaluate(TreeNode* root, const std::unordered_map<std::string, double>& variableValues) const;
    MyVector tokenize(const std::string& expression) const;

    //Expression Validation Functions
    void validateExpressionType(const MyVector& tokens, int expectedType);
    int  determineExpressionType(const MyVector& tokens);
    void validateExpressionStructure(const MyVector& tokens);
    void validatePostfixExpressionStructure(const MyVector& tokens);
    void validatePrefixExpressionStructure(const MyVector& tokens);

    // A function to collect variable values for evaluation
    unordered_map<std::string, double> getVariableValues(ExpressionTree::TreeNode* root);

};

#endif // EXPRESSION_TREE_H