#include "hash_string.cpp"
#include "hash_int.cpp"
#include <iostream>
#include <cstdlib>
#include <clocale>
#include <windows.h>

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
        std::cin >> opcion;
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
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                std::cout << "Ingrese el número: ";
                std::cin >> clave;
                hashInt.insertar(clave, metodo);
                break;
            case 2:
                std::cout << "Ingrese el número a buscar: ";
                std::cin >> clave;
                std::cout << (hashInt.buscar(clave, metodo) ? "Encontrado" : "No encontrado") << std::endl;
                system("pause");
                break;
            case 3:
                std::cout << "Ingrese el numero a eliminar: ";
                std::cin >> clave;
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
    std::cout << "1. Linear Probing\n";
    std::cout << "2. Quadratic Probing\n";
    std::cout << "3. Double Hashing\n";
    std::cout << "Opción: ";
    std::cin >> metodo;
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
        std::cin >> opcion;

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