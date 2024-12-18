/*******************************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                                  *
 * Proposito:                      Validacion para conversion de infija a prefija o posfija            *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz                    *
 * Fecha de creacion:              17/12/2024                                                          *
 * Fecha de modificacion:          18/12/2024                                                          *
 * Materia:                        Estructura de datos                                                 *
 * NRC :                           1992                                                                *
 *******************************************************************************************************/

#include <iostream>
#include <string>
#include <cctype>
#include "validaciones.h" // Incluir la cabecera

using namespace std;

// Función para validar si una expresión infija es válida
bool isValidExpression(const std::string& expr) {
    int parentheses = 0;            // Contador para balance de parentesis
    bool lastWasOperator = true;    // Controla si el ultimo caracter fue un operador
    bool lastWasOpenParen = false;  // Verifica si el ultimo caracter fue '('
    bool lastWasNegativeSign = false;  // Verifica si el último signo fue un negativo

    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];

        // 1. Verificar que no haya espacios
        if (std::isspace(c)) {
            std::cout << "Error: La expresion no debe contener espacios." << std::endl;
            return false;
        }

        // 2. Verificar caracteres validos
        if (!(std::isdigit(c) || c == '+' || c == '-' || 
              c == '*' || c == '/' || c == '^' || c == '(' || c == ')')) {
            std::cout << "Error: La expresion contiene caracteres invalidos: " << c << std::endl;
            return false;
        }

        // 3. Manejar parentesis
        if (c == '(') {
            parentheses++;
            lastWasOpenParen = true;
            lastWasOperator = true; // Un operador puede venir despues de '('
        } else if (c == ')') {
            if (parentheses == 0) {
                std::cout << "Error: Parentesis desbalanceados." << std::endl;
                return false;
            }
            if (lastWasOperator) {
                std::cout << "Error: Un operador no puede preceder un parentesis de cierre." << std::endl;
                return false;
            }
            parentheses--;
        }

        // 4. Manejar el '-' como signo negativo o como operador
        if (c == '-') {
            if (lastWasOperator || lastWasOpenParen || lastWasNegativeSign) {
                // Se permite como signo negativo
                lastWasOperator = false; 
                lastWasNegativeSign = true; // Es un signo negativo
            } else {
                // Es un operador de resta
                lastWasOperator = true;
                lastWasNegativeSign = true; 
            }
        }
        // 5. Manejar otros operadores
        else if (c == '+' || c == '*' || c == '/' || c == '^') {
            if (lastWasOperator && !lastWasOpenParen) {
                std::cout << "Error: Operador en posicion invalida o dos operadores consecutivos." << std::endl;
                return false;
            }
            if (c == '/' || c== '*' || c== '+' || c== '^' && i + 1 < expr.length() && expr[i + 1] == '-') {
                std::cout << "Error: No se permite un operador seguido de un signo negativo." << std::endl;
                return false;
            }
            lastWasOperator = true;
            lastWasNegativeSign = false;
        } 
        // 6. Manejar operandos (numeros)
        else if (std::isdigit(c)) {
            lastWasOperator = false;
            lastWasNegativeSign = false;
        }

        lastWasOpenParen = false;
    }

    if (parentheses != 0) {
        std::cout << "Error: Parentesis desbalanceados." << std::endl;
        return false;
    }

    return true;
}
