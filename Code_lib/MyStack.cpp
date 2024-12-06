#include "MyStack.h"
#include <string>
#include "ExpressionTree.h"


//Node Constructor: Initialize a new node with given value
template<typename T>
MyStack<T>::Node::Node(const T& value) : data(value), next(nullptr) {}

// Stack constructor
// - Creates an empty stack
// - Sets top pointer to nullptr
// - Initializes stack size to 0
template<typename T>
MyStack<T>::MyStack() : topNode(nullptr), stackSize(0) {}

// Destructor to free all dynamically allocated memory
template<typename T>
MyStack<T>::~MyStack() {
    clear();
}

// Copy constructor
// Creates a deep copy of another stack
// Key Steps:
// - Handle empty source stack
// - Use temporary array to preserve stack order
// - Reconstruct stack by pushing elements
template<typename T>
MyStack<T>::MyStack(const MyStack& other) : topNode(nullptr), stackSize(0) {
    // Exit if source stack is empty
    if (other.empty()) return;

    // Create array to store values in correct order
    T* values = new T[other.stackSize];
    Node* current = other.topNode;
    size_t index = other.stackSize;

    // Reverse copy to maintain original stack order
    while (current != nullptr) {
        values[--index] = current->data;
        current = current->next;
    }

    // Reconstruct stack by pushing values
    for (size_t i = 0; i < other.stackSize; ++i) {
        push(values[i]);
    }

    // Clean up temporary array
    delete[] values;
}


//Assignment Operator
// Assigns contents of another stack to current stack
// Handles:
// - Self-assignment prevention
// - Memory cleanup
// - Deep copying of source stack
template<typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack& other) {
    // Prevent self-assignment
    if (this != &other) {
        // Clear current stack contents
        clear();

        // Copy source stack if not empty
        if (!other.empty()) {
            // Create array to store values in correct order
            T* values = new T[other.stackSize];
            Node* current = other.topNode;
            size_t index = other.stackSize;

            // Reverse copy to maintain original order
            while (current != nullptr) {
                values[--index] = current->data;
                current = current->next;
            }

            // Push values in correct order
            for (size_t i = 0; i < other.stackSize; ++i) {
                push(values[i]);
            }

            // Clean up temporary array
            delete[] values;
        }
    }
    return *this;
}

// Push Operation
// - Adds new element to top of stack
// - Creates new node
// - Updates top pointer
// - Increases stack size
template<typename T>
void MyStack<T>::push(const T& value) {
    // Allocate new node
    Node* newNode = new Node(value);
    // Link new node to current top
    newNode->next = topNode;
    // Update top pointer
    topNode = newNode;
    // Increment stack size
    ++stackSize;
}

// Pop Operation
// Removes top element from stack
// Throws exception if stack is empty
template<typename T>
void MyStack<T>::pop() {
    // Check for empty stack
    if (empty()) {
        throw runtime_error("Cannot pop from empty stack");
    }
    // Store current top node
    Node* temp = topNode;
    // Move top pointer
    topNode = topNode->next;
    // Free memory
    delete temp;
    // Decrement stack size
    --stackSize;
}

// Top Element Access (Mutable)
// Returns reference to top element
// Throws exception if stack is empty
template<typename T>
T& MyStack<T>::top() {
    if (empty()) {
        throw runtime_error("Cannot access top of empty stack");
    }
    return topNode->data;
}

// Return top element (const version)
template<typename T>
const T& MyStack<T>::top() const {
    if (empty()) {
        throw runtime_error("Cannot access top of empty stack");
    }
    return topNode->data;
}

// Check if stack is empty
template<typename T>
bool MyStack<T>::empty() const {
    return topNode == nullptr;
}

// Return size of stack
template<typename T>
size_t MyStack<T>::size() const {
    return stackSize;
}

// Clear the stack
template<typename T>
void MyStack<T>::clear() {
    // Remove nodes until stack is empty
    while (!empty()) {
        pop();
    }
}

// Explicit Template Instantiations
template class MyStack<int>;
template class MyStack<char>;
template class MyStack<double>;
template class MyStack<string>;
template class MyStack<ExpressionTree::TreeNode*>;