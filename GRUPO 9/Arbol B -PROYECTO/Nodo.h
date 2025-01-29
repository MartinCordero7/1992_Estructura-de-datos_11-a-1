/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Archivo principal de proyecto                            *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          01/01/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef NODO_H
#define NODO_H

#include "Libro.cpp"

// Nodo de la lista circular doblemente enlazada
struct Nodo {
    Libro libro;       // Ahora contiene un objeto de tipo Libro
    Nodo* siguiente;
    Nodo* anterior;
};

#endif
