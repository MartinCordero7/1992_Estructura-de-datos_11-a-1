#include "SplayTree.h"
#include <iostream>
#include <fstream>

SplayTree::SplayTree() : root(nullptr) {}

SplayTree::~SplayTree()
{
    // Implementar destructor para liberar memoria.
}

void SplayTree::rotateLeft(SplayNode *node)
{
    SplayNode *rightChild = node->derecha;
    if (!rightChild)
        return;

    node->derecha = rightChild->izquierda;
    if (rightChild->izquierda)
        rightChild->izquierda->padre = node;

    rightChild->padre = node->padre;
    if (!node->padre)
        root = rightChild;
    else if (node == node->padre->izquierda)
        node->padre->izquierda = rightChild;
    else
        node->padre->derecha = rightChild;

    rightChild->izquierda = node;
    node->padre = rightChild;
}

void SplayTree::rotateRight(SplayNode *node)
{
    SplayNode *leftChild = node->izquierda;
    if (!leftChild)
        return;

    node->izquierda = leftChild->derecha;
    if (leftChild->derecha)
        leftChild->derecha->padre = node;

    leftChild->padre = node->padre;
    if (!node->padre)
        root = leftChild;
    else if (node == node->padre->izquierda)
        node->padre->izquierda = leftChild;
    else
        node->padre->derecha = leftChild;

    leftChild->derecha = node;
    node->padre = leftChild;
}

void SplayTree::splay(SplayNode *node)
{
    while (node->padre)
    {
        if (!node->padre->padre)
        { // Zig
            if (node == node->padre->izquierda)
                rotateRight(node->padre);
            else
                rotateLeft(node->padre);
        }
        else if (node == node->padre->izquierda &&
                 node->padre == node->padre->padre->izquierda)
        { // Zig-Zig
            rotateRight(node->padre->padre);
            rotateRight(node->padre);
        }
        else if (node == node->padre->derecha &&
                 node->padre == node->padre->padre->derecha)
        { // Zig-Zig
            rotateLeft(node->padre->padre);
            rotateLeft(node->padre);
        }
        else if (node == node->padre->izquierda &&
                 node->padre == node->padre->padre->derecha)
        { // Zig-Zag
            rotateRight(node->padre);
            rotateLeft(node->padre);
        }
        else
        { // Zig-Zag
            rotateLeft(node->padre);
            rotateRight(node->padre);
        }
    }
}

SplayNode *SplayTree::findNode(SplayNode *node, const string &key)
{
    while (node)
    {
        if (key < node->key)
            node = node->izquierda;
        else if (key > node->key)
            node = node->derecha;
        else
            return node;
    }
    return nullptr;
}

SplayNode *SplayTree::findMin(SplayNode *node)
{
    while (node->izquierda)
        node = node->izquierda;
    return node;
}

void SplayTree::insert(const string &key, Libro *libro)
{
    SplayNode *parent = nullptr;
    SplayNode *current = root;

    while (current)
    {
        parent = current;
        if (key < current->key)
            current = current->izquierda;
        else if (key > current->key)
            current = current->derecha;
        else
            return; // La clave ya existe
    }

    SplayNode *newNode = new SplayNode(key, libro);
    newNode->padre = parent;

    if (!parent)
        root = newNode;
    else if (key < parent->key)
        parent->izquierda = newNode;
    else
        parent->derecha = newNode;

    splay(newNode);
}

Libro *SplayTree::search(const string &key)
{
    SplayNode *node = findNode(root, key);
    if (node)
        splay(node);
    return node ? node->libro : nullptr;
}

void SplayTree::remove(const string &key)
{
    SplayNode *node = findNode(root, key);
    if (!node)
        return;

    splay(node);
    if (!node->izquierda)
        root = node->derecha;
    else if (!node->derecha)
        root = node->izquierda;
    else
    {
        SplayNode *minNode = findMin(node->derecha);
        if (minNode->padre != node)
        {
            rotateLeft(minNode->padre);
            minNode->derecha = node->derecha;
        }
        root = minNode;
        root->izquierda = node->izquierda;
    }

    delete node;
}

void SplayTree::printAll(SplayNode *node, ofstream &archivo)
{
    if (!node)
        return;
    printAll(node->izquierda, archivo);
    archivo << node->libro->getTitulo() << ";"
            << node->libro->getAutor().getNombre() << ";"
            << node->libro->getAutor().getIsni() << ";"
            << node->libro->getAutor().getFechaNacimiento().mostrar() << ";"
            << node->libro->getIsbn() << ";"
            << node->libro->getFechaPublicacion().mostrar() << endl;
    printAll(node->derecha, archivo);
}

void SplayTree::printAll(ofstream &archivo)
{
    printAll(root, archivo);
}

void SplayTree::collectAllBooks(SplayNode *node, vector<Libro *> &libros)
{
    if (!node)
        return;
    collectAllBooks(node->izquierda, libros);
    libros.push_back(node->libro);
    collectAllBooks(node->derecha, libros);
}

vector<Libro *> SplayTree::collectAllBooks()
{
    vector<Libro *> libros;
    collectAllBooks(root, libros);
    return libros;
}
