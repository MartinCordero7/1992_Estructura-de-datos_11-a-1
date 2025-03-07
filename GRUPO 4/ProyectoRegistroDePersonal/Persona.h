#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include "Fecha.h"

class Persona {
public:
    Persona();
    Persona(std::string cedula, std::string nombre, std::string apellido, Fecha fechaNacimiento);

    std::string getCedula();
    void setCedula(std::string newCedula);
    std::string getNombre();
    void setNombre(std::string newNombre);
    std::string getApellido();
    void setApellido(std::string newApellido);
    Fecha getFecha();
    void setFecha(Fecha newFecha);

    ~Persona();
    const Fecha& getFechaNacimiento() const {
        return fechaNacimiento;
    }

private:
   std::string cedula;
   std::string nombre;
   std::string apellido;
   Fecha fechaNacimiento;
};

#endif
