/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Archivo de NodoBTree.h                                   *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          01/01/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#ifndef NODOBTREE_H
#define NODOBTREE_H

#include "Libro.h"
#include <vector>

class NodoBTree {
public:
    std::vector<Libro> claves;
    std::vector<NodoBTree*> hijos;
    bool esHoja;

    NodoBTree(bool esHoja);
};

#endif // NODOBTREE_H
