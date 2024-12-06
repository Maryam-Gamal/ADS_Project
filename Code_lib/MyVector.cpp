#include "MyVector.h"

// // Default constructor
// Initializes an empty vector with no capacity and a null data pointer
MyVector::MyVector() : data(nullptr), current_size(0), current_capacity(0) {}


// Destructor
// Frees the dynamically allocated memory for the data array
MyVector::~MyVector() {
    delete[] data;
}


// Copy constructor
// Creates a new vector as a deep copy of another vector
// Initializes with default values, then uses assignment operator for copying
MyVector::MyVector(const MyVector& other) : data(nullptr), current_size(0), current_capacity(0) {
    *this = other;
}

//  Assignment operator (copy assignment)
// Performs a deep copy of another vector
// Handles self-assignment, memory deallocation, and memory allocation
// Copies each element from the source vector to the current vector
MyVector& MyVector::operator=(const MyVector& other) {
    // Check for self-assignment to prevent unnecessary work
    if (this != &other) {
        // Free existing memory
        delete[] data;
        // Copy size and capacity
        current_size = other.current_size;
        current_capacity = other.current_capacity;

        // Allocate new memory if capacity is non-zero
        if (current_capacity > 0) {
            data = new std::string[current_capacity];
            // Deep copy each element
            for (int i = 0; i < current_size; ++i) {
                data[i] = other.data[i];
            }
        } else {
            // Set to nullptr if no capacity
            data = nullptr;
        }
    }
    return *this;
}

// Resizes the internal array to a new capacity
// Copies existing elements to the new array
// Deallocates the old array
void MyVector::resize(int new_capacity) {
    // Create a new array with the specified capacity
    std::string* new_data = new std::string[new_capacity];

    // Copy existing elements to the new array
    for (int i = 0; i < current_size; ++i) {
        new_data[i] = data[i];
    }

    // Free the old array
    delete[] data;
    // Update data pointer and capacity
    data = new_data;
    current_capacity = new_capacity;
}

// Adds a new element to the end of the vector
// Automatically resizes the vector if it's full
void MyVector::push_back(const std::string& value) {
    // Check if resize is needed
    if (current_size == current_capacity) {
        // If empty, start with capacity 1
        // Otherwise, double the current capacity
        int new_capacity = current_capacity == 0 ? 1 : current_capacity * 2;
        resize(new_capacity);
    }

    // Add the new element and increment size
    data[current_size++] = value;
}

// Removes the last element from the vector
// Does nothing if the vector is empty
void MyVector::pop_back() {
    if (current_size > 0) {
        --current_size;
    }
}

// Provides bounds-checked access to elements
// Throws an out_of_range exception if the index is invalid
std::string& MyVector::at(int index) {
    if (index < 0 || index >= current_size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Provides bounds-checked access to elements (const version)
const std::string& MyVector::at(int index) const {
    if (index < 0 || index >= current_size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Returns the current number of elements in the vector
int MyVector::getSize() const {
    return current_size;
}

// Checks if the vector is empty
bool MyVector::empty() const {
    return current_size == 0;
}

// Clears the vector, deallocating memory and resetting to an empty state
void MyVector::clear() {
    delete[] data;
    data = nullptr;
    current_size = 0;
    current_capacity = 0;
}

// Provides unchecked access to elements (non-const version)
std::string& MyVector::operator[](int index) {
    return data[index];
}

// Provides unchecked access to elements (const version)
const std::string& MyVector::operator[](int index) const {
    return data[index];
}