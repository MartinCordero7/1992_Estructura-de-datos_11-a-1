#ifndef LIBROMANAGER_H
#define LIBROMANAGER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Nodo.h"
#include "Libro.h"
#include "Persona.cpp"
#include "SplayTree.h" // Incluimos SplayTree sin usar plantillas

using namespace std;

class LibroManager
{
private:
    SplayTree splayTree;                 // Declaración directa de SplayTree
    string archivoLibros = "libros.txt"; // Archivo donde se guardarán los libros
    bool evitarGuardar = false;          // Bandera para controlar el guardado
public:
    // Agregar libro
    void agregarLibro(const Libro &libro);
    // Imprimir todos los libros
    void imprimirLibros();
    // Buscar libro por título
    Libro *buscarLibro(const string &titulo);
    // Buscar libro por ISBN
    Libro *buscarLibroPorIsbn(const string &isbn);
    // Buscar autor por ISNI
    Persona buscarAutorPorIsni(const string &isni);
    // Eliminar libro
    void eliminarLibro(const string &titulo);
    // Crear backup
    void crearBackup(const string &nombreArchivo);
    // Restaurar backup
    void restaurarBackup(const string &nombreArchivo);
    // Guardar todos los libros en el archivo
    void guardarLibrosEnArchivo();
    // Cargar los libros desde el archivo
    void cargarLibrosDesdeArchivo();
    // Limpiar la lista
    void limpiarLista();
};

#endif
