/**********
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Steven Egas, Pablo Dominguez, Esteban Santos
 * FECHA CREACION: Viernes,  7 de Febrero de 2025
 * FECHA MODIFICACION: Miercoles, 12 de Febrero de 2025
 * PROYECTO: Grafos
 * Nivel: TERCERO     NRC: 1992
 ***********/
#include "Grafo.h"
#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Constructor
Grafo::Grafo() : numNodos(0), dirigido(true)
{
    std::srand(std::time(0));
}

// Crear un nuevo grafo con relaciones aleatorias
void Grafo::nuevoGrafo(int numNodos, bool dirigido)
{
    this->numNodos = numNodos;
    this->dirigido = dirigido;
    matrizAdyacencia = std::vector<std::vector<int>>(numNodos, std::vector<int>(numNodos, 0));
    generarRelacionesAleatorias();
}

// Generar relaciones aleatorias entre nodos
void Grafo::generarRelacionesAleatorias()
{
    for (int i = 0; i < numNodos; ++i)
    {
        for (int j = 0; j < numNodos; ++j)
        {
            if (i != j && (std::rand() % 6 == 0))
            { // 25% de probabilidad de crear una relación
                matrizAdyacencia[i][j] = 1;
                if (!dirigido)
                {
                    matrizAdyacencia[j][i] = 1;
                }
            }
        }
    }
}

// Representación lógica del grafo
void Grafo::representacionLogica()
{
    for (int i = 0; i < numNodos; ++i)
    {
        for (int j = 0; j < numNodos; ++j)
        {
            if (matrizAdyacencia[i][j] == 1)
            {
                std::cout << i << " -> " << j << std::endl;
            }
        }
    }
}

// Representación lógica gráfica del grafo
void Grafo::representacionLogicaGrafica(const std::string& titulo)
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, const_cast<char *>(""));
    setbkcolor(WHITE); // Set background color to white
    cleardevice(); // Clear the screen with the background color
    setcolor(BLACK); // Set drawing color to black
    int width = getmaxx();
    int height = getmaxy();
    int radius = 20;

    // Mostrar título
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    char tituloArray[100];
    strncpy(tituloArray, titulo.c_str(), sizeof(tituloArray));
    tituloArray[sizeof(tituloArray) - 1] = '\0';
    outtextxy((width - textwidth(tituloArray)) / 2, 10, tituloArray);

    // Generar posiciones distribuidas para los nodos
    std::vector<std::pair<int, int>> posiciones(numNodos);
    int rows = std::sqrt(numNodos);
    int cols = (numNodos + rows - 1) / rows;
    int cellWidth = width / cols;
    int cellHeight = height / rows;

    for (int i = 0; i < numNodos; ++i)
    {
        int row = i / cols;
        int col = i % cols;
        posiciones[i] = {col * cellWidth + cellWidth / 2, row * cellHeight + cellHeight / 2};
    }

    // Dibujar nodos y aristas
    for (int i = 0; i < numNodos; ++i)
    {
        int x1 = posiciones[i].first;
        int y1 = posiciones[i].second;
        for (int j = 0; j < numNodos; ++j)
        {
            if (matrizAdyacencia[i][j] == 1)
            {
                int x2 = posiciones[j].first;
                int y2 = posiciones[j].second;
                double angle = atan2(y2 - y1, x2 - x1);
                int x1b = x1 + radius * cos(angle);
                int y1b = y1 + radius * sin(angle);
                int x2b = x2 - radius * cos(angle);
                int y2b = y2 - radius * sin(angle);
                if (dirigido)
                {
                    // Dibujar flecha
                    line(x1b, y1b, x2b, y2b);
                    int arrowSize = 10;
                    int arrowX1 = x2b - arrowSize * cos(angle + M_PI / 6);
                    int arrowY1 = y2b - arrowSize * sin(angle + M_PI / 6);
                    int arrowX2 = x2b - arrowSize * cos(angle - M_PI / 6);
                    int arrowY2 = y2b - arrowSize * sin(angle - M_PI / 6);
                    line(x2b, y2b, arrowX1, arrowY1);
                    line(x2b, y2b, arrowX2, arrowY2);
                }
                else
                {
                    // Dibujar línea
                    line(x1b, y1b, x2b, y2b);
                }
            }
        }
    }
    for (int i = 0; i < numNodos; ++i)
    {
        int x = posiciones[i].first;
        int y = posiciones[i].second;
        circle(x, y, radius);
        outtextxy(x - 5, y - 5, const_cast<char *>(std::to_string(i).c_str()));
    }
    // Mantener la ventana abierta hasta que se presione una tecla
    getch();
    closegraph();
}

