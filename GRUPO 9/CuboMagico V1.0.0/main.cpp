#include <graphics.h>
#include <iostream>
#include <windows.h>
#include "CuboMagico.h"
#include "Validaciones.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);  // Habilita caracteres especiales en la consola

    int size;

    // Pedir al usuario un número válido usando la validación
    do {
        cout << "--- CUBO MÁGICO --- \n";
        size = Validaciones::validarEnteroImpar("Ingrese un tamaño impar para el cubo mágico (mínimo 3): ");
        if (size < 3 || size % 2 == 0) {
            cout << "El tamaño debe ser un número impar mayor o igual a 3.\n";
        }
    } while (size < 3 || size % 2 == 0);

    // Inicializar gráficos después de recibir el tamaño
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Centrar el cubo en la pantalla
    int x = (getmaxx() - 400) / 2;
    int y = (getmaxy() - 400) / 4;

    // Crear objeto y dibujar el cuadrado mágico
    CuboMagico cubo(size, x, y);
    cubo.dibujarCuadrado();

    // Esperar para cerrar
    cout << "Presione una tecla para salir...";
    getch();
    closegraph();

    return 0;
}
