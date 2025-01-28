#ifndef ARBOLBTREE_H
#define ARBOLBTREE_H

#include "NodoBTree.h"
#include "Libro.h"
#include <string>

class ArbolBTree {
private:
    NodoBTree* raiz;
    int t; // Grado mínimo
    std::string archivoLibros = "libros.txt";  // Archivo donde se guardarán los libros
    bool evitarGuardar = false;                // Bandera para controlar el guardado

    void insertarEnNodo(NodoBTree* nodo, const Libro& libro);
    void dividirNodo(NodoBTree* nodo, int i);
    Libro obtenerPredecesor(NodoBTree* nodo, int i);
    Libro obtenerSucesor(NodoBTree* nodo, int i);
    void fusionarNodos(NodoBTree* nodo, int i);
    void balancearNodo(NodoBTree* nodo, int i);

public:
    ArbolBTree(int t);
    void insertar(const Libro& libro);
    void eliminar(const std::string& titulo);
    void imprimirLibros();
    NodoBTree* buscarLibroPorIsbn(const std::string& isbn);
    Persona buscarAutorPorIsni(const std::string& isni);
    void guardarLibrosEnArchivo();
    void cargarLibrosDesdeArchivo();
    void crearBackup(const std::string& nombreArchivo);
    int getT() const; // Getter for t
};

#endif // ARBOLBTREE_H
