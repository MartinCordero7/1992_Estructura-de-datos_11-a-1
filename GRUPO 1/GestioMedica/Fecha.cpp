#include "fecha.h"

bool Fecha::esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int Fecha::diasEnMes(int mes, int anio) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return esBisiesto(anio) ? 29 : 28;
        default: return 0;
    }
}

Fecha::Fecha(int d, int m, int a, int h, int min, bool aceptada) : dia(d), mes(m), anio(a), hora(h), minuto(min), citaAceptada(aceptada) {
    if (!esFechaValida(d, m, a)) throw invalid_argument("Fecha invalida");
    if (h < 0 || h >= 24) throw invalid_argument("Hora invalida");
    if (min < 0 || min >= 60) throw invalid_argument("Minuto invalido");
}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }
int Fecha::getHora() const { return hora; }
int Fecha::getMinuto() const { return minuto; }
bool Fecha::isCitaAceptada() const { return citaAceptada; }

void Fecha::setDia(int d) {
    if (!esFechaValida(d, mes, anio)) throw invalid_argument("Dia invalido");
    dia = d;
}

void Fecha::setMes(int m) {
    if (!esFechaValida(dia, m, anio)) throw invalid_argument("Mes invalido");
    mes = m;
}

void Fecha::setAnio(int a) {
    if (!esFechaValida(dia, mes, a)) throw invalid_argument("Año invalido");
    anio = a;
}

void Fecha::setHora(int h) {
    if (h >= 0 && h < 24) {
        hora = h;
    } else {
        throw invalid_argument("Hora invalida");
    }
}

void Fecha::setMinuto(int m) {
    if (m >= 0 && m < 60) {
        minuto = m;
    } else {
        throw invalid_argument("Minuto invalido");
    }
}

void Fecha::setCitaAceptada(bool aceptada) {
    citaAceptada = aceptada;
}

string Fecha::mostrar() const {
    stringstream ss;
    ss << setw(2) << setfill('0') << dia << "/"
       << setw(2) << setfill('0') << mes << "/"
       << anio << " "
       << setw(2) << setfill('0') << hora << ":"
       << setw(2) << setfill('0') << minuto;
    return ss.str();
}

bool Fecha::esFechaValida(int dia, int mes, int anio) {
    if (anio < 1 || mes < 1 || mes > 12) return false;
    return dia >= 1 && dia <= diasEnMes(mes, anio);
}

Fecha Fecha::crearDesdeCadena(const string& fechaStr) {
    int d, m, a; char separador1, separador2;
    stringstream ss(fechaStr);
    ss >> d >> separador1 >> m >> separador2 >> a;
    if (separador1 != '-' || separador2 != '-' || !esFechaValida(d, m, a)) 
        throw invalid_argument("Formato o fecha invalida: " + fechaStr);
    return Fecha(d, m, a);
}