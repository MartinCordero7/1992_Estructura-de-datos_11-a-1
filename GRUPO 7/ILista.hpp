#pragma once

#include "Nodo.hpp"
#include <string>

template <typename T>
class ILista
{

public:
    virtual ~ILista();
    virtual Nodo<T>* getCabeza() const = 0;
    virtual Nodo<T>* getCola() const = 0;

    virtual void insertarACabeza(T dato) = 0;
    virtual void insertarACola(T dato) = 0;
    virtual void insertar(T dato, int posicion) = 0;
    virtual void intercambiar(int pos1, int pos2) = 0;

    virtual int buscar(T dato) = 0;
    virtual T conseguirDato(int posicion) = 0;
    virtual Nodo<T>* conseguirNodo(int posicion) = 0;

    virtual bool eliminar(T dato) = 0;
    virtual void eliminarPos(int posicion) = 0;

    virtual void mostrar(std::string = " => ") = 0;

    virtual int contar() = 0;

};

template<typename T>
inline ILista<T>::~ILista()
{
}
