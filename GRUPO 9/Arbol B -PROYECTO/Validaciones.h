/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Validaciones de entrada de datos           *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          01/01/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
#include <regex>
#include <iostream>
#include <cctype>
#include "Fecha.h"

using namespace std;

class Validaciones {
public:
    static bool validarFechaPublicacion(const string& fechaPub, const string& fechaNacAutor);
    static bool validarTituloNombre(const string& texto, const string& campo);
    static bool validarTitulo(const string& texto, const string& campo);
    static bool validarFecha(const string& fecha);
    static bool validarIsbn(const string& isbn);
    static bool validarIsni(const string& isni);
    static bool validarTextoNoVacio(const string& texto, const string& campo);
    static bool validarTexto(const string& texto, const string& campo);
    static bool validarIsbn10(const string& isbn);
    static bool validarIsbn13(const string& isbn);
    static int calcularDigitoControlIsbn10(const string& isbn);
    static int calcularDigitoControlIsbn13(const string& isbn);
    static int ingresarAnio(const string& mensaje); // Declaration for ingresarAnio
    static string leerSoloNumeros(); // Declaration for leerSoloNumeros
    static string leerIsbnIsni(); // Declaration for leerIsbnIsni
    static bool contieneLetra(const std::string& titulo); // Declaration for contieneLetra
    static std::string leerSoloCaracteres(); // Declaración de la nueva función
private:
    static int diasEnMes(int mes, int anio);
    static bool esBisiesto(int anio);
};

#endif // VALIDACIONES_H
