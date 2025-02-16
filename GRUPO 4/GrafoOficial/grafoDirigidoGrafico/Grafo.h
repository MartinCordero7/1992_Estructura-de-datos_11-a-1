/**********
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Steven Egas, Pablo Dominguez, Esteban Santos
 * FECHA CREACION: Viernes,  7 de Febrero de 2025
 * FECHA MODIFICACION: Miercoles, 12 de Febrero de 2025
 * PROYECTO: Grafos
 * Nivel: TERCERO     NRC: 1992
 ***********/
#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <iostream>
#include <queue>

class Grafo
{
public:
    Grafo();
    void nuevoGrafo(int numNodos, bool dirigido);
    void representacionLogica();
    void representacionListaAdyacencia();
    void representacionMatrizAdyacencia();
    void busquedaAmplitud(int verticeInicial);
    void representacionLogicaGrafica(const std::string& titulo);
    void representacionListaAdyacenciaGrafica(const std::string& titulo);
    void representacionMatrizAdyacenciaGrafica(const std::string& titulo);

private:
    int numNodos;
    bool dirigido;
    std::vector<std::vector<int>> matrizAdyacencia;
    void generarRelacionesAleatorias();
};

#endif // GRAFO_H