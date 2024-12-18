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
