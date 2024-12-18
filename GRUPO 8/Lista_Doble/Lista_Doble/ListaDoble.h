/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
// Lista_Doble.h
#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include <iostream>
#include "Nodo.h"

template <typename T>
class ListaDoble {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola; // Puntero al último nodo

public:
    ListaDoble();
    ~ListaDoble();
    
    void insertar(const T& elemento);
    void eliminar(const std::string& criterio, const std::string& valor);
    void buscar(const std::string& criterio, const std::string& valor) const;
    void mostrar() const;
    void limpiar();

    void cifrar(std::string criterio, char caracter, int desplazamiento, ListaDoble& listaAuxiliar);
    //ordenamiento merge sort 
    void ordenar(const int& criterio, const int& orden); 
};

#endif

