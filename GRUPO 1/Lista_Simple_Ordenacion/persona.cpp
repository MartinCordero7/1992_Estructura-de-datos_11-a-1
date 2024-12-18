/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO: Altamirano Xavier, Cordero Martin, Oña Isaac
 * FECHA CREACION: Lunes, 16 de diciembre de 2024
 * FECHA MODIFICACION: Lunes, 16 de diciembre de 2024
 * Enunciado del problema: Mediante el metodo de ordenacion externa RadixSort implementarlo en una lista simple
 * Nivel: TERCERO     NRC: 1992
 *************************/
#include "persona.h"

Persona::Persona(string cedula, string apellido, string nombre)
    : cedula(cedula), apellido(apellido), nombre(nombre) {}

string Persona::getCedula() const { return cedula; }
string Persona::getApellido() const { return apellido; }
string Persona::getNombre() const { return nombre; }

void Persona::setCedula(string cedula) { this->cedula = cedula; }
void Persona::setApellido(string apellido) { this->apellido = apellido; }
void Persona::setNombre(string nombre) { this->nombre = nombre; }
