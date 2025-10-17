#include "Trie.h"
#include "helpers.h"
#include <iostream>

// --- TrieNode Implementation ---
TrieNode::TrieNode() : studentPtr(nullptr) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        children[i] = nullptr;
    }
}

// --- Trie Implementation ---
Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    // For simplicity, recursive deletion is omitted here.
    delete root;
}

// Convert character to index with uppercase first, then lowercase, then space
int Trie::charToIndex(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';          // 0-25 for 'A'-'Z'
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;     // 26-51 for 'a'-'z'
    return 52; // space character
}

void Trie::insert(const char* name, Student* student) {
    TrieNode* currentNode = root;
    int len = custom_strlen(name);

    for (int i = 0; i < len; i++) {
        int index = charToIndex(name[i]);
        if (!currentNode->children[index]) {
            currentNode->children[index] = new TrieNode();
        }
        currentNode = currentNode->children[index];
    }
    // Mark last node as containing this student
    currentNode->studentPtr = student;
}

// Recursive traversal to display students in alphabetical order
void Trie::displaySortedRecursive(TrieNode* node) {
    if (!node) return;
    if (node->studentPtr != nullptr) {
        node->studentPtr->displayDetails();
    }
    // Traverse children in ascending order (A-Z, a-z, space)
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            displaySortedRecursive(node->children[i]);
        }
    }
}

void Trie::displaySorted() {
    std::cout << "\n--- Students Sorted by Name (using Trie) ---\n";
    displaySortedRecursive(root);
    std::cout << "------------------------------------------\n";
}
