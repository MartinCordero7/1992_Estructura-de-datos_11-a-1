/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Lista_Simple.h
#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H

#include <iostream>
#include "Nodo.h"

template <typename T>
class ListaCircular {
private:
    Nodo<T>* cabeza;

public:
    ListaCircular();
    ~ListaCircular();
    
    void insertar(const T& elemento);
    void eliminar(const std::string& criterio, const std::string& valor);
    void buscar(const std::string& criterio, const std::string& valor) const;
    void mostrar() const;
    void limpiar();
    void cifrar(std::string criterio, char caracter, int desplazamiento, ListaCircular& listaAuxiliar);
    void ordenar(const int& criterio, const int& orden);
};

#endif

