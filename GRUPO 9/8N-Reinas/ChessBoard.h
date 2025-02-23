/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              12/02/2025                                               *
 * Fecha de modificacion:          12/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include "Queen.h"

class ChessBoard {
public:
    // Constructor que inicializa el tablero con el tamaño dado
    ChessBoard(int size);

    // Destructor para liberar memoria dinámica
    ~ChessBoard();

    // Resuelve el problema de las N-Reinas
    bool resolver();

    // Dibuja el tablero y las reinas en la pantalla
    void dibujar() const;

    // Muestra las posibles soluciones en consola
    void mostrarSoluciones() const;

private:
    // Verifica si es seguro colocar una reina en la posición dada
    bool esSeguro(int fila, int col) const;

    // Resuelve el problema de las N-Reinas utilizando backtracking
    bool resolverNReinas(int col);

    int size; // Tamaño del tablero y número de reinas
    std::vector<std::vector<int>> tablero; // Representación del tablero
};

#endif // CHESSBOARD_H
