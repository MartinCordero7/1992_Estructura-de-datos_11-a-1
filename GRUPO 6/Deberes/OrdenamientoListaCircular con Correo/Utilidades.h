/*******************************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                                  *
 * Proposito:                      Utilidades para ordenamiento lista circular                         *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz                    *
 * Fecha de creacion:              17/12/2024                                                          *
 * Fecha de modificacion:          18/12/2024                                                          *
 * Materia:                        Estructura de datos                                                 *
 * NRC :                           1992                                                                *
 *******************************************************************************************************/

#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>

class Utilidades {
public:
    static std::string generarCorreo(const std::string& nombre, const std::string& sNombre, const std::string& apellido);
};

#endif // UTILIDADES_H