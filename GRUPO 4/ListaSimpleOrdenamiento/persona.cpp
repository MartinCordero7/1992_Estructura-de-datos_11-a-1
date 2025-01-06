/***********************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                  *
 * Proposito:                      Lista Simple                        *
 * Autor:                          Esteban Santos                      *
 * Fecha de creacion:              20/11/2024                          *
 * Fecha de modificacion:          10/12/2024                          *
 * Materia:                        Estructura de datos                 *
 * NRC :                           1992                                *
 ***********************************************************************/
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
