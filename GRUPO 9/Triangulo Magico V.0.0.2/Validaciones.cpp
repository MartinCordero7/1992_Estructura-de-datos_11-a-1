#include "Validaciones.h"
#include <conio.h>
#include <iostream>

using namespace std;

char obtenerEntradaValidada() {
    char tecla;
    while (true) {
        tecla = _getch();
        if ((tecla >= '0' && tecla <= '9') || tecla == '\b' || tecla == '\r' || tecla == 'x' || tecla == 'X') {
            return tecla;
        } else {
            cout << "\a"; // Beep sound for invalid input
        }
    }
}

std::string capturarEntrada() {
    std::string entrada;
    char tecla;
    while (true) {
        tecla = _getch();
        if ((tecla >= '0' && tecla <= '9') || tecla == '\b' || tecla == '\r') {
            if (tecla == '\r') {
                cout << endl;
                break;
            } else if (tecla == '\b') {
                if (!entrada.empty()) {
                    cout << "\b \b";
                    entrada.pop_back();
                }
            } else if (entrada.size() < 2) {
                cout << tecla;
                entrada.push_back(tecla);
            }
        } else {
            cout << "\a"; // Beep sound for invalid input
        }
    }
    return entrada;
}
