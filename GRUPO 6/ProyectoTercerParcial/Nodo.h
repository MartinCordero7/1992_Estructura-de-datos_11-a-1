/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * Proposito:       Interfaz de nodo para el uso de listas con entregas
 * Autor:           Abner Arboleda, Christian Acuña, Christian Bonifaz
 * Fecha de creacion:   01/12/2024
 * Fecha de modificacion: 08/11/2024
 * Materia:         Estructura de datos
 * NRC :            1992
 ********************************************************************************************/

#ifndef NODO_H
#define NODO_H

#include "Entrega.h"

// Nodo de la lista circular doblemente enlazada que contiene un objeto de tipo Entrega
struct NodoEntrega {
    Entrega entrega;
    NodoEntrega* siguiente;
    NodoEntrega* anterior;
};

#endif
