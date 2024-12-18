#pragma once

#include "ILista.hpp"
#include "Nodo.hpp"
#include <string>
#include <iostream>

template <typename T>
class ListaSimple : public ILista<T>
{
private:
    Nodo<T>* cabeza;
public:
    ListaSimple();
    ListaSimple(const ListaSimple& otraLista);
    ListaSimple(std::initializer_list<T> valoresIniciales);
    ~ListaSimple();
    Nodo<T>* getCabeza() const;

    void insertarACabeza(T dato);
    void insertarACola(T dato);
    void insertar(T dato, int posicion);
    void intercambiar(int pos1, int pos2);

    int buscar(T dato);
    T conseguirDato(int posicion);
    Nodo<T>* conseguirNodo(int posicion);

    bool eliminar(T dato);
    void eliminarPos(int posicion);

    int contar();

    void mostrar(std::string separador = " => ");

    void executarEnLista(void(*funcion)(T));

    template <typename U>
    int buscar(U id, U(*identifierGetter)(T));
    template <typename U>
    bool eliminar(U id, U(*identifierGetter)(T));
};

template<typename T>
inline ListaSimple<T>::ListaSimple()
    : cabeza(NULL)
{
}

template<typename T>
inline ListaSimple<T>::ListaSimple(const ListaSimple& otraLista)
    : cabeza(NULL)
{
    Nodo<T>*aux = otraLista.getCabeza();
    while (aux != NULL)
    {
        insertarACola(aux->getDato());
        aux = aux->getSiguiente();
    }
}

template<typename T>
inline ListaSimple<T>::ListaSimple(std::initializer_list<T> valoresIniciales)
{
    for (auto valor : valoresIniciales)
        insertarACola(valor);
}

template<typename T>
inline ListaSimple<T>::~ListaSimple()
{
    Nodo<T>* aEliminar;
    Nodo<T>* aux = cabeza;

    while (aux != NULL)
    {
        aEliminar = aux;
        aux = aux->getSiguiente();
        delete aEliminar;
    }
}

template<typename T>
inline Nodo<T>* ListaSimple<T>::getCabeza() const
{
    return cabeza;
}

template<typename T>
inline void ListaSimple<T>::insertarACabeza(T dato)
{
    Nodo<T>* nuevo = new Nodo<T>(dato);

    if (cabeza == NULL)
    {
        cabeza = nuevo;
    }
    else
    {
        nuevo->setSiguiente(cabeza);
        cabeza = nuevo;
    }
}

template<typename T>
inline void ListaSimple<T>::insertarACola(T dato)
{
    Nodo<T>* nuevo = new Nodo<T>(dato);

    if (cabeza == NULL)
        cabeza = nuevo;
    else
    {
        Nodo<T>* aux = cabeza;

        while (aux->siguiente != NULL)
            aux = aux->siguiente;

        aux->siguiente = nuevo;
    }
}

template<typename T>
inline void ListaSimple<T>::insertar(T dato, int posicion)
{
    Nodo<T>* nuevo = new Nodo<T>(dato);
    Nodo<T>* anterior = NULL;

    if (cabeza == NULL)
    {
        cabeza = nuevo;
    }
    else
    {
        int cantidad = contar();

        if (posicion < 0)
            posicion = cantidad + posicion;

        if (posicion > cantidad)
            posicion = cantidad;

        Nodo<T>* aux = cabeza;

        for (posicion; posicion > 0; posicion--)
        {
            anterior = aux;
            aux = aux->siguiente;
        }

        nuevo->siguiente = aux;

        if (anterior != NULL)
            anterior->siguiente = nuevo;
    }
}

