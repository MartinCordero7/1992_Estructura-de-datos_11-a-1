#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

class Fecha {
private:
    int dia;
    int mes;
    int anio;
    int hora;  // Nueva variable para la hora
    int minuto; // Nueva variable para los minutos
    bool citaAceptada; // Nueva variable para el estado de aceptación de la cita

    static bool esBisiesto(int anio);
    static int diasEnMes(int mes, int anio);

public:
    Fecha(int d = 1, int m = 1, int a = 1900, int h = 0, int min = 0, bool aceptada = false);  // Constructor modificado
    int getDia() const;
    int getMes() const;
    int getAnio() const;
    int getHora() const;  // Nuevo método
    int getMinuto() const;  // Nuevo método
    bool isCitaAceptada() const; // Nuevo método
    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);
    void setHora(int h);  // Nuevo método
    void setMinuto(int m);  // Nuevo método
    void setCitaAceptada(bool aceptada); // Nuevo método
    string mostrar() const;
    static bool esFechaValida(int dia, int mes, int anio);
    static Fecha crearDesdeCadena(const string& fechaStr);
};

#endif // FECHA_H