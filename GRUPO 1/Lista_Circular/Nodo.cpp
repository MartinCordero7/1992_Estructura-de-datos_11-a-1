#include "Nodo.h"

Nodo::Nodo(int dato) {
    this->dato = dato;
    this->siguiente = NULL;
}

void Nodo::setDato(int dato) {
    this->dato = dato;
}

int Nodo::getDato() {
    return this->dato;
}

void Nodo::setSiguiente(Nodo* siguiente) {
    this->siguiente = siguiente;
}

Nodo* Nodo::getSiguiente() {
    return this->siguiente;
}