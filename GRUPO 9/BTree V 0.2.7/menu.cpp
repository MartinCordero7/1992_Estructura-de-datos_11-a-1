#include "menu.h"
#include "BTree.h"
#include "Validaciones.h"
#include "funciones.h"
#include <iostream>
#include <cstdlib> // Para system("cls") o system("clear")

using namespace std;

BTree* arbol = nullptr;  // Declaración del árbol a nivel global

// Función para limpiar la consola
void limpiarPantalla() {
    try {
        #ifdef _WIN32
            system("cls");    // Windows
        #else
            system("clear");  // Linux / Mac
        #endif
    } catch (const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

void pausarPantalla(const string& mensaje) {
    cout << mensaje << endl;
    cin.ignore();
    cin.get();
}

void mostrarMenu() {
    try {
        int opcion;

        do {
            limpiarPantalla();  // Limpiar la pantalla antes de mostrar el menú
            cout << "--------- Arbol B --------" << endl;
            cout << "1. Ingresar numeros" << endl;
            cout << "2. Buscar un numero" << endl;
            cout << "3. Eliminar un numero" << endl;
            cout << "4. Mostrar numeros en orden infijo" << endl;
            cout << "5. Informacion del Arbol" << endl;
            cout << "6. Salir" << endl; // Updated option number
            cout << "\nSeleccione una opcion: ";
            string input = Validaciones::leerSoloNumerosLimitado(1); // Limitar a 1 dígito
            if (input.empty()) continue;

            try {
                opcion = stoi(input);
            } catch (const std::invalid_argument&) {
                Validaciones::mostrarMensajeError("Entrada no valida. Intente de nuevo.");
                continue;
            }

            switch(opcion) {
                case 1:
                    ingresarNumeros(arbol);
                    break;
                case 2:
                    buscarNumero(arbol);
                    break;
                case 3:
                    eliminarNumero(arbol);
                    break;
                case 4:
                    mostrarNumerosEnOrdenInfijo(arbol);
                    cout << "" << endl;
                    
                    break;
                case 5:
                    mostrarArbolConsola(arbol);
                    break;
                case 6:
                    cout << "Saliendo del programa..." << endl;
                    break;
                default:
                    Validaciones::mostrarMensajeError("Opcion invalida. Intente de nuevo.");
            }
            if (opcion != 6) {
                system("pause");
            }
        } while(opcion != 6);
    } catch (const std::exception& e) {
        Validaciones::mostrarMensajeError("Exception: " + string(e.what()));
    }
}
