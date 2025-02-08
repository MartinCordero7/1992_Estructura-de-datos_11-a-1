#include "Validaciones.h"
#include <iostream>
#include <limits>
#include <conio.h>

int Validaciones::validarEntero(const std::string& mensaje) {
    int valor;
    while (true) {
        std::cout << mensaje;
        std::cin >> valor;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Intente de nuevo.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
    }
}

std::string Validaciones::validarCadena(const std::string& mensaje) {
    char tecla;
    std::string entrada = ""; // Almacena la entrada del usuario
    std::cout << mensaje;

    while (true) {
        tecla = _getch(); // Captura una sola tecla

        if ((tecla >= 'a' && tecla <= 'z') || (tecla >= 'A' && tecla <= 'Z')) { // Solo permite letras
            entrada += tecla;
            std::cout << tecla; // Muestra la letra ingresada
        } 
        else if (tecla == 8 && !entrada.empty()) { // Permite borrar (Backspace)
            entrada.pop_back();
            std::cout << "\b \b"; // Borra el último carácter en pantalla
        } 
        else if ((tecla == '\r' || tecla == '\n') && !entrada.empty()) { // Enter para confirmar
            std::cout << std::endl; // Salto de línea para confirmar
            return entrada; // Retorna la entrada como string
        }
        else if (tecla == '-') { // Si presionan "-", seguimos leyendo
            char nextChar = _getch(); // Leemos el siguiente carácter después del guion
            if (nextChar == '1') {  // Si es "-1", terminamos
                std::cout << "-1" << std::endl; // Mostrar "-1" y finalizar
                return "-1"; // Retorna "-1" para finalizar
            }
        }
    }
}



int Validaciones::validarOpcionMenu(const std::string& mensaje) {
    char tecla;
    std::string entrada = ""; // Almacena la opción ingresada
    std::cout << mensaje;

    while (true) {
        tecla = _getch(); // Captura una sola tecla

        if (tecla >= '1' && tecla <= '3') { // Solo permite 1, 2 o 3
            if (entrada.empty()) { // Solo permitir una sola cifra
                entrada += tecla;
                std::cout << tecla; // Muestra la opción seleccionada
            }
        } 
        else if (tecla == 8 && !entrada.empty()) { // Tecla de borrar (Backspace)
            entrada.pop_back();
            std::cout << "\b \b"; // Borra el carácter de la consola
        } 
        else if ((tecla == '\r' || tecla == '\n') && !entrada.empty()) { // Si presiona Enter y hay algo escrito
            std::cout << std::endl; // Salto de línea para confirmar
            return entrada[0] - '0'; // Convertimos el carácter a número y lo retornamos
        }
    }
}

int Validaciones::validarOpcionSubMenu(const std::string& mensaje) {
    char tecla;
    std::string entrada = ""; // Almacena la opción ingresada
    std::cout << mensaje;

    while (true) {
        tecla = _getch(); // Captura una sola tecla

        if (tecla >= '1' && tecla <= '5') { // Solo permite 1, 2, 3, 4 o 5
            if (entrada.empty()) { // Solo permitir una sola cifra
                entrada += tecla;
                std::cout << tecla; // Muestra la opción seleccionada
            }
        } 
        else if (tecla == 8 && !entrada.empty()) { // Tecla de borrar (Backspace)
            entrada.pop_back();
            std::cout << "\b \b"; // Borra el carácter de la consola
        } 
        else if ((tecla == '\r' || tecla == '\n') && !entrada.empty()) { // Si presiona Enter y hay algo escrito
            std::cout << std::endl; // Salto de línea para confirmar
            return entrada[0] - '0'; // Convertimos el carácter a número y lo retornamos
        }
    }
}

#include "Validaciones.h"
#include <iostream>
#include <conio.h> // Para _getch()

std::string Validaciones::validarNumeroConSalida(const std::string& mensaje) {
    char tecla;
    std::string entrada = ""; // Almacena la entrada del usuario
    const int MAX_DIGITOS = 9; // Límite de 10 dígitos
    std::cout << mensaje;

    while (true) {
        tecla = _getch(); // Captura una sola tecla

        if (tecla >= '0' && tecla <= '9') { // Solo permite números
            if (entrada.length() < MAX_DIGITOS) { // Solo permite hasta 10 caracteres
                entrada += tecla;
                std::cout << tecla; // Muestra el número ingresado
            }
        } 
        else if ((tecla == 'n' || tecla == 'N') && entrada.empty()) { // Permite "n" o "N" solo si está vacío
            std::cout << tecla << std::endl; // Muestra la tecla y salta de línea
            return "n"; // Retorna "n" para finalizar
        }
        else if (tecla == 8 && !entrada.empty()) { // Permite borrar (Backspace)
            entrada.pop_back();
            std::cout << "\b \b"; // Borra el último carácter en pantalla
        } 
        else if ((tecla == '\r' || tecla == '\n') && !entrada.empty()) { // Enter para confirmar
            std::cout << std::endl; // Salto de línea para confirmar
            return entrada; // Retorna la entrada como string
        }
    }
}
