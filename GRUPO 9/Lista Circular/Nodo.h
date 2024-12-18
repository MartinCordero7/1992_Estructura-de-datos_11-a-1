/***********************************************************************
 * Module:  Nodo.h
 * Author:  Erika Guayanay, Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#pragma once
#include <iostream>
#include <string>

using namespace std;

class Nodo {
private:
    string cedula;
    string nombre;
    string apellido;
    Nodo* siguiente;
public:
    Nodo(string, string, string);
    string getCedula();
    string getNombre();
    string getApellido();
    void setNombre(string);
    void setApellido(string);
    Nodo* getSiguiente();
    void setSiguiente(Nodo*);
};
