/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Díaz Caizaluisa Cámeron Victoria y Bryan Rosero
 * FECHA CREACION: 4 de diciembre de 2024
 * FECHA MODIFICACION: 4 de diciembre de 2024
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
