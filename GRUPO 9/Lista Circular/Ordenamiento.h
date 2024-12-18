/***********************************************************************
 * Module:  Ordenamiento.h
 * Author:  Erika Guayanay, Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#pragma once
#include "ListasCirculares.h"
#include <string>

class Ordenamiento {
public:
    void ordenarNombresExterno(ListaCircular& lista, const std::string& archivo);
};
