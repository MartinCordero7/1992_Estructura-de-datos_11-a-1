#include "BigO.h"
#include "Menus.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include "ArbolRadix.h" 
#include "Empleado.h" 
#include <random>
#include <cstdio> 
#include <cstdlib> 
#include "GestorPersonas.h"
#include "extras.h"
#include "Fecha.h" 
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "ArbolRadix.h" 
#include "validaciones.h"
#include <fstream> 
#include <ctime>
#include "ArbolRadix.h"
#define ANSI_COLOR_CYAN     "\x1b[94m"
#define ANSI_COLOR_RESET    "\x1b[0m"
#include <random>

void ejecutarScriptsYBigO() {
    std::string comandoR = "script.R";
    int resultadoR = system(comandoR.c_str());
    if (resultadoR == 0) {
        std::cout << "Script de R ejecutado exitosamente." << std::endl;
    } else {
        std::cerr << "Error al ejecutar el script de R." << std::endl;
    }

    std::string comandoMATLAB = "script.m";
    int resultadoMATLAB = system(comandoMATLAB.c_str());
    if (resultadoMATLAB == 0) {
        std::cout << "Script de MATLAB ejecutado exitosamente." << std::endl;
    } else {
        std::cerr << "Error al ejecutar el script de MATLAB." << std::endl;
    }

    system("pause");
    BigO BigO(11);
    BigO.operarMenuBigO();
}

BigO::BigO(int totalOpcionesBigO) : totalOpcionesBigO(totalOpcionesBigO) {
    opcionActualBigO = 1;
}

void BigO::regresarMenuBigO() {
    while (true) {
        if (_kbhit()) {
            char tecla = _getch();
            if (tecla == 27) {
                break;
            }
        }
    }
}

void BigO::mostrarMenuBigO() {
    system("cls");
    std::cout << "\t\t\t=== Big O ===" << std::endl;
    for (int i = 1; i <= totalOpcionesBigO; i++) {
        if (i == opcionActualBigO) {
            std::cout << "\t> " << ANSI_COLOR_CYAN;
        }
        else {
            std::cout << "  ";
        }
        switch (i) {
        case 1:
            std::cout << "1) BigO Insertar un Empleado" << ANSI_COLOR_RESET << std::endl;
            break;
        case 2:
            std::cout << "2) BigO Buscar un Empleado por Cedula" << ANSI_COLOR_RESET << std::endl;
		    break;
        case 3:
            std::cout << "3) BigO Cargar desde el archivo" << ANSI_COLOR_RESET << std::endl;
            break;
        case 4:
            std::cout << "4) BigO Eliminar Persona" << ANSI_COLOR_RESET << std::endl;
            break;
        case 5:
            std::cout << "5) BigO Imprimir Lista" << ANSI_COLOR_RESET << std::endl;
            break;
        case 6:
            std::cout << "6) BigO QuickSort" << ANSI_COLOR_RESET << std::endl;
            break;
        case 7:
            std::cout << "7) BigO Buscar Persona" << ANSI_COLOR_RESET << std::endl;
            break;
        case 8:
            std::cout << "8) BigO Validar existencia de Cedula" << ANSI_COLOR_RESET << std::endl;
            break;
        case 9:
            std::cout << "Regresar al Menu Principal" << ANSI_COLOR_RESET << std::endl;
            break;            
        }
    }
}

