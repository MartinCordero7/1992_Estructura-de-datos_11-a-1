#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

#include <iostream>
using namespace std;

template <typename T>
class NodoCircular {
public:
    T data;
    NodoCircular* siguiente;
    NodoCircular* anterior;

    NodoCircular(T data) : data(data), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
class ListaCircular {
private:
    NodoCircular<T>* cabeza;
    NodoCircular<T>* cola;

    // Función auxiliar para copiar una ListaCircular
    void copiarListaCircular(const NodoCircular<T>* otraCabeza);

public:
    ListaCircular();
    ~ListaCircular();

    ListaCircular(const ListaCircular& otra);            // Constructor de copia
    ListaCircular& operator=(const ListaCircular& otra); // Operador de asignación

    void insertarPorCabeza(T data);
    void insertarPorCola(T data);
    void eliminarPorCabeza();
    void eliminarPorCedula(string cedula);
    void mostrarLista() const;
    void mostrarListaInversa() const; // Nueva función para mostrar la lista en orden inverso
    void eliminarCaracter(char c);
    void reemplazarCaracter(char original, char reemplazo);
    void buscarPorCedula(string cedula);
};

#endif
