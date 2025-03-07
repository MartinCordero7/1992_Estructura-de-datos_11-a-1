#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include "fecha.h"

using namespace std;

class Persona {
private:
    string nombre;
    Fecha fechaNacimiento;
    string cedula;       // Se usará para almacenar la cédula del doctor o paciente según el contexto
    Fecha cita;          // Fecha y hora de la cita
    string requerimiento;  // Nuevo: requerimiento de la cita
    bool citaAceptada;     // Nuevo: indica si la cita ya fue aceptada
    string celular;        // Nuevo: número de celular

public:
    // Se actualiza el constructor para incluir los nuevos atributos (con valores por defecto)
    Persona(string n = "", Fecha fn = Fecha(), string c = "", Fecha ci = Fecha(), string req = "", bool aceptada = false)
        : nombre(n), fechaNacimiento(fn), cedula(c), cita(ci), requerimiento(req), citaAceptada(aceptada) {}

    string getNombre() const;
    Fecha getFechaNacimiento() const;
    string getCedula() const;
    Fecha getCita() const;
    void setNombre(const string& n);
    void setFechaNacimiento(const Fecha& fn);
    void setCedula(const string& c);
    void setCita(const Fecha& ci);
    void mostrar() const;

    // NUEVOS métodos para requerimiento y estado de aceptación
    string getRequerimiento() const { return requerimiento; }
    void setRequerimiento(const string& req) { requerimiento = req; }

    bool isCitaAceptada() const { return citaAceptada; }
    void setCitaAceptada(bool status) { citaAceptada = status; }

    // NUEVOS métodos para celular
    void setCelular(const string& _celular) { celular = _celular; }
    string getCelular() const { return celular; }
};

#endif // PERSONA_H
