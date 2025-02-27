#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <thread>
#define _USE_MATH_DEFINES

using namespace std;

struct Client {
    string cedula;
    string nombre;
    string zona;
    double lat;
    double lon;
};
// Función para registrar un nuevo cliente
void registrarCliente() {
    string cedula, nombre;
    
    cout << "Ingrese la cédula del cliente: ";
    getline(cin, cedula);
    
    cout << "Ingrese el nombre del cliente: ";
    getline(cin, nombre);
    
    cout << "A continuación se abrirá el mapa para seleccionar la zona de entrega...\n";
    system("start select_zone.html");
    
    cout << "Por favor, seleccione la ubicación en el mapa y presione 'Confirmar'.\n";
    cout << "Presione ENTER cuando haya confirmado la ubicación...";
    cin.get();
    
    // Leer la zona seleccionada del archivo temporal
    ifstream zoneFile("selected_zone.txt");
    string zona;
    if (zoneFile.is_open()) {
        getline(zoneFile, zona);
        zoneFile.close();
        
        // Guardar el cliente en el archivo
        ofstream clientFile("clientes.txt", ios::app);
        if (clientFile.is_open()) {
            clientFile << "Cédula: " << cedula << ", Nombre: " << nombre 
                    << ", Zona de entrega: " << zona << endl;
            clientFile.close();
            cout << "\nCliente registrado exitosamente!\n";
            
            // Limpiar el archivo temporal
            remove("selected_zone.txt");
        } else {
            cout << "Error al guardar el cliente.\n";
        }
    } else {
        cout << "Error: No se pudo obtener la zona seleccionada.\n";
    }
}

// Función para consultar la API de Nominatim y obtener coordenadas a partir de una dirección
bool getCoordinates(const string &address, double &lat, double &lon) {
    // Codificar espacios como %20 (forma básica)
    string encoded = address;
    for (size_t pos = 0; pos < encoded.size(); pos++) {
        if (encoded[pos] == ' ') {
            encoded.replace(pos, 1, "%20");
            pos += 2;
        }
    }
    // Se usa curl para obtener la respuesta JSON
    string command = "curl -s \"https://nominatim.openstreetmap.org/search?format=json&countrycodes=EC&q=" 
                    + encoded + "\" > temp.json";
    system(command.c_str());
    
    ifstream inFile("temp.json");
    if (!inFile) {
        return false;
    }
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    remove("temp.json");
    
    // Extraer "lat" y "lon" del JSON (se asume que hay al menos un resultado)
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
    } catch (...) {
        return false;
    }
    return true;
}

// Función para calcular la distancia en línea recta usando la fórmula de Haversine (como fallback)
double haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0; // Radio de la Tierra en km
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

// Función para obtener la distancia de ruta real (por calles) entre dos puntos usando el API de OSRM
double getRoadDistance(double lat1, double lon1, double lat2, double lon2) {
    // Construir la URL para OSRM (nota: OSRM usa el formato lon,lat)
    string url = "http://router.project-osrm.org/route/v1/driving/";
    url += to_string(lon1) + "," + to_string(lat1) + ";" + to_string(lon2) + "," + to_string(lat2) + "?overview=false";
    string command = "curl -s \"" + url + "\" > route.json";
    system(command.c_str());
    
    ifstream inFile("route.json");
    if (!inFile) return haversine(lat1, lon1, lat2, lon2); // fallback a Haversine si falla
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    remove("route.json");
    
    // Buscar el campo "distance" en el JSON devuelto (en metros)
    size_t pos = content.find("\"distance\":");
    if (pos == string::npos) return haversine(lat1, lon1, lat2, lon2);
    pos += 11; // Moverse después de "distance":
    size_t endPos = content.find(",", pos);
    if (endPos == string::npos) return haversine(lat1, lon1, lat2, lon2);
    string distStr = content.substr(pos, endPos - pos);
    double distance;
    try {
        distance = stod(distStr);
    } catch (...) {
        return haversine(lat1, lon1, lat2, lon2);
    }
    return distance / 1000.0; // Convertir de metros a km
}

