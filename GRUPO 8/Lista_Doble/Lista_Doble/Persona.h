/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Persona.h
#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>

class Persona {
private:
    std::string cedula;
    std::string nombre;
    std::string apellido;

public:
    Persona(); // Constructor por defecto

    Persona(const std::string& cedula, const std::string& nombre, const std::string& apellido);
    
    void set_cedula(const std::string& cedula);
    std::string get_cedula() const;

    void set_nombre(const std::string& nombre);
    std::string get_nombre() const;

    void set_apellido(const std::string& apellido);
    std::string get_apellido() const;

    friend std::ostream& operator<<(std::ostream& os, const Persona& persona);
};

#endif // PERSONA_H

