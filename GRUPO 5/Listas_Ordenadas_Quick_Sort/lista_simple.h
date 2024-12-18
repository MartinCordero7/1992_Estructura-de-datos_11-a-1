#ifndef LISTA_SIMPLE_H
#define LISTA_SIMPLE_H

#include <iostream>
#include "persona.h"
using namespace std;

template <typename T>
class Nodo {
public:
    T data;
    Nodo* siguiente;

    Nodo(T data) : data(data), siguiente(nullptr) {}
};
template <typename T>
class ListaSimple {
private:
    Nodo<T>* cabeza;

    // Función auxiliar para copiar una ListaSimpleSimple
    void copiarListaSimple(const Nodo<T>* otraCabeza);
    Nodo<T>* partitionByCedula(Nodo<T>* low, Nodo<T>* high);
    Nodo<T>* partitionByNombre(Nodo<T>* low, Nodo<T>* high);
    Nodo<T>* partitionByApellido(Nodo<T>* low, Nodo<T>* high);
    Nodo<T>* getLastNode();
    
    void quicksortCedula(Nodo<T>* low, Nodo<T>* high);
    void quicksortNombre(Nodo<T>* low, Nodo<T>* high);
    void quicksortApellido(Nodo<T>* low, Nodo<T>* high);

public:
    ListaSimple();
    ~ListaSimple();

    ListaSimple(const ListaSimple& otra);            // Constructor de copia
    ListaSimple& operator=(const ListaSimple& otra); // Operador de asignación

    void insertarPorCabeza(T data);
    void insertarPorCola(T data);
    void eliminarPorCabeza();
    void eliminarPorCedula(string cedula);
    void mostrarLista() const;
    void eliminarCaracter(char c);
    void reemplazarCaracter(char original, char reemplazo);
    //void buscarEnListaSimple();
    void buscarPorCedula(string cedula);

    void ordenarPorCedula();
    void ordenarPorNombre();
    void ordenarPorApellido();
};


#endif