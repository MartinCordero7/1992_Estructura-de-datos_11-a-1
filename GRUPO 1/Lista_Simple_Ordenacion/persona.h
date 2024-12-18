/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO: Altamirano Xavier, Cordero Martin, Oña Isaac
 * FECHA CREACION: Lunes, 16 de diciembre de 2024
 * FECHA MODIFICACION: Lunes, 16 de diciembre de 2024
 * Enunciado del problema: Mediante el metodo de ordenacion externa RadixSort implementarlo en una lista simple
 * Nivel: TERCERO     NRC: 1992
 *************************/
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
