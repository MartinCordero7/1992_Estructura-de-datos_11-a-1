/***********************************************************************
 * Module:  ListaDoble.h
 * Author:  Erika Guayanay,Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#pragma once
#include "Nodo.h"
#include <string>
#include <vector>

using namespace std;

class ListaDoble {
private:
    Nodo* primero;
    Nodo* ultimo;
public:
    ListaDoble();
    ~ListaDoble();

    // Funciones básicas de la lista doble
    void insertar(string, string, string);
    Nodo* buscar(string);
    bool eliminar(string);
    void mostrar();
    void eliminarCaracter(string, char);
    bool validarCedulaUnica(string);

    // Nuevas funciones para gestión de archivos y operaciones auxiliares
    void guardarEnArchivo(const string& cedula, const string& nombre, const string& apellido, const string& nombreArchivo);
    void cargarDesdeArchivo(const string& nombreArchivo);

    // Nuevas funciones relacionadas con listas auxiliares y operaciones de cifrado
    void eliminarCaracter(string cedula, char caracter, ListaDoble& listaAuxiliar);
    void cifrarCaracter(string cedula, char caracter, int desplazamiento, ListaDoble& listaAuxiliar);
};
