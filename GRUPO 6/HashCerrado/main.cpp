#include "hash_string.cpp"
#include "hash_int.cpp"
#include <iostream>
#include <cstdlib>
#include <clocale>

void menuString(HashString& hashString) {
    int opcion, metodo;
    std::string clave;
    do {
        system("cls");
        std::cout << "\n--- Menú para Strings ---\n";
        std::cout << "1. Insertar\n";
        std::cout << "2. Buscar\n";
        std::cout << "3. Eliminar\n";
        std::cout << "4. Mostrar tabla\n";
        std::cout << "5. Visualizar tabla\n";
        std::cout << "6. Regresar al menú principal\n";
        std::cout << "Opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        if (opcion >= 1 && opcion <= 3) {
            std::cout << "Seleccione el método de sondeo:\n";
            std::cout << "1. Linear Probing\n";
            std::cout << "2. Quadratic Probing\n";
            std::cout << "3. Double Hashing\n";
            std::cin >> metodo;
            std::cin.ignore();
        }

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
                std::cout << "Opción no válida.\n";
                system("pause");
        }
    } while(opcion != 6);
}

void menuInt(HashInt& hashInt) {
    int opcion, metodo, clave;
    do {
        system("cls");
        std::cout << "\n--- Menú para Enteros ---\n";
        std::cout << "1. Insertar\n";
        std::cout << "2. Buscar\n";
        std::cout << "3. Eliminar\n";
        std::cout << "4. Mostrar tabla\n";
        std::cout << "5. Visualizar tabla\n";
        std::cout << "6. Regresar al menú principal\n";
        std::cout << "Opción: ";
        std::cin >> opcion;

        if (opcion >= 1 && opcion <= 3) {
            std::cout << "Seleccione el método de sondeo:\n";
            std::cout << "1. Linear Probing\n";
            std::cout << "2. Quadratic Probing\n";
            std::cout << "3. Double Hashing\n";
            std::cin >> metodo;
        }

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
                std::cout << "Ingrese el número a eliminar: ";
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
                std::cout << "Opción no válida.\n";
                system("pause");
        }
    } while(opcion != 6);
}

int main() {
    setlocale(LC_ALL, "");
    HashString hashString;
    HashInt hashInt;
    int opcion;

    do {
        system("cls");
        std::cout << "\n--- Menú Principal ---\n";
        std::cout << "1. Trabajar con Strings\n";
        std::cout << "2. Trabajar con Enteros\n";
        std::cout << "3. Salir\n";
        std::cout << "Opción: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                menuString(hashString);
                break;
            case 2:
                menuInt(hashInt);
                break;
            case 3:
                system("cls");
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
                system("pause");
        }
    } while(opcion != 3);

    return 0;
}