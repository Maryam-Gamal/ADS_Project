// implemented by Mohamed Enan
#ifndef MYSTACK_H
#define MYSTACK_H

#include <stdexcept>
#include <string>
using namespace std;
template<typename T>

// Purpose: Implement a generic stack data structure using a linked list
// - Supports dynamic memory management
// - Provides standard stack operations
// - Works with any data type
class MyStack {
private:
    struct Node {
        T data;   // Data stored in the node
        Node* next;   // Pointer to next node in stack
        Node(const T& value); //Node Constructor : Creates a new node with given value
    };
    Node* topNode;  // Pointer to top of stack
    size_t stackSize;   // Current number of elements

public:
    MyStack();  //  Default constructor creates empty stack
    ~MyStack();  // Destructor frees all allocated memory
    MyStack(const MyStack& other);    // Copy constructor creates deep copy
    MyStack& operator=(const MyStack& other); // Assignment operator

    //Core Stack Operations
    void push(const T& value);  // Add element to top
    void pop();  // Remove top element
    T& top();  // Access top element
    const T& top() const; // Access top element (const)

    bool empty() const; // Check if stack is empty
    size_t size() const;  // Get number of elements
    void clear(); // Remove all elements
};


#endif // MYSTACK_H