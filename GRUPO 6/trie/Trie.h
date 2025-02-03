#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <list>  // Cambiar vector por list
#include <map>
#include <string>

class Trie {
private:
    bool isLeaf;
    std::map<char, Trie*> children;

    struct SubtreeInfo {
        std::list<std::string> lines;
        int width;
        int root_pos;
    };

    SubtreeInfo buildSubtree(char c);
    
public:
    Trie();
    void insert(std::string key);
    bool search(std::string key);
    bool deletion(std::string key);
    void printTree();
    void printInOrder(std::string prefix);
    int getHeight();   // Obtiene la altura del Trie
    int getDepth();    // Profundidad máxima
    int getLevel();    // Nivel máximo

};

#endif