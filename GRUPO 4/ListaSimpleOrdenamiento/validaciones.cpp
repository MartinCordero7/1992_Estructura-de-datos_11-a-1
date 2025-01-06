/***********************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                  *
 * Proposito:                      Lista Simple                        *
 * Autor:                          Esteban Santos                      *
 * Fecha de creacion:              20/11/2024                          *
 * Fecha de modificacion:          10/12/2024                          *
 * Materia:                        Estructura de datos                 *
 * NRC :                           1992                                *
 ***********************************************************************/
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
