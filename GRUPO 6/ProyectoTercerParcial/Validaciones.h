/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Validaciones de entrada de datos           *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
#include <regex>
#include <iostream>
#include <cctype>

using namespace std;

class Validaciones {
public:
    static bool validarNombreCliente(const string& nombre);
    static bool validarCedulaEcuatoriana(const string& cedula);
    static bool validarNumeroCelular(const string& celular);
private:
    static bool verificarDigitoVerificadorCedula(const string& cedula);
};

#endif // VALIDACIONES_H
