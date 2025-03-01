#define _USE_MATH_DEFINES
#include "RutasManager.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <windows.h>
#include "Entrega.h"
#include "Cliente.h"
#include <fstream>
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
    string url = "http://router.project-osrm.org/route/v1/driving/";
    url += to_string(lon1) + "," + to_string(lat1) + ";" + to_string(lon2) + "," + to_string(lat2) + "?overview=false";
    string command = "curl -s \"" + url + "\" > route.json";
    system(command.c_str());
    
    ifstream inFile("route.json");
    if (!inFile) return haversine(lat1, lon1, lat2, lon2);
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    remove("route.json");
    
    size_t pos = content.find("\"distance\":");
    if (pos == string::npos) return haversine(lat1, lon1, lat2, lon2);
    pos += 11;
    size_t endPos = content.find(",", pos);
    if (endPos == string::npos) return haversine(lat1, lon1, lat2, lon2);
    
    string distStr = content.substr(pos, endPos - pos);
    try {
        double distance = stod(distStr);
        return distance / 1000.0;
    } catch (...) {
        return haversine(lat1, lon1, lat2, lon2);
    }
}

bool RutasManager::getCoordinates(const string &address, double &lat, double &lon) {
    string encoded = address;
    for (size_t pos = 0; pos < encoded.size(); pos++) {
        if (encoded[pos] == ' ') {
            encoded.replace(pos, 1, "%20");
            pos += 2;
        }
    }
    
    string command = "curl -s \"https://nominatim.openstreetmap.org/search?format=json&countrycodes=EC&q=" 
                    + encoded + "\" > temp.json";
    system(command.c_str());
    
    ifstream inFile("temp.json");
    if (!inFile) return false;
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    remove("temp.json");
    
    size_t latPos = content.find("\"lat\":\"");
    if (latPos == string::npos) return false;
    latPos += 7;
    size_t latEnd = content.find("\"", latPos);
    if (latEnd == string::npos) return false;
    string latStr = content.substr(latPos, latEnd - latPos);
    
    size_t lonPos = content.find("\"lon\":\"", latEnd);
    if (lonPos == string::npos) return false;
    lonPos += 7;
    size_t lonEnd = content.find("\"", lonPos);
    if (lonEnd == string::npos) return false;
    string lonStr = content.substr(lonPos, lonEnd - lonPos);
    
    try {
        lat = stod(latStr);
        lon = stod(lonStr);
        return true;
    } catch (...) {
        return false;
    }
}

void RutasManager::generarHTMLRuta(double localLat, double localLon, 
    const ListaCircularDoble& lista,
    const vector<int>& route,
    const vector<pair<double, double>>& coordenadas,
    const vector<NodoEntrega*>& nodos,
    double totalDistance) {
        ofstream out("api_mapa/route_result.html");
        if (!out) {
            cout << "No se pudo generar el archivo de resultado.\n";
            return;
        }
    
        out << "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n";
        out << "  <meta charset=\"UTF-8\">\n";
        out << "  <title>Ruta Óptima de Entregas</title>\n";
        out << "  <link rel=\"stylesheet\" href=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.css\"/>\n";
        out << "  <script src=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.js\"></script>\n";
        out << "  <style>#map { height: 600px; } body { text-align: center; font-family: Arial, sans-serif; }</style>\n";
        out << "</head>\n<body>\n";
        out << "  <h2>Ruta Óptima de Entregas</h2>\n";
        out << "  <p>Distancia total: " << totalDistance << " km</p>\n";
        out << "  <div id=\"map\"></div>\n";
        out << "  <script>\n";
    
        // Agregar la función completa de decodificación de polyline
        out << "    function decodePolyline(str) {\n";
        out << "        var points = [], lat = 0, lon = 0;\n";
        out << "        for(var i = 0; i < str.length;) {\n";
        out << "            var shift = 0, result = 0;\n";
        out << "            do {\n";
        out << "                var b = str.charCodeAt(i++) - 63;\n";
        out << "                result |= (b & 0x1f) << shift;\n";
        out << "                shift += 5;\n";
        out << "            } while(b >= 0x20);\n";
        out << "            lat += ((result & 1) ? ~(result >> 1) : (result >> 1));\n";
        out << "            shift = 0; result = 0;\n";
        out << "            do {\n";
        out << "                var b = str.charCodeAt(i++) - 63;\n";
        out << "                result |= (b & 0x1f) << shift;\n";
        out << "                shift += 5;\n";
        out << "            } while(b >= 0x20);\n";
        out << "            lon += ((result & 1) ? ~(result >> 1) : (result >> 1));\n";
        out << "            points.push([lat * 1e-5, lon * 1e-5]);\n";
        out << "        }\n";
        out << "        return points;\n";
        out << "    }\n\n";
        
        // Inicializar mapa
        out << "    var map = L.map('map').setView([" << localLat << ", " << localLon << "], 13);\n";
        out << "    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', "
            << "{attribution: '&copy; OpenStreetMap contributors'}).addTo(map);\n";
    
        // Generar URL de OSRM para la ruta completa
        string osrmURL = "http://router.project-osrm.org/route/v1/driving/";
        osrmURL += to_string(localLon) + "," + to_string(localLat);
        
        // Agregar marcador del local
        out << "    L.marker([" << localLat << ", " << localLon << "]).addTo(map).bindPopup('Local');\n";
        
        // Agregar marcadores y construir URL de la ruta
        for(int idx : route) {
            osrmURL += ";" + to_string(coordenadas[idx].second) + "," + to_string(coordenadas[idx].first);
            out << "    L.marker([" << coordenadas[idx].first << ", " << coordenadas[idx].second 
                << "]).addTo(map).bindPopup('Cliente: " << nodos[idx]->entrega.cliente.nombre << "');\n";
        }
        
        osrmURL += "?overview=full&geometries=polyline";
        
        // Obtener y dibujar la ruta real por carreteras usando OSRM
        out << "    fetch('" << osrmURL << "')\n";
        out << "      .then(response => response.json())\n";
        out << "      .then(data => {\n";
        out << "         var routeCoords = decodePolyline(data.routes[0].geometry);\n";
        out << "         var polyline = L.polyline(routeCoords, {color: 'blue', weight: 4}).addTo(map);\n";
        out << "         map.fitBounds(polyline.getBounds());\n";
        out << "      })\n";
        out << "      .catch(error => console.error('Error:', error));\n";
        
        out << "  </script>\n</body>\n</html>\n";
        out.close();
}

