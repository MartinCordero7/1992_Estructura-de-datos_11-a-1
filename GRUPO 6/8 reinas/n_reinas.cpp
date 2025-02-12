#include "n_reinas.h"
#include <cctype> // Para validar entrada del usuario

using namespace std;

// Verifica si una reina puede colocarse en la posición (fila, col)
bool esSeguro(int tablero[MAX_N][MAX_N], int fila, int col, int N) {
    for (int i = 0; i < fila; i++)
        if (tablero[i][col]) return false;

    for (int i = fila, j = col; i >= 0 && j >= 0; i--, j--)
        if (tablero[i][j]) return false;

    for (int i = fila, j = col; i >= 0 && j < N; i--, j++)
        if (tablero[i][j]) return false;

    return true;
}

// Resuelve el problema de las N reinas con backtracking
bool resolverNReinas(int tablero[MAX_N][MAX_N], int fila, int N) {
    if (fila >= N) return true;

    for (int col = 0; col < N; col++) {
        if (esSeguro(tablero, fila, col, N)) {
            tablero[fila][col] = 1;

            if (resolverNReinas(tablero, fila + 1, N)) return true;

            tablero[fila][col] = 0; // Backtracking
        }
    }
    return false;
}

// Dibuja el tablero en la pantalla
void dibujarTablero(int tablero[MAX_N][MAX_N], int N) {
    int ancho = 500, alto = 500;
    int margen = 50;
    int tam_celda = (ancho - 2 * margen) / N;

    // Inicializar ventana gráfica
    initwindow(ancho, alto, "N Reinas");

    // Dibujar el tablero
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x1 = margen + j * tam_celda;
            int y1 = margen + i * tam_celda;
            int x2 = x1 + tam_celda;
            int y2 = y1 + tam_celda;

            // Alternar colores de las casillas
            if ((i + j) % 2 == 0)
                setfillstyle(SOLID_FILL, WHITE);
            else
                setfillstyle(SOLID_FILL, DARKGRAY);

            bar(x1, y1, x2, y2); // Dibujar casilla

            // Dibujar reina si hay una en esta posición
            if (tablero[i][j] == 1) {
                setcolor(RED);
                setfillstyle(SOLID_FILL, RED);
                fillellipse((x1 + x2) / 2, (y1 + y2) / 2, tam_celda / 3, tam_celda / 3);
            }
        }
    }
    cout << "\nPresione cualquier tecla para cerrar el tablero...";
    getch();  // Esperar hasta que el usuario presione una tecla
    closegraph(); // Cerrar la ventana gráfica
    
    cout << "\nPresione Enter para volver al menu principal...";
    cin.ignore();
    cin.get();
}

// Obtiene un número válido para N con validación de entrada
int obtenerN() {
    string entrada;
    int N;

    while (true) {
        cout << "Ingrese el tamanio del tablero (N): ";
        cin >> entrada;

        // Validar que la entrada solo contenga dígitos y no esté vacía
        bool esNumero = true;
        for (char c : entrada) {
            if (!isdigit(c)) {
                esNumero = false;
                break;
            }
        }

        if (esNumero) {
            N = stoi(entrada);
            if (N > 0 && N <= MAX_N) return N;
        }

        cout << "Entrada invalida. Ingrese un numero entero positivo entre 1 y " << MAX_N << ".\n";
    }
}