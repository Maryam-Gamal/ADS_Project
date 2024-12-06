#include "ExpressionTree.h"
#include "MyStack.h"
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <functional>
#include <iostream>

// Constructors and destructors
ExpressionTree::ExpressionTree() {root = NULL;}
ExpressionTree::~ExpressionTree() {}

// Helper function to check if a token is a mathematical operator (+, -, *, /, %, ^).
// Returns true if the token is a valid operator, false otherwise.
bool ExpressionTree::isOperator(const std::string& token) const {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^";

}
// Validates the balance of parentheses in an infix expression
bool ExpressionTree::isValidParentheses(const std::string& expression) const {
    int balance = 0; // Tracks the balance of parentheses
    for (char ch : expression) {
        if (ch == '(') {
            balance++;  // Increment for an opening parenthesis
        } else if (ch == ')') {
            balance--;  // Decrement for a closing parenthesis.
            if (balance < 0) {
                // More closing parentheses than opening
                return false;
            }
        }
    }
    return balance == 0; // Balanced if zero
}

// Checks if a string represents a valid number (integer or decimal, including negative numbers)
bool ExpressionTree::isNumber(const std::string& str) const {
    if (str.empty()) return false;

    bool hasDecimal = false;
    // Allow negative numbers by starting from index 1 if first character is '-'
    size_t start = (str[0] == '-') ? 1 : 0;   // Handle negative numbers.

    if (start == str.length()) return false;

    for (size_t i = start; i < str.length(); i++) {
        if (str[i] == '.') {
            if (hasDecimal) return false;   // Multiple decimal points are invalid
            hasDecimal = true;
        } else if (!isdigit(str[i])) {
            return false;  // Non-digit characters are invalid.
        }
    }
    return true;
}


// Validates if a token is a valid variable name.
// Variable names must start with a letter
bool ExpressionTree::isVariable(const std::string& token)  {
    if (token.empty()) return false;

    // First character must be a letter
    if (!isalpha(token[0])) return false;

    // Remaining characters must be letters or numbers
    for (size_t i = 1; i < token.length(); i++) {
        if (!isalnum(token[i])) return false;
    }
    return true;
}

// Determines operator precedence for correct expression evaluation
int ExpressionTree::precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/" || op == "%") return 2;
    if (op == "^") return 3;
    return 0;  // Unknown operators have precedence 0.
}

// Recursively deletes all nodes in the tree to prevent memory leaks
// Traverses the tree in postorder to delete nodes.
void ExpressionTree::deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}


// Tree building functions
// Builds an expression tree from an infix expression.
// Validates the expression structure, tokenizes the input, and constructs the tree using stacks for nodes and operators.
ExpressionTree::TreeNode* ExpressionTree::buildTreeFromInfix(const std::string& infix) {
  MyVector tokens = tokenize(infix); // Tokenize the infix expression.
    // simple Validation for the structure of the infix expression
    if (tokens.getSize() < 3) {
        throw std::runtime_error("Incomplete expression: Not enough operands");
    }

    // New validation function to check expression structure
    validateExpressionStructure(tokens);

    //  Initialize stacks for tree nodes and operators.
    MyStack<TreeNode*> nodes;
    MyStack<string> ops;

    // Process tokens one by one.
    for (int i = 0; i < tokens.getSize(); ++i) {
        const string& token = tokens[i];

        if (isNumber(token) || isVariable(token)) {
            // Handle both numbers and variables (single or multi-character)
            nodes.push(new TreeNode(token)); // Create leaf node for operand or variable.
        }
        else if (token == "(") {
            ops.push(token);   // Push opening parenthesis to operator stack.
        }
        else if (token == ")") {
            // Pop and process operators until an opening parenthesis is encountered.
            while (!ops.empty() && ops.top() != "(") {
                string op = ops.top(); // Pop the operator.
                ops.pop();

                // Pop two nodes from the node stack to serve as the children of the operator node.
                TreeNode* right = nodes.empty() ? nullptr : nodes.top();
                if (!nodes.empty()) nodes.pop();

                TreeNode* left = nodes.empty() ? nullptr : nodes.top();
                if (!nodes.empty()) nodes.pop();

                // Create a new operator node and attach its children.
                TreeNode* node = new TreeNode(op);   // Create a new operator node.
                node->left = left;
                node->right = right;

                // Push the resulting subtree back onto the nodes stack.
                nodes.push(node);
            }
            if (!ops.empty()) ops.pop(); // Remove "("
        }
        else if (isOperator(token)) {
            // If the token is an operator, handle precedence and associativity.
            while (!ops.empty() && ops.top() != "(" &&
                   (precedence(ops.top()) > precedence(token) ||
                    (precedence(ops.top()) == precedence(token) && token != "^"))) {
                string op = ops.top();
                ops.pop();

                // Pop two nodes from the node stack to serve as the children of the operator node.
                TreeNode* right = nodes.empty() ? nullptr : nodes.top();
                if (!nodes.empty()) nodes.pop();

                TreeNode* left = nodes.empty() ? nullptr : nodes.top();
                if (!nodes.empty()) nodes.pop();

                // Create a new operator node and attach its children.
                TreeNode* node = new TreeNode(op);
                node->left = left;
                node->right = right;

                nodes.push(node);
            }
            // Push the current operator onto the operator stack.
            ops.push(token); // Push the current operator.
        }
    }

    // Process any remaining operators in the stack.
    while (!ops.empty()) {
        string op = ops.top(); // Pop the operator.
        ops.pop();

        // Pop two nodes from the node stack to serve as the children of the operator node.
        TreeNode* right = nodes.empty() ? nullptr : nodes.top();
        if (!nodes.empty()) nodes.pop();

        TreeNode* left = nodes.empty() ? nullptr : nodes.top();
        if (!nodes.empty()) nodes.pop();

        // Create a new operator node and attach its children.
        TreeNode* node = new TreeNode(op);
        node->left = left;
        node->right = right;

        // Push the resulting subtree back onto the nodes stack.
        nodes.push(node);
    }

    // The remaining node on the nodes stack is the root of the expression tree.
    return nodes.empty() ? nullptr : nodes.top();
}

