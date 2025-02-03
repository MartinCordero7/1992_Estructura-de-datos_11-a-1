#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <string>
#include <list>
#include <fstream>
#include "Libro.h"

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    Libro* libro;
    TrieNode() : libro(nullptr) {}
};

class Trie {
private:
    TrieNode* root;
    void collectAllBooks(TrieNode* node, list<Libro*>& libros);
    void collectSuggestions(TrieNode* node, const string& prefix, list<string>& suggestions);
    
public:
    Trie();
    void insert(const string& key, Libro* libro);
    Libro* search(const string& key);
    void remove(const string& key);
    bool removeHelper(TrieNode* node, const string& key, int depth);
    void printAll(TrieNode* node, string prefix, ofstream& archivo);
    void printAll(ofstream& archivo);
    list<Libro*> collectAllBooks();
    list<string> getSuggestions(const string& prefix);
    list<string> getTypoSuggestions(const string& prefix, int maxDistance);
    int levenshteinDistance(const string& s1, const string& s2);
};

#endif