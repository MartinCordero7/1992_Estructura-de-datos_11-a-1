#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <iostream>
using namespace std;

class Cliente {
public:
    string nombre;
    string cedula;
    
    Cliente(const string& nombre, const string& cedula)
        : nombre(nombre), cedula(cedula) {}

    // Función para mostrar información del cliente
    void mostrar() const {
        cout << "Nombre: " << nombre << ", Cédula: " << cedula;
    }
};

#endif
