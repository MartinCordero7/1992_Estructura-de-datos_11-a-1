#ifndef LIBRO_H
#define LIBRO_H

#include <iostream>
#include "Autor.h"
#include "Fecha.h"

using namespace std;

class Libro {
private:
    int id;
    string nombre;
    Autor autor;
    string editorial;
    string genero;
    string serie;
    double rating;
    Fecha fechaPublicacion;

public:
    Libro() : id(0) {}
    Libro(int id, string nombre, Autor autor, string editorial,string genero,string serie, double rating, Fecha fechaPublicacion)
        : id(id), nombre(nombre), autor(autor), editorial(editorial),genero(genero),serie(serie),rating(rating), fechaPublicacion(fechaPublicacion) {}

 Libro(int id, string nombre, Autor autor, Fecha fechaPublicacion)
        : id(id), nombre(nombre), autor(autor),  fechaPublicacion(fechaPublicacion) {}


    int getId() const { return id; }

    void imprimirLibro() const {
        cout << "ID: " << id << ", Titulo: " << nombre << ", ";
        autor.imprimirAutorB();
        cout << ", Editorial: " << editorial <<", Genero: "<<genero<<", Serie: "<<serie<<", Rating: "<<rating <<", Fecha de publicacion: ";
        fechaPublicacion.imprimirFecha();
    }

    bool operator==(const Libro& otro) const {
        return id == otro.id;
    }

    void setId(int id_) { id = id_; }

    string getNombre() const { return nombre; }
    void setNombre(const string &nombre_) { nombre = nombre_; }

    Autor getAutor() const { return autor; }
    void setAutor(const Autor &autor_) { autor = autor_; }

    string getEditorial() const { return editorial; }
    void setEditorial(const string &editorial_) { editorial = editorial_; }

    Fecha getFechaPublicacion() const { return fechaPublicacion; }
    void setFechaPublicacion(const Fecha &fechaPublicacion_) { fechaPublicacion = fechaPublicacion_; }

    string getGenero() const { return genero; }
    void setGenero(const string &genero_) { genero = genero_; }

    string getSerie() const { return serie; }
    void setSerie(const string &serie_) { serie = serie_; }

    double getRating() const { return rating; }
    void setRating(double rating_) { rating = rating_; }
};

#endif // LIBRO_H