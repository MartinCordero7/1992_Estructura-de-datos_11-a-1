/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Gestionar Libros                                         *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "Libro.h"
#include <iostream>
#include "Fecha.h"

Libro::Libro(const std::string& titulo, const std::string& isbn, const Persona& autor, const Fecha& fechaPublicacion)
    : titulo(titulo), isbn(isbn), autor(autor), fechaPublicacion(fechaPublicacion) {
    // Implementación pendiente
}

std::string Libro::getIsbn() const {
    return isbn;
}

void Libro::mostrar() const {
    cout << left << setw(41) << "Título" 
         << setw(25) << "Autor" 
         << setw(25) << "ISNI" 
         << setw(20) << "ISBN"
         << setw(15) << "Publicación" 
         << setw(15) << "Nac. Autor" << endl;
    cout << string(140, '-') << endl;
    cout << left << setw(40) << titulo
         << setw(25) << autor.getNombre()
         << setw(25) << autor.getIsni() 
         << setw(20) << isbn
         << setw(15) << fechaPublicacion.mostrar()
         << setw(15) << autor.getFechaNacimiento().mostrar() << endl;
}

string Libro::getTitulo() const { return titulo; }
Persona Libro::getAutor() const { return autor; }
Fecha Libro::getFechaPublicacion() const { return fechaPublicacion; }

void Libro::setTitulo(const string& t) { titulo = t; }
void Libro::setIsbn(const string& i) { isbn = i; }
void Libro::setAutor(const Persona& a) { autor = a; }
void Libro::setFechaPublicacion(const Fecha& fp) { fechaPublicacion = fp; }

std::string Fecha::toString() const {
    // Implement the method to return a string representation of the date
    // Ensure that day, month, and year are member variables of Fecha
    std::ostringstream oss;
    oss << day << "/" << month << "/" << year;
    return oss.str();
}
