#ifndef FECHA_H
#define FECHA_H

#include <string>

class Persona;
class Registro;

class Fecha {
private:
   std::string dia;
   std::string mes;
   std::string anio;
   std::string hora;
   std::string minutos;
   std::string segundos;
   Persona* persona;
   Registro* registro;

public:
   Fecha();
   Fecha(std::string fecha);
   Fecha(int dia, int mes, int anio);
   ~Fecha();

   static Fecha convertirStringAFecha(const std::string& fechaStr);

   std::string getDia();
   void setDia(std::string newDia);

   std::string getMes();
   void setMes(std::string newMes);

   std::string getAnio();
   void setAnio(std::string newAnio);

   std::string getHora();
   void setHora(std::string newHora);

   std::string getMinutos();
   void setMinutos(std::string newMinutos);

   std::string getSegundos();
   void setSegundos(std::string newSegundos);

   std::string toString() const {
      std::string fechaString = dia + "/" + mes + "/" + anio;
      return fechaString;
   }
};

#endif
