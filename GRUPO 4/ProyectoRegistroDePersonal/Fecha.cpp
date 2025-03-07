#include "Fecha.h"
#include <sstream>

Fecha::Fecha() {
   // Implementación del constructor por defecto
}

Fecha::~Fecha() {
   // Implementación del destructor si es necesario
}

std::string Fecha::getDia() {
   return dia;
}

void Fecha::setDia(std::string newDia) {
   dia = newDia;
}

std::string Fecha::getMes() {
   return mes;
}

void Fecha::setMes(std::string newMes) {
   mes = newMes;
}

std::string Fecha::getAnio() {
   return anio;
}

void Fecha::setAnio(std::string newAnio) {
   anio = newAnio;
}

std::string Fecha::getHora() {
   return hora;
}

void Fecha::setHora(std::string newHora) {
   hora = newHora;
}

std::string Fecha::getMinutos() {
   return minutos;
}

void Fecha::setMinutos(std::string newMinutos) {
   minutos = newMinutos;
}

std::string Fecha::getSegundos() {
   return segundos;
}

void Fecha::setSegundos(std::string newSegundos) {
   segundos = newSegundos;
}

Fecha::Fecha(std::string fecha) {
   std::istringstream iss(fecha);
   std::getline(iss, dia, '/'); // Separar el día de la fecha
   std::getline(iss, mes, '/'); // Separar el mes de la fecha
   std::getline(iss, anio); // Obtener el año de la fecha
}

Fecha::Fecha(int dia, int mes, int anio) {
   this->dia = std::to_string(dia);
   this->mes = std::to_string(mes);
   this->anio = std::to_string(anio);
}

Fecha Fecha::convertirStringAFecha(const std::string& fechaStr) {
    int dia, mes, anio;
    char delimiter;

    std::istringstream iss(fechaStr);
    iss >> dia >> delimiter >> mes >> delimiter >> anio;

    return Fecha(dia, mes, anio);
}
