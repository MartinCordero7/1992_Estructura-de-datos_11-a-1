#include "persona.h"

// Constructor
Persona::Persona(string cedula, string apellido, string nombre) 
    : cedula(cedula), apellido(apellido), nombre(nombre) {}

// Getters
string Persona::getCedula() const { return cedula; }
string Persona::getApellido() const { return apellido; }
string Persona::getNombre() const { return nombre; }

// Setters
void Persona::setCedula(string cedula) { this->cedula = cedula; }
void Persona::setApellido(string apellido) { this->apellido = apellido; }
void Persona::setNombre(string nombre) { this->nombre = nombre; }
