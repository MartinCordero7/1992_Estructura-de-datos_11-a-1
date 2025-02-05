/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Arbol trie en modo grafico                               *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/05/2025                                               *
 * Fecha de modificacion:          03/05/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#ifndef TRIE_H
#define TRIE_H

#include <list>
#include <map>
#include <string>
#include <graphics.h>
#include <conio.h>
#include <windows.h>

class Trie {
private:
    bool isLeaf;
    std::map<char, Trie*> children;
    void drawSubtree(Trie* node, int x, int y, int level, int spacing);
    void drawNode(int x, int y, char c, bool isLastLetter = false);
    void drawConnection(int x1, int y1, int x2, int y2);
public:
    Trie();
    void insert(std::string key);
    bool search(std::string key);
    bool deletion(std::string key);
    void printTree();
    void printInOrder(std::string prefix = ""); // Aquí se mantiene el argumento por defecto
    int getHeight();
    int getDepth();
    int getLevel();
};

#endif