// Builds an expression tree from a prefix expression.
// Processes tokens from right to left, using a stack to construct the tree.
ExpressionTree::TreeNode* ExpressionTree::buildTreeFromPrefix(const MyVector& tokens) {
    validatePrefixExpressionStructure(tokens);  // Validate prefix structure.
    MyStack<TreeNode*> nodeStack;  // Stack for nodes

    // Traverse the tokens in reverse order.
    for (int i = tokens.getSize() - 1; i >= 0; --i) {
        const string& token = tokens[i];

        // Handle negative numbers as single tokens
        if (isNumber(token)) {
            nodeStack.push(new TreeNode(token));  // Push operands directly.
        }
        else if (isOperator(token)) {
            TreeNode* node = new TreeNode(token);  // Create an operator node.
            // Attach the top two nodes from the stack as children.
            if (!nodeStack.empty()) {
                node->left = nodeStack.top();
                nodeStack.pop();
            }
            if (!nodeStack.empty()) {
                node->right = nodeStack.top();
                nodeStack.pop();
            }
            nodeStack.push(node);  // Push the constructed node back to the stack.
        } else {
            nodeStack.push(new TreeNode(token)); // Treat other tokens as variables.
        }
    }
    return nodeStack.empty() ? nullptr : nodeStack.top();  // Return the root.
}


// Builds an expression tree from a postfix expression.
// Processes tokens from left to right, using a stack to construct the tree.
ExpressionTree::TreeNode* ExpressionTree::buildTreeFromPostfix(const MyVector& tokens) {
    validatePostfixExpressionStructure(tokens);
    MyStack<TreeNode*> nodeStack;  // Stack for nodes.

    for (int i = 0; i < tokens.getSize(); ++i) {
        const string& token = tokens[i];

        // Handle negative numbers as single tokens
        if (isNumber(token)) {
            nodeStack.push(new TreeNode(token));   // Push operands directly.
        }
        else if (isOperator(token)) {
            TreeNode* node = new TreeNode(token); // Create an operator node.

            // Attach the top two nodes from the stack as children.
            if (!nodeStack.empty()) {
                node->right = nodeStack.top();
                nodeStack.pop();
            }
            if (!nodeStack.empty()) {
                node->left = nodeStack.top();
                nodeStack.pop();
            }
            nodeStack.push(node);  // Push the constructed node back to the stack.
        } else {
            nodeStack.push(new TreeNode(token));  // Treat other tokens as variables
        }
    }
    return nodeStack.empty() ? nullptr : nodeStack.top(); // Return the root.
}

