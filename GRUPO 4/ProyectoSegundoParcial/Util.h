/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Validaciones de entrada de datos           *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <regex>
#include <iostream>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

class Util {
public:
    static bool validarNumerosPermitidos(const string& input, const vector<int>& numerosPermitidos);
    static int validarNumero(int min, int max);
    static bool validarNumeroEnRango(const string& input, int min, int max);

private:

};

#endif // UTIL_H
