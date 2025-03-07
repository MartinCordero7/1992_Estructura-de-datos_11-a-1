#include "Empleado.h"
#include "Persona.h"

Empleado::Empleado() {
    // Constructor de Empleado (si es necesario)
}

Empleado::Empleado(std::string cedula, std::string nombre, std::string apellido, Fecha fechaNacimiento, std::string cargo, std::string salario)
    : Persona(cedula, nombre, apellido, fechaNacimiento) {
    this->cargo = cargo;
    this->salario = salario;
}

std::string Empleado::getCargo() {
    return cargo;
}

void Empleado::setCargo(std::string newCargo) {
    cargo = newCargo;
}

std::string Empleado::getSalario() {
    return salario;
}

void Empleado::setSalario(std::string newSalario) {
    salario = newSalario;
}

// Destructor de Empleado
Empleado::~Empleado() {
    // Implementación del destructor (si es necesario)
}
