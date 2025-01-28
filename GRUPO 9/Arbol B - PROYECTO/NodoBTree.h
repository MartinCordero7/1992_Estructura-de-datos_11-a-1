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
