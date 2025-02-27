/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Menu principal                                           *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

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
#include "funciones.h"
#include "Entrega.h"
#include "Cliente.h"
#include "Mapa.cpp"
#include <fstream>

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
                string nombreCliente, cedula, zona;
                
                cout << "Ingrese nombre del cliente (o presione Enter para regresar al menú): ";
                getline(cin, nombreCliente);
                if (nombreCliente.empty()) { cout << "Regresando al menú principal...\n"; continue; }
                
                cout << "Ingrese cédula del cliente (o presione Enter para regresar al menú): ";
                getline(cin, cedula);
                if (cedula.empty()) { cout << "Regresando al menú principal...\n"; continue; }
                
                cout << "A continuación se abrirá el mapa para seleccionar la zona de entrega...\n";
                system("start api_mapa/select_zone.html");
                
                cout << "Por favor, seleccione la ubicación en el mapa y presione 'Confirmar'.\n";
                cout << "Presione ENTER cuando haya confirmado la ubicación...";
                cin.get();
                
                // Leer la zona seleccionada del archivo temporal
                ifstream zoneFile("api_mapa/selected_zone.txt");
                if (zoneFile.is_open()) {
                    getline(zoneFile, zona);
                    zoneFile.close();
                    
                    Cliente cliente(nombreCliente, cedula);
                    Entrega entrega(cliente, zona);
                    lista.agregarEntrega(entrega);
                    cout << "\nEntrega registrada exitosamente!\n";
                    
                    remove("api_mapa/selected_zone.txt");
                } else {
                    cout << "Error: No se pudo obtener la zona seleccionada.\n";
                }
            }
            else if (opcionSeleccionada == "Buscar entrega") {
                string cedula;
                cout << "Ingrese cédula del cliente a buscar (o presione Enter para volver al menú principal): ";
                getline(cin, cedula);
                if (cedula.empty()) {
                    cout << "Regresando al menú principal...\n";
                    continue;
                }
                NodoEntrega* entrega = lista.buscarEntregaPorCedula(cedula);
                if (entrega) {
                    entrega->entrega.mostrar();
                } else {
                    cout << "Entrega no encontrada.\n";
                }
            }
            else if (opcionSeleccionada == "Eliminar entrega") {
                string cedula;
                cout << "Ingrese cédula del cliente de la entrega a eliminar: ";
                getline(cin, cedula);
                if (cedula.empty()) {
                    cout << "Regresando al menú principal...\n";
                    continue;
                }
                if (lista.eliminarEntrega(cedula)) {
                    cout << "Entrega eliminada exitosamente.\n";
                } else {
                    cout << "Entrega no encontrada.\n";
                }
            }
            else if (opcionSeleccionada == "Ver todas las entregas") {
                lista.imprimirEntregas();
            }
            else if (opcionSeleccionada == "Realizar entregas") {
                if (lista.estaVacia()) {
                    cout << "No hay entregas pendientes para realizar.\n";
                    continue;
                }
                
                cout << "Se abrirá una ventana para seleccionar la ubicación del local.\n";
                system("start api_mapa/select_local.html");
                cout << "Por favor, seleccione la ubicación del local en el mapa y presione 'Confirmar Local'.\n";
                cout << "Esperando confirmación...\n";
                Sleep(5000);
                
                system("start api_mapa/route_result.html");
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