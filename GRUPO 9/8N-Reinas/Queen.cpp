/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              12/02/2025                                               *
 * Fecha de modificacion:          12/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include "Queen.h"

// Constructor que inicializa la posicion de la reina
Queen::Queen(int fila, int col) {
    this->fila = new int(fila);
    this->col = new int(col);
}

// Destructor para liberar la memoria dinámica
Queen::~Queen() {
    delete fila;
    delete col;
}

// Obtiene la fila de la reina
int Queen::obtenerFila() const {
    return *fila;
}

// Obtiene la columna de la reina
int Queen::obtenerCol() const {
    return *col;
}
