/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Util de entrada de datos                                 *
 * Autor:                          Steven Egas, Esteban Santos,Pablo Dominguez       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/


#ifndef RADIX_TREE_H
#define RADIX_TREE_H

#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include "Libro.h"

using namespace std;

class RadixTreeNode {
public:
    unordered_map<string, RadixTreeNode*> children;
    Libro* libro;
    RadixTreeNode() : libro(nullptr) {}
};

class RadixTree {
private:
    RadixTreeNode* root;
    void collectAllBooks(RadixTreeNode* node, vector<Libro*>& libros);
    void collectSuggestions(RadixTreeNode* node, const string& prefix, vector<string>& suggestions);
    int levenshteinDistance(const string& s1, const string& s2);
    void printInOrder(RadixTreeNode* node, const string& prefix);
    void printPreOrder(RadixTreeNode* node, const string& prefix);
    void printPostOrder(RadixTreeNode* node, const string& prefix);
public:
    RadixTree();
    void insert(const string& key, Libro* libro);
    Libro* search(const string& key);
    void remove(const string& key);
    bool removeHelper(RadixTreeNode* node, const string& key, size_t depth);
    void printAll(RadixTreeNode* node, string prefix, ofstream& archivo);
    void printAll(ofstream& archivo);
    vector<Libro*> collectAllBooks();
    vector<string> getSuggestions(const string& prefix);
    vector<string> getTypoSuggestions(const string& prefix, int maxDistance);
    vector<string> getSuggestionsByAuthor(const string& prefix);
    vector<string> getSuggestionsByIsbn(const string& prefix);
    vector<string> getSuggestionsByCharacter(const string& input);
    void generateGraph(const string& outputFile);
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
};

#endif