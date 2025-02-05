#include "HashAbierto.h"
#include "Validaciones.h"
#include <iostream>
#include <graphics.h>

void resetGraphics() {
    closegraph();
}

void menuNumeros() {
    HashAbierto<int> hashTable(13); // Updated size to 13
    int opcion;
    do {
        system("cls");
        std::cout << "---------- HASH INTEGER ----------\n";
        std::cout << "1. Insertar\n";
        std::cout << "2. Buscar\n";
        std::cout << "3. Eliminar\n";
        std::cout << "4. Mostrar Hash por consola\n";
        std::cout << "5. Salir\n";
        std::cout << "\n";
        opcion = Validaciones::validarOpcionSubMenu("Ingrese una opcion (1-5): ");
        switch (opcion) {
            case 1: {
                while (true) {
                    std::string input = Validaciones::validarNumeroConSalida("Ingrese un numero (pulsa n para finalizar): ");
                    if (input == "n") break;
                    int num = std::stoi(input);
                    hashTable.insertar(num);
                }
                break;
            }
            case 2: {
                std::string input = Validaciones::validarNumeroConSalida("Ingrese un numero a buscar: ");
                int num = std::stoi(input);
                if (hashTable.buscar(num)) {
                    std::cout << "Numero encontrado.\n";
                } else {
                    std::cout << "Numero no encontrado.\n";
                }
                break;
            }
            case 3: {
            std::string input = Validaciones::validarNumeroConSalida("Ingrese un numero a eliminar: ");
            int num = std::stoi(input);
            if (hashTable.eliminar(num)) {  // Asegúrate de que la función `eliminar` devuelva un valor booleano
            std::cout << "Numero " << num << " eliminado exitosamente.\n";
            } else {
            std::cout << "Numero " << num << " no encontrado en la tabla.\n";
            }
                break;
            }
            case 4: {
                hashTable.mostrar();
                break;
            }
            case 5:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opcion invalida.\n";
        }system("pause");
    } while (opcion != 5);
    resetGraphics(); // Reset graphics when exiting the menu
}

void menuLetras() {
    HashAbierto<std::string> hashTable(13); // Updated size to 13
    int opcion;
    do {
        system("cls");
        std::cout << "---------- HASH STRINGS ----------\n";
        std::cout << "1. Insertar\n";
        std::cout << "2. Buscar\n";
        std::cout << "3. Eliminar\n";
        std::cout << "4. Mostrar Hash por consola\n";
        std::cout << "5. Salir\n";
        std::cout << "\n";
        opcion = Validaciones::validarOpcionSubMenu("Ingrese una opcion (1-5): ");
        switch (opcion) {
            case 1: {
            while (true) {
            std::string str = Validaciones::validarCadena("Ingrese una cadena (pulsa -1 para finalizar): ");
            if (str == "-1") break;  // Salir del ciclo si se ingresa "-1"
            hashTable.insertar(str);
            }
                break;
            }
            case 2: {
                std::string str = Validaciones::validarCadena("Ingrese una cadena a buscar: ");
                if (hashTable.buscar(str)) {
                    std::cout << "Cadena encontrada.\n";
                } else {
                    std::cout << "Cadena no encontrada.\n";
                }
                break;
            }
            case 3: {
            std::string str = Validaciones::validarCadena("Ingrese una cadena a eliminar: ");
            if (hashTable.eliminar(str)) {  // Comprobamos si la cadena fue eliminada
            std::cout << "Cadena '" << str << "' eliminada exitosamente.\n";
            } else {
            std::cout << "Cadena '" << str << "' no encontrada en la tabla.\n";
            }
                break;
            }
            case 4: {
                hashTable.mostrar();
                break;
            }
            case 5:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opcion invalida.\n";
        }system("pause");
    } while (opcion != 5);
    resetGraphics(); // Reset graphics when exiting the menu
}

int main() {
    int opcion;
    do {
        system("cls");
        std::cout << "---------- OPEN HASHING ---------- \n";
        std::cout << " \n";
        std::cout << "1. Trabajar con Enteros\n";
        std::cout << "2. Trabajar con cadenas String\n";
        std::cout << "3. Salir\n";
        std::cout << " \n";
        opcion = Validaciones::validarOpcionMenu("Ingrese una opcion (1-3): ");
        switch (opcion) {
            case 1:
                menuNumeros();
                break;
            case 2:
                menuLetras();
                break;
            case 3:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opcion invalida.\n";
        }
        
    } while (opcion != 3);

    return 0;
}
