#include "reina.h"
#include <cmath>
#include <cstdlib>

bool esvalido(std::vector<int>& reinas, int filas, int col) {
    for (int i = 0; i < filas; i++) {
        if (reinas[i] == col || abs(i - filas) == abs(reinas[i] - col))
            return false;
    }
    return true;
}

bool solveNreinas(std::vector<int>& reinas, int filas, int N) {
    if (filas == N) {
        return true;
    }

    for (int col = 0; col < N; col++) {
        if (esvalido(reinas, filas, col)) {
            reinas[filas] = col;
            if (solveNreinas(reinas, filas + 1, N))
                return true;
        }
    }

    return false;
}
