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
