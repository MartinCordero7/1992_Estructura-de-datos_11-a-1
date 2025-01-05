/***********************************************************************
 * Module:  ListasCirculares.h
 * Author:  Erika Guayanay, Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#pragma once
#include "Nodo.h"

using namespace std;

class ListaCircular {
private:
    Nodo* primero;
    Nodo* ultimo;
public:
    ListaCircular();
    void insertar(string cedula, string nombre, string apellido, bool mostrarMensaje = true);
    Nodo* buscar(string);
    bool eliminar(string);
    void mostrar();
    void eliminarCaracter(string, char);
    bool validarCedulaUnica(string);
    void normalizarLista();
    void cifrarCaracter(const std::string& cedula, char caracter, int desplazamiento);
    void mostrarListaAuxiliar(const std::string& archivo);
    void mostrarArchivoOrdenado(const std::string& archivo);

    // Métodos para acceder y modificar los punteros
    Nodo* getPrimero() const { return primero; }
    Nodo* getUltimo() const { return ultimo; }
    void setPrimero(Nodo* nodo) { primero = nodo; }
    void setUltimo(Nodo* nodo) { ultimo = nodo; }
};
