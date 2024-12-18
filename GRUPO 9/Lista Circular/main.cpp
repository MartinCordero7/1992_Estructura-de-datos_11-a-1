/***********************************************************************
 * Module:  main.cpp
 * Author:  Maycol Celi
 * Date: 27/11/2024
 * Purpose: Lista de Personas con Listas Circulares.
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
                do {
                    cout << "Ingrese su cedula: ";
                    string cedulaInput;
                    cin >> cedulaInput;
                    if (cedulaInput.length() == 10 && validarCedula(cedulaInput)) {
                        cedulaNumerica = stol(cedulaInput); // Convertir a número
                        if (validarCedulaReal(cedulaNumerica)) {
                            imprimirResultadoCedula(true);
                            cedulaValida = true;
                        } else {
                            imprimirResultadoCedula(false);
                        }
                    } else {
                        cout << "Ingrese una cedula valida (10 digitos)\n";
                    }
                } while (!cedulaValida);

                cout << "Ingrese el nombre: ";
                cin.ignore(INT_MAX, '\n'); // Limpia el buffer antes de capturar texto
                getline(cin, nombre);

                cout << "Ingrese el apellido: ";
                getline(cin, apellido);

                lista.insertar(to_string(cedulaNumerica), nombre, apellido);
                cout << "Persona registrada.\n";
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
            std::cout << "Ordenando los nombres de A a Z...\n";
            ordenamiento.ordenarNombresExterno(lista, "datos.json");
            break;
            }

            case 7:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opción no válida. Seleccione una opción del menú.\n";
        }

        if (opcion != 7) {
            cout << "\nPresione Enter para regresar al menú...";
            cin.ignore(INT_MAX, '\n');
            cin.get();
        }
    } while (opcion != 7);

    return 0;
}

