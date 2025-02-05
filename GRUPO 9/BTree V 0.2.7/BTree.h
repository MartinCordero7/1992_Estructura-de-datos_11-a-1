#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <fstream>
#include <string>
#include "BTreeNode.h"  // Incluimos la clase BTreeNode

using namespace std;

class BTree {
public:
    BTreeNode *root;
    int t;

    BTree(int _t);
    ~BTree();
    void insert(int k);
    void traverse();
    void saveToFile(const string &filename);
    BTreeNode* search(int k);
    void remove(int k);
    void imprimirArbol(); // Nueva función para imprimir el árbol en consola
    int calcularAltura(); // Nueva función para calcular la altura del árbol
    void imprimirNiveles(); // Nueva función para imprimir los niveles del árbol
    void imprimirProfundidades(); // Nueva función para imprimir las profundidades de los nodos
    void imprimirArbolDetallado(); // Nueva función para imprimir el árbol detalladamente
    BTreeNode* getRoot(); // Add this declaration

private:
    void imprimirNodo(BTreeNode* nodo, int nivel); // Función auxiliar para imprimir nodos
    void imprimirNodo(BTreeNode* nodo, int nivel, const std::string& posicion); // Nueva función auxiliar para imprimir nodos con posición
    int calcularAlturaNodo(BTreeNode* nodo); // Función auxiliar para calcular la altura de un nodo
    void imprimirNivelNodo(BTreeNode* nodo, int nivel); // Función auxiliar para imprimir un nivel del árbol
    void imprimirProfundidadNodo(BTreeNode* nodo, int profundidad); // Función auxiliar para imprimir la profundidad de un nodo
    void imprimirNodoDetallado(BTreeNode* nodo, int nivel, const std::string& posicion); // Nueva función auxiliar para imprimir nodos detalladamente
};

#endif // BTREE_H
