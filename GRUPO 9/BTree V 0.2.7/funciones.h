#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "BTree.h"
#include <string>
using namespace std;

void ingresarNumeros(BTree*& arbol);
void buscarNumero(BTree* arbol);
void eliminarNumero(BTree*& arbol);
void mostrarArbolConsola(BTree* arbol);
void mostrarNumerosEnOrdenInfijo(BTree* arbol);
void inOrderTraversal(BTreeNode* node);
void probarGraphics();
void graficarArbol(BTree* arbol);
void actualizarArbol(BTree* arbol);

#endif // FUNCIONES_H
