#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <string>
#include <map>
#include <limits>

class Mapa {
private:
    struct Punto {
        int x, y;
        std::string zona;
        Punto(int x = 0, int y = 0, const std::string& zona = "") 
            : x(x), y(y), zona(zona) {}
    };

    struct Ruta {
        std::vector<int> orden;
        double distanciaTotal;
        Ruta() : distanciaTotal(std::numeric_limits<double>::max()) {}
    };

    std::vector<Punto> puntos;
    std::vector<std::vector<double>> distancias;
    std::map<std::string, int> zonaIndice;
    Punto puntoPartida;

public:
    Mapa();
    void inicializarMapa();
    bool existeZona(const std::string& zona) const;
    std::vector<std::string> calcularRutaOptima(const std::vector<std::string>& zonasEntrega);
    void mostrarMapa() const;
    void mostrarRuta(const std::vector<std::string>& ruta) const;
    
private:
    void backtrackingRuta(std::vector<int>& rutaActual, 
                        std::vector<bool>& visitado, 
                        double distanciaActual, 
                        Ruta& mejorRuta, 
                        int posActual,
                        const std::vector<int>& puntosObjetivo) const;
    double calcularDistancia(const Punto& p1, const Punto& p2) const;
};

#endif