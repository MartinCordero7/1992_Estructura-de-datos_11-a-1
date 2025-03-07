#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <string>
#include "Persona.h"

class Empleado : public Persona {
public:
    Empleado();
    Empleado(std::string cedula, std::string nombre, std::string apellido, Fecha fechaNacimiento, std::string cargo, std::string salario);

    std::string getCargo();
    void setCargo(std::string newCargo);
    std::string getSalario();
    void setSalario(std::string newSalario);

    ~Empleado();

private:
    std::string cargo;
    std::string salario;
};

#endif
