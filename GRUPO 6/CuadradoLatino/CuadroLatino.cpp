#include "CuadroLatino.h"
#include <iostream>
#include <string>
#include <cctype>
#include <graphics.h>

using namespace std;

// Función recursiva para validar dígitos en cadena
bool validarDigitos(const string& s, int pos) {
    if (pos >= s.length()) return true;
    if (!isdigit(s[pos])) return false;
    return validarDigitos(s, pos + 1);
}

// Función recursiva para obtener entrada válida
int obtenerEnteroPositivo() {
    cout << "Ingrese el tamano del cuadro latino: ";
    string entrada;
    getline(cin, entrada);
    
    if (entrada.empty()) {
        cout << "Error: Entrada vacia.\n";
        return obtenerEnteroPositivo();
    }
    
    if (!validarDigitos(entrada)) {
        cout << "Error: Solo numeros enteros positivos.\n";
        return obtenerEnteroPositivo();
    }
    
    int n = stoi(entrada);
    if (n <= 0) {
        cout << "Error: Debe ser positivo.\n";
        return obtenerEnteroPositivo();
    }
    
    return n;
}

// Función recursiva para llenar matriz
void llenarCuadro(int** matriz, int n, int fila, int col) {
    if (fila >= n) return;
    
    matriz[fila][col] = (fila + col) % n + 1;
    
    (col + 1 < n) ? llenarCuadro(matriz, n, fila, col + 1)
                  : llenarCuadro(matriz, n, fila + 1, 0);
}

// Función recursiva para crear matriz
void crearMatriz(int**& matriz, int n, int i) {
    if (i >= n) return;
    matriz[i] = new int[n];
    crearMatriz(matriz, n, i + 1);
}

// Función recursiva para imprimir
void imprimirMatriz(int** matriz, int n, int fila, int col) {
    if (fila >= n) return;
    
    cout << matriz[fila][col] << " ";
    
    (col + 1 < n) ? imprimirMatriz(matriz, n, fila, col + 1)
                   : (cout << endl, imprimirMatriz(matriz, n, fila + 1, 0));
}

// Función recursiva para dibujar columnas
void dibujarColumnas(int** matriz, int n, int fila, int col, int ancho, int margen) {
    if (col >= n) return;
    
    int x = margen + col * ancho;
    int y = margen + fila * ancho;
    
    rectangle(x, y, x + ancho, y + ancho);
    char texto[3];
    sprintf(texto, "%d", matriz[fila][col]);
    outtextxy(x + ancho/2, y + ancho/2, texto);
    
    dibujarColumnas(matriz, n, fila, col + 1, ancho, margen);
}

// Función recursiva para dibujar filas
void dibujarFilas(int** matriz, int n, int fila, int ancho, int margen) {
    if (fila >= n) return;
    
    dibujarColumnas(matriz, n, fila, 0, ancho, margen);
    dibujarFilas(matriz, n, fila + 1, ancho, margen);
}

// Función gráfica recursiva
void visualizarCuadro(int** matriz, int n) {
    int ancho = 50, margen = 20;
    initwindow(n * ancho + 2 * margen, n * ancho + 2 * margen, "Cuadro Latino");
    
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    
    dibujarFilas(matriz, n, 0, ancho, margen);
    
    getch();
    closegraph();
}

// Función recursiva para liberar memoria
void liberarMatriz(int** matriz, int n, int i) {
    if (i >= n) return;
    delete[] matriz[i];
    liberarMatriz(matriz, n, i + 1);
}
