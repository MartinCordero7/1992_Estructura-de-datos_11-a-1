/***********************************************************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * Module:  main.cpp
 * Grupo 5: Ayuquina, Villagómez, Cañarte
 * Date: 01/12/2024
 * Purpose: Codigo Polaca
 ***********************************************************************/

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
