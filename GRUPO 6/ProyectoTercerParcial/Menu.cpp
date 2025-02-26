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

using namespace std;

std::wstring getExecutablePath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH); 
    std::wstring path(buffer);
    return path.substr(0, path.find_last_of(L"\\/"));
}
int ingresarAnio(const string& mensaje) {
    int anio;
    string input;
    while (true) {
        cout << mensaje;
        getline(cin, input);  // Usamos getline para permitir validación de la entrada completa

        // Validar si la entrada está vacía o contiene solo espacios
        if (input.empty() || input.find_first_not_of(' ') == string::npos) {
            cout << "Error: Debe ingresar un dato (no puede estar vacío o contener solo espacios)." << endl;
            continue;
        }

        // Validar que el año sea numérico y tenga 4 dígitos
        try {
            anio = stoi(input);  // Convertimos la entrada a entero
            if (anio < 1 || anio > 2024) {
                throw invalid_argument("Año fuera de rango.");
            }
            break;  // Salimos del bucle si el año es válido
        } catch (const invalid_argument& e) {
            cout << "Error: Ingrese un año válido de 4 dígitos entre 0001 y 2024." << endl;
        }
    }
    return anio;
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
    string ruta = "entregas.txt"; // Actualizado para entregas
    int anioInicio, anioFin;

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
                string nombreCliente, cedula, zona, prioridadInput;
                int prioridad;
                
                cout << "Ingrese nombre del cliente (o presione Enter para regresar al menú): ";
                getline(cin, nombreCliente);
                if (nombreCliente.empty()) { cout << "Regresando al menú principal...\n"; continue; }
                
                cout << "Ingrese cédula del cliente (o presione Enter para regresar al menú): ";
                getline(cin, cedula);
                if (cedula.empty()) { cout << "Regresando al menú principal...\n"; continue; }
                
                cout << "Ingrese zona de entrega (NORTE, NORESTE, ESTE, SUR, OESTE) (o presione Enter para regresar al menú): ";
                getline(cin, zona);
                if (zona.empty()) { 
                    cout << "Regresando al menú principal...\n"; 
                    continue; 
                }
                
                Mapa mapa;
                if (!mapa.existeZona(zona)) {
                    cout << "Error: La zona ingresada no existe en el mapa.\n";
                    cout << "Zonas disponibles: NORTE, NORESTE, ESTE, SUR, OESTE\n";
                    continue;
                }
                
                cout << "Ingrese la prioridad (número, menor valor indica mayor prioridad) (o presione Enter para regresar): ";
                getline(cin, prioridadInput);
                if (prioridadInput.empty()) { cout << "Regresando al menú principal...\n"; continue; }
                try {
                    prioridad = stoi(prioridadInput);
                } catch (...) {
                    cout << "Prioridad inválida.\n";
                    continue;
                }
                
                Cliente cliente(nombreCliente, cedula);
                Entrega entrega(cliente, zona, prioridad);
                lista.agregarEntrega(entrega);
            }
            else if (opcionSeleccionada == "Buscar entrega") {
                string cedula;
                cout << "Ingrese cédula del cliente a buscar (o presione Enter para volver al menú principal): ";
                getline(cin, cedula);
                if (cedula.empty()) {
                    cout << "Regresando al menú principal...\n";
                    continue;
                }
                // Se asume método buscarEntregaPorCedula en lista
                NodoEntrega* entrega = lista.buscarEntregaPorCedula(cedula); // Método placeholder
                if (entrega) {
                    entrega->entrega.mostrar(); // Método para mostrar detalles de la entrega (placeholder)
                } else {
                    cout << "Entrega no encontrada.\n";
                }
            }
            else if (opcionSeleccionada == "Eliminar entrega") {
                string cedula;
                cout << "Ingrese cédula del cliente de la entrega a eliminar (o presione Enter para volver al menú principal): ";
                getline(cin, cedula);
                if (cedula.empty()) {
                    cout << "Regresando al menú principal...\n";
                    continue;
                }
                // Se asume método eliminarEntrega en lista
                if (lista.eliminarEntrega(cedula)) { // Método placeholder
                    cout << "Entrega eliminada exitosamente.\n";
                } else {
                    cout << "Entrega no encontrada para la cédula: " << cedula << endl;
                }
            }
            else if (opcionSeleccionada == "Ver todas las entregas") {
                lista.imprimirEntregas(); // Método actualizado para entregas
            }
            else if (opcionSeleccionada == "Exportar entregas a PDF") {
                createPDF(ruta);
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
            else if (opcionSeleccionada == "Realizar entregas") {
                if (lista.estaVacia()) {
                    cout << "No hay entregas pendientes para realizar.\n";
                    continue;
                }
                
                // Recopilar todas las zonas de entrega
                vector<string> zonasEntrega;
                NodoEntrega* actual = lista.cabeza;
                do {
                    zonasEntrega.push_back(actual->entrega.zona);
                    actual = actual->siguiente;
                } while (actual != lista.cabeza);
                
                // Calcular y mostrar la ruta óptima
                Mapa mapa;
                cout << "Calculando ruta óptima para las entregas...\n\n";
                vector<string> rutaOptima = mapa.calcularRutaOptima(zonasEntrega);
                mapa.mostrarRuta(rutaOptima);
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