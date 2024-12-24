#pragma once

#include "Nodo.hpp"
#include <string>
#include <functional>

template <typename T>
class ILista
{

public:
    virtual ~ILista();
    virtual Nodo<T>* getCabeza() const = 0;
    virtual Nodo<T>* getCola() const = 0;

    virtual void insertarACabeza(const T& dato) = 0;
    virtual void insertarACola(const T& dato) = 0;
    virtual void insertar(const T& dato, int posicion) = 0;
    virtual void intercambiar(int pos1, int pos2) = 0;

    virtual int buscar(const T& dato) const = 0;
    virtual int buscar(const std::string& id, std::function<const std::string& (const T&)> identifierGetter) const = 0;
    virtual const T& conseguirDato(int posicion) const = 0;
    virtual Nodo<T>* conseguirNodo(int posicion) const = 0;

    virtual bool eliminar(const T& dato) = 0;
    virtual bool eliminar(const std::string& id, std::function<const std::string& (const T&)> identifierGetter) = 0;
    virtual void eliminarPos(int posicion) = 0;

    virtual void mostrar(const std::string& = " => ") const = 0;

    virtual int contar() const = 0;

};

template<typename T>
inline ILista<T>::~ILista()
{
}
