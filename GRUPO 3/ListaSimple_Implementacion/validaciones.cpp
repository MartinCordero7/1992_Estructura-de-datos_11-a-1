
#include <algorithm> // Necesario para std::all_of
#include <cctype>    // Necesario para std::isdigit y std::isalpha
#include "validaciones.h"


bool validarCedula(const string& cedula) {
    return cedula.size() == 10 && all_of(cedula.begin(), cedula.end(), ::isdigit);
}

bool validarTexto(const string& texto) {
    return !texto.empty() && all_of(texto.begin(), texto.end(), [](char c) {
        return isalpha(c) || c == ' ';
    });
}
