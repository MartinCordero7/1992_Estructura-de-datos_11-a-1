#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H

#include "Empleado.h"
#include "ArbolRadix.h"

class ListaCircularDoble
{
private:
    struct Nodo
    {
        Empleado *dato;
        Nodo *siguiente;
        Nodo *anterior;

        Nodo(Empleado *empleado) : dato(empleado), siguiente(nullptr), anterior(nullptr) {}
    };

    Nodo *primero;
    Nodo *ultimo;
    Nodo *particion(Nodo *bajo, Nodo *alto);
    void quickSortRecursivo(Nodo *bajo, Nodo *alto);

public:
    ListaCircularDoble();
    ~ListaCircularDoble();

    bool estaVacia();
    void insertarAlInicio(Empleado *empleado);
    void insertarAlFinal(Empleado *empleado);
    void eliminarPersona(Empleado *empleado);
    void eliminarAlInicio();
    void eliminarAlFinal();
    Empleado *buscarPersona(const std::string &cedula);
    void quickSort();
    int contarElementos();

    void imprimirLista() const;
    void cargarDesdeArchivo(const std::string &nombreArchivo);
    friend void cargarListaEnArbol(ListaCircularDoble &lista, ArbolRadix &arbol);
};

#endif /* LISTACIRCULARDOBLE_H */