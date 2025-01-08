/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Pila para conversion de infija a prefija o posfija  *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              17/12/2024                                          *
 * Fecha de modificacion:          18/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/

#ifndef PILA_CPP
#define PILA_CPP

#include "pila.h"

// Insertar un elemento en la pila
template <typename T>
void Pila<T>::push(T elemento) {
    elementos.push_back(elemento);
}

// Eliminar el elemento en la parte superior
template <typename T>
void Pila<T>::pop() {
    if (elementos.empty()) {
        throw std::out_of_range("La pila esta vacia");
    }
    elementos.pop_back();
}

// Obtener el elemento en la parte superior
template <typename T>
T Pila<T>::top() const {
    if (elementos.empty()) {
        throw std::out_of_range("La pila esta vacia");
    }
    return elementos.back();
}

// Verificar si la pila está vacía
template <typename T>
bool Pila<T>::empty() const {
    return elementos.empty();
}

#endif // PILA_CPP
