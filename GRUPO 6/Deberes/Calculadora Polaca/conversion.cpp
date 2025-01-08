/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Conversion de infija a prefija o posfija            *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              17/12/2024                                          *
 * Fecha de modificacion:          18/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/

#include "conversion.h"
#include "pila.h"
#include <iostream>
#include <stack>
#include <cctype>
#include <string>
#include <algorithm>

using namespace std;

// Precedencia de los operadores
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Función para aplicar el operador
float applyOperator(char op, float a, float b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

// Convertir de infija a prefija
string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());
    stack<char> operators;
    string prefix;

    for (char& c : infix) {
        if (isdigit(c)) {
            prefix += c;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                prefix += operators.top();
                operators.pop();
            }
            operators.push(c);
        } else if (c == ')') {
            operators.push(c);
        } else if (c == '(') {
            while (!operators.empty() && operators.top() != ')') {
                prefix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
    }

    while (!operators.empty()) {
        prefix += operators.top();
        operators.pop();
    }

    reverse(prefix.begin(), prefix.end());
    return prefix;
}

// Convertir de infija a posfija
string infixToPostfix(string infix) {
    stack<char> operators;
    string postfix;

    for (char& c : infix) {
        if (isdigit(c)) {
            postfix += c;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}


// Evaluar una expresión en notación infija
float evaluateInfix(string infix) {
    stack<float> values;    // Pila de valores
    stack<char> ops;        // Pila de operadores

    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];

        // Si el carácter es un número
        if (isdigit(c)) {
            values.push(c - '0'); // Convertir a número y apilar
        } 
        // Si el carácter es un operador
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
                // Evaluar la operación en la cima de la pila
                float b = values.top(); values.pop();
                float a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperator(op, a, b));
            }
            ops.push(c);
        }
    }
 // Evaluar las operaciones restantes
    while (!ops.empty()) {
        float b = values.top(); values.pop();
        float a = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOperator(op, a, b));
    }

    return values.top();
}

// Evaluar una expresión en notación prefija
float evaluatePrefix(string prefix) {
    stack<string> operands;  // Pila para formar la notación infija

    // Recorrer la expresión prefija de derecha a izquierda
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];

        if (isdigit(c)) {
            operands.push(string(1, c)); // Insertar como cadena
        } else {
            // Tomar los dos operandos más recientes
            string a = operands.top(); operands.pop();
            string b = operands.top(); operands.pop();

            // Formar la notación infija para el operador actual
            string infixExpr = "(" + a + c + b + ")";
            operands.push(infixExpr);
        }
    }

    // La pila ahora contiene la expresión infija completa
    string infix = operands.top();
    operands.pop();

    // Evaluar la expresión infija
    return evaluateInfix(infix);
}

