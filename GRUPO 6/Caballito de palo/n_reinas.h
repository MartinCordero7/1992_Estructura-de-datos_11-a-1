#ifndef N_REINAS_H
#define N_REINAS_H

#include <iostream>
#include <graphics.h>

#define MAX_N 8 // Tamaño máximo permitido del tablero

// Declaraciones de funciones
bool esSeguro(int x, int y, int N);
void dibujarTablero(int x, int y, int N);
int obtenerN();

#endif