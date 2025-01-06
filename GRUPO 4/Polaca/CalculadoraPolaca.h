/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Dominguez Pablo, Egas Steven, Santos Estaban
 * FECHA CREACION: Domingo,  1 de enero de 2025
 * FECHA MODIFICACION: Domingo,  1 de enero de 2025
 * Asignatura:Estructura de datos
 * Nivel: TERCERO     NRC: 1992
 *************************/

#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <string>

class Calculadora {
public:
    static bool esOperador(char c);
    static int obtenerPrecedencia(char op);
    static std::string infijaAPosfija(const std::string &infijo);
    static std::string infijaAPrefija(const std::string &infijo);
    static bool esExpresionValida(const std::string &expresion);
};

#endif // CALCULADORA_H
