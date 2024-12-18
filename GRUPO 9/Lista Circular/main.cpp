/***********************************************************************
 * Module:  main.cpp
 * Author:  Erika Guayanay, Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * Purpose: Metodo de Ordenamiento Externo para lista circular con el método (Distribution sort)
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "ListasCirculares.h"
#include "Validaciones.h"
#include "Ordenamiento.h"
#include <iostream>
#include <string>
using namespace std;

void limpiarConsola() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    ListaCircular lista;
    Ordenamiento ordenamiento; // Instancia de la clase Ordenamiento
    ordenamiento.ordenarPorCubetas(lista);
    string nombre, apellido;
    long int cedulaNumerica;
    char caracter;
    int opcion;

    do {
        limpiarConsola();
        cout << "\n*** Menu de opciones ***\n";
        cout << "1. Insertar persona\n";
        cout << "2. Buscar persona\n";
        cout << "3. Eliminar persona\n";
        cout << "4. Mostrar lista\n";
        cout << "5. Eliminar caracter\n";
        cout << "6. Ordenar nombres (A-Z)\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Limpia el buffer después de capturar la opción
        cin.clear();
        cin.ignore(INT_MAX, '\n');

        switch (opcion) {
            case 1: {
    bool cedulaValida = false;
    std::string cedulaInput;
    do {
        std::cout << "Ingrese su cedula: ";
        std::cin >> cedulaInput;
        if (cedulaInput.length() == 10 && validarCedula(cedulaInput)) {
            long int cedulaNumerica = stol(cedulaInput); // Convertir a número
            if (validarCedulaReal(cedulaNumerica)) {
                imprimirResultadoCedula(true);
                cedulaValida = true;
            } else {
                imprimirResultadoCedula(false);
            }
        } else {
            std::cout << "Ingrese una cedula valida (Solo numeros y 10 dígitos).\n";
        }
    } while (!cedulaValida);

    // Limpiar el búfer antes de usar getline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string nombre, apellido;

    // Solicitar el nombre
    do {
        std::cout << "Ingrese el nombre: ";
        std::getline(std::cin, nombre);
    } while (!validarNombre(nombre));

    // Solicitar el apellido
    do {
        std::cout << "Ingrese el apellido: ";
        std::getline(std::cin, apellido);
    } while (!validarNombre(apellido));

    // Insertar la persona en la lista
    lista.insertar(cedulaInput, nombre, apellido);
    std::cout << "Persona registrada.\n";
    break;
}
            case 2: {
                cout << "Ingrese la cedula a buscar: ";
                cin >> cedulaNumerica;
                Nodo* encontrado = lista.buscar(to_string(cedulaNumerica));
                if (encontrado != nullptr) {
                    cout << "Persona encontrada: <Cedula: " << encontrado->getCedula()
                         << ", Nombre: " << encontrado->getNombre()
                         << ", Apellido: " << encontrado->getApellido() << ">\n";
                } else {
                    cout << "Persona no encontrada.\n";
                }
                break;
            }

            case 3: {
                cout << "Ingrese cedula a eliminar: ";
                cin >> cedulaNumerica;
                if (lista.eliminar(to_string(cedulaNumerica))) {
                    cout << "Persona eliminada correctamente.\n";
                } else {
                    cout << "Persona no encontrada.\n";
                }
                break;
            }

            case 4: {
                cout << "\nLista de personas:\n";
                lista.mostrar();
                break;
            }

            case 5: {
                cout << "Ingrese cedula de la persona: ";
                cin >> cedulaNumerica;
                cout << "Ingrese caracter a eliminar: ";
                cin >> caracter;
                lista.eliminarCaracter(to_string(cedulaNumerica), caracter);
                break;
            }

            case 6: {
    std::cout << "Guardando la lista original en personas.txt...\n";
    ordenamiento.guardarEnArchivo(lista, "personas.txt");

    std::cout << "Ordenando los nombres...\n";
    ordenamiento.ordenarPorCubetas(lista);

    std::cout << "Lista ordenada:\n";
    lista.mostrar();
    break;
}

            case 7:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion no valida. Seleccione una opción del menu (1-7).\n";
        }

        if (opcion != 7) {
            cout << "\nPresione Enter para regresar al menu.";
            cin.ignore(INT_MAX, '\n');
            cin.get();
        }
    } while (opcion != 7);

    return 0;
}

