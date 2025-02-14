/**
 * @file
 * @description 
 * @author Eric000
 * @date 2/9/2025, 8:13:35 PM
 */

#include "table_string.cpp"
#include "table_int.cpp"
#include <iostream>
#include <cstdlib>
#include <clocale>
#include <windows.h>
#include <limits>
#include <conio.h>

void menuString(HashString& hashString, int metodo) {
    int opcion = 0;
    std::string clave;
    const char* opciones[] = {"Agregar", "Buscar", "Eliminar", "Grafico", "Regresar al menu principal"};
    const int numOpciones = sizeof(opciones) / sizeof(opciones[0]);


    do {
        system("cls");
        std::cout << "\nHash Strings\n";
        for (int i = 0; i < numOpciones; ++i) {
            if (i == opcion)
                std::cout << ">> " << opciones[i] << " <<\n";
            else
                std::cout << "   " << opciones[i] << "\n";
        }

        char tecla = _getch();
        if (tecla == 72) { // Flecha Arriba
            opcion = (opcion - 1 + numOpciones) % numOpciones;
        } else if (tecla == 80) { // Flecha Abajo
            opcion = (opcion + 1) % numOpciones;
        } else if (tecla == '\r') { // Enter
            switch(opcion) {
                case 0:
                    std::cout << "Agrege el string: ";
                    std::getline(std::cin, clave);
                    hashString.insertar(clave, metodo);
                    break;
                case 1:
                    std::cout << "Ingrese el string: ";
                    std::getline(std::cin, clave);
                    std::cout << (hashString.buscar(clave, metodo) ? "Encontrado" : "No encontrado") << std::endl;
                    system("pause");
                    break;
                case 2:
                    std::cout << "Ingrese el string:  ";
                    std::getline(std::cin, clave);
                    hashString.eliminar(clave, metodo);
                    break;
                case 3:
                    hashString.visualizar();
                    system("pause");
                    break;
                case 4:
                    return;
            }
        }
    } while(true);
}

void menuInt(HashInt& hashInt, int metodo) {
    int opcion = 0, clave;
    const char* opciones[] = {"Agregar", "Buscar", "Eliminar", "Grafico", "Regresar al menu principal"};
    const int numOpciones = sizeof(opciones) / sizeof(opciones[0]);

    do {
        system("cls");
        std::cout << "\n Hash Integer\n";
        for (int i = 0; i < numOpciones; ++i) {
            if (i == opcion)
                std::cout << ">> " << opciones[i] << " <<\n";
            else
                std::cout << "   " << opciones[i] << "\n";
        }

        char tecla = _getch();
        if (tecla == 72) { // Flecha Arriba
            opcion = (opcion - 1 + numOpciones) % numOpciones;
        } else if (tecla == 80) { // Flecha Abajo
            opcion = (opcion + 1) % numOpciones;
        } else if (tecla == '\r') { // Enter
            switch(opcion) {
                case 0:
                    std::cout << "Agregue el numero: ";
                    while (!(std::cin >> clave)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "No valido. Ingrese de nuevo:   ";
                    }
                    hashInt.insertar(clave, metodo);
                    break;
                case 1:
                    std::cout << "Ingrese el numero: ";
                    while (!(std::cin >> clave)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "No valido. Ingrese de nuevo:   ";
                    }
                    std::cout << (hashInt.buscar(clave, metodo) ? "Encontrado" : "No encontrado") << std::endl;
                    break;
                case 2:
                    std::cout << "Ingrese el numero: ";
                    while (!(std::cin >> clave)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "No valido. Ingrese de nuevo:   ";
                    }
                    hashInt.eliminar(clave, metodo);
                    break;
                case 3:
                    hashInt.visualizar();
                    system("pause");
                    break;
                case 4:
                    return;
            }
        }
    } while(true);
}

int seleccionarMetodo() {
    int metodo = 0;
    const char* opciones[] = {"Linear Probing: f(i) = i", "Quadratic Probing: f(i) = i * i", "Double Hashing: f(i) = i * hash2(elem)"};
    const int numOpciones = sizeof(opciones) / sizeof(opciones[0]);

    do {
        system("cls");
        std::cout << "\nSeleccione la forma de calculo\n";
        for (int i = 0; i < numOpciones; ++i) {
            if (i == metodo)
                std::cout << ">> " << opciones[i] << " <<\n";
            else
                std::cout << "   " << opciones[i] << "\n";
        }

        char tecla = _getch();
        if (tecla == 72) { // Flecha Arriba
            metodo = (metodo - 1 + numOpciones) % numOpciones;
        } else if (tecla == 80) { // Flecha Abajo
            metodo = (metodo + 1) % numOpciones;
        } else if (tecla == '\r') { // Enter
            return metodo + 1;
        }
    } while(true);
}

int main() {
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    setlocale(LC_ALL, "spanish");
    
    int opcion = 0, metodo;
    const char* opciones[] = {"Hash Strings", "Hash Integer", "Salir"};
    const int numOpciones = sizeof(opciones) / sizeof(opciones[0]);

    do {
        HashString hashString;
        HashInt hashInt;
        
        system("cls");
        std::cout << "\nClosed Hashing\n";
        for (int i = 0; i < numOpciones; ++i) {
            if (i == opcion)
                std::cout << ">> " << opciones[i] << " <<\n";
            else
                std::cout << "   " << opciones[i] << "\n";
        }

        char tecla = _getch();
        if (tecla == 72) { // Flecha Arriba
            opcion = (opcion - 1 + numOpciones) % numOpciones;
        } else if (tecla == 80) { // Flecha Abajo
            opcion = (opcion + 1) % numOpciones;
        } else if (tecla == '\r') { // Enter
            if (opcion == 0 || opcion == 1) {
                metodo = seleccionarMetodo();
                if (opcion == 0) {
                    menuString(hashString, metodo);
                } else if (opcion == 1) {
                    menuInt(hashInt, metodo);
                }
            } else if (opcion == 2) {
                break;
            }
        }
    } while(true);
    
    return 0;
}