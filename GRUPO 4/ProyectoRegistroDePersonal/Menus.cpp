#include "Menus.h"
#include "BigO.h"
#include "GestorPersonas.h"
#include "extras.h"
#include "Fecha.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "ArbolRadix.h"
#include "validaciones.h"
#include <ctime>
#include "ArbolRadix.h"
#define ANSI_COLOR_CYAN "\x1b[94m"
#define ANSI_COLOR_RESET "\x1b[0m"

Menus::Menus(int totalOpciones) : totalOpciones(totalOpciones)
{
    opcionActual = 1;
}

void Menus::regresarMenu()
{
    while (true)
    {
        if (_kbhit())
        {
            char tecla = _getch();
            if (tecla == 27)
            {
                break;
            }
        }
    }
}

void Menus::mostrarMenu()
{
    system("cls");
    std::cout << "\t\t\t=== MENU DE OPCIONES===" << std::endl;
    for (int i = 1; i <= totalOpciones; i++)
    {
        if (i == opcionActual)
        {
            std::cout << "\t> " << ANSI_COLOR_CYAN;
        }
        else
        {
            std::cout << "  ";
        }
        switch (i) {
        case 1:
            std::cout << "1) Registrar Nuevo Empleado" << ANSI_COLOR_RESET << std::endl;
            break;
        case 2:
            std::cout << "2) Buscar Registro de Empleado" << ANSI_COLOR_RESET << std::endl;
            break;
        case 3:
            std::cout << "3) Eliminar Registro de Empleado" << ANSI_COLOR_RESET << std::endl;
            break;
        case 4:
            std::cout << "4) Ordenamiento QuickSort" << ANSI_COLOR_RESET << std::endl;
            break;
        case 5:
            std::cout << "5) Arbol Radix" << ANSI_COLOR_RESET << std::endl;
            break;
        case 6:
            std::cout << "6) Generar PDF" << ANSI_COLOR_RESET << std::endl;
            break;
        case 7:
            std::cout << "7) Crear backup" << ANSI_COLOR_RESET << std::endl;
            break;
        case 8:
            std::cout << "8) Entrada del personal" << ANSI_COLOR_RESET << std::endl;
            break;
        case 9:
            std::cout << "9) Salida del personal" << ANSI_COLOR_RESET << std::endl;
            break;
        case 10:
            std::cout << "10) Help" << ANSI_COLOR_RESET << std::endl;
            break;
        case 11:
            std::cout << "11) Big O" << ANSI_COLOR_RESET << std::endl;
            break;
        case 12:
            std::cout << "12) Mostrar Ubicacion" << ANSI_COLOR_RESET << std::endl;
            break;
        case 13:
            std::cout << "13) Salir del programa" << ANSI_COLOR_RESET << std::endl;
            break;
        }
    }
}

int Menus::operarMenu()
{
    GestorPersonas gestorPersonas;
    ListaCircularDoble miLista;
    ArbolRadix miArbol;
    std::string nombreArchivo = "personas.txt";
    miLista.cargarDesdeArchivo(nombreArchivo);
    cargarListaEnArbol(miLista, miArbol);

    while (true)
    {
        mostrarMenu();
        char tecla = _getch();

        switch (tecla)
        {
        case 72: // Flecha arriba
            opcionActual = (opcionActual > 1) ? opcionActual - 1 : totalOpciones;
            break;
        case 80: // Flecha abajo
            opcionActual = (opcionActual < totalOpciones) ? opcionActual + 1 : 1;
            break;
        case 13: // Tecla Enter
            system("cls");
            switch (opcionActual) {
                case 1:
                {
                    Empleado *nuevoEmpleado = gestorPersonas.ingresarPersona();
                    miLista.insertarAlInicio(nuevoEmpleado);
                    system("pause");
                    system("clean");
                    Menus menus(13);
                    menus.operarMenu();
                }
                break;
                case 2:
                {
                    cargarListaEnArbol(miLista, miArbol);
                    miArbol.buscarYMostrarEmpleadoPorCedula();
                    system("pause");
                    system("clean");
                    Menus menus(13);
                    menus.operarMenu();
                }
                break;
                case 3:
                {
                    gestorPersonas.eliminarPersona(miLista);
                    system("pause");
                    system("clean");
                    Menus menus(13);
                    menus.operarMenu();
                }
                break;
                case 4:
                {
                    miLista.quickSort();
                    miLista.imprimirLista();
                    system("pause");
                    system("clean");
                    Menus menus(13);
                    menus.operarMenu();
                }
                break;
                case 5:
                {
                    std::cout << "Funcionalidad del Arbol Radix" << std::endl;
                    std::cout << "Lista de empleados:" << std::endl;
                    miLista.imprimirLista();
                    ArbolRadix::Nodo *raiz = miArbol.getRaiz();
                    if (raiz != nullptr)
                    {
                        std::cout << "Recorrido del arbol Radix: ";
                        miArbol.imprimirArbolRecursivo(raiz, "");
                        std::cout << std::endl;
                        miArbol.graficarArbol(""); 
                    }
                    else
                    {
                        std::cout << "El arbol esta vacio" << std::endl;
                    }
                    system("pause");
                    system("cls");
                    Menus menus(13);
                    menus.operarMenu();
                }
                break;
                case 6:
                {
                    std::string text = leerArchivoComoString("personas.txt");
                    std::string outputFilePath = "personas.pdf";
                    createPdfFromText(text, outputFilePath);
                    std::cout << "PDF Creado Correctamente" << std::endl;
                    system("pause");
                    system("clean");
                    Menus menus(13);
                    menus.operarMenu();
                }
                break;
                case 7:
                {
                    createBackupRegistro();
                    createBackup();
                    system("pause");
                    system("clean");
                    Menus menus(13);
                    menus.operarMenu();
                }
                break;
                case 8:
                {
                    entradaPersonal();
                    system("pause");
                    system("clean");
                    Menus menus(13);
                    menus.operarMenu();
                }
                break;
                case 9:
                {
                    salidaPersonal();
                    system("pause");
                    system("clean");
                    Menus menus(13);
                    menus.operarMenu();
                }
                break;
                case 10:
                {
                    std::cout << "----------AYUDA----------" << std::endl;
                    system("help.chm");
                    system("pause");
                    system("clean");
                    Menus menus(13);
                    menus.operarMenu();
                }
                break;
                case 11:
                {
                    std::cout << "---Big O---" << std::endl;
                    BigO BigO(11);
                    BigO.operarMenuBigO();
                    system("pause");
                }
                break;
                case 12:
                {
                    std::cout << "Mostrando ubicacion...." << std::endl;
                    system("start map.html");
                    system("pause");
                    Menus menus(13);
                    menus.operarMenu();
                    return 0;
                }
                break;
                case 13:
                {
                    std::cout << "Saliendo del programa...." << std::endl;
                    exit(0);
                    return 0;
                }
                break;
            }
            regresarMenu();
            system("cls");
            break;
        }
    }
    return opcionActual;
}