#ifndef ENTREGA_H
#define ENTREGA_H

#include <string>
#include <iostream>
#include "Cliente.h"
using namespace std;

class Entrega {
public:
    Cliente cliente;
    string zona;
    int prioridad;
    
    Entrega(const Cliente& cliente, const string& zona, int prioridad)
        : cliente(cliente), zona(zona), prioridad(prioridad) {}

    // Función para mostrar información de la entrega
    void mostrar() const {
        cout << "Cliente: ";
        cliente.mostrar();
        cout << ", Zona: " << zona << ", Prioridad: " << prioridad << endl;
    }
};

#endif
