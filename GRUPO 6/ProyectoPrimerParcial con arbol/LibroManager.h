/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Realizar una Lista circular doble          *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef LIBROMANAGER_H
#define LIBROMANAGER_H

#include <iostream>
#include <string>
#include <sstream>
#include "Nodo.h"
#include "Libro.h"
#include "Persona.cpp"
#include "Trie.cpp"

using namespace std;

class LibroManager {
private:
    Trie trie;
    string archivoLibros = "libros.txt";  // Archivo donde se guardarán los libros
    bool evitarGuardar = false;           // Bandera para controlar el guardado
    list<Libro> libros;
public:
    // Agregar libro
    void agregarLibro(const Libro& libro);
    // Imprimir todos los libros
    void imprimirLibros();
    // Buscar libro por título
    Libro* buscarLibro(const string& titulo);
    // Buscar libro por título
    Libro* buscarLibroPorTitulo(const string& titulo);
    // Buscar libro por ISBN
    Libro* buscarLibroPorIsbn(const string& isbn);
    // Buscar autor por ISNI
    Persona buscarAutorPorIsni(const string& isni);
    // Eliminar libro
    void eliminarLibro(const string& titulo);
    // Crear backup
    void crearBackup(const string& nombreArchivo);
    // Restaurar backup
    void restaurarBackup(const string& nombreArchivo);
    // Guardar todos los libros en el archivo
    void guardarLibrosEnArchivo();
    // Cargar los libros desde el archivo
    void cargarLibrosDesdeArchivo();
    // Limpiar la lista
    void limpiarLista();
    // Buscar libro con autocompletado
    list<string> buscarLibroConAutocompletado(const string& prefijo);
    list<string> buscarLibroConErroresTipograficos(const string& prefijo);
    void imprimirTitulosLibros() const; // Declaración del método imprimirTitulosLibros
    void listarLibrosPorLetra(const char letra); // Declaración del método listarLibrosPorLetra
    void buscarLibroCortoLargo(); // Declaración del método buscarLibroCortoLargo
    void buscarLibroPorSubcadena(const string& subcadena); // Declaración del método buscarLibroPorSubcadena
    void buscarLibroPorIsbnConAutocompletado(const string& prefijo); // Declaración del método buscarLibroPorIsbnConAutocompletado
    void buscarLibroCercano(const string& ruta, const int anioInicio, const int anioFin); // Declaración del método buscarLibroPorRango


};

#endif