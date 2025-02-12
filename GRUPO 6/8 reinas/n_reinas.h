#ifndef N_REINAS_H
#define N_REINAS_H

#include <iostream>
#include <graphics.h>

#define MAX_N 8  // Tamaño máximo permitido del tablero

// Declaraciones de funciones
bool esSeguro(int tablero[MAX_N][MAX_N], int fila, int col, int N);
bool resolverNReinas(int tablero[MAX_N][MAX_N], int fila, int N);
void dibujarTablero(int tablero[MAX_N][MAX_N], int N);
int obtenerN();

#endif