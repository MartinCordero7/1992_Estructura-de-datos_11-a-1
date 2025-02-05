#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

class Validaciones {
public:
    static int validarEntero(const std::string& mensaje);
    static std::string validarCadena(const std::string& mensaje);
    static int validarOpcionMenu(const std::string& mensaje); // Nueva función
    static int validarOpcionSubMenu(const std::string& mensaje); // Para opciones 1-5
     static std::string validarNumeroConSalida(const std::string& mensaje); // Nueva función
};

#endif // VALIDACIONES_H
