#pragma once

#include "ILista.hpp"
#include "Nodo.hpp"
#include <string>
#include <iostream>

template <typename T>
class ListaCircularDoble : public ILista<T> {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;

public:
    ListaCircularDoble();
    ~ListaCircularDoble();

    Nodo<T>* getCabeza() const;
    Nodo<T>* getCola() const;

    void insertarACabeza(T dato) override;
    void insertarACola(T dato) override;
    void insertar(T dato, int posicion) override;
    void intercambiar(int pos1, int pos2) override;

    int buscar(T dato) override;
    T conseguirDato(int posicion) override;
    Nodo<T>* conseguirNodo(int posicion) override;

    bool eliminar(T dato) override;
    void eliminarPos(int posicion) override;

    int contar() override;
    void mostrar(std::string separador = " <=> ") override;
};

// Constructor
template <typename T>
ListaCircularDoble<T>::ListaCircularDoble() : cabeza(NULL), cola(NULL) 
    : cabeza(NULL)
{
}

// Destructor
template <typename T>
ListaCircularDoble<T>::~ListaCircularDoble() {
    if (cabeza) {
    Nodo<T>* aux = cabeza;
    do {
        Nodo<T>* siguiente = aux->getSiguiente();
        delete aux;
        aux = siguiente;
    } while (actual != cabeza);
    }
}
 // Obtener la cabeza
template <typename T>
Nodo<T>* ListaCircularDoble<T>::getCabeza() const {
    return cabeza;
}
// Obtener la cola
template <typename T>
Nodo<T>* ListaCircularDoble<T>::getCola() const {
    return cola;
}

// Insertar al inicio
template <typename T>
void ListaCircularDoble<T>::insertarACabeza(T dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (!cabeza) {
        cabeza = cola = nuevo;
        cabeza->setSiguiente(cabeza);
        cabeza->setAnterior(cabeza);
    }
    else {
        nuevo->setSiguiente(cabeza);
        nuevo->setAnterior(cola);
        cabeza->setAnterior(nuevo);
        cola->setSiguiente(nuevo);
        cabeza = nuevo;
    }
}

// Insertar al final
template <typename T>
void ListaCircularDoble<T>::insertarACola(T dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (!cabeza) {
        cabeza = cola = nuevo;
        cabeza->setSiguiente(cabeza);
        cabeza->setAnterior(cabeza);
    }
    else {
        nuevo->setSiguiente(cabeza);
        nuevo->setAnterior(cola);
        cola->setSiguiente(nuevo);
        cabeza->setAnterior(nuevo);
        cola = nuevo;
    }
}

// Insertar en posicion especifica
template <typename T>
void ListaCircularDoble<T>::insertar(T dato, int posicion) {
    if (posicion <= 0) {
        insertarACabeza(dato);
    }
    else if (posicion >= contar()) {
        insertarACola(dato);
    }
    else {
        Nodo<T>* aux = cabeza;
        for (int i = 0; i < posicion - 1; i++) {
            aux = aux->getSiguiente();
        
        Nodo<T>* nuevo = new Nodo<T>(dato);
        nuevo->setSiguiente(aux->getSiguiente());
        nuevo->setAnterior(aux);
        aux->getSiguiente()->setAnterior(nuevo);
        aux->setSiguiente(nuevo);
        }
    }    
}
    // Intercambiar dos nodos
template <typename T>
void ListaCircularDoble<T>::intercambiar(int pos1, int pos2) {
    if (pos1 == pos2) return;

    Nodo<T>* nodo1 = conseguirNodo(pos1);
    Nodo<T>* nodo2 = conseguirNodo(pos2);

    if (!nodo1 || !nodo2) return;

    // Intercambio de datos
    T temp = nodo1->getDato();
    nodo1->setDato(nodo2->getDato());
    nodo2->setDato(temp);
}
// Buscar un elemento
template <typename T>
int ListaCircularDoble<T>::buscar(T dato) {
    if (!cabeza) return -1 do {
        if (actu
    if (cabeza) {
l->getDato() == dato) return posicion;
        actual = actual->getSiguiente();
        posicion++;
    } while (actual != cabeza);

    return -1;
}

// Conseguir dato en posicion especifica
template <typename T>
T ListaCircularDoble<T>::conseguirDato(int posicion) {
    if (!cabeza) throw std::out_of_range("Lista vacia");

    Nodo<T>* aux = cabeza;
    int contador = 0;
    do {
        if (contador == posicion) return aux->getDato();
        aux = aux->getSiguiente();
        contador++;
    } while (aux != cabeza);

    throw std::out_of_range("Posicion fuera de rango");
}

// Eliminar un elemento por valor
template <typename T>
bool ListaCircularDoble<T>::eliminar(T dato) {
    if (!cabeza) return false;

    Nodo<T>* actual = cabeza;

    do {
        if (actual->getDato() == dato) {
            if (actual == cabeza && actual->getSiguiente() == cabeza) {
                delete actual;
                cabeza = NULL;
                return true;
            }

            Nodo<T>* anterior = actual->getAnterior();
            Nodo<T>* siguiente = actual->getSiguiente();
            anterior->setSiguiente(siguiente);
            siguiente->setAnterior(anterior);

            if (actual == cabeza) cabeza = siguiente;

            delete actual;
            return true;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    return false;
}

// Eliminar por posici0n
template <typename T>
void ListaCircularDoble<T>::eliminarPos(int posicion) {
    int cantidad = contar();
    if (posicion < 0 || posicion >= cantidad) throw std::out_of_range("Posicion fuera de rango");

    Nodo<T>* aux = cabeza;

    for (int i = 0; i < posicion; i++) {
        aux = aux->getSiguiente();
    }
    eliminar(aux->getDato());
}

// Contar elementos
template <typename T>
int ListaCircularDoble<T>::contar() {
    if (!cabeza) return 0;

    int contador = 0;
    Nodo<T>* actual = cabeza;

    do {
        contador++;
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    return contador;
}

// Mostrar lista
template <typename T>
void ListaCircularDoble<T>::mostrar(std::string separador) {
    if (!cabeza) {
        std::cout << "Lista vacia\n";
        return;
    }
    Nodo<T>* actual = cabeza;
    do {
        std::cout << actual->getDato() << separador;
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    std::cout << " (cabeza)\n";
}
