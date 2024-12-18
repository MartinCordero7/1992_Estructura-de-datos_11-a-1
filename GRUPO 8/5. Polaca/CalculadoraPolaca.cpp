/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Díaz Caizaluisa Cámeron Victoria y Bryan Rosero
 * FECHA CREACION: 4 de diciembre de 2024
 * FECHA MODIFICACION: 4 de diciembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
#include "CalculadoraPolaca.h"
#include <stack>
#include <algorithm>
#include <cctype>

using namespace std;

bool Calculadora::esOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int Calculadora::obtenerPrecedencia(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0; // Si no es un operador válido
}

bool Calculadora::esExpresionValida(const string &expresion) {
    if (expresion.empty()) {
        return false; // No se permite cadena vacía
    }

    int contadorOperandos = 0;
    int contadorOperadores = 0;

    for (size_t i = 0; i < expresion.size(); ++i) {
        char c = expresion[i];

        if (isdigit(c)) {
            contadorOperandos++;
            while (i + 1 < expresion.size() && isdigit(expresion[i + 1])) {
                i++; // Avanzar para números de varios dígitos
            }
        } else if (esOperador(c)) {
            contadorOperadores++;
            if (i + 1 < expresion.size() && esOperador(expresion[i + 1])) {
                return false; // Operadores consecutivos no válidos
            }
        } else if (c != '(' && c != ')') {
            return false; // Caracter no permitido
        }
    }

    return contadorOperandos >= 2 && contadorOperadores >= 1;
}

string Calculadora::infijaAPosfija(const string &infijo) {
    stack<char> operadores;
    string posfija;

    for (char c : infijo) {
        if (isdigit(c)) {
            posfija += c;
        } else if (c == '(') {
            operadores.push(c);
        } else if (c == ')') {
            while (!operadores.empty() && operadores.top() != '(') {
                posfija += operadores.top();
                operadores.pop();
            }
            operadores.pop();
        } else if (esOperador(c)) {
            while (!operadores.empty() && obtenerPrecedencia(operadores.top()) >= obtenerPrecedencia(c)) {
                posfija += operadores.top();
                operadores.pop();
            }
            operadores.push(c);
        }
    }

    while (!operadores.empty()) {
        posfija += operadores.top();
        operadores.pop();
    }

    return posfija;
}

string Calculadora::infijaAPrefija(const string &infijo) {
    string invertida = infijo;
    reverse(invertida.begin(), invertida.end());

    for (char &c : invertida) {
        if (c == '(') {
            c = ')';
        } else if (c == ')') {
            c = '(';
        }
    }

    string prefija = infijaAPosfija(invertida);
    reverse(prefija.begin(), prefija.end());

    return prefija;
}
