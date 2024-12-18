/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//ValidarPersona.h

#ifndef VALIDARPERSONA_H
#define VALIDARPERSONA_H
#include <string>
#include "Persona.cpp"


class ValidarPersona {
public:
    static void ingresar_cedula(const char* mensaje, Persona& persona);

    static void ingresar_nombre(const char* mensaje, Persona& persona);

    static void ingresar_apellido(const char* mensaje, Persona& persona);

    static std::string ingresar_cedula_sin_persona();

    static std::string ingresar_nombre_sin_persona();

    static std::string ingresar_apellido_sin_persona();

    static int ingresar_entero(char numero);

    static int ingresar_desplazamiento(int maximo);

    static char leerLetra();

};

#endif 