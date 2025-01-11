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
    static void buscarPorSufijo(const ListaCircularDoble& lista, const string& sufijo);
    static void ordenarPorTitulo(ListaCircularDoble& lista);
    static void buscarPorRangoFecha(const ListaCircularDoble& lista, const Fecha& fechaInicio, const Fecha& fechaFin);
private:
    static bool estaOrdenada(const ListaCircularDoble& lista);
    static bool comparaPrefijo(const string& str, const string& prefijo);
    static bool comparaSufijo(const string& str, const string& sufijo);
    static int contarNodos(const ListaCircularDoble& lista);
    static Nodo* obtenerNodoPorIndice(const ListaCircularDoble& lista, int indice);
    static bool estaEnRango(const Fecha& fecha, const Fecha& inicio, const Fecha& fin);
    static void ordenarPorFecha(ListaCircularDoble& lista);
    static bool compararFechas(const Fecha& fecha1, const Fecha& fecha2);
};

#endif