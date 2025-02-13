#include "hash_string.cpp"
#include "hash_int.cpp"
#include <iostream>
#include <cstdlib>
#include <clocale>
#include <windows.h>
#include <limits>

void menuString(HashString& hashString, int metodo) {
    int opcion;
    std::string clave;
    do {
        system("cls");
        std::cout << "\n--- Menu para Strings ---\n";
        std::cout << "1. Insertar\n";
        std::cout << "2. Buscar\n";
        std::cout << "3. Eliminar\n";
        std::cout << "4. Mostrar tabla\n";
        std::cout << "5. Visualizar tabla\n";
        std::cout << "6. Regresar al menu principal\n";
        std::cout << "Opcion: ";
        while (!(std::cin >> opcion) || opcion < 1 || opcion > 6) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Opcion no valida. Ingrese un numero entre 1 y 6: ";
        }
        std::cin.ignore();

        switch(opcion) {
            case 1:
                std::cout << "Ingrese la cadena: ";
                std::getline(std::cin, clave);
                hashString.insertar(clave, metodo);
                break;
            case 2:
                std::cout << "Ingrese la cadena a buscar: ";
                std::getline(std::cin, clave);
                std::cout << (hashString.buscar(clave, metodo) ? "Encontrado" : "No encontrado") << std::endl;
                system("pause");
                break;
            case 3:
                std::cout << "Ingrese la cadena a eliminar: ";
                std::getline(std::cin, clave);
                hashString.eliminar(clave, metodo);
                break;
            case 4:
                hashString.mostrar();
                system("pause");
                break;
            case 5:
                hashString.visualizar();
                break;
            case 6:
                break;
            default:
                std::cout << "Opcion no valida.\n";
                system("pause");
        }
    } while(opcion != 6);
}

void menuInt(HashInt& hashInt, int metodo) {
    int opcion, clave;
    do {
        system("cls");
        std::cout << "\n--- Menu para Enteros ---\n";
        std::cout << "1. Insertar\n";
        std::cout << "2. Buscar\n";
        std::cout << "3. Eliminar\n";
        std::cout << "4. Mostrar tabla\n";
        std::cout << "5. Visualizar tabla\n";
        std::cout << "6. Regresar al menu principal\n";
        std::cout << "Opcion: ";
        while (!(std::cin >> opcion) || opcion < 1 || opcion > 6) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Opcion no valida. Ingrese un numero entre 1 y 6: ";
        }

        switch(opcion) {
            case 1:
                std::cout << "Ingrese el número: ";
                while (!(std::cin >> clave)) {
                    std::cin.clear(); // clear the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                    std::cout << "Entrada no válida. Ingrese un número: ";
                }
                hashInt.insertar(clave, metodo);
                break;
            case 2:
                std::cout << "Ingrese el número a buscar: ";
                while (!(std::cin >> clave)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Entrada no válida. Ingrese un número: ";
                }
                std::cout << (hashInt.buscar(clave, metodo) ? "Encontrado" : "No encontrado") << std::endl;
                system("pause");
                break;
            case 3:
                std::cout << "Ingrese el numero a eliminar: ";
                while (!(std::cin >> clave)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Entrada no válida. Ingrese un número: ";
                }
                hashInt.eliminar(clave, metodo);
                break;
            case 4:
                hashInt.mostrar();
                system("pause");
                break;
            case 5:
                hashInt.visualizar();
                break;
            case 6:
                break;
            default:
                std::cout << "Opcion no valida.\n";
                system("pause");
        }
    } while(opcion != 6);
}

int seleccionarMetodo() {
    int metodo;
    system("cls");
    std::cout << "\n--- Seleccione el metodo de sondeo ---\n";
    std::cout << "1. Linear Probing: f(i) = i\n";
    std::cout << "2. Quadratic Probing: f(i) = i * i\n";
    std::cout << "3. Double Hashing: f(i) = i * hash2(elem)\n";
    std::cout << "Opcion: ";
    while (!(std::cin >> metodo) || metodo < 1 || metodo > 3) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Opcion no valida. Ingrese un numero entre 1 y 3: ";
    }
    std::cin.ignore();
    return metodo;
}

int main() {
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    setlocale(LC_ALL, "spanish");
    
    int opcion, metodo;

    do {
        HashString hashString;
        HashInt hashInt;
        
        system("cls");
        std::cout << "\n--- Menu Principal ---\n";
        std::cout << "1. Trabajar con Strings\n";
        std::cout << "2. Trabajar con Enteros\n";
        std::cout << "3. Salir\n";
        std::cout << "Opcion: ";
        while (!(std::cin >> opcion) || opcion < 1 || opcion > 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Opcion no valida. Ingrese un numero entre 1 y 3: ";
        }

        if (opcion >= 1 && opcion <= 2) {
            metodo = seleccionarMetodo();
            switch(opcion) {
                case 1:
                    menuString(hashString, metodo);
                    break;
                case 2:
                    menuInt(hashInt, metodo);
                    break;
            }
        }
    } while(opcion != 3);
    
    return 0;
}