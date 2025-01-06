#ifndef NODO_H
#define NODO_H

#include "Libro.cpp"

// Nodo de la lista circular doblemente enlazada
struct Nodo
{
    Libro libro; // Ahora contiene un objeto de tipo Libro
    Nodo *siguiente;
    Nodo *anterior;
};

#endif
