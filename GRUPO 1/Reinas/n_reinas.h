/**********
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Altamirano Xavier, Cordero Martin, Oña Isaac
 * FECHA CREACION: Miercoles,  12 de Febrero de 2025
 * FECHA MODIFICACION: Miercoles, 12 de Febrero de 2025
 * PROYECTO: N reinas
 * Nivel: TERCERO     NRC: 1992
 ***********/
#ifndef N_REINAS_H
#define N_REINAS_H

#include <vector>

using namespace std;

extern int N; // Ahora N es una variable modificable

bool isSafe(vector<vector<int>>& board, int row, int col);
bool solveNQueensUtil(vector<vector<int>>& board, int col);

// Nuevas funciones para el movimiento
bool isValidMove(vector<vector<int>>& board, int fromRow, int fromCol, int toRow, int toCol);
void highlightSelectedQueen(int x, int y, int cellSize);
bool isSafeAfterMove(vector<vector<int>>& board, int toRow, int toCol);

#endif // N_REINAS_H
