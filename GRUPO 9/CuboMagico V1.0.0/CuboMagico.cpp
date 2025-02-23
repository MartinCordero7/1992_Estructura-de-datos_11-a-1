#include "CuboMagico.h"
#include <iostream>
#include <cstdlib>  // Para srand() y rand()
#include <ctime>    // Para time()

using namespace std;

// Constructor
CuboMagico::CuboMagico(int size, int x, int y) {
    this->size = size;
    this->x = x;
    this->y = y;
    generarCuadradoMagico();
}

// Algoritmo de Siamés para generar un cuadrado mágico de tamaño impar
void CuboMagico::generarCuadradoMagico() {
    // Inicializar la matriz con ceros
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matriz[i][j] = 0;

    int fila = 0;                // Primera fila
    int columna = size / 2;       // Columna del medio
    int num = 1;

    while (num <= size * size) {
        matriz[fila][columna] = num;  // Colocar el número en la matriz

        int nuevaFila = (fila - 1 + size) % size;  // Mover una fila arriba
        int nuevaColumna = (columna + 1) % size;   // Mover una columna a la derecha

        // Si la celda ya está ocupada, moverse una fila abajo en lugar de la diagonal
        if (matriz[nuevaFila][nuevaColumna] != 0) {
            fila = (fila + 1) % size;
        } else {
            fila = nuevaFila;
            columna = nuevaColumna;
        }

        num++;
    }
}


// Método para dibujar el cuadrado mágico
void CuboMagico::dibujarCuadrado() {
    int cellSize = 400 / size;  // Ajustar el tamaño de cada celda
    int centerX = x + (size * cellSize) / 2;  // Centro del cuadrado

    setbkcolor(BLACK);  // Fondo negro
    cleardevice();
    setcolor(WHITE);

    // Dibujar título centrado en la parte superior
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(centerX - 100, y - 60, "CUBO MAGICO");

    // Dibujar la cuadrícula
    for (int i = 0; i <= size; i++) {
        line(x, y + i * cellSize, x + size * cellSize, y + i * cellSize);  // Horizontales
        line(x + i * cellSize, y, x + i * cellSize, y + size * cellSize);  // Verticales
    }

    // Dibujar números dentro del cuadrado
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char num[3];
            sprintf(num, "%d", matriz[i][j]);
            int textX = x + j * cellSize + cellSize / 3;
            int textY = y + i * cellSize + cellSize / 3;
            outtextxy(textX, textY, num);
        }
    }

    // Calcular la suma mágica correcta
    int sumaMagica = (size * (size * size + 1)) / 2;

    // Dibujar sumas en filas y columnas correctamente alineadas
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    char sumText[4];
    sprintf(sumText, "%d", sumaMagica);

    for (int i = 0; i < size; i++) {
        // Sumas al final de cada fila
        outtextxy(x + size * cellSize + 20, y + i * cellSize + cellSize / 3, sumText);
        // Sumas debajo de cada columna
        outtextxy(x + i * cellSize + cellSize / 3, y + size * cellSize + 15, sumText);
    }

    // Sumas de diagonales correctamente alineadas
    outtextxy(x + size * cellSize + 20, y + size * cellSize + 15, sumText);
    outtextxy(x - 30, y + size * cellSize + 15, sumText);

    // Dibujar correctamente "SUMA MÁGICA: 15"
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(centerX - 100, y + size * cellSize + 40, "SUMA MAGICA:");

    // Mostrar el valor correcto al lado
    outtextxy(centerX + 80, y + size * cellSize + 40, sumText);
}