// Representación como lista de adyacencia
void Grafo::representacionListaAdyacencia()
{
    for (int i = 0; i < numNodos; ++i)
    {
        std::cout << i << ": ";
        for (int j = 0; j < numNodos; ++j)
        {
            if (matrizAdyacencia[i][j] == 1)
            {
                std::cout << j << " ";
            }
        }
        std::cout << std::endl;
    }
}

// Representación como lista de adyacencia gráfica
void Grafo::representacionListaAdyacenciaGrafica(const std::string& titulo)
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, const_cast<char *>(""));
    setbkcolor(WHITE); // Set background color to white
    cleardevice(); // Clear the screen with the background color
    setcolor(BLACK); // Set drawing color to black
    int width = getmaxx();
    int height = getmaxy();
    int radius = 10;
    int cellHeight = height / (numNodos + 3);
    int cellWidth = (width - 100) / (numNodos + 2);

    // Mostrar título
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    char tituloArray[100];
    strncpy(tituloArray, titulo.c_str(), sizeof(tituloArray));
    tituloArray[sizeof(tituloArray) - 1] = '\0';
    outtextxy((width - textwidth(tituloArray)) / 2, 10, tituloArray);

    // Dibujar nodos y sus listas de adyacencia
    for (int i = 0; i < numNodos; ++i)
    {
        int x = 50;
        int y = 20 + i * cellHeight;
        rectangle(x - radius, y - radius, x + radius, y + radius);
        outtextxy(x - 5, y - 5, const_cast<char *>(std::to_string(i).c_str()));

        int xOffset = 100;
        for (int j = 0; j < numNodos; ++j)
        {
            if (matrizAdyacencia[i][j] == 1)
            {
                int x1b = x + radius;
                int x2b = x + xOffset - radius;
                line(x1b, y, x2b, y);
                rectangle(x + xOffset - radius, y - radius, x + xOffset + radius, y + radius);
                outtextxy(x + xOffset - 5, y - 5, const_cast<char *>(std::to_string(j).c_str()));
                xOffset += cellWidth;
            }
        }
    }
    // Mantener la ventana abierta hasta que se presione una tecla
    getch();
    closegraph();
}

// Representación como matriz de adyacencia
void Grafo::representacionMatrizAdyacencia()
{
    for (int i = 0; i < numNodos; ++i)
    {
        for (int j = 0; j < numNodos; ++j)
        {
            std::cout << matrizAdyacencia[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Representación como matriz de adyacencia gráfica
void Grafo::representacionMatrizAdyacenciaGrafica(const std::string& titulo)
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, const_cast<char *>(""));
    setbkcolor(WHITE); // Set background color to white
    cleardevice(); // Clear the screen with the background color
    setcolor(BLACK); // Set drawing color to black
    int width = getmaxx();
    int height = getmaxy();
    int cellSize = std::min(width, height) / (numNodos + 2); // Ajustar tamaño de celda para mejor visualización

    // Mostrar título
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    char tituloArray[100];
    strncpy(tituloArray, titulo.c_str(), sizeof(tituloArray));
    tituloArray[sizeof(tituloArray) - 1] = '\0';
    outtextxy((width - textwidth(tituloArray)) / 2, 10, tituloArray);

    // Dibujar matriz de adyacencia
    for (int i = 0; i < numNodos; ++i)
    {
        for (int j = 0; j < numNodos; ++j)
        {
            int x = 50 + j * cellSize; // Ajustar margen izquierdo
            int y = 50 + i * cellSize; // Ajustar margen superior
            outtextxy(x, y, const_cast<char *>(std::to_string(matrizAdyacencia[i][j]).c_str()));
        }
    }
    // Mantener la ventana abierta hasta que se presione una tecla
    getch();
    closegraph();
}

// Búsqueda por amplitud
void Grafo::busquedaAmplitud(int verticeInicial)
{
    std::vector<bool> visitado(numNodos, false);
    std::queue<int> cola;
    cola.push(verticeInicial);
    visitado[verticeInicial] = true;

    std::cout << "Vertice\tVisitado" << std::endl;
    while (!cola.empty())
    {
        int vertice = cola.front();
        cola.pop();
        std::cout << vertice << "\ttrue" << std::endl;

        for (int i = 0; i < numNodos; ++i)
        {
            if (matrizAdyacencia[vertice][i] == 1 && !visitado[i])
            {
                cola.push(i);
                visitado[i] = true;
            }
        }
    }
    for (int i = 0; i < numNodos; ++i)
    {
        if (!visitado[i])
        {
            std::cout << i << "\tfalse" << std::endl;
        }
    }
}