#include "lista.h"

Nodo::Nodo(std::string texto, int id) {
    this->texto = texto;
    this->id = id;
    this->siguiente = nullptr;
    this->anterior = nullptr;
}

Lista::Lista() {
    actual = nullptr;
    size = 0;
}

Lista::~Lista() {
    limpiar();
}

void Lista::insertarOpcion(std::string texto, int id) {
    Nodo* nuevo = new Nodo(texto, id);
    
    if (estaVacia()) {
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
        actual = nuevo;
    } else {
        nuevo->siguiente = actual->siguiente;
        nuevo->anterior = actual;
        actual->siguiente->anterior = nuevo;
        actual->siguiente = nuevo;
    }
    size++;
}

void Lista::siguiente() {
    if (!estaVacia()) {
        if (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        } else {
            // Volver al primer elemento
            while (actual->anterior != nullptr) {
                actual = actual->anterior;
            }
        }
    }
}

void Lista::anterior() {
    if (!estaVacia()) {
        if (actual->anterior != nullptr) {
            actual = actual->anterior;
        } else {
            // Ir al último elemento
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
        }
    }
}

Nodo* Lista::getActual() const {
    return actual;
}

bool Lista::estaVacia() const {
    return actual == nullptr;
}

void Lista::limpiar() {
    if (estaVacia()) return;
    
    Nodo* temp = actual->siguiente;
    while (temp != actual) {
        Nodo* siguiente = temp->siguiente;
        delete temp;
        temp = siguiente;
    }
    delete actual;
    actual = nullptr;
    size = 0;
}

int Lista::getSize() const {
    return size;
}
