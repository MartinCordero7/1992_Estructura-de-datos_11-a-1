/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Menu principal                                           *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include "Menu.h"
#include "BackupManager.cpp"
#include <iostream>
#include "Validaciones.cpp" 
#include <conio.h> 
#include <vector>
#include <sstream>
#include <ctime>
#include "pdf_generator.h"
#include <windows.h>
#include "Entrega.h"
#include "Cliente.h"
#include <fstream>
#include <iomanip>
#include <functional>

using namespace std;

std::wstring getExecutablePath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH); 
    std::wstring path(buffer);
    return path.substr(0, path.find_last_of(L"\\/"));
}

// Helper functions
double haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0;
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

double getRoadDistance(double lat1, double lon1, double lat2, double lon2) {
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

bool getCoordinates(const string &address, double &lat, double &lon) {
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

void generarHTMLRuta(double localLat, double localLon, 
                     const ListaCircularDoble& lista,
                     const vector<int>& route,
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
    
    // Initialize map
    out << "    var map = L.map('map').setView([" << localLat << ", " << localLon << "], 13);\n";
    out << "    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {attribution: '&copy; OpenStreetMap contributors'}).addTo(map);\n";
    
    // Add markers
    out << "    L.marker([" << localLat << ", " << localLon << "]).addTo(map).bindPopup('Local');\n";
    
    // Add delivery points
    NodoEntrega* actual = lista.cabeza;
    int count = 0;
    do {
        double lat, lon;
        if (getCoordinates(actual->entrega.zona, lat, lon)) {
            out << "    L.marker([" << lat << ", " << lon << "]).addTo(map)"
                << ".bindPopup('Cliente: " << actual->entrega.cliente.nombre << "');\n";
        }
        actual = actual->siguiente;
        count++;
    } while (actual != lista.cabeza);

    out << "  </script>\n</body>\n</html>\n";
    out.close();
}


void mostrarMenu(ListaCircularDoble& lista) {
    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Registrar entrega");
    menuOpciones.insertar("Buscar entrega");
    menuOpciones.insertar("Eliminar entrega");
    menuOpciones.insertar("Ver todas las entregas");
    menuOpciones.insertar("Realizar entregas");
    menuOpciones.insertar("Exportar entregas a PDF");
    menuOpciones.insertar("Crear backup");
    menuOpciones.insertar("Restaurar backup");
    menuOpciones.insertar("Salir");

    int seleccion = 0;

    while (true) {
        system("cls");
        cout << "=== Menu Principal ===\n";
        NodoMenu* actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++) {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<\n";
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72) { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        } else if (tecla == 80) { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        } else if (tecla == '\r') { // Enter
            string opcionSeleccionada = menuOpciones.obtenerOpcion(seleccion);

            if (opcionSeleccionada == "Registrar entrega") {
                string nombreCliente, cedula, zona;
                
                cout << "Ingrese nombre del cliente: ";
                getline(cin, nombreCliente);
                if (nombreCliente.empty()) continue;
                
                cout << "Ingrese cédula del cliente: ";
                getline(cin, cedula);
                if (cedula.empty()) continue;
                
                cout << "Seleccionando zona de entrega...\n";
                system("start api_mapa/select_zone.html");
                
                cout << "Por favor, seleccione la ubicación en el mapa y presione 'Confirmar'.\n";
                cout << "Presione ENTER cuando haya confirmado la ubicación...";
                cin.get();
                
                // Esperar hasta que el archivo exista o timeout
                bool zoneFound = false;
                for(int i = 0; i < 30 && !zoneFound; i++) {
                    ifstream zoneFile("selected_zone.txt");
                    if (zoneFile.is_open()) {
                        getline(zoneFile, zona);
                        zoneFile.close();
                        remove("selected_zone.txt");
                        zoneFound = true;
                        
                        Cliente cliente(nombreCliente, cedula);
                        Entrega entrega(cliente, zona);
                        lista.agregarEntrega(entrega);
                        cout << "\nEntrega registrada exitosamente!\n";
                    } else {
                        Sleep(1000); // Esperar 1 segundo antes de intentar de nuevo
                    }
                }
                
                if (!zoneFound) {
                    cout << "Error: No se pudo obtener la zona seleccionada.\n";
                }
            }
            else if (opcionSeleccionada == "Buscar entrega") {
                string cedula;
                cout << "Ingrese la cédula del cliente a buscar: ";
                getline(cin, cedula);
                if (cedula.empty()) continue;
                
                NodoEntrega* encontrado = lista.buscarEntregaPorCedula(cedula);
                if (encontrado) {
                    cout << "\nEntrega encontrada:\n";
                    cout << "Nombre: " << encontrado->entrega.cliente.nombre << "\n";
                    cout << "Cédula: " << encontrado->entrega.cliente.cedula << "\n";
                    cout << "Zona: " << encontrado->entrega.zona << "\n";
                } else {
                    cout << "No se encontró ninguna entrega con esa cédula.\n";
                }
            }
            else if (opcionSeleccionada == "Eliminar entrega") {
                string cedula;
                cout << "Ingrese la cédula del cliente cuya entrega desea eliminar: ";
                getline(cin, cedula);
                if (cedula.empty()) continue;
                
                if (lista.eliminarEntrega(cedula)) {
                    cout << "Entrega eliminada exitosamente.\n";
                } else {
                    cout << "No se encontró ninguna entrega con esa cédula.\n";
                }
            }
            else if (opcionSeleccionada == "Ver todas las entregas") {
                if (lista.estaVacia()) {
                    cout << "\nNo hay entregas registradas.\n";
                } else {
                    cout << "\n=== LISTA DE ENTREGAS ===\n";
                    cout << left << setw(30) << "Cliente"
                         << setw(15) << "Cédula"
                         << setw(30) << "Zona" << endl;
                    cout << string(75, '-') << endl;
            
                    NodoEntrega* actual = lista.cabeza;
                    do {
                        cout << left << setw(30) << actual->entrega.cliente.nombre
                             << setw(15) << actual->entrega.cliente.cedula
                             << setw(30) << actual->entrega.zona << endl;
                        actual = actual->siguiente;
                    } while (actual != lista.cabeza);
                    cout << string(75, '-') << endl;
                }
            }
            // En Menu.cpp, reemplaza la sección de "Realizar entregas" con esto:
            else if (opcionSeleccionada == "Realizar entregas") {
                if (lista.estaVacia()) {
                    cout << "No hay entregas pendientes.\n";
                    continue;
                }
            
                cout << "Se abrirá una ventana para seleccionar la ubicación del local.\n";
                system("start api_mapa/select_local.html");
                cout << "Por favor, seleccione la ubicación del local en el mapa y presione 'Confirmar Local'.\n";
                cout << "Esperando confirmación...\n";
                
                double localLat, localLon;
                bool coordsRead = false;
                
                // Leer coordenadas del local
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
                                cout << "Error al leer coordenadas.\n";
                            }
                        }
                    }
                    if(!coordsRead) Sleep(1000);
                }
                
                if(!coordsRead) {
                    cout << "No se pudo obtener la ubicación del local.\n";
                    continue;
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
                    } else {
                        cout << "No se pudieron obtener coordenadas para: " << actual->entrega.zona << "\n";
                    }
                    actual = actual->siguiente;
                } while(actual != lista.cabeza);
            
                if(coordenadas.empty()) {
                    cout << "No se pudieron obtener coordenadas para ninguna entrega.\n";
                    continue;
                }
            
                // Calcular ruta óptima usando backtracking con distancias reales por carretera
                vector<int> bestRoute;
                double bestDistance = 1e9;
                vector<int> currentRoute;
                vector<bool> used(coordenadas.size(), false);
            
                function<void(double)> backtrack = [&](double currentDist) {
                    if(currentRoute.size() == coordenadas.size()) {
                        if(currentDist < bestDistance) {
                            bestDistance = currentDist;
                            bestRoute = currentRoute;
                        }
                        return;
                    }
            
                    for(size_t i = 0; i < coordenadas.size(); i++) {
                        if(!used[i]) {
                            double fromLat = currentRoute.empty() ? localLat : coordenadas[currentRoute.back()].first;
                            double fromLon = currentRoute.empty() ? localLon : coordenadas[currentRoute.back()].second;
                            
                            // Usar getRoadDistance para obtener la distancia real por carreteras
                            double dist = getRoadDistance(fromLat, fromLon, coordenadas[i].first, coordenadas[i].second);
                            
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
            
                backtrack(0);
            
                if(!bestRoute.empty()) {
                    cout << "\nRuta óptima de entregas:\n";
                    cout << "Punto de inicio (Local): (" << localLat << ", " << localLon << ")\n";
                    
                    ofstream out("api_mapa/route_result.html");
                    if(out.is_open()) {
                        out << "<!DOCTYPE html>\n<html lang=\"es\">\n<head>\n";
                        out << "  <meta charset=\"UTF-8\">\n";
                        out << "  <title>Ruta Óptima de Entregas</title>\n";
                        out << "  <link rel=\"stylesheet\" href=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.css\"/>\n";
                        out << "  <script src=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.js\"></script>\n";
                        out << "  <style>#map { height: 600px; } body { text-align: center; font-family: Arial, sans-serif; }</style>\n";
                        out << "</head>\n<body>\n";
                        out << "  <h2>Ruta Óptima de Entregas</h2>\n";
                        out << "  <p>Distancia total: " << bestDistance << " km</p>\n";
                        out << "  <div id=\"map\"></div>\n";
                        out << "  <script>\n";
            
                        // Función para decodificar polyline
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
                        
                        // Agregar marcadores
                        out << "    L.marker([" << localLat << ", " << localLon << "]).addTo(map).bindPopup('Local');\n";
                        
                        for(int idx : bestRoute) {
                            osrmURL += ";" + to_string(coordenadas[idx].second) + "," + to_string(coordenadas[idx].first);
                            out << "    L.marker([" << coordenadas[idx].first << ", " << coordenadas[idx].second 
                                << "]).addTo(map).bindPopup('Cliente: " << nodos[idx]->entrega.cliente.nombre << "');\n";
                            
                            cout << "-> Cliente: " << nodos[idx]->entrega.cliente.nombre 
                                 << " (" << nodos[idx]->entrega.zona << ")\n";
                        }
                        
                        osrmURL += "?overview=full&geometries=polyline";
                        
                        // Obtener y dibujar la ruta real por carreteras
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
                        
                        system("start api_mapa/route_result.html");
                    }
                    cout << "\nDistancia total: " << bestDistance << " km\n";
                } else {
                    cout << "No se pudo calcular una ruta óptima.\n";
                }
            }
            else if (opcionSeleccionada == "Exportar entregas a PDF") {
                createPDF("entregas.pdf");
            }
            else if (opcionSeleccionada == "Crear backup") {
                time_t ahora = time(0);
                tm* tiempo = localtime(&ahora);
                stringstream ss;
                ss << (1900 + tiempo->tm_year) << "_" << (1 + tiempo->tm_mon) << "_" << tiempo->tm_mday << "_"
                << tiempo->tm_hour << "_" << tiempo->tm_min << "_" << tiempo->tm_sec << ".txt";
                lista.crearBackup(ss.str());
            }
            else if (opcionSeleccionada == "Restaurar backup") {
                BackupManager::restaurarBackup(lista);
            }
            else if (opcionSeleccionada == "Salir") {
                break;
            }
            cout << "Presione cualquier tecla para continuar...\n";
            _getch();
        }
        else if (tecla == 59) { // F1
            std::wstring base_path = getExecutablePath();
            std::wstring ayuda_path = base_path + L"\\output\\ayuda.exe";
            std::string command = "start cmd /C \"" + std::string(ayuda_path.begin(), ayuda_path.end()) + "\"";
            system(command.c_str());
        }
    }
}