/*******************************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                                  *
 * Proposito:                      Validacion para ordenamiento lista circular                         *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz                    *
 * Fecha de creacion:              17/12/2024                                                          *
 * Fecha de modificacion:          18/12/2024                                                          *
 * Materia:                        Estructura de datos                                                 *
 * NRC :                           1992                                                                *
 *******************************************************************************************************/

#include "Validaciones.h"
#include <regex>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Validación de fecha
bool Validaciones::validarFecha(const string& fecha) {
    regex formatoFecha(R"(\d{2}-\d{2}-\d{4})");
    if (!regex_match(fecha, formatoFecha)) {
        cout << "Error: El formato de la fecha debe ser DD-MM-YYYY.\n";
        return false;
    }

    int dia, mes, anio;
    sscanf(fecha.c_str(), "%d-%d-%d", &dia, &mes, &anio);

    if (anio <= 0 || mes < 1 || mes > 12 || dia < 1 || dia > diasEnMes(mes, anio)) {
        cout << "Error: Fecha no válida.\n";
        return false;
    }

    // Obtener la fecha actual
    time_t t = time(nullptr);
    tm* fechaActual = localtime(&t);

    int diaActual = fechaActual->tm_mday;
    int mesActual = fechaActual->tm_mon + 1;
    int anioActual = fechaActual->tm_year + 1900;

    // Verificar que la fecha ingresada no sea mayor a la actual
    if (anio > anioActual || (anio == anioActual && mes > mesActual) || (anio == anioActual && mes == mesActual && dia > diaActual)) {
        cout << "Error: La fecha no puede ser mayor a la fecha actual.\n";
        return false;
    }
    
    return true;
}

// Validación de cédula ecuatoriana
bool Validaciones::validarCedula(const string& cedula) {
    if (cedula.length() != 10) {
        cout << "Error: La cédula debe tener 10 dígitos.\n";
        return false;
    }

    int provincia = stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24) {
        cout << "Error: Los dos primeros dígitos deben corresponder a una provincia válida.\n";
        return false;
    }

    int tercerDigito = cedula[2] - '0';
    if (tercerDigito >= 6) {
        cout << "Error: El tercer dígito debe ser menor a 6.\n";
        return false;
    }

    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) {
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        suma += digito;
    }

    int digitoVerificador = (10 - (suma % 10)) % 10;
    if (digitoVerificador != (cedula[9] - '0')) {
        cout << "Error: La cédula no es válida.\n";
        return false;
    }

    return true;
}

// Validación de texto no vacío
bool Validaciones::validarTextoNoVacio(const string& texto, const string& campo) {
    if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
        cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
        return false;
    }
    return true;
}

// Validación de texto
bool Validaciones::validarTexto(const string& texto, const string& campo) {
    regex formatoTexto(R"([a-zA-ZñÑáéíóúÁÉÍÓÚ\s]+)");
    if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
        cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
        return false;
    } else if (!regex_match(texto, formatoTexto)) {
        cout << "Error: El campo " << campo << " solo debe contener letras, espacios y caracteres válidos en español.\n";
        return false;
    }
    return true;
}

// Validación de título y nombre
bool Validaciones::validarTituloNombre(const string& texto, const string& campo) {
    regex formatoTituloNombre(R"([A-ZÁÉÍÓÚÑ][a-záéíóúñ]+)");
    if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
        cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
        return false;
    } else if (!regex_match(texto, formatoTituloNombre)) {
        cout << "Error: El campo " << campo << " debe comenzar con una letra mayúscula y no contener espacios.\n";
        return false;
    }
    return true;
}

// Función auxiliar: días en un mes
int Validaciones::diasEnMes(int mes, int anio) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return (esBisiesto(anio)) ? 29 : 28;
        default: return 0;
    }
}

// Función auxiliar: año bisiesto
bool Validaciones::esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}