int BigO::operarMenuBigO() {
    GestorPersonas gestorPersonas;
    ListaCircularDoble miLista;
    ArbolRadix miArbol; 
    std::string nombreArchivo = "personas.txt";
	miLista.cargarDesdeArchivo(nombreArchivo);
	cargarListaEnArbol(miLista, miArbol);

    while (true) {
        mostrarMenuBigO();
        char tecla = _getch();

        switch (tecla) {
        case 72: // Flecha arriba
            opcionActualBigO = (opcionActualBigO > 1) ? opcionActualBigO - 1 : totalOpcionesBigO;
            break;
        case 80: // Flecha abajo
            opcionActualBigO = (opcionActualBigO < totalOpcionesBigO) ? opcionActualBigO + 1 : 1;
            break;
        case 13: // Tecla Enter
            system("cls");
            switch (opcionActualBigO) {
                case 1:
                {
                    ArbolRadix arbol; 
                    const int numDatos = 1000;
                    const int numRepeticiones = 50; 
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> distribucion(0, numDatos - 1);

                    // Abre el archivo para escribir
                    std::ofstream archivo("BigO.txt");
                    if (!archivo.is_open()) {
                        std::cerr << "Error al abrir el archivo" << std::endl;
                        return 1;
                    }

                    int numDato = 1; // Inicializa el número de dato en 1
                    for (int i = 0; i < numRepeticiones; ++i) {
                        // Genera un índice aleatorio
                        int indiceAleatorio = distribucion(gen);
                        std::string cedulaAleatoria = "CEDULA_" + std::to_string(indiceAleatorio);

                        // Mide el tiempo antes de la búsqueda
                        auto inicio = std::chrono::high_resolution_clock::now();
                        for (int i = 0; i < numDatos; ++i) {
                        std::string cedula = "CEDULA_" + std::to_string(i);
                        Empleado* empleado = new Empleado(cedula, "Nombre", "Apellido", Fecha(), "Cargo", "Salario");
                        arbol.insertarEmpleado(empleado);}

                        // Mide el tiempo después de la búsqueda
                        auto fin = std::chrono::high_resolution_clock::now();

                        // Calcula el tiempo de ejecución en milisegundos
                        std::chrono::duration<double, std::milli> tiempoEjecucion = fin - inicio;

                        // Guarda los resultados en el archivo separados por comas
                        archivo << numDato << "," << tiempoEjecucion.count() << "\n";

                        ++numDato; // Incrementa el número de dato
                    }
                    // Cierra el archivo
                    archivo.close();
                    ejecutarScriptsYBigO();		
                }
                break;
                case 2:
                { 
                    ArbolRadix arbol; 
                    const int numDatos = 100000;
                    for (int i = 0; i < numDatos; ++i) {
                        std::string cedula = "CEDULA_" + std::to_string(i);
                        Empleado* empleado = new Empleado(cedula, "Nombre", "Apellido", Fecha(), "Cargo", "Salario");
                        arbol.insertarEmpleado(empleado);
                    }
                    
                    const int numRepeticiones = 70; 
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> distribucion(0, numDatos - 1);

                    // Abre el archivo para escribir
                    std::ofstream archivo("BigO.txt");
                    if (!archivo.is_open()) {
                        std::cerr << "Error al abrir el archivo" << std::endl;
                        return 1;
                    }

                    int numDato = 1; // Inicializa el número de dato en 1
                    for (int i = 0; i < numRepeticiones; ++i) {
                        // Genera un índice aleatorio
                        int indiceAleatorio = distribucion(gen);
                        std::string cedulaAleatoria = "CEDULA_" + std::to_string(indiceAleatorio);

                        // Mide el tiempo antes de la búsqueda
                        auto inicio = std::chrono::high_resolution_clock::now();
                        
                        // Llama a la función de búsqueda
                        Empleado* encontrado = arbol.buscarPorCedula(cedulaAleatoria);

                        // Mide el tiempo después de la búsqueda
                        auto fin = std::chrono::high_resolution_clock::now();

                        // Calcula el tiempo de ejecución en milisegundos
                        std::chrono::duration<double, std::milli> tiempoEjecucion = fin - inicio;

                        // Guarda los resultados en el archivo separados por comas
                        archivo << numDato << "," << tiempoEjecucion.count() << "\n";

                        ++numDato; // Incrementa el número de dato
                    }
                    // Cierra el archivo
                    archivo.close();
                    ejecutarScriptsYBigO();          		
                }
                break;
                case 3:
                {
                    ListaCircularDoble lista;
                    const std::string nombreArchivo = "personas.txt";
                    std::ofstream archivoSalida("BigO.txt", std::ios_base::app);
                    if (!archivoSalida.is_open()) {
                        std::cerr << "Error al abrir el archivo." << std::endl;
                        return 1;
                    }

                    const int numRepeticiones = 1000; // Número de repeticiones
                    for (int repeticion = 0; repeticion < numRepeticiones; ++repeticion) {
                        auto inicioCarga = std::chrono::high_resolution_clock::now(); // Inicio de la carga
                        lista.cargarDesdeArchivo(nombreArchivo);
                        auto finCarga = std::chrono::high_resolution_clock::now(); // Fin de la carga

                        std::chrono::duration<double, std::milli> tiempoCarga = finCarga - inicioCarga;

                        archivoSalida << repeticion + 1 << "," << tiempoCarga.count() << std::endl;
                    }

                    archivoSalida.close(); // Cierra el archivo después de agregar los resultados
                    ejecutarScriptsYBigO();
                }
                break;
                case 5:
                {
                    ListaCircularDoble lista; 
                    const int numDatos = 100000;
                    for (int i = 0; i < numDatos; ++i) {
                        std::string cedula = "CEDULA_" + std::to_string(i);
                        Empleado* empleado = new Empleado(cedula, "Nombre", "Apellido", Fecha(), "Cargo", "Salario");
                        lista.insertarAlInicio(empleado);
                    }

                    const int numRepeticiones = 50; // Número de veces que se repite la búsqueda
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> distribucion(0, numDatos - 1);

                    // Abre el archivo para escribir
                    std::ofstream archivo("BigO.txt");
                    if (!archivo.is_open()) {
                        std::cerr << "Error al abrir el archivo" << std::endl;
                        return 1;
                    }

                    int numDato = 1; // Inicializa el número de dato en 1
                    for (int i = 0; i < numRepeticiones; ++i) {
                        // Genera un índice aleatorio
                        int indiceAleatorio = distribucion(gen);
                        std::string cedulaAleatoria = "CEDULA_" + std::to_string(indiceAleatorio);

                        // Mide el tiempo antes de la búsqueda
                        auto inicio = std::chrono::high_resolution_clock::now();

                        std::string cedula = "CEDULA_" + std::to_string(i);
                        Empleado* empleado = new Empleado(cedula, "Nombre", "Apellido", Fecha(), "Cargo", "Salario");
                        lista.eliminarPersona(empleado);

                        // Mide el tiempo después de la búsqueda
                        auto fin = std::chrono::high_resolution_clock::now();

                        // Calcula el tiempo de ejecución en milisegundos
                        std::chrono::duration<double, std::milli> tiempoEjecucion = fin - inicio;

                        // Guarda los resultados en el archivo separados por comas
                        archivo << numDato << "," << tiempoEjecucion.count() << "\n";

                        ++numDato; // Incrementa el número de dato
                    }
                    // Cierra el archivo
                    archivo.close();
                    ejecutarScriptsYBigO();
                }
                break;
                case 6:
                {
                    ListaCircularDoble lista; 
                    const int numDatos = 10;
                    for (int i = 0; i < numDatos; ++i) {
                        std::string cedula = "CEDULA_" + std::to_string(i);
                        Empleado* empleado = new Empleado(cedula, "Nombre", "Apellido", Fecha(), "Cargo", "Salario");
                        lista.insertarAlInicio(empleado);
                    }

                    const int numRepeticiones = 6; 
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> distribucion(0, numDatos - 1);

                    // Abre el archivo para escribir
                    std::ofstream archivo("BigO.txt");
                    if (!archivo.is_open()) {
                        std::cerr << "Error al abrir el archivo" << std::endl;
                        return 1;
                    }

                    int numDato = 1; // Inicializa el número de dato en 1
                    for (int i = 0; i < numRepeticiones; ++i) {
                        // Genera un índice aleatorio
                        int indiceAleatorio = distribucion(gen);
                        std::string cedulaAleatoria = "CEDULA_" + std::to_string(indiceAleatorio);

                        // Mide el tiempo antes de la búsqueda
                        auto inicio = std::chrono::high_resolution_clock::now();

                        lista.imprimirLista();

                        // Mide el tiempo después de la búsqueda
                        auto fin = std::chrono::high_resolution_clock::now();

                        // Calcula el tiempo de ejecución en milisegundos
                        std::chrono::duration<double, std::milli> tiempoEjecucion = fin - inicio;

                        // Guarda los resultados en el archivo separados por comas
                        archivo << numDato << "," << tiempoEjecucion.count() << "\n";
                        ++numDato; // Incrementa el número de dato
                    }
                    // Cierra el archivo
                    archivo.close();
                    ejecutarScriptsYBigO();        	
                }
                break;
                case 7:
                {
                    ListaCircularDoble lista; 
                    const int numDatos = 1000;
                    for (int i = 0; i < numDatos; ++i) {
                        std::string cedula = "CEDULA_" + std::to_string(i);
                        Empleado* empleado = new Empleado(cedula, "Nombre", "Apellido", Fecha(), "Cargo", "Salario");
                        lista.insertarAlInicio(empleado);
                    }

                    const int numRepeticiones = 50; 
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> distribucion(0, numDatos - 1);

                    // Abre el archivo para escribir
                    std::ofstream archivo("BigO.txt");
                    if (!archivo.is_open()) {
                        std::cerr << "Error al abrir el archivo" << std::endl;
                        return 1;
                    }

                    int numDato = 1; // Inicializa el número de dato en 1
                    for (int i = 0; i < numRepeticiones; ++i) {
                        // Genera un índice aleatorio
                        int indiceAleatorio = distribucion(gen);
                        std::string cedulaAleatoria = "CEDULA_" + std::to_string(indiceAleatorio);

                        // Mide el tiempo antes de la búsqueda
                        auto inicio = std::chrono::high_resolution_clock::now();

                        lista.quickSort();

                        // Mide el tiempo después de la búsqueda
                        auto fin = std::chrono::high_resolution_clock::now();

                        // Calcula el tiempo de ejecución en milisegundos
                        std::chrono::duration<double, std::milli> tiempoEjecucion = fin - inicio;

                        // Guarda los resultados en el archivo separados por comas
                        archivo << numDato << "," << tiempoEjecucion.count() << "\n";
                        ++numDato; // Incrementa el número de dato
                    }
                    // Cierra el archivo
                    archivo.close();
                    ejecutarScriptsYBigO();			
                }
                break;   
                case 8:
                {
                    ListaCircularDoble lista; 
                    const int numDatos = 100000;
                    for (int i = 0; i < numDatos; ++i) {
                        std::string cedula = "CEDULA_" + std::to_string(i);
                        Empleado* empleado = new Empleado(cedula, "Nombre", "Apellido", Fecha(), "Cargo", "Salario");
                        lista.insertarAlFinal(empleado);
                    }

                    const int numRepeticiones = 50; // Número de veces que se repite la búsqueda
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> distribucion(0, numDatos - 1);

                    // Abre el archivo para escribir
                    std::ofstream archivo("BigO.txt");
                    if (!archivo.is_open()) {
                        std::cerr << "Error al abrir el archivo" << std::endl;
                        return 1;
                    }

                    int numDato = 1; // Inicializa el número de dato en 1
                    for (int i = 0; i < numRepeticiones; ++i) {
                        // Genera un índice aleatorio
                        int indiceAleatorio = distribucion(gen);
                        std::string cedulaAleatoria = "CEDULA_" + std::to_string(indiceAleatorio);

                        // Mide el tiempo antes de la búsqueda
                        auto inicio = std::chrono::high_resolution_clock::now();

                        // Llama a la función de búsqueda
                        Empleado* encontrado = lista.buscarPersona(cedulaAleatoria);

                        // Mide el tiempo después de la búsqueda
                        auto fin = std::chrono::high_resolution_clock::now();

                        // Calcula el tiempo de ejecución en milisegundos
                        std::chrono::duration<double, std::milli> tiempoEjecucion = fin - inicio;

                        // Guarda los resultados en el archivo separados por comas
                        archivo << numDato << "," << tiempoEjecucion.count() << "\n";
                        ++numDato; // Incrementa el número de dato
                    }
                    // Cierra el archivo
                    archivo.close();
                    ejecutarScriptsYBigO();
                }
                break;
                case 9:
                {
                    ArbolRadix arbol;  
                    const int numDatos = 100;
                    for (int i = 0; i < numDatos; ++i) {
                        std::string cedula = "CEDULA_" + std::to_string(i);
                        Empleado* empleado = new Empleado(cedula, "Nombre", "Apellido", Fecha(), "Cargo", "Salario");
                        arbol.insertarEmpleado(empleado);
                    }

                    const int numRepeticiones = 10; // Número de veces que se repite la búsqueda
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> distribucion(0, numDatos - 1);

                    // Abre el archivo para escribir
                    std::ofstream archivo("BigO.txt");
                    if (!archivo.is_open()) {
                        std::cerr << "Error al abrir el archivo" << std::endl;
                        return 1;
                    }

                    int numDato = 1; // Inicializa el número de dato en 1
                    for (int i = 0; i < numRepeticiones; ++i) {
                        // Genera un índice aleatorio
                        int indiceAleatorio = distribucion(gen);
                        std::string cedulaAleatoria = "CEDULA_" + std::to_string(indiceAleatorio);

                        // Mide el tiempo antes de la búsqueda
                        auto inicio = std::chrono::high_resolution_clock::now();

                        
                        std::string x = arbol.validarExistenciaCedula(cedulaAleatoria);

                        // Mide el tiempo después de la búsqueda
                        auto fin = std::chrono::high_resolution_clock::now();

                        // Calcula el tiempo de ejecución en milisegundos
                        std::chrono::duration<double, std::milli> tiempoEjecucion = fin - inicio;

                        // Guarda los resultados en el archivo separados por comas
                        archivo << numDato << "," << tiempoEjecucion.count() << "\n";

                        ++numDato; // Incrementa el número de dato
                    }
                    // Cierra el archivo
                    archivo.close();
                    ejecutarScriptsYBigO();
                }
                break;
                case 10:
                {   				
                    Menus menus(13);
                    menus.operarMenu();       	               
                }
                regresarMenuBigO();
                system("cls");
                break;
            }
        }
    }
    return opcionActualBigO;   
}