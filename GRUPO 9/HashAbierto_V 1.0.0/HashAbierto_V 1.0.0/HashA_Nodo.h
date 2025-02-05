#ifndef HASHA_NODO_H
#define HASHA_NODO_H

template <typename T>
struct HashA_Nodo {
    T data;
    HashA_Nodo* next;
    HashA_Nodo(T val) : data(val), next(nullptr) {}
};

#endif // HASHA_NODO_H
