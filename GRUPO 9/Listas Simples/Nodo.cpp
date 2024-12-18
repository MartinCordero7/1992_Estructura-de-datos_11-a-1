/***********************************************************************
 * Module:  Nodo.cpp
 * Author:  Erika Guayanay,Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "Nodo.h"

Nodo::Nodo(string cedula, string nombre, string apellido)
    : cedula(cedula), nombre(nombre), apellido(apellido), siguiente(nullptr) {}

string Nodo::getCedula() {
    return cedula;
}

string Nodo::getNombre() {
    return nombre;
}


string Nodo::getApellido() {
    return apellido;
}

void Nodo::setNombre(string nuevoNombre) {
    nombre = nuevoNombre;
}

void Nodo::setApellido(string nuevoApellido) {
    apellido = nuevoApellido;
}

Nodo* Nodo::getSiguiente() {
    return siguiente;
}

void Nodo::setSiguiente(Nodo* nuevoSiguiente) {
    siguiente = nuevoSiguiente;
}
