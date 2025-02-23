#include "Validaciones.h"

void Validaciones::validarEntero(int n) {
    if (n <= 0 || n > 14) {
        throw std::invalid_argument("El número debe estar entre 1 y 14.");
    }
}

std::string Validaciones::leerSoloNumerosOX() {
    try {
        std::string input;
        char ch;
        while ((ch = _getch()) != '\r') { // Leer hasta presionar Enter
            // Acepta dígitos del 1 al 14 y la letra 'X' o 'x'
            if ((isdigit(ch) && (input.empty() || (input.size() == 1 && input[0] == '1' && ch <= '4'))) || ch == 'X' || ch == 'x') {
                std::cout << ch;
                input += ch;
            } else if (ch == '\b' && !input.empty()) { // Permitir backspace
                std::cout << "\b \b";
                input.pop_back();
            }
        }
        std::cout << std::endl;
        return input;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return "";
    }
}
