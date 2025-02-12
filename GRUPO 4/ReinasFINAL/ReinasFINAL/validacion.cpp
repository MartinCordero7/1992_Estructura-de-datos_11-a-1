#include <iostream>
#include <conio.h>
#include <string>
#include <stdexcept>
#include <algorithm>

int getValidInput() {
    int N;
    while (true) {
        char ch = _getch();
        if (ch >= '1' && ch <= '8') {
            N = ch - '0';
            std::cout << ch; // Display the number without a newline
            char enter = _getch();
            if (enter == '\r') { // Check for Enter key
                if (N >= 2 && N <= 3) {
                    std::cout << "\nNo hay solucion con este numero!\nIngrese de nuevo:" << std::endl;
                    continue;
                }
                std::cout << std::endl; // Move to the next line after Enter
                break;
            } else {
                std::cout << "\b \b"; // Erase the character if Enter is not pressed
            }
        }
    }
    return N;
}

int validarNumero(int min, int max) {
    std::string input;
    int numero;
    while (true) {
        std::getline(std::cin, input);

        // Limitar la entrada a un máximo de tres caracteres
        if (input.length() > 3) {
            std::cout << "\033[A\33[2K\rEntrada demasiado larga. Intente nuevamente: ";
            continue;
        }

        // Eliminar espacios al inicio y al final de la entrada
        input.erase(0, input.find_first_not_of(' '));
        input.erase(input.find_last_not_of(' ') + 1);

        // Validar si la entrada está vacía o contiene espacios
        if (input.empty() || input.find(' ') != std::string::npos) {
            std::cout << "\033[A\33[2K\rEntrada inválida. Intente nuevamente: ";
            continue;
        }

        // Validar que la entrada sea numérica
        if (!all_of(input.begin(), input.end(), ::isdigit)) {
            std::cout << "\033[A\33[2K\rEntrada inválida. Intente nuevamente: ";
            continue;
        }

        // Convertir la entrada a un número entero
        try {
            numero = stoi(input);
            if (numero >= min && numero <= max) {
                break;  // Salir del bucle si el número está dentro del rango permitido
            } else {
                std::cout << "\033[A\33[2K\rNúmero fuera de rango. Intente nuevamente: ";
            }
        } catch (const std::invalid_argument&) {
            std::cout << "\033[A\33[2K\rEntrada inválida. Intente nuevamente: ";
        }
    }
    return numero;
}

