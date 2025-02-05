#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
#include <regex>
#include <iostream>
#include <cctype>

using namespace std;

class Validaciones {
public:
    static bool validarTituloNombre(const string& texto, const string& campo);  // Validación de nombres o títulos
    static bool validarSoloNumeros(const string& texto);  // Validación para permitir solo números
    static string leerSoloNumeros();
    static string leerSoloNumerosON();
    static string leerSoloNumerosONLimitado(int limite); // 
    static string leerSoloNumerosLimitado(int limite);
    static void mostrarMensajeError(const string& mensaje);
};

#endif // VALIDACIONES_H
