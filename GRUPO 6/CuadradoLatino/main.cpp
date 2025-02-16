#include <iostream>
#include "CuadroLatino.cpp"

using namespace std;

int main() {
    int n = obtenerEnteroPositivo();
    
    int** matriz = new int*[n];
    crearMatriz(matriz, n);
    
    llenarCuadro(matriz, n);
    
    cout << "\nCuadro Latino:\n";
    imprimirMatriz(matriz, n);
    
    visualizarCuadro(matriz, n);
    
    liberarMatriz(matriz, n);
    delete[] matriz;

    return 0;
}
