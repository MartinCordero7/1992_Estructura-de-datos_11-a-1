/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Conversion de infija a prefija o posfija            *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              17/12/2024                                          *
 * Fecha de modificacion:          18/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/

#ifndef CONVERSION_H
#define CONVERSION_H

#include <string>

// Declaraciones de funciones
int precedence(char op);
float applyOperator(char op, float a, float b);
std::string infixToPrefix(std::string infix);
std::string infixToPostfix(std::string infix);
float evaluatePrefix(std::string prefix);

#endif // CONVERSION_H
