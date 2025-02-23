/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 *                                                                                          *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              12/02/2025                                               *
 * Fecha de modificacion:          12/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

class Validaciones {
public:
    // Valida que la entrada sea un número entre 1 y 8 o 'X' para salir
    static bool validarEntrada(const std::string& entrada, int& size);

    // Captura y valida la entrada del usuario, permitiendo solo números del 1 al 8 y 'X'
    static int validarEntero(const std::string& mensaje);

    static bool validarEntradaCaballo(int& fila, int& col);
};

#endif // VALIDACIONES_H
