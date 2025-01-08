/*******************************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                                  *
 * Proposito:                      Nodo para ordenamiento lista circular                               *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz                    *
 * Fecha de creacion:              17/12/2024                                                          *
 * Fecha de modificacion:          18/12/2024                                                          *
 * Materia:                        Estructura de datos                                                 *
 * NRC :                           1992                                                                *
 *******************************************************************************************************/

#ifndef NODO_H
#define NODO_H

#include "Persona.h"

// Nodo de la lista circular simple
struct Nodo {
    Persona persona;   // Ahora contiene un objeto de tipo Persona
    Nodo* siguiente;
};

#endif // NODO_H