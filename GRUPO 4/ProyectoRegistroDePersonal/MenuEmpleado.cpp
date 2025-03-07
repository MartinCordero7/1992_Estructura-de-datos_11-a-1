#include "MenuEmpleado.h"
#include "GestorPersonas.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#define ANSI_COLOR_CYAN     "\x1b[94m"
#define ANSI_COLOR_RESET    "\x1b[0m"

MenuEmpleado::MenuEmpleado(int totalOpcionesEmpleado) : totalOpcionesEmpleado(totalOpcionesEmpleado) {
    opcionActualEmpleado = 1;
}

void MenuEmpleado::regresarMenuEmpleado() {
    char tecla;
    do {
        tecla = _getch();
    } while (tecla != 13); // Espera hasta que se presione la tecla Enter (código 13)
}

void MenuEmpleado::mostrarMenuEmpleado() {
    system("cls");
    std::cout << "Elija el cargo del empleado:" << std::endl;
    for (int i = 1; i <= totalOpcionesEmpleado; i++) {
        if (i == opcionActualEmpleado) {
            std::cout << "\t> " << ANSI_COLOR_CYAN;
        }
        else {
            std::cout << "  ";
        }
        switch (i) {
        case 1:
            std::cout << "--Rector--" << ANSI_COLOR_RESET << std::endl;
            break;
        case 2:
            std::cout << "--Vicerrector--" << ANSI_COLOR_RESET << std::endl;
            break;
        case 3:
            std::cout << "--Director de Departamento--" << ANSI_COLOR_RESET << std::endl;
            break;
        case 4:
            std::cout << "--Docente--" << ANSI_COLOR_RESET << std::endl;
            break;
        case 5:
            std::cout << "--Personal Administrativo--" << ANSI_COLOR_RESET << std::endl;
            break;
        }
    }
}

int MenuEmpleado::operarMenuEmpleado() {
    while (true) {
        mostrarMenuEmpleado();

        char tecla = _getch();

        switch (tecla) {
        case 72: // Flecha arriba
            opcionActualEmpleado = (opcionActualEmpleado > 1) ? opcionActualEmpleado - 1 : totalOpcionesEmpleado;
            break;
        case 80: // Flecha abajo
            opcionActualEmpleado = (opcionActualEmpleado < totalOpcionesEmpleado) ? opcionActualEmpleado + 1 : 1;
            break;
        case 13: // Tecla Enter
            regresarMenuEmpleado();
            return opcionActualEmpleado; // Retorna el valor seleccionado
        }
    }
    return opcionActualEmpleado; // Agrega esta línea de retorno adicional
}