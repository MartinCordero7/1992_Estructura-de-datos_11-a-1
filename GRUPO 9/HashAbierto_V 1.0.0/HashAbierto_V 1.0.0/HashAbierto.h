#ifndef HASHABIERTO_H
#define HASHABIERTO_H

#include "HashA_Nodo.h"
#include <vector>
#include <string>

template <typename T>
class HashAbierto {
private:
    std::vector<HashA_Nodo<T>*> table;
    int size;
    int hashFunction(T key);

public:
    HashAbierto(int size);
    ~HashAbierto();
    void insertar(T key);
    bool buscar(T key);
    bool eliminar(T key);
    void mostrar();
    void graficar(); // New method declaration
};

#endif // HASHABIERTO_H
