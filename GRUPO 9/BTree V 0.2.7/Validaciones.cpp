#include "Validaciones.h"
#include <regex>
#include <conio.h> // Para _getch()

bool Validaciones::validarTituloNombre(const string& texto, const string& campo) {
    try {
        regex formatoTituloNombre("^[A-Za-z ]+$");
        if (!regex_match(texto, formatoTituloNombre)) {
            mostrarMensajeError("Error: El campo " + campo + " solo debe contener letras y espacios.");
            return false;
        }
        return true;
    } catch (const std::exception& e) {
        mostrarMensajeError("Exception: " + string(e.what()));
        return false;
    }
}

bool Validaciones::validarSoloNumeros(const string& texto) {
    try {
        return regex_match(texto, regex("^[0-9]+$"));  // Solo permite números del 0 al 9
    } catch (const std::exception& e) {
        mostrarMensajeError("Exception: " + string(e.what()));
        return false;
    }
}

// Función para leer solo números
string Validaciones::leerSoloNumeros() {
    try {
        string input;
        char ch;
        while ((ch = _getch()) != '\r') { // Leer hasta presionar Enter
            if (isdigit(ch)) {
                cout << ch;
                input += ch;
            } else if (ch == '\b' && !input.empty()) { // Permitir backspace
                cout << "\b \b";
                input.pop_back();
            }
        }
        cout << endl;
        return input;
    } catch (const std::exception& e) {
        mostrarMensajeError("Exception: " + string(e.what()));
        return "";
    }
}

// Acepta números y la letra 'n'
string Validaciones::leerSoloNumerosON() {
    try {
        string input;
        char ch;
        while ((ch = _getch()) != '\r') { // Leer hasta presionar Enter
            if (isdigit(ch) || ch == 'n' || ch == 'N') { // Acepta dígitos y la letra 'n' o 'N'
                cout << ch;
                input += ch;
            } else if (ch == '\b' && !input.empty()) { // Permitir backspace
                cout << "\b \b";
                input.pop_back();
            }
        }
        cout << endl;
        return input;
    } catch (const std::exception& e) {
        mostrarMensajeError("Exception: " + string(e.what()));
        return "";
    }
}

// Acepta números, 'n' y limita la longitud de la entrada
string Validaciones::leerSoloNumerosONLimitado(int limite) {
    try {
        string input;
        char ch;
        while ((ch = _getch()) != '\r') { // Leer hasta presionar Enter
            if ((isdigit(ch) && input.size() < limite) || (ch == 'n' || ch == 'N')) { // Limitar a 'limite' dígitos
                cout << ch;
                input += ch;
            } else if (ch == '\b' && !input.empty()) { // Permitir backspace
                cout << "\b \b";
                input.pop_back();
            }
        }
        cout << endl;
        return input;
    } catch (const std::exception& e) {
        mostrarMensajeError("Exception: " + string(e.what()));
        return "";
    }
}

// Función para leer solo números con un límite de longitud
string Validaciones::leerSoloNumerosLimitado(int limite) {
    try {
        string input;
        char ch;
        while ((ch = _getch()) != '\r') { // Leer hasta presionar Enter
            if (isdigit(ch) && input.size() < limite) { // Limitar a 'limite' dígitos
                cout << ch;
                input += ch;
            } else if (ch == '\b' && !input.empty()) { // Permitir backspace
                cout << "\b \b";
                input.pop_back();
            }
        }
        cout << endl;
        return input;
    } catch (const std::exception& e) {
        mostrarMensajeError("Exception: " + string(e.what()));
        return "";
    }
}

void Validaciones::mostrarMensajeError(const string& mensaje) {
    cout << mensaje << endl;
}