bool RutasManager::leerCoordenadasLocal(double& lat, double& lon) {
    bool coordsRead = false;
    for(int i = 0; i < 30 && !coordsRead; i++) {
        ifstream coordsFile("local_coords.txt");
        if(coordsFile.is_open()) {
            string coords;
            getline(coordsFile, coords);
            coordsFile.close();
            remove("local_coords.txt");
            
            size_t comma = coords.find(',');
            if(comma != string::npos) {
                try {
                    lat = stod(coords.substr(0, comma));
                    lon = stod(coords.substr(comma + 1));
                    coordsRead = true;
                } catch(...) {
                    cout << "Error al leer coordenadas.\n";
                }
            }
        }
        if(!coordsRead) Sleep(1000); // Esperar 1 segundo antes de intentar de nuevo
    }
    return coordsRead;
}

void RutasManager::calcularRutaOptima(ListaCircularDoble& lista) {
    double localLat, localLon;
    if (!leerCoordenadasLocal(localLat, localLon)) {
        cout << "No se pudo obtener la ubicación del local.\n";
        return;
    }

    // Obtener coordenadas de todas las entregas usando la lista circular
    vector<pair<double, double>> coordenadas;
    vector<NodoEntrega*> nodos;
    NodoEntrega* actual = lista.cabeza;
    
    do {
        double lat, lon;
        if (getCoordinates(actual->entrega.zona, lat, lon)) {
            coordenadas.push_back({lat, lon});
            nodos.push_back(actual);
            cout << "Coordenadas obtenidas para: " << actual->entrega.zona 
                << " (" << lat << ", " << lon << ")\n";
        } else {
            cout << "No se pudieron obtener coordenadas para: " << actual->entrega.zona << "\n";
        }
        actual = actual->siguiente;
    } while(actual != lista.cabeza);

    if(coordenadas.empty()) {
        cout << "No se pudieron obtener coordenadas para ninguna entrega.\n";
        return;
    }

    // Variables para la mejor ruta
    vector<int> bestRoute;
    double bestDistance = 1e9;
    vector<int> currentRoute;
    vector<bool> used(coordenadas.size(), false);

    // Función recursiva de backtracking para encontrar la ruta óptima
    function<void(double)> backtrack = [&](double currentDist) {
        // Si hemos visitado todos los puntos, verificamos si es la mejor ruta
        if(currentRoute.size() == coordenadas.size()) {
            // Calcular distancia de regreso al local si es necesario
            double finalDist = currentDist;
            if (!currentRoute.empty()) {
                int lastIdx = currentRoute.back();
                finalDist += getRoadDistance(
                    coordenadas[lastIdx].first, coordenadas[lastIdx].second,
                    localLat, localLon
                );
            }
            
            if(finalDist < bestDistance) {
                bestDistance = finalDist;
                bestRoute = currentRoute;
                cout << "Nueva mejor ruta encontrada: " << finalDist << " km\n";
            }
            return;
        }

        // Probar cada punto no visitado como siguiente destino
        for(size_t i = 0; i < coordenadas.size(); i++) {
            if(!used[i]) {
                // Calcular distancia desde el punto actual
                double fromLat = currentRoute.empty() ? localLat : coordenadas[currentRoute.back()].first;
                double fromLon = currentRoute.empty() ? localLon : coordenadas[currentRoute.back()].second;
                
                // Obtener distancia real por carretera usando OSRM
                double dist = getRoadDistance(fromLat, fromLon, coordenadas[i].first, coordenadas[i].second);
                
                // Si esta ruta podría ser mejor que la mejor actual, explorarla
                if(currentDist + dist < bestDistance) {
                    used[i] = true;
                    currentRoute.push_back(i);
                    backtrack(currentDist + dist);
                    currentRoute.pop_back();
                    used[i] = false;
                }
            }
        }
    };

    cout << "Calculando ruta óptima...\n";
    backtrack(0);

    if(!bestRoute.empty()) {
        cout << "\nRuta óptima de entregas encontrada:\n";
        cout << "Punto de inicio (Local): (" << localLat << ", " << localLon << ")\n";
        
        // Mostrar la ruta paso a paso
        for(size_t i = 0; i < bestRoute.size(); i++) {
            int idx = bestRoute[i];
            cout << i + 1 << ". Cliente: " << nodos[idx]->entrega.cliente.nombre 
                 << " (" << nodos[idx]->entrega.zona << ")\n";
        }
        
        // Generar visualización HTML de la ruta
        generarHTMLRuta(localLat, localLon, lista, bestRoute, coordenadas, nodos, bestDistance);
        system("start api_mapa/route_result.html");
        
        cout << "\nDistancia total de la ruta: " << bestDistance << " km\n";
    } else {
        cout << "No se pudo calcular una ruta óptima.\n";
    }
}