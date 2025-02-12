#include "n_reinas.cpp"

using namespace std;

int main() {
    int N = obtenerN();  // Obtener un valor válido para N

    int tablero[MAX_N][MAX_N] = {0}; // Inicializar tablero con ceros

    if (resolverNReinas(tablero, 0, N)) {
        dibujarTablero(tablero, N); // Mostrar la solución gráficamente
    } else {
        cout << "No hay solucion para N = " << N << endl;
    }

    return 0;
}