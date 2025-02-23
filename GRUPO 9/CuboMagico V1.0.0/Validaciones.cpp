#include "Validaciones.h"
#include <iostream>
#include <conio.h>  // Para _getch()

int Validaciones::validarEntero(const std::string& mensaje) {
    char tecla;
    std::string entrada = "";  // Almacena la entrada del usuario
    std::cout << mensaje;

    while (true) {
        tecla = _getch();  // Captura una sola tecla

        if (tecla >= '0' && tecla <= '9') {  // Solo permite números
            if (entrada.length() < 2) {  // Permitir hasta dos cifras
                entrada += tecla;
                std::cout << tecla;  // Muestra el número ingresado
            }
        } 
        else if (tecla == 8 && !entrada.empty()) {  // Permite borrar (Backspace)
            entrada.pop_back();
            std::cout << "\b \b";  // Borra el último carácter en pantalla
        } 
        else if ((tecla == '\r' || tecla == '\n') && !entrada.empty()) {  // Enter para confirmar
            std::cout << std::endl;  // Salto de línea para confirmar
            return std::stoi(entrada);  // Retorna la entrada como entero
        }
    }
}

int Validaciones::validarEnteroImpar(const std::string& mensaje) {
    char tecla;
    std::string entrada = "";  // Almacena la entrada del usuario
    std::cout << mensaje;

    while (true) {
        tecla = _getch();  // Captura una sola tecla

        if (tecla >= '1' && tecla <= '9' && (tecla - '0') % 2 != 0) {  
            // Solo permite números impares (1, 3, 5, 7, 9)
            if (entrada.length() < 2) {  // Permitir hasta dos cifras
                entrada += tecla;
                std::cout << tecla;  // Muestra el número ingresado
            }
        } 
        else if (tecla == 8 && !entrada.empty()) {  // Permite borrar (Backspace)
            entrada.pop_back();
            std::cout << "\b \b";  // Borra el último carácter en pantalla
        } 
        else if ((tecla == '\r' || tecla == '\n') && !entrada.empty()) {  // Enter para confirmar
            std::cout << std::endl;  // Salto de línea para confirmar
            return std::stoi(entrada);  // Retorna la entrada como entero
        }
    }
}
