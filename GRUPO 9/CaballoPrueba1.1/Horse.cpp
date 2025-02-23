/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              17/02/2025                                               *
 * Fecha de modificacion:          17/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include "Horse.h"

// Constructor que inicializa la posicion de la reina
Horse::Horse(int fila, int col) {
    this->fila = new int(fila);
    this->col = new int(col);
}

// Destructor para liberar la memoria dinámica
Horse::~Horse() {
    delete fila;
    delete col;
}

// Obtiene la fila de la reina
int Horse::obtenerFila() const {
    return *fila;
}

// Obtiene la columna de la reina
int Horse::obtenerCol() const {
    return *col;
}
