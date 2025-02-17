#include "n_caballito.h"
#include <cctype> // Para validar entrada del usuario

using namespace std;

const int movX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int movY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// Verifica si un caballo puede moverse a la posición (x, y)
bool esSeguro(int x, int y, int N)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Dibuja el tablero en la pantalla con los posibles movimientos del caballo
void dibujarTablero(int x, int y, int N)
{
    int ancho = 500, alto = 500;
    int margen = 50;
    int tam_celda = (ancho - 2 * margen) / N;

    // Inicializar ventana gráfica
    initwindow(ancho, alto, "Movimientos del Caballo");

    // Dibujar el tablero
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
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

            // Dibujar posibles movimientos del caballo
            for (int k = 0; k < 8; k++)
            {
                int nextX = x + movX[k];
                int nextY = y + movY[k];
                if (esSeguro(nextX, nextY, N) && nextX == i && nextY == j)
                {
                    setcolor(GREEN);
                    setfillstyle(SOLID_FILL, GREEN);
                    fillellipse((x1 + x2) / 2, (y1 + y2) / 2, tam_celda / 3, tam_celda / 3);
                }
            }

            // Dibujar caballo en la posición inicial
            if (i == x && j == y)
            {
                setcolor(RED);
                setfillstyle(SOLID_FILL, RED);
                fillellipse((x1 + x2) / 2, (y1 + y2) / 2, tam_celda / 3, tam_celda / 3);
            }
        }
    }
    cout << "\nPresione cualquier tecla para cerrar el tablero...";
    getch();      // Esperar hasta que el usuario presione una tecla
    closegraph(); // Cerrar la ventana gráfica

    cout << "\nPresione Enter para volver al menu principal...";
    cin.ignore();
    cin.get();
}

// Obtiene un número válido para N con validación de entrada
int obtenerN()
{
    string entrada;
    int N;

    while (true)
    {
        cout << "Ingrese el tamanio del tablero (N): ";
        cin >> entrada;

        // Validar que la entrada solo contenga dígitos y no esté vacía
        bool esNumero = true;
        for (char c : entrada)
        {
            if (!isdigit(c))
            {
                esNumero = false;
                break;
            }
        }

        if (esNumero)
        {
            N = stoi(entrada);
            if (N > 0 && N <= MAX_N)
                return N;
        }

        cout << "Entrada invalida. Ingrese un numero entero positivo entre 1 y " << MAX_N << ".\n";
    }
}