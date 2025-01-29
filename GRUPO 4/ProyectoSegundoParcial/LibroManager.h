/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Realizar una Lista circular doble          *
 * Autor:                          Steven Egas, Esteban Santos,Pablo Dominguez       *
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
#include "RadixTree.cpp"

using namespace std;

class LibroManager {
private:
    RadixTree radix;
    string archivoLibros = "libros.txt";  // Archivo donde se guardarán los libros
    bool evitarGuardar = false;           // Bandera para controlar el guardado
    vector<Libro> libros;
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
    vector<string> buscarLibroConAutocompletado(const string& prefijo);
    vector<string> buscarLibroConErroresTipograficos(const string& prefijo);
    void imprimirTitulosLibros() const; // Declaración del método imprimirTitulosLibros
    void listarLibrosPorLetra(const char letra); // Declaración del método listarLibrosPorLetra
    void buscarLibroCortoLargo(); // Declaración del método buscarLibroCortoLargo
    void buscarLibroPorSubcadena(const string& subcadena); // Declaración del método buscarLibroPorSubcadena
    void buscarLibroPorIsbnConAutocompletado(const string& prefijo); // Declaración del método buscarLibroPorIsbnConAutocompletado
    void buscarLibroCercano(const string& ruta, const int anioInicio, const int anioFin); // Declaración del método buscarLibroPorRango
    void busquedaPorAutocompletado(); // Declaración del método busquedaPorAutocompletado
    Libro* buscarLibroPorAutor(const std::string& autor);
    void busquedaCompleta(); // Declaración del método busquedaPorAutocompletado
    void generarGraficoRadixTree(const string& outputFile); // Declaración del método generarGraficoRadixTree
    void imprimirEnOrden(); // Declaración del método imprimirEnOrden
    void imprimirEnPreOrden(); // Declaración del método imprimirEnPreOrden
    void imprimirEnPosOrden(); // Declaración del método imprimirEnPosOrden
    void busquedaCompleta1();
    void busquedaPorAutocompletado1();
    void ordenarLibros(); // Declaración del método ordenarLibros
};

#endif