// Muestra los clientes registrados leyendo "clientes.txt"
void mostrarClientes() {
    ifstream archivo("clientes.txt");
    if (!archivo) {
        cout << "No hay clientes registrados.\n";
        return;
    }
    cout << "Clientes registrados:\n";
    string linea;
    while(getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
}

// Lee y parsea los clientes del archivo "clientes.txt"
vector<Client> leerClientes() {
    vector<Client> clients;
    ifstream archivo("clientes.txt");
    if (!archivo) {
        return clients;
    }
    string linea;
    while(getline(archivo, linea)) {
        // Formato esperado: 
        // "Cédula: {cedula}, Nombre: {nombre}, Zona de entrega: {zona}"
        Client cli;
        size_t pos1 = linea.find("Cédula: ");
        if (pos1 == string::npos) continue;
        pos1 += 8;  // "Cédula: " tiene 8 caracteres
        size_t pos2 = linea.find(",", pos1);
        if (pos2 == string::npos) continue;
        cli.cedula = linea.substr(pos1, pos2 - pos1);
        
        size_t pos3 = linea.find("Nombre: ", pos2);
        if (pos3 == string::npos) continue;
        pos3 += 8;  // "Nombre: " tiene 8 caracteres
        size_t pos4 = linea.find(",", pos3);
        if (pos4 == string::npos) continue;
        cli.nombre = linea.substr(pos3, pos4 - pos3);
        
        size_t pos5 = linea.find("Zona de entrega: ", pos4);
        if (pos5 == string::npos) continue;
        pos5 += 17; // "Zona de entrega: " tiene 17 caracteres
        cli.zona = linea.substr(pos5);
        
        clients.push_back(cli);
    }
    archivo.close();
    return clients;
}

// Variables globales para almacenar la mejor solución encontrada en el backtracking
double bestDistance = 1e9;
vector<int> bestRoute;

// Algoritmo de backtracking para encontrar la ruta con menor distancia total usando distancias por carretera
void backtrack(vector<int>& route, vector<bool>& used, double currentDistance,
            double startLat, double startLon, const vector<Client>& clients) {
    int n = clients.size();
    if(route.size() == n) {
        if(currentDistance < bestDistance) {
            bestDistance = currentDistance;
            bestRoute = route;
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        if(!used[i]) {
            double fromLat, fromLon;
            if(route.empty()) {
                fromLat = startLat;
                fromLon = startLon;
            } else {
                int lastIndex = route.back();
                fromLat = clients[lastIndex].lat;
                fromLon = clients[lastIndex].lon;
            }
            // Usamos getRoadDistance en lugar de haversine
            double d = getRoadDistance(fromLat, fromLon, clients[i].lat, clients[i].lon);
            if(currentDistance + d < bestDistance) { // poda
                used[i] = true;
                route.push_back(i);
                backtrack(route, used, currentDistance + d, startLat, startLon, clients);
                route.pop_back();
                used[i] = false;
            }
        }
    }
}

// Función para generar el archivo HTML que muestra la ruta en el mapa usando Leaflet
void generarHTMLRuta(const double localLat, const double localLon,
        const vector<Client>& clients, const vector<int>& route,
        double totalDistance) {
    ofstream out("route_result.html");
    if (!out) {
    cout << "No se pudo generar el archivo de resultado.\n";
    return;
    }
    // Generamos la URL de OSRM con todos los puntos (en formato lon,lat)
    string osrmURL = "http://router.project-osrm.org/route/v1/driving/";
    // Primer punto: local (recordar: OSRM usa lon,lat)
    osrmURL += to_string(localLon) + "," + to_string(localLat);
    // Luego, cada cliente en el orden de la ruta
    for (int idx : route) {
    osrmURL += ";" + to_string(clients[idx].lon) + "," + to_string(clients[idx].lat);
    }
    osrmURL += "?overview=full&geometries=polyline";

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
    out << "    // Función para decodificar una cadena polyline (algoritmo de Google)\n";
    out << "    function decodePolyline(encoded) {\n";
    out << "      var points = [];\n";
    out << "      var index = 0, len = encoded.length;\n";
    out << "      var lat = 0, lng = 0;\n";
    out << "      while (index < len) {\n";
    out << "        var b, shift = 0, result = 0;\n";
    out << "        do {\n";
    out << "          b = encoded.charCodeAt(index++) - 63;\n";
    out << "          result |= (b & 0x1f) << shift;\n";
    out << "          shift += 5;\n";
    out << "        } while (b >= 0x20);\n";
    out << "        var dlat = ((result & 1) ? ~(result >> 1) : (result >> 1));\n";
    out << "        lat += dlat;\n";
    out << "        shift = 0;\n";
    out << "        result = 0;\n";
    out << "        do {\n";
    out << "          b = encoded.charCodeAt(index++) - 63;\n";
    out << "          result |= (b & 0x1f) << shift;\n";
    out << "          shift += 5;\n";
    out << "        } while (b >= 0x20);\n";
    out << "        var dlng = ((result & 1) ? ~(result >> 1) : (result >> 1));\n";
    out << "        lng += dlng;\n";
    out << "        points.push([lat / 1e5, lng / 1e5]);\n";
    out << "      }\n";
    out << "      return points;\n";
    out << "    }\n\n";

    // Inicializar el mapa en la ubicación del local
    out << "    var map = L.map('map').setView([" << localLat << ", " << localLon << "], 13);\n";
    out << "    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {attribution: '&copy; OpenStreetMap contributors'}).addTo(map);\n";
    // Marcador para el local
    out << "    L.marker([" << localLat << ", " << localLon << "]).addTo(map).bindPopup('Local');\n";

    // Agregar marcadores para los clientes en la ruta
    for (int idx : route) {
    out << "    L.marker([" << clients[idx].lat << ", " << clients[idx].lon << "]).addTo(map).bindPopup('Cliente: " << clients[idx].nombre << "');\n";
    }

    // Obtener la ruta real (geométricamente) de OSRM
    out << "    fetch('" << osrmURL << "')\n";
    out << "      .then(response => response.json())\n";
    out << "      .then(data => {\n";
    out << "         var encoded = data.routes[0].geometry;\n";
    out << "         var routeCoords = decodePolyline(encoded);\n";
    out << "         var polyline = L.polyline(routeCoords, {color: 'blue'}).addTo(map);\n";
    out << "         map.fitBounds(polyline.getBounds());\n";
    out << "      })\n";
    out << "      .catch(error => console.error('Error obteniendo la ruta:', error));\n";

    out << "  </script>\n";
    out << "</body>\n</html>\n";
    out.close();
}

// Función que realiza todo el proceso para calcular la ruta de entregas
void calcularRutaEntregas() {
    cout << "Se abrirá una ventana para seleccionar la ubicación del local.\n";
    system("start select_local.html");
    cout << "Por favor, seleccione la ubicación del local en el mapa y presione 'Confirmar Local'.\n";
    cout << "Esperando confirmación...\n";
    
    double localLat, localLon;
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
                    localLat = stod(coords.substr(0, comma));
                    localLon = stod(coords.substr(comma + 1));
                    coordsRead = true;
                } catch(...) {
                    cout << "Error al leer las coordenadas.\n";
                    return;
                }
            }
        }
        if(!coordsRead) {
            Sleep(1000); // Using Windows.h Sleep instead of chrono
        }
    }
    
    if(!coordsRead) {
        cout << "No se pudo obtener la ubicación del local.\n";
        return;
    }
    
    vector<Client> clients = leerClientes();
    if (clients.empty()) {
        cout << "No hay clientes registrados para calcular la ruta.\n";
        return;
    }
    // Obtener coordenadas para cada zona de entrega de los clientes
    for (auto &cli : clients) {
        if (!getCoordinates(cli.zona, cli.lat, cli.lon)) {
            cout << "No se pudieron obtener coordenadas para la zona: " << cli.zona << "\n";
            return;
        }
    }
    // Ejecutar backtracking para hallar la ruta óptima usando distancias reales por carretera
    bestDistance = 1e9;
    bestRoute.clear();
    vector<int> route;
    vector<bool> used(clients.size(), false);
    backtrack(route, used, 0, localLat, localLon, clients);
    
    if(bestRoute.empty()) {
        cout << "No se encontró una ruta de entrega.\n";
        return;
    }
    
    cout << "\nRuta óptima de entregas:\n";
    cout << "Punto de inicio (Local): (" << localLat << ", " << localLon << ")\n";
    for (int idx : bestRoute) {
        cout << "-> " << clients[idx].zona << " (Cliente: " << clients[idx].nombre << ")\n";
    }
    cout << "\nDistancia total: " << bestDistance << " km\n";
    
    // Generar archivo HTML que muestra la ruta en el mapa
    generarHTMLRuta(localLat, localLon, clients, bestRoute, bestDistance);
    system("start route_result.html");
}

int main() {
    // Verificar que el servidor Flask esté corriendo
    cout << "Verificando conexión con el servidor...\n";
    string check_command = "curl -s http://localhost:5000/get_clients > nul 2>&1";
    if (system(check_command.c_str()) != 0) {
        cout << "Error: El servidor no está en ejecución.\n";
        cout << "Por favor, ejecute 'python server.py' en una terminal separada.\n";
        return 1;
    }

    int opcion;
    do {
        cout << "\n===== SISTEMA DE GESTIÓN DE ENTREGAS =====\n";
        cout << "1. Registrar nuevo cliente\n";
        cout << "2. Mostrar clientes registrados\n";
        cout << "3. Calcular ruta óptima de entregas\n";
        cout << "4. Salir\n";
        cout << "Ingrese su opción: ";
        
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1:
                registrarCliente();
                break;
            case 2:
                mostrarClientes();
                break;
            case 3:
                calcularRutaEntregas();
                break;
            case 4:
                cout << "Gracias por usar el sistema.\n";
                break;
            default:
                cout << "Opción no válida. Por favor intente de nuevo.\n";
        }
    } while(opcion != 4);

    return 0;
}


