#ifndef TRIE_H
#define TRIE_H

#include "Student.h"

// Number of possible characters (A-Z, a-z, space)
const int ALPHABET_SIZE = 53;

class TrieNode {
public:
    TrieNode* children[ALPHABET_SIZE];
    Student* studentPtr; // Student pointer if this node marks the end of a name

    TrieNode();
};

class Trie {
private:
    TrieNode* root;
    int charToIndex(char c);
    void displaySortedRecursive(TrieNode* node);

public:
    Trie();
    ~Trie();
    void insert(const char* name, Student* student);
    void displaySorted();
};

#endif // TRIE_H
