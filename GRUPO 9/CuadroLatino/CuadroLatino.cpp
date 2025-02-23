#include "CuadroLatino.h"
#include <stdexcept> // Necesario para std::invalid_argument

CuadroLatino::CuadroLatino(int size) : n(size) {
    try {
        matriz.resize(n, std::vector<int>(n, 0));
    } catch (const std::exception& e) {
        throw std::runtime_error("Error al inicializar la matriz: " + std::string(e.what()));
    }
}

void CuadroLatino::generar() {
    try {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                matriz[i][j] = ((i + j) % n) + 1;
    } catch (const std::exception& e) {
        throw std::runtime_error("Error al generar el cuadro latino: " + std::string(e.what()));
    }
}

std::vector<std::vector<int>> CuadroLatino::getMatriz() const {
    return matriz;
}
