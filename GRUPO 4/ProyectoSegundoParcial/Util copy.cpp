/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Util de entrada de datos                                 *
 * Autor:                          Steven Egas, Esteban Santos,Pablo Dominguez       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "Util.h"

// Validación de números permitidos
bool Util::validarNumerosPermitidos(const string& input, const vector<int>& numerosPermitidos) {
    if (input.empty() || input.find_first_not_of(' ') == string::npos) {
        return false; // No permitir entradas vacías o solo con espacios
    }

    // Verificar que la entrada no contenga letras ni espacios
    if (!all_of(input.begin(), input.end(), ::isdigit)) {
        return false;
    }

    // Convertir la entrada a un número entero
    int numero;
    try {
        numero = stoi(input);
    } catch (const invalid_argument&) {
        return false; // No permitir si la conversión falla
    }

    // Verificar si el número está en la lista de números permitidos
    if (find(numerosPermitidos.begin(), numerosPermitidos.end(), numero) == numerosPermitidos.end()) {
        return false;
    }

    return true;
}

int Util::validarNumero(int min, int max) {
    string input;
    int numero;
    while (true) {
        getline(cin, input);

        // Eliminar espacios al inicio y al final de la entrada
        input.erase(0, input.find_first_not_of(' '));
        input.erase(input.find_last_not_of(' ') + 1);

        // Validar si la entrada está vacía o contiene espacios
        if (input.empty() || input.find(' ') != string::npos) {
            cout << "\033[A\33[2K\rEntrada inválida. Intente nuevamente: ";
            continue;
        }

        // Validar que la entrada sea numérica
        if (!all_of(input.begin(), input.end(), ::isdigit)) {
            cout << "\033[A\33[2K\rEntrada inválida. Intente nuevamente: ";
            continue;
        }

        // Convertir la entrada a un número entero
        try {
            numero = stoi(input);
            if (numero >= min && numero <= max) {
                break;  // Salir del bucle si el número está dentro del rango permitido
            } else {
                cout << "\033[A\33[2K\rNúmero fuera de rango. Intente nuevamente: ";
            }
        } catch (const invalid_argument&) {
            cout << "\033[A\33[2K\rEntrada inválida. Intente nuevamente: ";
        }
    }
    return numero;
}

