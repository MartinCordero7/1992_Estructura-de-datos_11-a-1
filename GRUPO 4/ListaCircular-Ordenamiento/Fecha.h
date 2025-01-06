#ifndef FECHA_H
#define FECHA_H
#include <sstream>
#include <string>
#include <algorithm>
class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    Fecha() : dia(0), mes(0), anio(0) {}
    Fecha(int dia, int mes, int anio) : dia(dia), mes(mes), anio(anio) {}

    void imprimirFecha() const {
        printf("%02d/%02d/%04d\n", dia, mes, anio);
    }
    
    std::string toString() const {
        std::ostringstream ss;
        ss << dia << "/" << mes << "/" << anio;
        return ss.str();
    }

 static Fecha fromString(const std::string& fechaStr) {
    // Trim leading and trailing whitespace
    std::string trimmedFecha = fechaStr;
    trimmedFecha.erase(trimmedFecha.find_last_not_of(" \t\r\n") + 1);
    trimmedFecha.erase(0, trimmedFecha.find_first_not_of(" \t\r\n"));

    std::istringstream stream(trimmedFecha);
    int dia, mes, anio;
    char sep1, sep2;  // for the slashes ("/")
    stream >> dia >> sep1 >> mes >> sep2 >> anio;

    if (stream.fail() || sep1 != '/' || sep2 != '/' || dia < 1 || mes < 1 || mes > 12 || anio < 1) {
        throw std::invalid_argument("Formato de fecha incorrecto: " + fechaStr);
    }


    return Fecha(dia, mes, anio);
}
    int getDia() const { return dia; }
    void setDia(int dia_) { dia = dia_; }

    int getMes() const { return mes; }
    void setMes(int mes_) { mes = mes_; }

    int getAnio() const { return anio; }
    void setAnio(int anio_) { anio = anio_; }
};
#endif // FECHA_H