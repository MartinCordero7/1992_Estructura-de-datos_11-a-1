#ifndef BTREENODE_H
#define BTREENODE_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class BTreeNode {
public:
    vector<int> keys;
    vector<BTreeNode*> children;
    bool leaf;
    int t;

    BTreeNode(int _t, bool _leaf);
    ~BTreeNode();
    void traverse();
    BTreeNode* search(int k);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);
    void saveToFile(ofstream &file);
    void imprimir(int nivel); // Declaración de la función
    void remove(int k);       // Cambiado a público para acceso desde BTree

private:
    int findKey(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
};

#endif // BTREENODE_H
