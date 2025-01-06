#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <string>
#include <vector>
#include "Libro.h"

using namespace std;

class SplayNode
{
public:
    string key;
    Libro *libro;
    SplayNode *izquierda;
    SplayNode *derecha;
    SplayNode *padre;

    SplayNode(const string &key, Libro *libro)
        : key(key), libro(libro), izquierda(nullptr), derecha(nullptr), padre(nullptr) {}
};

class SplayTree
{
private:
    SplayNode *root;

    void rotateLeft(SplayNode *node);
    void rotateRight(SplayNode *node);
    void splay(SplayNode *node);

    SplayNode *findNode(SplayNode *node, const string &key);
    SplayNode *findMin(SplayNode *node);

    void printAll(SplayNode *node, ofstream &archivo);
    void collectAllBooks(SplayNode *node, vector<Libro *> &libros);

public:
    SplayTree();
    ~SplayTree();
    void insert(const string &key, Libro *libro);
    Libro *search(const string &key);
    void remove(const string &key);

    void printAll(ofstream &archivo);
    vector<Libro *> collectAllBooks();
};

#endif
