/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              17/02/2025                                               *
 * Fecha de modificacion:          17/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector> // Agregar esta línea
#include "Caballo.h"

class ChessBoard {
public:
    // Constructor que inicializa el tablero con el tamaño dado
    ChessBoard(int size);

    // Destructor para liberar memoria dinámica
    ~ChessBoard();

    // Dibuja el tablero y el caballo en la pantalla
    void dibujarCaballo(int fila, int col); // Cambiar a no const

    // Mueve el caballo y guarda las posiciones posibles en un archivo
    void moverCaballo(int fila, int col);

private:
    int size; // Tamaño del tablero
    std::vector<std::vector<int>> tablero; // Representación del tablero
    Caballo* caballo; // Puntero al objeto Caballo
};

#endif // CHESSBOARD_H
