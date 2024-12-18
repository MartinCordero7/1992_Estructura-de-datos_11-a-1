/***********************************************************************
 * Module:  Validaciones.h
 * Author:  Erika Guayanay,Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#pragma once
#include <string>

bool validarCedulaReal(const std::string& cedula);
bool validarCedulaUnica(const std::string& cedula);
void registrarCedula(const std::string& cedula);
void eliminarCedula(const std::string& cedula);
bool validarSoloLetras(const std::string& texto);
bool existeCedula(const std::string& cedula);
int capturarSoloNumeros();
std::string capturarSoloLetras(); // Permite capturar solo letras
std::string normalizarNombre(const std::string& nombre);
std::string capturarCedula();
char capturarUnaLetra();
int validarNumero1a25();
