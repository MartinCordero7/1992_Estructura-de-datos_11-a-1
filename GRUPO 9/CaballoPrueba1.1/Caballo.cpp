/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              12/02/2025                                               *
 * Fecha de modificacion:          12/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include "Caballo.h"

// Constructor que inicializa la posicion del caballo
Caballo::Caballo(int fila, int col) {
    this->fila = new int(fila);
    this->col = new int(col);
}

// Destructor para liberar la memoria dinámica
Caballo::~Caballo() {
    delete fila;
    delete col;
}

// Obtiene la fila del caballo
int Caballo::obtenerFila() const {
    return *fila;
}

// Obtiene la columna del caballo
int Caballo::obtenerCol() const {
    return *col;
}

// Mueve el caballo a una nueva posición
void Caballo::mover(int nuevaFila, int nuevaCol) {
    *fila = nuevaFila;
    *col = nuevaCol;
}

std::vector<std::pair<int, int>> Caballo::obtenerMovimientosPosibles() const {
    std::vector<std::pair<int, int>> movimientos;
    int movimientosPosibles[8][2] = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };

    for (int i = 0; i < 8; ++i) {
        int nuevaFila = *fila + movimientosPosibles[i][0];
        int nuevaCol = *col + movimientosPosibles[i][1];
        if (nuevaFila >= 0 && nuevaFila < 8 && nuevaCol >= 0 && nuevaCol < 8) {
            movimientos.push_back({nuevaFila, nuevaCol});
        }
    }

    return movimientos;
}