template<typename T>
inline void ListaSimple<T>::intercambiar(int pos1, int pos2)
{
    if (nodo1 == cabeza)
        cabeza = nodo2;
    else if (nodo2 == cabeza)
        cabeza = nodo1;

    Nodo<T>* nodo1 = conseguirNodo(pos1);
    Nodo<T>* nodo1Ant = NULL;
    if (pos1 > 0)
        nodo1Ant = conseguirNodo(pos1 - 1);

    Nodo<T>* nodo2 = conseguirNodo(pos2);
    Nodo<T>* nodo2Ant = NULL;
    if (pos2 > 0)
        nodo2Ant = conseguirNodo(pos2 - 1);

    if (nodo1Ant != NULL)
        nodo1Ant->siguiente = nodo2;
    if (nodo2Ant != NULL && nodo2Ant != nodo1)
        nodo2Ant->siguiente = nodo1;

    Nodo<T>* nodo1Sig = nodo1->siguiente;

    nodo1->siguiente = nodo2->siguiente;

    if (nodo2 != nodo1Sig)
        nodo2->siguiente = nodo1Sig;
    else
        nodo2->siguiente = nodo1;
}

template<typename T>
inline int ListaSimple<T>::buscar(T dato)
{
    Nodo<T>* aux = cabeza;

    while (aux != NULL)
    {
        if (aux->dato == dato)
            return true;

        aux = aux->siguiente;
    }

    return false;
}

template<typename T>
inline T ListaSimple<T>::conseguirDato(int posicion)
{
    return conseguirNodo(posicion)->dato;
}

template<typename T>
inline Nodo<T>* ListaSimple<T>::conseguirNodo(int posicion)
{
    Nodo<T>* aux = cabeza;

    for (posicion; posicion > 0; posicion--) // ERROR INTENCIONADO SI ESTÁ FUERA DE RANGO
        aux = aux->siguiente;

    return aux;
}

template<typename T>
inline bool ListaSimple<T>::eliminar(T dato)
{
    Nodo<T>* aux = cabeza;
    Nodo<T>* anterior = NULL;

    while (aux != NULL)
    {
        if (aux->dato == dato)
        {
            if (aux == cabeza)
                cabeza = aux->siguiente;
            else
                anterior->siguiente = aux->siguiente;

            delete aux;
            return true;
        }

        anterior = aux;
        aux = aux->siguiente;
    }

    return false;
}

template<typename T>
inline void ListaSimple<T>::eliminarPos(int posicion)
{
    Nodo<T>* aux = conseguirNodo(posicion);
    Nodo<T>* auxAnt = NULL;
    if (pos1 > 0)
        auxAnt = conseguirNodo(pos1 - 1);


    if (aux == cabeza)
        cabeza = aux->siguiente;
    else
        auxAnt->siguiente = aux->siguiente;

    delete aux;
}

template<typename T>
inline int ListaSimple<T>::contar()
{
    int cont = 0;
    Nodo<T>* aux = cabeza;

    while (aux != NULL)
    {
        cont++;
        aux = aux->siguiente;
    }

    return cont;
}

template<typename T>
inline void ListaSimple<T>::mostrar(std::string separador)
{
    Nodo<T>* aux = cabeza;

    while (aux != NULL)
    {
        std::cout << aux->dato << separador;
        aux = aux->siguiente;
    }

    std::cout << "NULL";
}

template<typename T>
inline void ListaSimple<T>::executarEnLista(void(*funcion)(T))
{
    Nodo<T>* aux = cabeza;

    while (aux != NULL)
    {
        funcion(aux->dato);

        aux = aux->siguiente;
    }
}

template<typename T>
template<typename U>
inline int ListaSimple<T>::buscar(U id, U(*identifierGetter)(T))
{
    Nodo<T>* aux = cabeza;

    while (aux != NULL)
    {
        if (identifierGetter(aux->dato) == id)
            return true;

        aux = aux->siguiente;
    }

    return false;
}

template<typename T>
template<typename U>
inline bool ListaSimple<T>::eliminar(U id, U(*identifierGetter)(T))
{
    Nodo<T>* aux = cabeza;
    Nodo<T>* anterior = NULL;

    while (aux != NULL)
    {
        if (identifierGetter(aux->dato) == id)
        {
            if (aux == cabeza)
                cabeza = aux->siguiente;
            else
                anterior->siguiente = aux->siguiente;

            delete aux;
            return true;
        }

        anterior = aux;
        aux = aux->siguiente;
    }

    return false;
}