// Traversal functions
// Performs an inorder traversal of the tree to give infix expression
// Constructs a string representation with parentheses for clarity.
std::string ExpressionTree::inorder(TreeNode* root) const {
    if (!root) return "";
    if (isOperator(root->value)) {
        return "( " + inorder(root->left) + " " + root->value + " " + inorder(root->right) + " )";
    }
    return root->value;
}

// Performs a preorder traversal of the tree to give preorder expression
// Constructs a string representation of the traversal.
std::string ExpressionTree::preorder(TreeNode* root) const {
    if (!root) return "";
    string result = root->value;
    string leftStr = preorder(root->left);
    string rightStr = preorder(root->right);

    if (!leftStr.empty()) result += " " + leftStr;
    if (!rightStr.empty()) result += " " + rightStr;
    return result;
}

// Performs a postorder traversal of the tree to give postorder expression
// Constructs a string representation of the traversal.
std::string ExpressionTree::postorder(TreeNode* root) const {
    if (!root) return "";
    string result = "";
    string leftStr = postorder(root->left);
    string rightStr = postorder(root->right);

    if (!leftStr.empty()) result += leftStr + " ";
    if (!rightStr.empty()) result += rightStr + " ";
    result += root->value;
    return result;
}

// Evaluates the expression tree.
// Recursively calculates the result using operator nodes and operand/variable values.
long double ExpressionTree::evaluate(TreeNode* root, const std::unordered_map<std::string, double>& variableValues) const {
    if (!root) return 0;
    // If the node is not an operator, evaluate as a number or variable.
    if (!isOperator(root->value)) {
        if (isNumber(root->value)) {
            return stod(root->value); // Convert number strings to double
        }
        if (isVariable(root->value) && variableValues.find(root->value) != variableValues.end()) {
            return variableValues.at(root->value); // Use the value for the variable
        }
        throw std::runtime_error("Undefined variable: " + root->value);
    }

    // Recursively evaluate the left and right subtrees.
    double leftValue = evaluate(root->left, variableValues);
    double rightValue = evaluate(root->right, variableValues);

    // Perform the operation based on the operator.
    if (root->value == "+") return leftValue + rightValue;
    if (root->value == "-") return leftValue - rightValue;
    if (root->value == "*") return leftValue * rightValue;
    if (root->value == "/") {
        if (rightValue == 0) throw std::runtime_error("Division by zero!");
        return leftValue / rightValue;
    }
    if (root->value == "%") {
        if (rightValue == 0) throw std::runtime_error("Modulo by zero!");
        return fmod(leftValue, rightValue);
    }
    if (root->value == "^") return pow(leftValue, rightValue);

    throw std::runtime_error("Invalid operator!"); // Handle unexpected operators.
}

// Tokenizes an expression into a vector of strings representing numbers, operators, and parentheses.
// Handles negative numbers, multi-character variables, and various delimiters.
// Input Format: The expression must be entered with leaving spaces between numbers/varaibles/parenthesis
MyVector ExpressionTree::tokenize(const std::string& expression) const {
    MyVector tokens;  // Vector to store tokens.
    istringstream iss(expression); // String stream for processing the expression.
    string token;

    // Process each space-separated segment of the input expression.
    while (iss >> token) {
        // If token is just a minus sign, it's an operator
        if (token == "-") {
            tokens.push_back(token); // Add the minus sign as an operator.
            continue;
        }

        // Check if it's a negative number (starts with minus and has more characters)
        if (token[0] == '-' && token.length() > 1) {
            // Verify the rest is a valid number
            bool isValidNumber = true;
            bool hasDecimal = false;
            for (size_t i = 1; i < token.length(); i++) {
                if (token[i] == '.') {
                    // Only one decimal point is allowed.
                    if (hasDecimal) {
                        isValidNumber = false;
                        break;
                    }
                    hasDecimal = true;
                } else if (!isdigit(token[i])) {
                    // If a non-digit character is found, the token is invalid.
                    isValidNumber = false;
                    break;
                }
            }
            if (isValidNumber) {
                tokens.push_back(token);  // Add as a single negative number token
                continue;
            }
        }

        // Handle other operators
        if (isOperator(token)) {
            tokens.push_back(token);
            continue;
        }

        // Handle parentheses (opening or closing).
        if (token == "(" || token == ")") {
            tokens.push_back(token);
            continue;
        }

        // Handle regular numbers and variables
        if (isNumber(token) || (token.length() == 1 && isalpha(token[0]))) {
            tokens.push_back(token);
            continue;
        }

        // If we get here, it might be a multi-character variable, so validate it.
        bool isVariable = true;
        for (char c : token) {
            if (!isalnum(c)) {
                isVariable = false;
                break;
            }
        }

        // If the token is a valid multi-character variable, add it to the vector.
        if (isVariable) {
            tokens.push_back(token);
        }

    }
    return tokens; // Return the vector of the tokens
}

