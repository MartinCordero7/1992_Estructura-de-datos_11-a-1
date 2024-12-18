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
