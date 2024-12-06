#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <string>
#include <stdexcept>
using namespace std;
/*
 * MyVector class: A custom implementation of a dynamic array (vector)
 * that stores strings with dynamic resizing capabilities.
 * Mimics basic functionality of std::vector
 */
class MyVector {
private:

    string* data;  // Pointer to the dynamically allocated array of strings
    int current_size; // Current number of elements in the vector
    int current_capacity;  // Total capacity of the allocated array

    /* Resizes the internal array to a new capacity.
     Copies existing elements to the new array.*/
    void resize(int new_capacity);

public:
    // Default constructor : Initializes an empty vector with no capacity
    MyVector();
    // Destructor : Frees the dynamically allocated memory
    ~MyVector();
    // Copy constructor : Creates a deep copy of another MyVector
    MyVector(const MyVector& other);
    // Assignment operator : Performs a deep copy of another MyVector
    MyVector& operator=(const MyVector& other);

    /*
    * Adds a new element to the end of the vector
    * Automatically resizes the vector if needed*/
    void push_back(const std::string& value);

    // Removes the last element from the vector
    void pop_back();

    // Provides access to an element at a specific index with bounds checking
    std::string& at(int index);
    const string& at(int index) const;
    // Returns the current number of elements in the vector
    int getSize() const;
    //  Checks if the vector is empty
    bool empty() const;
    // Removes all elements from the vector
    void clear();

    // Provides unchecked access to elements by index
    string& operator[](int index);
    const string& operator[](int index) const;

    /*  - iterator class for traversing the vector
        - Supports basic iterator operations */
    class iterator {
    private:
        string* ptr;  // Pointer to the current element
    public:
        //  Constructor : p Pointer to the initial element
        iterator(string* p) : ptr(p) {}

        // Dereference operator : return Reference to the current element
        string& operator*() { return *ptr; }

        // Prefix increment operator: Moves iterator to the next element
        iterator& operator++() { ++ptr; return *this; }
        // Prefix decrement operator : Moves iterator to the previous element
        iterator &operator--() { --ptr; return *this; }
        // Inequality comparison operator
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
    };

    // Returns an iterator to the first element of the vector
    iterator begin() { return iterator(data); }
    // Returns an iterator to the position one past the last element
    iterator end() { return iterator(data + current_size); }
    // Returns a reverse iterator to the last element of the vector
    iterator rbegin() { return iterator(data + current_size - 1); }
    // Returns a reverse iterator to the position before the first element
    iterator rend() { return iterator(data - 1); }
};

#endif // MYVECTOR_H