// Validates the structure of an infix expression.
// Checks for balanced parentheses, proper operator placement, and overall syntax correctness.
void ExpressionTree::validateExpressionStructure(const MyVector& tokens) {
    int operandCount = 0;        // Tracks the number of operands (numbers or variables).
    int operatorCount = 0;       // Tracks the number of operators.
    int parenthesesBalance = 0;  // Tracks the balance of parentheses.

    // Iterate through the tokens to analyze the structure.
    for (int i = 0; i < tokens.getSize(); ++i) {
        const string& token = tokens[i];

        // Check for opening parentheses.
        if (token == "(") {
            parenthesesBalance++;  // Increment balance for an opening parenthesis.

            // Ensure that an operator precedes an opening parenthesis (if applicable).
            if (i > 0 && (isNumber(tokens[i-1]) || isVariable(tokens[i-1]) || tokens[i-1] == ")")) {
                throw std::runtime_error("Invalid syntax: Missing operator before opening parenthesis");
            }
        }
        // Check for closing parentheses.
        else if (token == ")") {
            parenthesesBalance--; // Decrement balance for a closing parenthesis.

            // Detect unmatched closing parentheses (more closing than opening).
            if (parenthesesBalance < 0) {
                throw std::runtime_error("Unbalanced parentheses: Too many closing parentheses");
            }
        }
        // Check for operators.
        else if (isOperator(token)) {
            operatorCount++;  // Increment operator count.
            // Check if operator is at the start or end of expression
            if (i == 0 || i == tokens.getSize() - 1) {
                throw std::runtime_error("Invalid expression: Operator cannot be at the start or end");
            }
            // Ensure operators are separated by operands ( not consecutive ).
            if (i > 0 && isOperator(tokens[i-1])) {
                throw std::runtime_error("Invalid syntax: Consecutive operators");
            }
        }
        // Check for operands (numbers or variables).
        else if (isNumber(token) || isVariable(token)) {
            operandCount++; // Increment operand count.
            // Check for implicit multiplication (number/variable next to parenthesis)
            if (i > 0 && (tokens[i-1] == ")" || isNumber(tokens[i-1]) || isVariable(tokens[i-1]))) {
                throw std::runtime_error("Invalid syntax: Missing operator between operands");
            }
        }
    }

    // Final validation checks
    if (parenthesesBalance != 0) {
        throw std::runtime_error("Unbalanced parentheses");
    }

    // Ensure we have the right balance of operands and operators
    if (operandCount <= operatorCount) {
        throw std::runtime_error("Incomplete expression: Not enough operands for operators");
    }
}

// Validates the structure of a postfix expression.
void ExpressionTree::validatePostfixExpressionStructure(const MyVector& tokens) {
    // Stack to track operand availability
    MyStack<int> operandStack;

    // Iterate through tokens from left to right
    for (int i = 0; i < tokens.getSize(); ++i) {
        const string& token = tokens[i];

        if (isNumber(token) || isVariable(token)) {
            // Operand found, add to stack
            operandStack.push(0);
        }
        else if (isOperator(token)) {
            // Check if there are enough operands for this operator
            int requiredOperands = 2;  // Most operators need 2 operands

            // Check if we have enough operands in the stack
            if (operandStack.size() < requiredOperands) {
                throw std::runtime_error("Postfix validation error: Insufficient operands for operator '" + token + "'");
            }

            // Remove the required number of operand placeholders
            for (int j = 0; j < requiredOperands; ++j) {
                if (!operandStack.empty()) {
                    operandStack.pop();
                }
            }

            // The operator consumes operands and becomes a result
            operandStack.push(0);
        }
        else {
            throw std::runtime_error("Invalid token in postfix expression: " + token);
        }
    }

    // Final validation: exactly one operand (the final result) should remain
    if (operandStack.size() != 1) {
        throw std::runtime_error("Invalid postfix expression: Incorrect number of operands");
    }
}

