/***********************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                  *
 * Proposito:                      Lista Simple                        *
 * Autor:                          Esteban Santos                      *
 * Fecha de creacion:              20/11/2024                          *
 * Fecha de modificacion:          10/12/2024                          *
 * Materia:                        Estructura de datos                 *
 * NRC :                           1992                                *
 ***********************************************************************/
#ifndef PERSONA_H
#define PERSONA_H

#include <string>
using namespace std;

class Persona {
private:
    string cedula;
    string apellido;
    string nombre;

public:
    // Constructor
    Persona(string cedula, string apellido, string nombre);

    // Getters
    string getCedula() const;
    string getApellido() const;
    string getNombre() const;

    // Setters
    void setCedula(string cedula);
    void setApellido(string apellido);
    void setNombre(string nombre);
};

#endif
