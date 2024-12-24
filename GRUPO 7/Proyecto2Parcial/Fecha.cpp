#include "Fecha.hpp"

Fecha::Fecha(int day, int month, int year)
{
    struct tm datetime;
    datetime.tm_year = year;
    datetime.tm_mon = month;
    datetime.tm_mday = day;
    datetime.tm_hour = 0;
    datetime.tm_min = 0;
    datetime.tm_sec = 0;

    tiempo = mktime(&datetime);
}
Fecha::Fecha(std::time_t tiempo)
    : tiempo(tiempo)
{
}
time_t Fecha::getTiempo() const
{
    return tiempo;
}
void Fecha::setTiempo(int day, int month, int year)
{
    struct tm datetime;
    datetime.tm_year = year;
    datetime.tm_mon = month;
    datetime.tm_mday = day;
    datetime.tm_hour = 0;
    datetime.tm_min = 0;
    datetime.tm_sec = 0;

    tiempo = mktime(&datetime);
}

void Fecha::setTiempo(std::time_t nuevoTiempo)
{
    tiempo = nuevoTiempo;
}
 
std::ostream& operator<<(std::ostream& os, const Fecha& fecha)
{
    os << ctime(&fecha.tiempo);
    return os;
}
