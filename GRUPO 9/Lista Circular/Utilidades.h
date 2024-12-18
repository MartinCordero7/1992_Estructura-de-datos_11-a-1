/***********************************************************************
 * Module:  Utilidades.h
 * Author:  Erika Guayanay, Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#pragma once
#include <string>
#include <algorithm>
#include <cctype>

std::string normalizarNombre(const std::string& nombre) {
    if (nombre.empty()) return "";

    std::string normalizado = nombre;
    std::transform(normalizado.begin(), normalizado.end(), normalizado.begin(), ::tolower);
    normalizado[0] = std::toupper(normalizado[0]);

    return normalizado;
}
