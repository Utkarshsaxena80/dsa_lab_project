#include "UnrolledLinkedList.h"
#include <stdexcept>
#include <cstring>

UnrolledLinkedList::UnrolledLinkedList() {
    head = new Node();
    totalLength = 0;
}

UnrolledLinkedList::~UnrolledLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void UnrolledLinkedList::insert(int index, char c) {
    if (index < 0 || index > totalLength) {
        throw std::out_of_range("Index out of bounds");
    }

    Node* current = head;
    int currentIndex = 0;

    // Traverse to find the correct node
    while (current != nullptr && currentIndex + current->numElements < index && current->next != nullptr) {
        currentIndex += current->numElements;
        current = current->next;
    }

    int posInNode = index - currentIndex;

    // If node is full, we must split it
    if (current->numElements == NODE_CAPACITY) {
        Node* newNode = new Node();
        int half = NODE_CAPACITY / 2;
        
        // Move the second half of elements to the new node
        for (int i = half; i < NODE_CAPACITY; ++i) {
            newNode->elements[i - half] = current->elements[i];
        }
        newNode->numElements = NODE_CAPACITY - half;
        current->numElements = half;
        
        // Insert new node into the list
        newNode->next = current->next;
        current->next = newNode;

        // Decide which node gets the new character
        if (posInNode > half) {
            current = newNode;
            posInNode -= half;
        }
    }

    // Shift elements to the right to make space
    for (int i = current->numElements; i > posInNode; --i) {
        current->elements[i] = current->elements[i - 1];
    }
    
    // Insert new character
    current->elements[posInNode] = c;
    current->numElements++;
    totalLength++;
}

void UnrolledLinkedList::insertString(int index, const std::string& seq) {
    for (size_t i = 0; i < seq.length(); ++i) {
        insert(index + i, seq[i]);
    }
}

void UnrolledLinkedList::remove(int index, int length) {
    for(int i = 0; i < length; ++i) {
        if (index < 0 || index >= totalLength) {
            throw std::out_of_range("Index out of bounds");
        }

        Node* current = head;
        int currentIndex = 0;

        while (current != nullptr && currentIndex + current->numElements <= index) {
            currentIndex += current->numElements;
            current = current->next;
        }

        int posInNode = index - currentIndex;
        
        // Shift elements to the left to overwrite the removed character
        for (int j = posInNode; j < current->numElements - 1; ++j) {
            current->elements[j] = current->elements[j + 1];
        }
        current->numElements--;
        totalLength--;

        // Note: For a fully optimized list, we would merge nodes that fall below half capacity.
        // Omitted here for simplicity, focusing on core functionality.
    }
}

char UnrolledLinkedList::charAt(int index) const {
    if (index < 0 || index >= totalLength) {
        throw std::out_of_range("Index out of bounds");
    }

    Node* current = head;
    int currentIndex = 0;

    while (current != nullptr && currentIndex + current->numElements <= index) {
        currentIndex += current->numElements;
        current = current->next;
    }

    return current->elements[index - currentIndex];
}

std::string UnrolledLinkedList::toString() const {
    std::string result = "";
    result.reserve(totalLength);
    Node* current = head;
    while (current != nullptr) {
        result.append(current->elements, current->numElements);
        current = current->next;
    }
    return result;
}

int UnrolledLinkedList::length() const {
    return totalLength;
}

void UnrolledLinkedList::display() const {
    Node* current = head;
    int nodeIdx = 0;
    while (current != nullptr) {
        std::cout << "[Node " << nodeIdx++ << " (" << current->numElements << "/" << NODE_CAPACITY << ")]: ";
        for (int i = 0; i < current->numElements; ++i) {
            std::cout << current->elements[i];
        }
        std::cout << " ->\n";
        current = current->next;
    }
    std::cout << "NULL\n";
}