// Validates the structure of a prefix expression.
void ExpressionTree::validatePrefixExpressionStructure(const MyVector& tokens) {
    // Stack to track operand requirements
    MyStack<int> operandStack;

    // Iterate through tokens from right to left
    for (int i = tokens.getSize() - 1; i >= 0; --i) {
        const string& token = tokens[i];

        if (isNumber(token) || isVariable(token)) {
            // Operand found, add to stack with no further requirements
            operandStack.push(0);
        }
        else if (isOperator(token)) {
            // Check if there are enough operands for this operator
            int requiredOperands = 2;  // Most operators need 2 operands

            // Check if we have enough operands in the stack
            if (operandStack.size() < requiredOperands) {
                throw std::runtime_error("Prefix validation error: Insufficient operands for operator '" + token + "'");
            }

            // Remove the required number of operand placeholders
            for (int j = 0; j < requiredOperands; ++j) {
                if (!operandStack.empty()) {
                    operandStack.pop();
                }
            }

            // The operator itself becomes an operand
            operandStack.push(0);
        }
        else {
            throw std::runtime_error("Invalid token in prefix expression: " + token);
        }
    }

    // Final validation: exactly one operand (the final result) should remain
    if (operandStack.size() != 1) {
        throw std::runtime_error("Invalid prefix expression: Incorrect number of operands");
    }
}


// Validate if the expression entered matches the expected type (the one chosen by the user)
void ExpressionTree::validateExpressionType(const MyVector& tokens, int expectedType) {
    // expectedType: 1 for Infix, 2 for Prefix, 3 for Postfix

    // Check for empty expression, if the user enters nothing
    if (tokens.getSize() < 1) {
        throw std::runtime_error("Empty expression. Enter an expression and leave spaces between tokens, operators, and parentheses");
    }

    // Determine the actual type of expression
    int actualType = determineExpressionType(tokens);

    // Compare actual type with expected type
    if (actualType != expectedType) {
        std::string typeNames[] = {"", "Infix", "Prefix", "Postfix"};
        throw std::runtime_error("Incorrect expression type. Expected " +
                                 typeNames[expectedType] + ", but got " +
                                 typeNames[actualType] + " expression.");
    }
}


// Detect expression type based on token arrangement
int ExpressionTree::determineExpressionType(const MyVector& tokens) {

    // Prefix: Operator comes first
    if (isOperator(tokens[0])) {
        return 2; // Prefix
    }

    // Postfix: Operator comes last
    if (isOperator(tokens[tokens.getSize() - 1])) {
        return 3; // Postfix
    }

    // Infix: Operators are between operands
    for (int i = 1; i < tokens.getSize() - 1; ++i) {
        if (isOperator(tokens[i])) {
            return 1; // Infix
        }
    }

    // If no clear type is detected
    throw std::runtime_error("Unable to determine expression type");
}


// Function to prompt the user for variable values if he enters an expressions containing variables for instance: A + B * C
// and even if it contians numbers/ variables, the user will be asked to enter numbers for the variables
unordered_map<std::string, double> ExpressionTree::getVariableValues(ExpressionTree::TreeNode* root) {
    // Map to store variable names and their corresponding values.
    unordered_map<std::string, double> variableValues;

    // Helper function to traverse the tree and collect variable names.
    function<void(ExpressionTree::TreeNode*)> collectVariables = [&](ExpressionTree::TreeNode* node) {
        if (!node) return;  // Base case: If the node is null, return.
        // Check if the variable is not already in the map to avoid redundant prompts.
        if (ExpressionTree::isVariable(node->value)) {
            if (variableValues.find(node->value) == variableValues.end()) {
                cout << "Enter the value for variable '" << node->value << "': " << std::endl;
                double value;
                // cin >> value;
                // Loop to ensure valid numeric input from the user.
                while (!(cin >> value)) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid input! Please enter a numeric value for '" << node->value << "': " << endl;
                }
                // Store the entered value in the map.
                variableValues[node->value] = value;
            }
        }
        // Recursively traverse the left and right subtrees.
        collectVariables(node->left);
        collectVariables(node->right);
    };

    // Start the traversal from the root of the tree.
    collectVariables(root);
    // Return the map containing all variable values.
    return variableValues;
}