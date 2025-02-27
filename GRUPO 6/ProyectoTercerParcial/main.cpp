/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Archivo principal de proyecto                            *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/


#include "ListaCircularDoble.cpp"
#include "Menu.cpp"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

// Función para verificar si el servidor Flask está corriendo
bool verificarServidor() {
    string check_command = "curl -s http://localhost:5000/get_clients > nul 2>&1";
    return system(check_command.c_str()) == 0;
}


int main() {
    // Configurar la consola para usar UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Verificar el servidor Flask
    if (!verificarServidor()) {
        std::cerr << "Error: El servidor Flask no está en ejecución.\n";
        std::cerr << "Por favor, ejecute 'python server.py' en una terminal separada.\n";
        system("pause");
        return 1;
    }

     // Verifica y crea la carpeta de backups si no existe
    BackupManager::crearCarpetaSiNoExiste("backup");

    ListaCircularDoble lista;
    // Cargar las entregas desde el archivo al iniciar (se actualiza el método)
    try {
        lista.cargarEntregasDesdeArchivo();
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error al cargar las entregas desde el archivo: " << e.what() << std::endl;
        return 1;
    }

    mostrarMenu(lista);
    return 0;
}

