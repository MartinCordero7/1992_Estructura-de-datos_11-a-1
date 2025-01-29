/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Archivo principal de proyecto                            *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          01/01/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <vector>

using namespace std;

vector<string> dividir(const string& linea, char delimitador);
void imprimirCabecera();
void buscarPorRango(const string& rutaArchivo, int anioInicio, int anioFin);
void distribuirDatos(const string& archivoEntrada);
void ordenarArchivo(const string& nombreArchivo);
void fusionarArchivos(const string& archivoSalida);
void mostrarArchivo(const string& nombreArchivo);
void eliminarDeCubeta(const string& titulo); // Declaration for eliminarDeCubeta

#endif
