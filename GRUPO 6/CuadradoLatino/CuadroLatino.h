#ifndef CUADROLATINO_H
#define CUADROLATINO_H

#include <string>

bool validarDigitos(const std::string& s, int pos = 0);
int obtenerEnteroPositivo();
void llenarCuadro(int** matriz, int n, int fila = 0, int col = 0);
void crearMatriz(int**& matriz, int n, int i = 0);
void imprimirMatriz(int** matriz, int n, int fila = 0, int col = 0);
void dibujarColumnas(int** matriz, int n, int fila, int col, int ancho, int margen);
void dibujarFilas(int** matriz, int n, int fila, int ancho, int margen);
void visualizarCuadro(int** matriz, int n);
void liberarMatriz(int** matriz, int n, int i = 0);

#endif
