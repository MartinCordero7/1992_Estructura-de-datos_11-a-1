/***********************************************************************
 * Module:  Validaciones.h
 * Author:  Erika Guayanay, Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#pragma once
#include <string>
#include <regex>
#include <iostream>


bool validarCedula(const std::string& cedula);   // Valida que la cédula tenga 10 dígitos.
bool validarSoloLetras(const std::string& texto); // Valida que un texto solo contenga letras.
long int ingresarCedulaNumerica();              // Permite ingresar una cédula como número.
bool validarCedulaReal(long int cedula);        // Valida si una cédula es real (según cálculo).
void imprimirResultadoCedula(bool valido);      // Imprime el resultado de la validación.
bool validarNombre(const std::string& nombre);
