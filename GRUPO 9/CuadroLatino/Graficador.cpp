#include "Graficador.h"
#include <stdexcept> // Necesario para std::runtime_error

void Graficador::dibujarCuadroLatino(const std::vector<std::vector<int>>& matriz) {
    try {
        int n = matriz.size();
        int cellSize = 50;  // Tamaño de celdas
        int padding = 50;   // Espaciado interno
        int width = n * cellSize + 2 * padding;
        int height = n * cellSize + 2 * padding + 50; // Espacio extra para el título
        
        // Inicializar ventana con el tamaño adecuado
        initwindow(width, height, "Cuadro Latino");

        // Fondo blanco
        setbkcolor(WHITE);
        cleardevice();

        // Dibujar título centrado
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
        setcolor(BLACK);
        outtextxy(width / 2, 20, "Cuadro Latino");

        int startX = padding;
        int startY = padding + 30; // Ajuste por el título

        // Dibujar la matriz con colores diferenciados
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int x1 = startX + j * cellSize;
                int y1 = startY + i * cellSize;
                int x2 = x1 + cellSize;
                int y2 = y1 + cellSize;

                // Alternar colores para mejor visibilidad
                int color = (i + j) % 2 == 0 ? LIGHTCYAN : LIGHTGRAY;
                setfillstyle(SOLID_FILL, color);
                bar(x1, y1, x2, y2);

                // Bordes negros para mejor contraste
                setcolor(BLACK);
                rectangle(x1, y1, x2, y2);

                // Centrar los números sin fondo, solo color fuerte
                char num[2];
                sprintf(num, "%d", matriz[i][j]);

                settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
                setcolor(BLUE); // Números azules para alto contraste
                settextjustify(CENTER_TEXT, CENTER_TEXT);
                outtextxy(x1 + cellSize / 2, y1 + cellSize / 2, num);
            }
        }

        getch(); // Esperar tecla para cerrar
        closegraph();
    } catch (const std::exception& e) {
        throw std::runtime_error("Error al dibujar el cuadro latino: " + std::string(e.what()));
    }
}
