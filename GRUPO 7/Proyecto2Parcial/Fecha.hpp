#include <chrono>
#include <ctime>
#include <iostream>

class Fecha
{
private:
    std::time_t tiempo;

public:
    Fecha(int day = 0, int month = 0, int year = 0);
    Fecha(std::time_t tiempo);
    time_t getTiempo() const;
    void setTiempo(int day, int month, int year);
    void setTiempo(std::time_t nuevoTiempo);

    friend std::ostream& operator<<(std::ostream& os, const Fecha& fecha);

};