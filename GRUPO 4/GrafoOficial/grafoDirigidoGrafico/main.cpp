/**********
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Steven Egas, Pablo Dominguez, Esteban Santos
 * FECHA CREACION: Viernes,  7 de Febrero de 2025
 * FECHA MODIFICACION: Miercoles, 12 de Febrero de 2025
 * PROYECTO: Grafos
 * Nivel: TERCERO     NRC: 1992
 ***********/
#include <iostream>
#include <limits>
#include <conio.h>
#include <windows.h>
#include "Grafo.cpp"

void mostrarMenuPrincipal(int opcion)
{
    const char* opciones[] = {"Grafo grande", "Grafo pequeño", "Salir del programa"};
    const int numOpciones = sizeof(opciones) / sizeof(opciones[0]);

    system("cls");
    std::cout << "\nMenu Principal\n";
    for (int i = 0; i < numOpciones; ++i) {
        if (i == opcion)
            std::cout << ">> " << opciones[i] << " <<\n";
        else
            std::cout << "   " << opciones[i] << "\n";
    }
}

void mostrarMenuTipoGrafo(int opcion)
{
    const char* opciones[] = {"Grafo dirigido", "Grafo no dirigido"};
    const int numOpciones = sizeof(opciones) / sizeof(opciones[0]);

    system("cls");
    std::cout << "\nTipo de Grafo\n";
    for (int i = 0; i < numOpciones; ++i) {
        if (i == opcion)
            std::cout << ">> " << opciones[i] << " <<\n";
        else
            std::cout << "   " << opciones[i] << "\n";
    }
}

void mostrarMenuRepresentacion(int opcion)
{
    const char* opciones[] = {"Representación lógica", "Lista de adyacencia", "Matriz de adyacencia", "Salir"};
    const int numOpciones = sizeof(opciones) / sizeof(opciones[0]);

    system("cls");
    std::cout << "\nMenu Representacion\n";
    for (int i = 0; i < numOpciones; ++i) {
        if (i == opcion)
            std::cout << ">> " << opciones[i] << " <<\n";
        else
            std::cout << "   " << opciones[i] << "\n";
    }
}

int obtenerOpcion()
{
    int opcion;
    while (true)
    {
        std::cin >> opcion;
        if (std::cin.fail() || opcion < 1)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Por favor, ingrese un número entero positivo: ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return opcion;
        }
    }
}

int obtenerVertice(int numNodos)
{
    int vertice;
    while (true)
    {
        std::cin >> vertice;
        if (std::cin.fail() || vertice < 0 || vertice >= numNodos)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Por favor, ingrese un número entero positivo entre 0 y " << numNodos - 1 << ": ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return vertice;
        }
    }
}

int main()
{
    Grafo grafo;
    int opcionPrincipal = 0, opcionTipoGrafo = 0, opcionRepresentacion = 0, verticeInicial;

    do
    {
        mostrarMenuPrincipal(opcionPrincipal);
        char tecla = _getch();
        if (tecla == 72) { // Flecha Arriba
            opcionPrincipal = (opcionPrincipal - 1 + 3) % 3;
        } else if (tecla == 80) { // Flecha Abajo
            opcionPrincipal = (opcionPrincipal + 1) % 3;
        } else if (tecla == '\r') { // Enter
            if (opcionPrincipal == 0 || opcionPrincipal == 1)
            {
                int numNodos = (opcionPrincipal == 0) ? 18 : 8;
                do {
                    mostrarMenuTipoGrafo(opcionTipoGrafo);
                    tecla = _getch();
                    if (tecla == 72) { // Flecha Arriba
                        opcionTipoGrafo = (opcionTipoGrafo - 1 + 2) % 2;
                    } else if (tecla == 80) { // Flecha Abajo
                        opcionTipoGrafo = (opcionTipoGrafo + 1) % 2;
                    } else if (tecla == '\r') { // Enter
                        break;
                    }
                } while (true);

                bool dirigido = (opcionTipoGrafo == 0);
                grafo.nuevoGrafo(numNodos, dirigido);
                std::cout << "Nuevo grafo generado." << std::endl;

                do
                {
                    mostrarMenuRepresentacion(opcionRepresentacion);
                    tecla = _getch();
                    if (tecla == 72) { // Flecha Arriba
                        opcionRepresentacion = (opcionRepresentacion - 1 + 4) % 4;
                    } else if (tecla == 80) { // Flecha Abajo
                        opcionRepresentacion = (opcionRepresentacion + 1) % 4;
                    } else if (tecla == '\r') { // Enter
                        switch (opcionRepresentacion)
                        {
                        case 0:
                            // grafo.representacionLogica();
                            grafo.representacionLogicaGrafica("Representación lógica");

                            break;
                        case 1:
                            // grafo.representacionListaAdyacencia();
                            grafo.representacionListaAdyacenciaGrafica("Lista de Adyacencia");

                            break;
                        case 2:
                            // grafo.representacionMatrizAdyacencia();
                            grafo.representacionMatrizAdyacenciaGrafica("Matriz de Adyacencia");
                            break;
                        case 3:
                            std::cout << "Volviendo al menú principal..." << std::endl;
                            break;
                        default:
                            std::cout << "Opción no válida." << std::endl;
                            break;
                        }

                        if (opcionRepresentacion >= 0 && opcionRepresentacion <= 2)
                        {
                            std::cout << "Ingrese el vértice inicial para la búsqueda por amplitud: ";
                            verticeInicial = obtenerVertice(numNodos);
                            grafo.busquedaAmplitud(verticeInicial);
                        }
                    }
                } while (opcionRepresentacion != 3 || tecla != '\r');
            }
            else if (opcionPrincipal == 2)
            {
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            }
        }
    } while (true);

    return 0;
}