/*******************************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                                  *
 * Proposito:                      Utilidades para ordenamiento lista circular                         *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz                    *
 * Fecha de creacion:              17/12/2024                                                          *
 * Fecha de modificacion:          18/12/2024                                                          *
 * Materia:                        Estructura de datos                                                 *
 * NRC :                           1992                                                                *
 *******************************************************************************************************/

#include "Utilidades.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string Utilidades::generarCorreo(const std::string& nombre, const std::string& sNombre, const std::string& apellido) {
    std::string nombreLower = nombre;
    std::string sNombreLower = sNombre;
    std::string apellidoLower = apellido;

    // Convertir todo a minúsculas
    for (int i = 0; i < nombreLower.length(); i++) {
        nombreLower[i] = tolower(nombreLower[i]);
    }
    for (int i = 0; i < sNombreLower.length(); i++) {
        sNombreLower[i] = tolower(sNombreLower[i]);
    }
    for (int i = 0; i < apellidoLower.length(); i++) {
        apellidoLower[i] = tolower(apellidoLower[i]);
    }

    // Generar correo base
    std::string correoBase = std::string(1, nombreLower[0]) + std::string(1, sNombreLower[0]) + apellidoLower + "@espe.edu.ec";
    std::string correoGenerado = correoBase;

    // Leer el archivo y verificar duplicados
    std::ifstream archivo("personas.txt"); // Archivo de texto donde están los correos
    std::string linea;
    int contador = 0;

    while (archivo.is_open() && std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string dato;
        int columna = 0;
        std::string correoExistente;

        // Dividir la línea por ';' y extraer el correo (5ta posición)
        while (std::getline(ss, dato, ';')) {
            columna++;
            if (columna == 5) {
                correoExistente = dato;
                break;
            }
        }

        // Verificar si el correo ya existe
        if (correoExistente == correoGenerado) {
            contador++;
            correoGenerado = correoBase; // Reiniciar correo base
            correoGenerado.insert(correoGenerado.find('@'), std::to_string(contador));
        }
    }

    archivo.close(); // Cerrar el archivo
    return correoGenerado;
}