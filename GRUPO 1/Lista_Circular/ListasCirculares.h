#pragma once
#include "Nodo.h"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class ListaCircular {
private:
    Nodo* primero;
    Nodo* ultimo;

    // Métodos privados auxiliares para Radix Sort
    int obtenerNumeroDigitos(int numero);
    int obtenerDigito(int numero, int posicion);

public:
    ListaCircular();
    void Insertar(int);
    void Buscar(int);
    void Eliminar(int);
    void Mostrar();
    void RadixSort();
    int ObtenerMaximo();
};