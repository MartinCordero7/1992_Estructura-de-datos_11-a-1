#ifndef RUTAS_MANAGER_H
#define RUTAS_MANAGER_H

#include "ListaCircularDoble.h"
#include <vector>
#include <functional>
#include <string>

class RutasManager {
private:
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    static double getRoadDistance(double lat1, double lon1, double lat2, double lon2);
    static bool getCoordinates(const std::string &address, double &lat, double &lon);
    static void generarHTMLRuta(double localLat, double localLon, 
        const ListaCircularDoble& lista,
        const std::vector<int>& route,
        const std::vector<std::pair<double, double>>& coordenadas,
        const std::vector<NodoEntrega*>& nodos,
        double totalDistance);

public:
    static void calcularRutaOptima(ListaCircularDoble& lista);
    static bool leerCoordenadasLocal(double& lat, double& lon);
};

#endif