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
#include <fstream>
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
    lista.cargarDesdeArchivo("personas.txt");
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
        cout << "7. Cifrar un caracter\n";
        cout << "8. Mostrar Lista Auxiliar\n";
        cout << "9. Mostrar archivo de distribucion ordenado.\n";
        cout << "10. Salir\n";
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
        cedulaInput = leerSoloNumeros(); // Capturamos directamente con leerSoloNumeros()

        if (cedulaInput.length() == 10 && validarCedula(cedulaInput)) {
            long int cedulaNumerica = stol(cedulaInput); // Convertir a número
            if (validarCedulaReal(cedulaNumerica)) {
                imprimirResultadoCedula(true);
                cedulaValida = true;
            } else {
                imprimirResultadoCedula(false);
            }
        } else {
            std::cout << "Ingrese una cedula válida (Solo números y 10 dígitos).\n";
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
    break;
}

            case 2: {
    std::cout << "Ingrese la cedula a buscar: ";
    std::string cedula = leerSoloNumeros(); // Captura directamente la cédula como cadena numérica

    Nodo* encontrado = lista.buscar(cedula); // Usamos la cédula como string
    if (encontrado != nullptr) {
        std::cout << "Persona encontrada: <Cedula: " << encontrado->getCedula()
                  << ", Nombre: " << encontrado->getNombre()
                  << ", Apellido: " << encontrado->getApellido() << ">\n";
    } else {
        std::cout << "Persona no encontrada.\n";
    }
    break;
}

            case 3: {
    std::cout << "Ingrese cedula a eliminar: ";
    std::string cedula = leerSoloNumeros(); // Capturamos directamente la cédula como string

    if (lista.eliminar(cedula)) { // Usamos la cédula directamente como string
        std::cout << "Persona eliminada correctamente.\n";
    } else {
        std::cout << "Persona no encontrada.\n";
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

case 7: {
    std::cout << "Ingrese cedula para cifrar: ";
    std::string cedula = leerSoloNumeros();

    Nodo* persona = lista.buscar(cedula);
    if (!persona) {
        std::cout << "Persona no encontrada.\n";
        break;
    }

    // Mostrar datos de la persona encontrada
    std::cout << "--Persona encontrada--\n";
    std::cout << "Cedula: " << persona->getCedula() << "\n";
    std::cout << "Nombre: " << persona->getNombre() << "\n";
    std::cout << "Apellido: " << persona->getApellido() << "\n";

    // Validar carácter a cifrar
    char caracter;
    while (true) {
        std::cout << "Ingrese caracter a cifrar: ";
        std::cin >> caracter;
        if (isalpha(caracter)) {
            break; // Es una letra válida
        }
        std::cout << "Error: Por favor ingrese un carácter alfabetico (una letra).\n";
    }

    // Validar desplazamiento como número entero
    std::string desplazamientoStr;
    int desplazamiento = 0;
    do {
        std::cout << "Ingrese el desplazamiento: ";
        desplazamientoStr = leerSoloNumeros();
        try {
            desplazamiento = std::stoi(desplazamientoStr);
            break; // Conversión exitosa
        } catch (...) {
            std::cout << "Error: Por favor ingrese un número valido para el desplazamiento.\n";
        }
    } while (true);

    // Cifrar el carácter
    lista.cifrarCaracter(cedula, caracter, desplazamiento);

    // Actualizar archivo auxiliar
    ordenamiento.guardarEnArchivo(lista, "lista_auxiliar.txt");

    std::cout << "Datos guardados en lista_auxiliar.txt\n";
    break;
}
           case 8: {
    lista.mostrarAuxiliar();
    break;
}

case 9: {
    std::cout << "Archivo de distribucion ordenado:\n";
    lista.mostrarArchivoOrdenado("personas_ordenadas.txt"); // Ajusta el nombre del archivo si es diferente
    break;
}
            case 10:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion no valida. Seleccione una opcion del menu (1-7).\n";
        }

        if (opcion != 10) {
            cout << "\nPresione Enter para regresar al menu.";
            cin.ignore(INT_MAX, '\n');
            cin.get();
        }
    } while (opcion != 10);

    return 0;
}

