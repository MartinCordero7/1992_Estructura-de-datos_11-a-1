#ifndef N_CABALLITO_H
#define N_CABALLITO_H

#include <iostream>
#include <graphics.h>

#define MAX_N 8 // Tamaño máximo permitido del tablero

// Declaraciones de funciones
bool esSeguro(int x, int y, int N);
void dibujarTablero(int &x, int &y, int N);
void exportarTablero(int x, int y, int N);
void manejarClick(int &x, int &y, int N);

#endif