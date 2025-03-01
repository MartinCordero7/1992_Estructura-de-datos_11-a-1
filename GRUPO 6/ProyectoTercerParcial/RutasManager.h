#ifndef RUTAS_MANAGER_H
#define RUTAS_MANAGER_H

#include "ListaCircularDoble.h"
#include <vector>
#include <functional>

class RutasManager {
private:
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    static double getRoadDistance(double lat1, double lon1, double lat2, double lon2);
    static bool getCoordinates(const std::string &address, double &lat, double &lon);
    static void generarHTMLRuta(double localLat, double localLon, 
                               const ListaCircularDoble& lista,
                               const std::vector<int>& route,
                               double totalDistance);

public:
    static bool obtenerCoordenadas(const std::string& zona, double& lat, double& lon);
    static void calcularRutaOptima(ListaCircularDoble& lista);
    static bool leerCoordenadasLocal(double& lat, double& lon);
};

#endif