#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include <iostream>
using namespace std;

template <typename T>
class NodoDoble {
public:
    T data;
    NodoDoble* siguiente;
    NodoDoble* anterior;

    NodoDoble(T data) : data(data), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
class ListaDoble {
private:
    NodoDoble<T>* cabeza;
    NodoDoble<T>* cola;

    // Función auxiliar para copiar una lista
    void copiarListaDoble(const NodoDoble<T>* otraCabeza);

public:
    ListaDoble();
    ~ListaDoble();

    ListaDoble(const ListaDoble& otra);            // Constructor de copia
    ListaDoble& operator=(const ListaDoble& otra); // Operador de asignación

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
