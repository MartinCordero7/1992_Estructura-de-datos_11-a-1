/*******************************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                                  *
 * Proposito:                      Lista doble                                                         *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz                    *
 * Fecha de creacion:              17/12/2024                                                          *
 * Fecha de modificacion:          18/12/2024                                                          *
 * Materia:                        Estructura de datos                                                 *
 * NRC :                           1992                                                                *
 *******************************************************************************************************/

#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include <iostream>
#include <string>
#include <sstream>
#include "Nodo.h"
#include "Persona.cpp"

using namespace std;

// Clase para la lista doblemente enlazada
class ListaDoble {
private:
    Nodo* cabeza = nullptr;
    Nodo* cola = nullptr;  // Puntero al último nodo de la lista
    string archivoPersonas = "personas.txt";  // Archivo donde se guardarán las personas
    bool evitarGuardar = false;               // Bandera para controlar el guardado
public:
    // Agregar persona
    void agregarPersona(const Persona& persona);
    // Imprimir todas las personas
    void imprimirPersonas();
    // Buscar persona por nombre
    Nodo* buscarPersona(const string& nombre);
    // Buscar persona por cédula
    Nodo* buscarPersonaPorCedula(const string& cedula);
    // Eliminar persona por nombre
    void eliminarPersona(const string& nombre);
    // Eliminar persona por cédula
    void eliminarPersonaPorCedula(const string& cedula);
    // Crear backup
    void crearBackup(const string& nombreArchivo);
    // Restaurar backup
    void restaurarBackup(const string& nombreArchivo);
    // Guardar todas las personas en el archivo
    void guardarPersonasEnArchivo();
    // Cargar las personas desde el archivo
    void cargarPersonasDesdeArchivo();
    // Limpiar la lista
    void limpiarLista();
    // Ordenar la lista por cédula usando merge sort externo
    void ordenarPorCedula();
};

#endif // LISTADOBLE_H