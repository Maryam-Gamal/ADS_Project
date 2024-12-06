#include <chrono>
#include <functional>
#include <iostream>
#include <limits>
#include <thread>
#include <unordered_map>
#include <iomanip>
#include "Code_lib/ExpressionTree.h"
using namespace  std;
/*When entering an expression, follow these guidelines to ensure the program can correctly interpret and process your input:

1. Space-separated Tokens:
Leave a space between every number, variable, operator, and parenthesis.
Example:
Correct: A + B * ( C - D )
Incorrect: A+B*(C-D)

2. Allowed Operators:
The following operators are supported:
+ (addition), - (subtraction), * (multiplication), / (division), % (modulus), and ^ (exponentiation).

3. Parentheses:
Use parentheses for grouping expressions to define precedence explicitly in an infix expression.
Ensure parentheses are balanced (each opening parenthesis ( has a corresponding closing parenthesis )).

4. Variable Names:
Variable names must start with a letter and may include letters and digits.
Example: x, y1, var2, AB are valid, but 1x and x-y are not.

5. Numbers:
You can use integers (e.g., 2, -5) or decimals (e.g., 3.14, -0.75).
Note: Two decimal points in a number are not allowed. For example, 3.14.5 is invalid.


6. Negative Numbers:
Negative numbers should be entered as -5 or -3.14 with the minus sign directly preceding the number.

7. Operand Requirement for Binary Operators:
Don’t miss operands for binary operators (operators that require two operands, like +, -, *, /).
For example, an expression like A + or * B is invalid because it lacks a second operand.

8. Expression Type:
Do not mix expression types. If you choose a type, make sure the expression matches that type, or the program will produce an error.

9. Handling Variables:
If the expression contains variables, you must enter correct numeric values for all variables.
*/


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

                // Ask if user wants to evaluate the expression after showing traversals
                char evalChoice;
                cout << "Do you want to evaluate the expression? (y/n): ";
                cin >> evalChoice;
                cin.ignore(); // Clear newline

                if (tolower(evalChoice) == 'y') {
                    // Get variable values and evaluate
                    unordered_map<string, double> variableValues = exprTree.getVariableValues(root);
                    try {
                        std::cout << std::fixed << std::setprecision(9);
                        cout << "Evaluation Result: " << exprTree.evaluate(root, variableValues) << endl;
                    } catch (const exception& e) {
                        cerr << "Note: " << e.what() << endl;
                    }
                }   exprTree.deleteTree(root);
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