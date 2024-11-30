#include <chrono>
#include <functional>
#include <iostream>
#include <limits>
#include <thread>
#include <unordered_map>
#include <iomanip>
#include "Code_lib/ExpressionTree.h"
using namespace  std;


// Function to prompt the user for variable values if he enters an expressions containing variables
unordered_map<std::string, double> getVariableValues(ExpressionTree::TreeNode* root) {
    unordered_map<std::string, double> variableValues;

   function<void(ExpressionTree::TreeNode*)> collectVariables = [&](ExpressionTree::TreeNode* node) {
        if (!node) return;
        if (ExpressionTree::isVariable(node->value)) {
            if (variableValues.find(node->value) == variableValues.end()) {
                cout << "Enter the value for variable '" << node->value << "': " << std::endl;
                double value;
               // cin >> value;
                while (!(cin >> value)) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid input! Please enter a numeric value for '" << node->value << "': " << endl;
                }
                variableValues[node->value] = value;
            }
        }
        collectVariables(node->left);
        collectVariables(node->right);
    };

    collectVariables(root);
    return variableValues;
}




int main() {
    ExpressionTree exprTree;
    string input;
    int choice;
    char repeat;

    do {
        // Input and validate choice
        while (true) {
            cout << "Choose input type:\n";
            cout << "1. Infix Expression\n";
            cout << "2. Prefix Expression\n";
            cout << "3. Postfix Expression\n";
            cout << "Enter choice: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number (1, 2, or 3).\n";
                continue;
            }

            if (choice >= 1 && choice <= 3) {
                break;
            }

            cout << "Invalid choice! Please enter 1, 2, or 3.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(); // Clear newline
        cout << "Enter the expression (Please leave spaces between tokens, operators, and parentheses): " <<endl;
        getline(cin, input);

        try {
            // Validate parentheses for infix
            if (choice == 1 && !exprTree.isValidParentheses(input)) {
                throw runtime_error("Invalid parentheses in the input expression!");
            }

            ExpressionTree::TreeNode* root = nullptr;

            switch (choice) {
                case 1: {
                    MyVector tokens = exprTree.tokenize(input);
                    exprTree.validateExpressionType(tokens, 1); // Validate as Infix
                    root = exprTree.buildTreeFromInfix(input);
                    break;
                }
                case 2: {
                    MyVector tokens = exprTree.tokenize(input);
                    exprTree.validateExpressionType(tokens, 2); // Validate as Prefix
                    root = exprTree.buildTreeFromPrefix(tokens);
                    break;
                }
                case 3: {
                    MyVector tokens = exprTree.tokenize(input);
                    exprTree.validateExpressionType(tokens, 3); // Validate as Postfix
                    root = exprTree.buildTreeFromPostfix(tokens);
                    break;
                }
            }

            if (root) {
                // Display tree traversals
                cout << "\nInfix: " << exprTree.inorder(root) << endl;
                cout << "Prefix: " << exprTree.preorder(root) << endl;
                cout << "Postfix: " << exprTree.postorder(root) << endl;

                // Get variable values and evaluate
                unordered_map<string, double> variableValues = getVariableValues(root);

                try {
                    std::cout << std::fixed << std::setprecision(9);
                    cout << "Evaluation Result: " << exprTree.evaluate(root, variableValues) << endl;
                } catch (const exception& e) {
                    cerr << "Note: " << e.what() << endl;
                }

                exprTree.deleteTree(root);
            } else {
                cout << "Failed to build expression tree! Try to leave spaces between the tokens. For example: ( 5 + 3 ) * 3" << endl;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

        }

        // Ask to repeat
        cout << "Do you want to convert another expression? (y/n): " << endl;
        cin >> repeat;
        cin.ignore();

    } while (tolower(repeat) == 'y');

    cout << "Goodbye!" << endl;
    return 0;
}