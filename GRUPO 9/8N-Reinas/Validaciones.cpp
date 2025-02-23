/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      validaciones                                             *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              12/02/2025                                               *
 * Fecha de modificacion:          12/02/2025                                               *
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
