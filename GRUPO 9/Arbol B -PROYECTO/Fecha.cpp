/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Gestionar Fechas                                         *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "Fecha.h"
#include <stdexcept>
#include <sstream>
#include <string>

bool Fecha::esBisiesto(int anio) {
    try {
        return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    } catch (const std::exception& e) {
        std::cerr << "Error al verificar si el año es bisiesto: " << e.what() << std::endl;
        return false;
    }
}

int Fecha::diasEnMes(int mes, int anio) {
    try {
        switch (mes) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
            case 4: case 6: case 9: case 11: return 30;
            case 2: return esBisiesto(anio) ? 29 : 28;
            default: return 0;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error al obtener los días en el mes: " << e.what() << std::endl;
        return 0;
    }
}

Fecha::Fecha(int d, int m, int a) {
    try {
        if (!esFechaValida(d, m, a)) throw std::invalid_argument("Fecha invalida");
        dia = d; mes = m; anio = a;
    } catch (const std::exception& e) {
        std::cerr << "Error al crear la fecha: " << e.what() << std::endl;
    }
}

int Fecha::getDia() const {
    try {
        return dia;
    } catch (const std::exception& e) {
        std::cerr << "Error al obtener el día: " << e.what() << std::endl;
        return 0;
    }
}

int Fecha::getMes() const {
    try {
        return mes;
    } catch (const std::exception& e) {
        std::cerr << "Error al obtener el mes: " << e.what() << std::endl;
        return 0;
    }
}

int Fecha::getAnio() const {
    try {
        return anio;
    } catch (const std::exception& e) {
        std::cerr << "Error al obtener el año: " << e.what() << std::endl;
        return 0;
    }
}

void Fecha::setDia(int d) {
    try {
        if (!esFechaValida(d, mes, anio)) throw std::invalid_argument("Dia invalido");
        dia = d;
    } catch (const std::exception& e) {
        std::cerr << "Error al establecer el día: " << e.what() << std::endl;
    }
}

void Fecha::setMes(int m) {
    try {
        if (!esFechaValida(dia, m, anio)) throw std::invalid_argument("Mes invalido");
        mes = m;
    } catch (const std::exception& e) {
        std::cerr << "Error al establecer el mes: " << e.what() << std::endl;
    }
}

void Fecha::setAnio(int a) {
    try {
        if (!esFechaValida(dia, mes, a)) throw std::invalid_argument("Año invalido");
        anio = a;
    } catch (const std::exception& e) {
        std::cerr << "Error al establecer el año: " << e.what() << std::endl;
    }
}

std::string Fecha::mostrar() const {
    try {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << dia << "/"
           << std::setw(2) << std::setfill('0') << mes << "/"
           << anio;
        return ss.str();
    } catch (const std::exception& e) {
        std::cerr << "Error al mostrar la fecha: " << e.what() << std::endl;
        return "";
    }
}

std::string Fecha::toString() const {
    try {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << dia << "-"
           << std::setw(2) << std::setfill('0') << mes << "-"
           << anio;
        return ss.str();
    } catch (const std::exception& e) {
        std::cerr << "Error al convertir la fecha a cadena: " << e.what() << std::endl;
        return "";
    }
}

bool Fecha::esFechaValida(int dia, int mes, int anio) {
    try {
        if (anio < 1 || mes < 1 || mes > 12) return false;
        return dia >= 1 && dia <= diasEnMes(mes, anio);
    } catch (const std::exception& e) {
        std::cerr << "Error al validar la fecha: " << e.what() << std::endl;
        return false;
    }
}

Fecha Fecha::crearDesdeCadena(const std::string& fechaStr) {
    try {
        int d, m, a; char separador1, separador2;
        std::stringstream ss(fechaStr);
        ss >> d >> separador1 >> m >> separador2 >> a;
        if (separador1 != '-' || separador2 != '-' || !esFechaValida(d, m, a)) 
            throw std::invalid_argument("Formato o fecha invalida: " + fechaStr);
        return Fecha(d, m, a);
    } catch (const std::exception& e) {
        std::cerr << "Error al crear la fecha desde cadena: " << e.what() << std::endl;
        return Fecha(1, 1, 1900); // Retornar una fecha por defecto en caso de error
    }
}
