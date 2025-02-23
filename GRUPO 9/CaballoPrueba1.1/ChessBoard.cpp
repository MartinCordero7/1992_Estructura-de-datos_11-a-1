/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              17/02/2025                                               *
 * Fecha de modificacion:          17/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include "ChessBoard.h"
#include <graphics.h>
#include <stdexcept>
#include <iostream>
#include <fstream>

// Constructor que inicializa el tablero con ceros
ChessBoard::ChessBoard(int size) : size(size), tablero(size, std::vector<int>(size, 0)), caballo(nullptr) {
    // No need to manually allocate memory
}

// Destructor para liberar la memoria dinámica
ChessBoard::~ChessBoard() {
    delete caballo;
}

// Mueve el caballo y guarda las posiciones posibles en un archivo
void ChessBoard::moverCaballo(int fila, int col) {
    delete caballo;
    caballo = new Caballo(fila, col);

    // Limpiar el tablero
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            tablero[i][j] = 0;
        }
    }

    // Posibles movimientos del caballo
    int movimientos[8][2] = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };

    for (int i = 0; i < 8; ++i) {
        int nuevaFila = fila + movimientos[i][0];
        int nuevaCol = col + movimientos[i][1];
        if (nuevaFila >= 0 && nuevaFila < 8 && nuevaCol >= 0 && nuevaCol < 8) {
            tablero[nuevaFila][nuevaCol] = 2; // Marca con 2 las posiciones posibles del caballo
        }
    }

    tablero[fila][col] = 1; // Marca la posición del caballo con 1

    // Guardar el estado del tablero en un archivo
    std::ofstream archivo("movimientos_caballo.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para guardar los movimientos." << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (tablero[i][j] == 2) {
                archivo << "X ";
            } else {
                archivo << tablero[i][j] << " ";
            }
        }
        archivo << std::endl;
    }

    archivo.close();
}

// Dibuja el tablero y el caballo en la pantalla
void ChessBoard::dibujarCaballo(int fila, int col) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int tamanoCelda = 50;
    int offset = 50; // Espacio para los índices

    // Dibuja los índices horizontales y verticales
    for (int i = 0; i < 8; ++i) {
        char indice[2];
        sprintf(indice, "%d", i + 1);
        outtextxy(offset + i * tamanoCelda + tamanoCelda / 2, offset / 2, indice);
        outtextxy(offset / 2, offset + i * tamanoCelda + tamanoCelda / 2, indice);
    }

    int movimientos[8][2] = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };

    int currentMove = 0;
    while (currentMove < 8) {
        // Limpiar el tablero
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                int izquierda = offset + j * tamanoCelda;
                int arriba = offset + i * tamanoCelda;
                int derecha = izquierda + tamanoCelda;
                int abajo = arriba + tamanoCelda;

                // Dibuja las celdas del tablero
                if ((i + j) % 2 == 0)
                    setfillstyle(SOLID_FILL, WHITE);
                else
                    setfillstyle(SOLID_FILL, LIGHTGRAY);

                bar(izquierda, arriba, derecha, abajo);

                // Dibuja las posiciones posibles del caballo
                if (tablero[i][j] == 2) {
                    char* xMark = (char*)"X";
                    setcolor(BLUE);
                    outtextxy(izquierda + tamanoCelda / 2, arriba + tamanoCelda / 2, xMark);
                }

                // Dibuja el caballo
                if (i == fila && j == col) {
                    setcolor(GREEN);
                    setfillstyle(SOLID_FILL, GREEN);
                    fillellipse(izquierda + tamanoCelda / 2, arriba + tamanoCelda / 2, tamanoCelda / 3, tamanoCelda / 3);
                }
            }
        }

        getch(); // Espera una tecla para mover el caballo

        int nuevaFila = fila + movimientos[currentMove][0];
        int nuevaCol = col + movimientos[currentMove][1];
        if (nuevaFila >= 0 && nuevaFila < 8 && nuevaCol >= 0 && nuevaCol < 8) {
            tablero[nuevaFila][nuevaCol] = 2; // Deja una huella en la posición actual

            // Dibuja el movimiento del caballo
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    int izquierda = offset + j * tamanoCelda;
                    int arriba = offset + i * tamanoCelda;
                    int derecha = izquierda + tamanoCelda;
                    int abajo = arriba + tamanoCelda;

                    // Dibuja las celdas del tablero
                    if ((i + j) % 2 == 0)
                        setfillstyle(SOLID_FILL, WHITE);
                    else
                        setfillstyle(SOLID_FILL, LIGHTGRAY);

                    bar(izquierda, arriba, derecha, abajo);

                    // Dibuja las posiciones posibles del caballo
                    if (tablero[i][j] == 2) {
                        char* xMark = (char*)"X";
                        setcolor(BLUE);
                        outtextxy(izquierda + tamanoCelda / 2, arriba + tamanoCelda / 2, xMark);
                    }

                    // Dibuja el caballo en la nueva posición
                    if (i == nuevaFila && j == nuevaCol) {
                        setcolor(GREEN);
                        setfillstyle(SOLID_FILL, GREEN);
                        fillellipse(izquierda + tamanoCelda / 2, arriba + tamanoCelda / 2, tamanoCelda / 3, tamanoCelda / 3);
                    }
                }
            }

            getch(); // Espera una tecla para volver a la posición inicial
        }

        currentMove++;
    }

    getch();
    closegraph();
    system("cls");
}
