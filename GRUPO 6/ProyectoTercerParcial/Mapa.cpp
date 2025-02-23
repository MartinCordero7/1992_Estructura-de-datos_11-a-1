#include "Mapa.h"
#include <cmath>
#include <iostream>
#include <iomanip>

Mapa::Mapa() {
    inicializarMapa();
}

void Mapa::inicializarMapa() {
    // Inicializar zonas predefinidas
    puntos = {
        {0, 0, "CENTRO"},      // Punto de partida
        {2, 4, "NORTE"},
        {4, 4, "NORESTE"},
        {4, 0, "ESTE"},
        {2, -4, "SUR"},
        {0, -2, "OESTE"}
    };

    // Crear mapeo de zonas a índices
    for (size_t i = 0; i < puntos.size(); i++) {
        zonaIndice[puntos[i].zona] = i;
    }

    // Calcular matriz de distancias
    size_t n = puntos.size();
    distancias.resize(n, std::vector<double>(n));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            distancias[i][j] = calcularDistancia(puntos[i], puntos[j]);
        }
    }
}

bool Mapa::existeZona(const std::string& zona) const {
    return zonaIndice.find(zona) != zonaIndice.end();
}

double Mapa::calcularDistancia(const Punto& p1, const Punto& p2) const {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

void Mapa::mostrarMapa() const {
    std::cout << "\nMapa de Zonas de Entrega:\n\n";
    
    // Crear una matriz para el mapa
    const int MAPA_ALTO = 15;
    const int MAPA_ANCHO = 30;
    std::vector<std::vector<char>> mapaVisual(MAPA_ALTO, std::vector<char>(MAPA_ANCHO, ' '));
    
    // Marcar puntos en el mapa
    for (const auto& punto : puntos) {
        int y = MAPA_ALTO/2 - punto.y;
        int x = MAPA_ANCHO/2 + punto.x*2;
        if (y >= 0 && y < MAPA_ALTO && x >= 0 && x < MAPA_ANCHO) {
            mapaVisual[y][x] = 'O';
        }
    }
    
    // Mostrar el mapa
    std::cout << std::string(MAPA_ANCHO + 2, '-') << '\n';
    for (const auto& fila : mapaVisual) {
        std::cout << '|';
        for (char c : fila) {
            std::cout << c;
        }
        std::cout << "|\n";
    }
    std::cout << std::string(MAPA_ANCHO + 2, '-') << '\n';
    
    // Mostrar leyenda
    std::cout << "\nZonas:\n";
    for (const auto& punto : puntos) {
        std::cout << "O : " << std::setw(10) << punto.zona 
                 << " (" << punto.x << "," << punto.y << ")\n";
    }
}

std::vector<std::string> Mapa::calcularRutaOptima(const std::vector<std::string>& zonasEntrega) {
    std::vector<int> puntosObjetivo;
    puntosObjetivo.push_back(zonaIndice.at("CENTRO")); // Punto de inicio

    for (const auto& zona : zonasEntrega) {
        if (zonaIndice.find(zona) != zonaIndice.end()) {
            puntosObjetivo.push_back(zonaIndice.at(zona));
        }
    }

    std::vector<int> rutaActual;
    std::vector<bool> visitado(puntos.size(), false);
    Ruta mejorRuta;
    
    rutaActual.push_back(zonaIndice.at("CENTRO"));
    visitado[zonaIndice.at("CENTRO")] = true;
    
    backtrackingRuta(rutaActual, visitado, 0, mejorRuta, zonaIndice.at("CENTRO"), puntosObjetivo);
    
    std::vector<std::string> rutaOptima;
    for (int idx : mejorRuta.orden) {
        rutaOptima.push_back(puntos[idx].zona);
    }
    rutaOptima.push_back("CENTRO"); // Volver al punto de inicio
    
    return rutaOptima;
}

void Mapa::mostrarRuta(const std::vector<std::string>& ruta) const {
    mostrarMapa();
    std::cout << "\nRuta óptima de entrega:\n";
    for (size_t i = 0; i < ruta.size(); i++) {
        std::cout << (i+1) << ". " << ruta[i];
        if (i < ruta.size() - 1) std::cout << " -> ";
    }
    std::cout << "\n";
}

void Mapa::backtrackingRuta(std::vector<int>& rutaActual, 
                        std::vector<bool>& visitado, 
                        double distanciaActual, 
                        Ruta& mejorRuta, 
                        int posActual,
                        const std::vector<int>& puntosObjetivo) const {
    if (rutaActual.size() == puntosObjetivo.size()) {
        double distanciaTotal = distanciaActual + distancias[posActual][0];
        if (distanciaTotal < mejorRuta.distanciaTotal) {
            mejorRuta.orden = rutaActual;
            mejorRuta.distanciaTotal = distanciaTotal;
        }
        return;
    }

    for (int siguiente : puntosObjetivo) {
        if (!visitado[siguiente]) {
            visitado[siguiente] = true;
            rutaActual.push_back(siguiente);
            backtrackingRuta(rutaActual, visitado, 
                            distanciaActual + distancias[posActual][siguiente],
                            mejorRuta, siguiente, puntosObjetivo);
            rutaActual.pop_back();
            visitado[siguiente] = false;
        }
    }
}