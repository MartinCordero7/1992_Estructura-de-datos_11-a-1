/**********
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Altamirano Xavier, Cordero Martin, Oña Isaac
 * FECHA CREACION: Miercoles,  12 de Febrero de 2025
 * FECHA MODIFICACION: Miercoles, 12 de Febrero de 2025
 * PROYECTO: N reinas
 * Nivel: TERCERO     NRC: 1992
 ***********/
#include "n_reinas.h"
#include <vector>

using namespace std;

bool isSafe(vector<vector<int>>& board, int row, int col) {
    // Verifica la fila hacia la izquierda
    for (int i = 0; i < col; ++i)
        if (board[row][i])
            return false;

    // Verifica diagonal superior izquierda
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
        if (board[i][j])
            return false;

    // Verifica diagonal inferior izquierda
    for (int i = row, j = col; i < N && j >= 0; ++i, --j)
        if (board[i][j])
            return false;

    return true;
}

bool solveNQueensUtil(vector<vector<int>>& board, int col) {
    // Caso base: si todas las reinas están colocadas
    if (col >= N)
        return true;

    // Backtracking: intenta colocar la reina en cada fila de la columna actual
    for (int i = 0; i < N; ++i) {
        // Verifica si es seguro colocar la reina en board[i][col]
        if (isSafe(board, i, col)) {
            // Coloca la reina
            board[i][col] = 1;
            
            // Recursivamente intenta colocar el resto de reinas
            if (solveNQueensUtil(board, col + 1))
                return true;
            
            // Si colocar la reina en board[i][col] no lleva a una solución,
            // entonces quita la reina de board[i][col] (backtrack)
            board[i][col] = 0;
        }
    }

    // Si no se puede colocar una reina en ninguna fila de esta columna
    return false;
}
