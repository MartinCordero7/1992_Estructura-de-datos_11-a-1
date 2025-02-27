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

    Entrega(const Cliente& cliente, const string& zona)
        : cliente(cliente), zona(zona) {}

    void mostrar() const {
        cout << "Cliente: ";
        cliente.mostrar();
        cout << ", Zona: " << zona << endl;
    }
};

#endif
