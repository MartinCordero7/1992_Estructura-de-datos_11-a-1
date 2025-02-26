#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

struct Client {
    string cedula;
    string nombre;
    string zona;
    double lat;
    double lon;
};

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
    string command = "curl -s \"https://nominatim.openstreetmap.org/search?format=json&countrycodes=EC&q=" + encoded + "\" > temp.json";
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

// Calcula la distancia entre dos puntos (en km) usando la fórmula de Haversine
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

// Algoritmo de backtracking para encontrar la ruta con menor distancia total
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
            double d = haversine(fromLat, fromLon, clients[i].lat, clients[i].lon);
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
    out << "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n";
    out << "<meta charset=\"UTF-8\">\n";
    out << "<title>Ruta Óptima de Entregas</title>\n";
    out << "<link rel=\"stylesheet\" href=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.css\"/>\n";
    out << "<script src=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.js\"></script>\n";
    out << "<style>#map { height: 600px; } body { text-align: center; font-family: Arial, sans-serif; }</style>\n";
    out << "</head>\n<body>\n";
    out << "<h2>Ruta Óptima de Entregas</h2>\n";
    out << "<p>Distancia total: " << totalDistance << " km</p>\n";
    out << "<div id=\"map\"></div>\n";
    out << "<script>\n";
    out << "var map = L.map('map').setView([" << localLat << ", " << localLon << "], 13);\n";
    out << "L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {attribution: '&copy; OpenStreetMap contributors'}).addTo(map);\n";
    // Definir arreglo de coordenadas: primer punto es el local y luego las coordenadas de los clientes en orden
    out << "var routeCoords = [\n";
    out << "[" << localLat << ", " << localLon << "],\n";
    for (int idx : route) {
        out << "[" << clients[idx].lat << ", " << clients[idx].lon << "],\n";
    }
    out << "];\n";
    // Agregar marcador para el local
    out << "L.marker([" << localLat << ", " << localLon << "]).addTo(map).bindPopup('Local');\n";
    // Agregar marcadores para los clientes
    for (int idx : route) {
        out << "L.marker([" << clients[idx].lat << ", " << clients[idx].lon << "]).addTo(map).bindPopup('Cliente: " << clients[idx].nombre << "');\n";
    }
    // Dibujar polyline con la ruta
    out << "var polyline = L.polyline(routeCoords, {color: 'blue'}).addTo(map);\n";
    out << "map.fitBounds(polyline.getBounds());\n";
    out << "</script>\n";
    out << "</body>\n</html>\n";
    out.close();
}

// Función que realiza todo el proceso para calcular la ruta de entregas
void calcularRutaEntregas() {
    cout << "Se abrirá una ventana para seleccionar la ubicación del local.\n";
    // Abre la página para seleccionar la ubicación del local
    system("start select_local.html");  // Para Windows; en Linux/Mac usar "xdg-open" o "open"
    cout << "Seleccione la ubicación del local en el mapa y haga clic en 'Confirmar Local'.\n";
    cout << "Cuando se muestren los valores (latitud y longitud), cópielos y péguelo aquí.\n";
    
    double localLat, localLon;
    cout << "Ingrese la latitud del local: ";
    cin >> localLat;
    cout << "Ingrese la longitud del local: ";
    cin >> localLon;
    cin.ignore();
    
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
    // Ejecutar backtracking para hallar la ruta óptima
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
    int opcion;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Registrar cliente (abrir mapa)\n";
        cout << "2. Mostrar clientes registrados\n";
        cout << "3. Calcular ruta de entregas\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar buffer
        switch(opcion) {
            case 1:
                cout << "Abriendo registro de cliente en el navegador...\n";
                system("start map.html");  // Asegúrate de tener tu map.html para registrar clientes
                cout << "Presione ENTER cuando cierre la ventana...\n";
                cin.get();
                break;
            case 2:
                mostrarClientes();
                break;
            case 3:
                calcularRutaEntregas();
                break;
            case 4:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while(opcion != 4);
    return 0;
}
