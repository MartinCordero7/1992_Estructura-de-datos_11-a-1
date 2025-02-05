#include "hash_string.cpp"
#include "hash_int.cpp"
#include <iostream>
#include <cstdlib>    // Para system()
#include <clocale>    // Para setlocale()
#include <limits> 

void menuString(HashString& hashString) {
    int opcion;
    std::string clave;
    do {
        system("cls");  // Limpiar la consola (usa "clear" si no estás en Windows)
        std::cout << "\n--- Menú para Strings ---\n";
        std::cout << "1. Insertar\n";
        std::cout << "2. Buscar\n";
        std::cout << "3. Eliminar\n";
        std::cout << "4. Mostrar tabla\n";
        std::cout << "5. Visualizar tabla\n"; // Nueva opción
        std::cout << "6. Regresar al menú principal\n";
        std::cout << "Opción: ";
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar el buffer

        switch(opcion) {
            case 1:
                std::cout << "Ingrese la cadena: ";
                std::getline(std::cin, clave);
                hashString.insertar(clave);
                break;
            case 2:
                std::cout << "Ingrese la cadena a buscar: ";
                std::getline(std::cin, clave);
                std::cout << (hashString.buscar(clave) ? "Encontrado" : "No encontrado") << std::endl;
                system("pause");
                break;
            case 3:
                std::cout << "Ingrese la cadena a eliminar: ";
                std::getline(std::cin, clave);
                hashString.eliminar(clave);
                break;
            case 4:
                hashString.mostrar();
                system("pause");
                break;
            case 5: // Visualizar
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
    int opcion, clave;
    do {
        system("cls");  // Limpiar la consola
        std::cout << "\n--- Menú para Enteros ---\n";
        std::cout << "1. Insertar\n";
        std::cout << "2. Buscar\n";
        std::cout << "3. Eliminar\n";
        std::cout << "4. Mostrar tabla\n";
        std::cout << "5. Visualizar tabla\n"; // Nueva opción
        std::cout << "6. Regresar al menú principal\n";
        std::cout << "Opción: ";

        while (!(std::cin >> opcion) || opcion < 1 || opcion > 6) {
            std::cout << "Entrada inválida. Ingrese un número entre 1 y 6: ";
            std::cin.clear();  // Limpia el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta la entrada incorrecta
        }

        switch (opcion) {
            case 1:
                std::cout << "Ingrese el número: ";
                while (!(std::cin >> clave)) {
                    std::cout << "Entrada inválida. Ingrese un número entero: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                hashInt.insertar(clave);
                break;
            case 2:
                std::cout << "Ingrese el número a buscar: ";
                while (!(std::cin >> clave)) {
                    std::cout << "Entrada inválida. Ingrese un número entero: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::cout << (hashInt.buscar(clave) ? "Encontrado" : "No encontrado") << std::endl;
                system("pause");
                break;
            case 3:
                std::cout << "Ingrese el número a eliminar: ";
                while (!(std::cin >> clave)) {
                    std::cout << "Entrada inválida. Ingrese un número entero: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                hashInt.eliminar(clave);
                break;
            case 4:
                hashInt.mostrar();
                system("pause");
                break;
            case 5: // Visualizar
                hashInt.visualizar();
                break;
            case 6:
                break;
            default:
                std::cout << "Opción no válida.\n";
                system("pause");
        }
    } while (opcion != 6);
}

int main() {
    // Permitir la visualización de tildes y caracteres especiales
    setlocale(LC_ALL, "");

    HashString hashString;
    HashInt hashInt;
    int opcion;

    do {
        system("cls");  // Limpiar la consola
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
