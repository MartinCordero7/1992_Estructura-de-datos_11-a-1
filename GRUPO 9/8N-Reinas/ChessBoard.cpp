/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              12/02/2025                                               *
 * Fecha de modificacion:          12/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include "ChessBoard.h"
#include <graphics.h>
#include <stdexcept>
#include <iostream>

// Constructor que inicializa el tablero con ceros
ChessBoard::ChessBoard(int size) : size(size), tablero(size, std::vector<int>(size, 0)) {
    // No need to manually allocate memory
}

// Destructor para liberar la memoria dinámica
ChessBoard::~ChessBoard() {
    // No need to manually deallocate memory
}

// Verifica si es seguro colocar una reina en la posición dada
bool ChessBoard::esSeguro(int fila, int col) const {
    // Verifica la fila a la izquierda
    for (int i = 0; i < col; ++i)
        if (tablero[fila][i])
            return false;

    // Verifica la diagonal superior izquierda
    for (int i = fila, j = col; i >= 0 && j >= 0; --i, --j)
        if (tablero[i][j])
            return false;

    // Verifica la diagonal inferior izquierda
    for (int i = fila, j = col; j >= 0 && i < size; ++i, --j)
        if (tablero[i][j])
            return false;

    return true;
}

// Resuelve el problema de las N-Reinas utilizando backtracking
bool ChessBoard::resolverNReinas(int col) {
    if (col >= size)
        return true;

    auto esSeguro = [this](int fila, int col) -> bool {
        for (int i = 0; i < col; ++i)
            if (tablero[fila][i])
                return false;

        for (int i = fila, j = col; i >= 0 && j >= 0; --i, --j)
            if (tablero[i][j])
                return false;

        for (int i = fila, j = col; j >= 0 && i < size; ++i, --j)
            if (tablero[i][j])
                return false;

        return true;
    };

    for (int i = 0; i < size; ++i) {
        if (esSeguro(i, col)) {
            tablero[i][col] = 1;

            // Colocar recursivamente reinas en la siguiente columna
            if (resolverNReinas(col + 1))
                return true;

            // Retroceder si colocar la reina en tablero[i][col] no lleva a una solucion
            tablero[i][col] = 0;
        }
    }

    return false;
}

// Inicia la resolución del problema de las N-Reinas
bool ChessBoard::resolver() {
    return resolverNReinas(0);
}

// Dibuja el tablero y las reinas en la pantalla
void ChessBoard::dibujar() const {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int tamanoCelda = 50;
    int offset = 50; // Espacio para los índices

    // Dibuja los índices horizontales
    for (int i = 0; i < size; ++i) {
        char indice[2];
        sprintf(indice, "%d", i + 1);
        outtextxy(offset + i * tamanoCelda + tamanoCelda / 2, offset / 2, indice);
    }

    // Dibuja los índices verticales
    for (int i = 0; i < size; ++i) {
        char indice[2];
        sprintf(indice, "%d", i + 1);
        outtextxy(offset / 2, offset + i * tamanoCelda + tamanoCelda / 2, indice);
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int izquierda = offset + j * tamanoCelda;
            int arriba = offset + i * tamanoCelda;
            int derecha = izquierda + tamanoCelda;
            int abajo = arriba + tamanoCelda;

            // Dibuja las celdas del tablero
            if ((i + j) % 2 == 0)
                setfillstyle(SOLID_FILL, WHITE);
            else
                setfillstyle(SOLID_FILL, LIGHTGRAY); // Beige color

            bar(izquierda, arriba, derecha, abajo);

            // Dibuja las reinas
            if (tablero[i][j] == 1) {
                setcolor(RED);
                setfillstyle(SOLID_FILL, RED);
                fillellipse(izquierda + tamanoCelda / 2, arriba + tamanoCelda / 2, tamanoCelda / 3, tamanoCelda / 3);
            }
        }
    }

    getch();
    std::cout << "Pulsa una tecla para cerrar el grafico." << std::endl;
    getch();
    closegraph();
    system("cls"); // Clear the console
}

// Muestra las posibles soluciones en consola
void ChessBoard::mostrarSoluciones() const {
    std::cout << "Posiciones de las reinas:" << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (tablero[i][j] == 1) {
                std::cout << "Reina en: (" << i << ", " << j << ")" << std::endl;
            }
        }
    }
}
