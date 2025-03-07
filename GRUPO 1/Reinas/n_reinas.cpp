/**********
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Altamirano Xavier, Cordero Martin, Oña Isaac
 * FECHA CREACION: Miercoles,  12 de Febrero de 2025
 * FECHA MODIFICACION: Miercoles, 12 de Febrero de 2025
 * PROYECTO: N reinas
 * Nivel: TERCERO     NRC: 1992
 ***********/
#include <graphics.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include "n_reinas_util.cpp"
#include <windows.h>

using namespace std;

int N = 8;

void clearScreen() {
    system("cls");
}

void showMenu() {
    clearScreen();
    cout << "\n=== PROBLEMA DE LAS N REINAS ===\n" << endl;
    cout << "Tamanio actual del tablero: " << N << "x" << N << endl;
    cout << "Numero de reinas: " << N << endl;
    cout << "--------------------------------" << endl;
    cout << "1. Resolver problema automaticamente" << endl;
    cout << "2. Cambiar dimension del tablero (4-8)" << endl;
    cout << "3. Salir" << endl;
    cout << "\nNota: El numero de reinas siempre es igual al tamanio del tablero" << endl;
    cout << "\nSeleccione una opcion: ";
}

int getValidOption() {
    int option;
    while (!(cin >> option) || option < 1 || option > 4) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nOpcion invalida. Por favor ingrese un numero entre 1 y 4: ";
    }
    return option;
}

void changeBoardSize() {
    clearScreen();
    int newSize;
    cout << "\n=== CAMBIAR TAMANIO DEL TABLERO ===\n" << endl;
    do {
        cout << "Ingrese el nuevo tamanio del tablero (4-8): ";
        cin >> newSize;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Por favor, ingrese un numero valido." << endl;
            continue;
        }
        if (newSize < 4 || newSize > 8) {
            cout << "El tamanio debe estar entre 4 y 8" << endl;
        }
    } while (newSize < 4 || newSize > 8);
    N = newSize;
    cout << "\nTamanio del tablero cambiado a " << N << "x" << N << endl;
    cout << "Presione cualquier tecla para continuar...";
    _getch();
}

bool isValidMove(vector<vector<int>>& board, int fromRow, int fromCol, int toRow, int toCol) {
    // Verificar que el movimiento esté dentro del tablero
    if (toRow < 0 || toRow >= N || toCol < 0 || toCol >= N) return false;
    
    // Verificar que el destino esté vacío
    if (board[toRow][toCol] == 1) return false;
    
    // Temporalmente remover la reina de su posición actual
    board[fromRow][fromCol] = 0;
    bool safe = isSafe(board, toRow, toCol);
    // Restaurar la reina
    board[fromRow][fromCol] = 1;
    
    return safe;
}

void highlightSelectedQueen(int x, int y, int cellSize) {
    setcolor(YELLOW);
    rectangle(x, y, x + cellSize, y + cellSize);
    rectangle(x+1, y+1, x + cellSize-1, y + cellSize-1);
}

void drawBoard(vector<vector<int>>& board) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    
    if (graphresult() != grOk) {
        cout << "Error grafico" << endl;
        system("pause");
        return;
    }

    int cellSize = 60;
    int startX = (getmaxx() - N * cellSize) / 2;
    int startY = (getmaxy() - N * cellSize) / 2;
    int selectedRow = -1, selectedCol = -1;
    bool selected = false;
    char key;

    do {
        cleardevice();
        // Dibujar tablero
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int x = startX + j * cellSize;
                int y = startY + i * cellSize;
                
                // Dibujar celda
                rectangle(x, y, x + cellSize, y + cellSize);
                if ((i + j) % 2 == 0) {
                    setfillstyle(SOLID_FILL, WHITE);
                } else {
                    setfillstyle(SOLID_FILL, DARKGRAY);
                }
                floodfill(x + cellSize/2, y + cellSize/2, WHITE);

                // Dibujar reina
                if (board[i][j] == 1) {
                    if (i == selectedRow && j == selectedCol) {
                        highlightSelectedQueen(x, y, cellSize);
                    }
                    setcolor(RED);
                    setfillstyle(SOLID_FILL, RED);
                    circle(x + cellSize/2, y + cellSize/2, cellSize/3);
                    floodfill(x + cellSize/2, y + cellSize/2, RED);
                    setcolor(WHITE);
                }
            }
        }

        setcolor(WHITE);
        outtextxy(10, getmaxy() - 20, "Use flechas para mover, Enter para seleccionar, ESC para salir");
        
        key = getch();
        if (key == 0) key = getch(); // Teclas especiales

        if (!selected) {
            // Modo selección
            if (key == '\r') { // Enter
                if (board[selectedRow >= 0 ? selectedRow : 0][selectedCol >= 0 ? selectedCol : 0] == 1) {
                    selected = true;
                }
            } else {
                // Mover cursor de selección
                switch(key) {
                    case 72: selectedRow = max(0, selectedRow - 1); break; // Arriba
                    case 80: selectedRow = min(N-1, selectedRow + 1); break; // Abajo
                    case 75: selectedCol = max(0, selectedCol - 1); break; // Izquierda
                    case 77: selectedCol = min(N-1, selectedCol + 1); break; // Derecha
                }
                if (selectedRow == -1) selectedRow = 0;
                if (selectedCol == -1) selectedCol = 0;
            }
        } else {
            // Modo movimiento
            int newRow = selectedRow;
            int newCol = selectedCol;
            
            switch(key) {
                case 72: newRow--; break; // Arriba
                case 80: newRow++; break; // Abajo
                case 75: newCol--; break; // Izquierda
                case 77: newCol++; break; // Derecha
                case '\r': selected = false; break; // Enter para deseleccionar
            }

            if (isValidMove(board, selectedRow, selectedCol, newRow, newCol)) {
                board[selectedRow][selectedCol] = 0;
                board[newRow][newCol] = 1;
                selectedRow = newRow;
                selectedCol = newCol;
            }
        }
        
    } while (key != 27); // ESC para salir
    
    closegraph();
}

void solveNQueens() {
    vector<vector<int>> board(N, vector<int>(N, 0));
    clearScreen();
    cout << "\nResolviendo para un tablero de " << N << "x" << N << "...\n" << endl;
    
    if (solveNQueensUtil(board, 0)) {
        cout << "¡Solucion encontrada! Mostrando tablero..." << endl;
        Sleep(1000); // Pausa de 1 segundo
        drawBoard(board);
    } else {
        cout << "\nNo existe solución para un tablero de " << N << "x" << N << endl;
        cout << "\nPresione cualquier tecla para continuar...";
        _getch();
    }
}

void startInteractiveMode() {
    vector<vector<int>> board(N, vector<int>(N, 0));
    clearScreen();
    cout << "\nModo interactivo - Tablero " << N << "x" << N << "\n" << endl;
    cout << "Debe colocar " << N << " reinas de forma segura" << endl;
    Sleep(2000);
    drawBoard(board);
}

int main() {
    int option;
    do {
        showMenu();
        option = getValidOption();
        
        switch(option) {
            case 1:
                solveNQueens();
                break;
            case 2:
                changeBoardSize();
                break;
            case 3:
                startInteractiveMode();
                break;
            case 4:
                clearScreen();
                cout << "\n¡Gracias por usar el programa!\n" << endl;
                Sleep(1000);
                break;
        }
    } while (option != 4);
    
    return 0;
}
