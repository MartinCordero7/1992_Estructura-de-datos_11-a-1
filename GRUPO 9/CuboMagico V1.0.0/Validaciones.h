#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <iostream>
#include <conio.h>  // Para _getch()
#include <string>

class Validaciones {
public:
    static int validarEntero(const std::string& mensaje); // Validar entrada numérica
    static int validarEnteroImpar(const std::string& mensaje); // Validar solo números impares
};

#endif
