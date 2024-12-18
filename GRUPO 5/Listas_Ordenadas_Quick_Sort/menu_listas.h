#ifndef MENU_LISTAS_H
#define MENU_LISTAS_H

#include <iostream>
#include <string>
#include <limits>

#include "persona.cpp"
#include "lista_simple.cpp"
#include "lista_circular.cpp"
#include "lista_doble.cpp"

class MenuListas {
public:
    MenuListas();
    void menuPrincipal(); // Changed to non-static
    void limpiarBuffer();
    std::string obtenerCedula();
    std::string obtenerNombre(const std::string& tipo);
};

// Function declarations for menu functions
void menuListaSimple();
void menuListaCircular();
void menuListaDoble();

#endif