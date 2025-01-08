#ifndef FUNCIONESBUSQUEDABINARIA_H
#define FUNCIONESBUSQUEDABINARIA_H

#include "ListaCircularDoble.h"
#include "Libro.h"
#include <algorithm>
#include <string>
#include <iomanip>
#include <iostream>

class FuncionesBusquedaBinaria {
public:
    static void buscarPorPrefijo(const ListaCircularDoble& lista, const string& prefijo);
    static void ordenarPorTitulo(ListaCircularDoble& lista);
private:
    static bool estaOrdenada(const ListaCircularDoble& lista);
    static bool comparaPrefijo(const string& str, const string& prefijo);
    static int contarNodos(const ListaCircularDoble& lista);
    static Nodo* obtenerNodoPorIndice(const ListaCircularDoble& lista, int indice);
};

#endif