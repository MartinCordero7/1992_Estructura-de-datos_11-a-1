#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <iostream>
using namespace std;

class Cliente {
public:
    string nombre;
    string cedula;
    string celular;  // Nuevo campo
    
    Cliente(const string& nombre, const string& cedula, const string& celular)
        : nombre(nombre), cedula(cedula), celular(celular) {}

    void mostrar() const {
        cout << "Nombre: " << nombre << ", Cédula: " << cedula << ", Celular: " << celular;
    }
};

#endif