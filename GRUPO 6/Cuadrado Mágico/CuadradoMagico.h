#ifndef CUADRADO_MAGICO_H
#define CUADRADO_MAGICO_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <graphics.h>
using namespace std;

// Funciones para cuadrado 3x3
bool solveManual3x3(int square[3][3]);
void generar3x3(int cuadrado[3][3]);
void imprimir3x3(int cuadrado[3][3]);
void mostrarGrafico3x3(int cuadrado[3][3]);

// Funciones para cuadrado 4x4
bool solveManual4x4(int square[4][4]);
void generar4x4(int cuadrado[4][4]);
void imprimir4x4(int cuadrado[4][4]);
void mostrarGrafico4x4(int cuadrado[4][4]);

#endif // CUADRADO_MAGICO_H
