#ifndef UNROLLED_LINKED_LIST_H
#define UNROLLED_LINKED_LIST_H

#include <string>
#include <iostream>

class UnrolledLinkedList {
private:
    static const int NODE_CAPACITY = 64; // Fixed capacity for chunks
    
    struct Node {
        int numElements;
        char elements[NODE_CAPACITY];
        Node* next;
        
        Node() : numElements(0), next(nullptr) {}
    };

    Node* head;
    int totalLength;

public:
    UnrolledLinkedList();
    ~UnrolledLinkedList();

    // Insert a single character at a specific index
    void insert(int index, char c);
    
    // Insert a whole string starting at a specific index
    void insertString(int index, const std::string& seq);
    
    // Remove characters starting at a specific index
    void remove(int index, int length = 1);
    
    // Get character at index
    char charAt(int index) const;
    
    // Extract the full sequence to a contiguous string
    std::string toString() const;
    
    // Get total length of the sequence
    int length() const;
    
    // Debug method to display internal structure
    void display() const;
};

#endif // UNROLLED_LINKED_LIST_H
