#include "RutasManager.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <iostream>
#include <conio.h> 
#include <vector>
#include <sstream>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <functional>


double RutasManager::haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0;
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

double RutasManager::getRoadDistance(double lat1, double lon1, double lat2, double lon2) {
    // ... código existente de getRoadDistance ...
}

bool RutasManager::getCoordinates(const string &address, double &lat, double &lon) {
    // ... código existente de getCoordinates ...
}

void RutasManager::generarHTMLRuta(double localLat, double localLon, 
                                  const ListaCircularDoble& lista,
                                  const vector<int>& route,
                                  double totalDistance) {
    // ... código existente de generarHTMLRuta ...
}

bool RutasManager::leerCoordenadasLocal(double& lat, double& lon) {
    bool coordsRead = false;
    for(int i = 0; i < 30 && !coordsRead; i++) {
        ifstream coordsFile("local_coords.txt");
        if(coordsFile.is_open()) {
            // ... código existente de lectura de coordenadas ...
        }
        if(!coordsRead) Sleep(1000);
    }
    return coordsRead;
}

void RutasManager::calcularRutaOptima(ListaCircularDoble& lista) {
    // ... código existente de cálculo de ruta óptima ...
}