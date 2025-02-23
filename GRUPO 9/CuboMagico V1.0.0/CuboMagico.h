#ifndef CUBOMAGICO_H
#define CUBOMAGICO_H

#include <graphics.h>

class CuboMagico {
private:
    int size;  // Tamaño del cubo
    int x, y;  // Posición inicial en pantalla
    int matriz[3][3];  // Matriz del cuadrado mágico

public:
    // Constructor
    CuboMagico(int size, int x, int y);

    // Método para generar un cuadrado mágico aleatorio
    void generarCuadradoMagico();

    // Método para dibujar el cuadrado mágico en la pantalla
    void dibujarCuadrado();
};

#endif
