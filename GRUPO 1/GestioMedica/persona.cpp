#include "persona.h"
#include <iostream>

string Persona::getNombre() const { return nombre; }

Fecha Persona::getFechaNacimiento() const { return fechaNacimiento; }

string Persona::getCedula() const { return cedula; }
Fecha Persona::getCita() const { return cita; }

void Persona::setNombre(const string& n) { nombre = n; }

void Persona::setFechaNacimiento(const Fecha& fn) { fechaNacimiento = fn; }

void Persona::setCedula(const string& c) { cedula = c; }
void Persona::setCita(const Fecha& ci) { cita = ci; }

void Persona::mostrar() const {
    cout << "Nombre: " << nombre << endl
         << "Fecha de nacimiento: " << fechaNacimiento.mostrar() << endl;
}
