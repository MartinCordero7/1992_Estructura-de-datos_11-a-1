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
        cout << "9. Mostrar archivo de distribución ordenado.\n";
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

case 7: {
    std::cout << "Ingrese cedula para cifrar: ";
    std::string cedula;
    std::cin >> cedula;

    Nodo* persona = lista.buscar(cedula);
    if (!persona) {
        std::cout << "Persona no encontrada.\n";
        break;
    }

    // Mostrar datos de la persona encontrada inmediatamente
    std::cout << "--Persona encontrada--\n";
    std::cout << "Cedula: " << persona->getCedula() << "\n";
    std::cout << "Nombre: " << persona->getNombre() << "\n";
    std::cout << "Apellido: " << persona->getApellido() << "\n";

    // Validar "Ingrese caracter a cifrar"
    char caracter;
    while (true) {
        std::cout << "Ingrese caracter a cifrar: ";
        std::cin >> caracter;
        if (isalpha(caracter)) {
            break; // Es una letra válida
        }
        std::cout << "Error: Por favor ingrese un caracter alfabetico (una letra).\n";
    }

    // Validar "Ingrese el desplazamiento"
    int desplazamiento;
    while (true) {
        std::cout << "Ingrese el desplazamiento: ";
        std::cin >> desplazamiento;

        if (std::cin.fail()) { // Si la entrada no es un número
            std::cin.clear();  // Limpia el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora lo que queda en el buffer
            std::cout << "Error: Por favor ingrese un numero entero.\n";
        } else {
            break; // Entrada válida
        }
    }

    // Cifrar el carácter en el nombre
    lista.cifrarCaracter(cedula, caracter, desplazamiento);

    // Actualizar archivo auxiliar
    ordenamiento.guardarEnArchivo(lista, "lista_auxiliar.txt");

    std::cout << "Datos guardados en lista_auxiliar.txt\n";
    break;
}
            case 8: {
    std::cout << "Lista auxiliar:\n";
                lista.mostrarListaAuxiliar("lista_auxiliar.txt");
                break;
}

case 9: {
    std::cout << "Archivo de distribución ordenado:\n";
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

