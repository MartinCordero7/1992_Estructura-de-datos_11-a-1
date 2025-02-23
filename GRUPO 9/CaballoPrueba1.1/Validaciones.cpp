/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      validaciones                                             *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              17/02/2025                                               *
 * Fecha de modificacion:          17/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include "Validaciones.h"
#include <cctype>
#include <iostream>
#include <conio.h>

bool Validaciones::validarEntrada(const std::string& entrada, int& size) {
    if (entrada == "X" || entrada == "x") {
        return true;
    }

    if (entrada.length() == 1 && std::isdigit(entrada[0])) {
        size = entrada[0] - '0';
        if (size >= 1 && size <= 8) {
            return true;
        }
    }

    return false;
}

bool Validaciones::validarEntradaCaballo(int& fila, int& col) {
    char tecla;
    std::string entrada = ""; // Almacena la entrada del usuario
    std::cout << "Ingrese la posicion inicial del caballo (fila columna) o 'X' para salir: ";

    while (true) {
        tecla = _getch(); // Captura una sola tecla

        if (tecla >= '1' && tecla <= '8') { // Solo permite números del 1 al 8
            if (entrada.length() == 0 || entrada.length() == 2) { // Permitir solo en la primera y tercera posición
                entrada += tecla;
                std::cout << tecla; // Muestra el número ingresado
            }
        } 
        else if (tecla == ' ' && entrada.length() == 1) { // Permite un espacio después del primer número
            entrada += tecla;
            std::cout << tecla; // Muestra el espacio ingresado
        }
        else if (tecla == 8 && !entrada.empty()) { // Permite borrar (Backspace)
            entrada.pop_back();
            std::cout << "\b \b"; // Borra el último carácter en pantalla
        } 
        else if ((tecla == '\r' || tecla == '\n') && entrada.length() == 3) { // Enter para confirmar
            std::cout << std::endl; // Salto de línea para confirmar
            fila = entrada[0] - '0';
            col = entrada[2] - '0';
            if (fila >= 1 && fila <= 8 && col >= 1 && col <= 8) {
                fila--; // Ajustar a índice 0
                col--; // Ajustar a índice 0
                return true;
            } else {
                std::cerr << "Entrada invalida. Intente de nuevo." << std::endl;
                entrada.clear();
                std::cout << "Ingrese la posicion inicial del caballo (fila columna) o 'X' para salir: ";
            }
        }
        else if (tecla == 'X' || tecla == 'x') { // Permite salir con 'X'
            std::cout << tecla; // Muestra la 'X'
            tecla = _getch(); // Espera la confirmación con Enter
            if (tecla == '\r' || tecla == '\n') {
                std::cout << std::endl; // Salto de línea para confirmar
                return false; // Retorna false para indicar salida
            } else {
                std::cout << "\b \b"; // Borra la 'X' si no se confirma con Enter
            }
        }
    }
}

int Validaciones::validarEntero(const std::string& mensaje) {
    char tecla;
    std::string entrada = ""; // Almacena la entrada del usuario
    std::cout << mensaje;

    while (true) {
        tecla = _getch(); // Captura una sola tecla

        if (tecla >= '1' && tecla <= '8') { // Solo permite números del 1 al 8
            if (entrada.length() < 1) { // Permitir solo una cifra
                entrada += tecla;
                std::cout << tecla; // Muestra el número ingresado
            }
        } 
        else if (tecla == 8 && !entrada.empty()) { // Permite borrar (Backspace)
            entrada.pop_back();
            std::cout << "\b \b"; // Borra el último carácter en pantalla
        } 
        else if ((tecla == '\r' || tecla == '\n') && !entrada.empty()) { // Enter para confirmar
            std::cout << std::endl; // Salto de línea para confirmar
            return std::stoi(entrada); // Retorna la entrada como entero
        }
        else if (tecla == 'X' || tecla == 'x') { // Permite salir con 'X'
            std::cout << tecla; // Muestra la 'X'
            tecla = _getch(); // Espera la confirmación con Enter
            if (tecla == '\r' || tecla == '\n') {
                std::cout << std::endl; // Salto de línea para confirmar
                return -1; // Retorna -1 para indicar salida
            } else {
                std::cout << "\b \b"; // Borra la 'X' si no se confirma con Enter
            }
        }
    }
}
