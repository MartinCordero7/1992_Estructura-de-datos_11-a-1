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
#include "RutasManager.cpp"

using namespace std;

std::wstring getExecutablePath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH); 
    std::wstring path(buffer);
    return path.substr(0, path.find_last_of(L"\\/"));
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
                string nombreCliente, cedula, celular, zona;
                
                cout << "Ingrese nombre del cliente: ";
                getline(cin, nombreCliente);
                if (nombreCliente.empty()) continue;
                
                cout << "Ingrese cédula del cliente: ";
                getline(cin, cedula);
                if (cedula.empty()) continue;
                
                cout << "Ingrese número de celular del cliente: ";
                getline(cin, celular);
                if (celular.empty()) continue;
                
                cout << "Seleccionando zona de entrega...\n";
                system("start api_mapa/select_zone.html");
                
                cout << "Por favor, seleccione la ubicación en el mapa y presione 'Confirmar'.\n";
                cout << "Presione ENTER cuando haya confirmado la ubicación...";
                cin.get();
                
                bool zoneFound = false;
                for(int i = 0; i < 30 && !zoneFound; i++) {
                    ifstream zoneFile("selected_zone.txt");
                    if (zoneFile.is_open()) {
                        getline(zoneFile, zona);
                        zoneFile.close();
                        remove("selected_zone.txt");
                        zoneFound = true;
                        
                        Cliente cliente(nombreCliente, cedula, celular);
                        Entrega entrega(cliente, zona);
                        lista.agregarEntrega(entrega);
                        cout << "\nEntrega registrada exitosamente!\n";
                    } else {
                        Sleep(1000);
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
                         << setw(15) << "Celular"
                         << setw(30) << "Zona" << endl;
                    cout << string(90, '-') << endl;
            
                    NodoEntrega* actual = lista.cabeza;
                    do {
                        cout << left << setw(30) << actual->entrega.cliente.nombre
                             << setw(15) << actual->entrega.cliente.cedula
                             << setw(15) << actual->entrega.cliente.celular
                             << setw(30) << actual->entrega.zona << endl;
                        actual = actual->siguiente;
                    } while (actual != lista.cabeza);
                    cout << string(90, '-') << endl;
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
                
                RutasManager::calcularRutaOptima(lista);
                _getch();
            }
            else if (opcionSeleccionada == "Exportar entregas a PDF") {
                if (lista.estaVacia()) {
                    cout << "No hay entregas para exportar a PDF.\n";
                    continue;
                }
                
                // Primero asegurarse de que el archivo entregas.txt esté actualizado
                ofstream archivo("entregas.txt");
                if (archivo.is_open()) {
                    NodoEntrega* actual = lista.cabeza;
                    do {
                        archivo << actual->entrega.cliente.nombre << ";"
                               << actual->entrega.cliente.cedula << ";"
                               << actual->entrega.cliente.celular << ";"
                               << actual->entrega.zona << "\n";
                        actual = actual->siguiente;
                    } while (actual != lista.cabeza);
                    archivo.close();
                    
                    // Ahora crear el PDF
                    createPDF("entregas.txt");
                    
                    // Abrir el PDF generado
                    system("start entregas.pdf");
                } else {
                    cout << "Error al crear el archivo de entregas.\n";
                }
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