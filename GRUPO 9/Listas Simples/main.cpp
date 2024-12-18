/***********************************************************************
 * Module:  main.cpp
 * Author:  Erika Guayanay,Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * Purpose: Metodo de Ordenamiento Externo para lista simple con el metodo (Distribution sort)
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "Lista_Simple.h"
#include "MetodoOrdenamientoExterno.h"
#include "Validaciones.h"
#include <iostream>
#include <cstdlib> // Para system("cls") o system("clear")

using namespace std;


int main()
{
    ListaSimple listaPrincipal;
    ListaSimple listaAuxiliar;
    MetodoOrdenamientoExterno metodoOrdenamiento;
    string cedula, nombre, apellido;
    int desplazar;
    char caracter;
    int opcion;

    listaPrincipal.cargarDesdeArchivo("personas.txt");

    do
    {
        system("cls");
        cout << "** Menu de opciones **\n";
        cout << "1. Insertar persona\n";
        cout << "2. Buscar persona\n";
        cout << "3. Eliminar persona\n";
        cout << "4. Mostrar lista\n";
        cout << "5. Eliminar caracter de nombre\n";
        cout << "6. Cifrar un caracter\n";
        cout << "7. Mostrar lista auxiliar\n";
        cout << "8. Ordenar lista por nombre (Distribution Sort)\n";
        cout << "9. Mostrar archivo de distribucion ordenado\n";
        cout << "10. Salir\n";
        opcion = capturarSoloNumeros();

        system("cls");
        switch (opcion)
        {
        case 1: // Insertar persona
        {
            do
            {
                cout << "Ingrese la cedula: ";
                cedula = capturarCedula(); // Usamos la nueva función para capturar solo números para cédula

                if (!validarCedulaReal(cedula))
                {
                    cout << "Cedula invalida. Intente de nuevo.\n";
                }
                else if (!validarCedulaUnica(cedula))
                {
                    cout << "La cedula ya esta registrada. Intente de nuevo.\n";
                }
                else
                {
                    break;
                }
            }
            while (true);

            do
            {
                cout << "Ingrese nombre: ";
                nombre = capturarSoloLetras(); // Capturamos solo letras
                nombre = normalizarNombre(nombre); // Normalizamos el nombre

                if (!validarSoloLetras(nombre)) // Por si quieres verificar adicionalmente
                {
                    cout << "Error: El nombre debe contener solo letras. Intente nuevamente.\n";
                }
                else
                {
                    break;
                }
            }
            while (true);

            do
            {
                cout << "Ingrese apellido: ";
                apellido = capturarSoloLetras(); // Capturamos solo letras
                apellido = normalizarNombre(apellido); // Normalizamos el apellido

                if (!validarSoloLetras(apellido)) // Por si quieres verificar adicionalmente
                {
                    cout << "Error: El apellido debe contener solo letras. Intente nuevamente.\n";
                }
                else
                {
                    break;
                }
            }
            while (true);

            listaPrincipal.insertarACola(cedula, nombre, apellido);
            listaPrincipal.guardarEnArchivo(cedula, nombre, apellido, "personas.txt");
            registrarCedula(cedula); // Registrar cédula en el conjunto
            cout << "Persona registrada exitosamente.\n";
            break;
        }

        case 2:   // Buscar persona
        {
            do
            {
                cout << "Ingrese cedula para buscar: ";
                cedula = capturarCedula();
                if (!validarCedulaReal(cedula))
                {
                    cout << "Cedula invalida. Intente de nuevo.\n";
                }
                else
                {
                    break;
                }
            }
            while (true);

            Nodo* persona = listaPrincipal.buscar(cedula);
            if (persona == nullptr)
            {
                cout << "Error: Persona no encontrada.\n";
            }
            break;
        }

        case 3:   // Eliminar persona
        {
            do
            {
                cout << "Ingrese cedula a eliminar: ";
                cedula = capturarCedula();
                if (!validarCedulaReal(cedula))
                {
                    cout << "Cedula invalida. Intente de nuevo.\n";
                }
                else
                {
                    break;
                }
            }
            while (true);

            if (listaPrincipal.eliminar(cedula))
            {
                cout << "Persona eliminada exitosamente.\n";
            }
            else
            {
                cout << "Error: Persona no encontrada o no pudo ser eliminada.\n";
            }
            break;
        }

        case 4:   // Mostrar lista principal
        {
            listaPrincipal.mostrar();
            break;
        }

        case 5:   // Eliminar carácter de nombre
        {
            cout << "Ingrese cedula: ";
            cedula = capturarCedula();

            // Validar formato de cédula
            if (!validarCedulaReal(cedula))
            {
                cout << "Cedula invalida. Intente de nuevo.\n";
                break;
            }

            // Verificar si la cédula existe en el archivo
            Nodo* personaEncontrada = listaPrincipal.buscar(cedula);
            if (personaEncontrada == nullptr)
            {
                // cout << "La cedula no existe en el archivo.\n";
                break;
            }

            // Si la cédula existe, proceder con la eliminación del carácter
            cout << "Ingrese caracter a eliminar ej.(a - A): ";
            caracter= capturarUnaLetra();
            listaPrincipal.eliminarCaracter(cedula, caracter, listaAuxiliar);

            // Liberar el nodo encontrado ya que no será reutilizado
            delete personaEncontrada;

            break;
        }

        case 6:   // Cifrar carácter
        {
            cout << "Ingrese cedula para cifrar: ";
            cedula = capturarCedula();

            // Validar formato de cédula
            if (!validarCedulaReal(cedula))
            {
                cout << "Cedula invalida. Intente de nuevo.\n";
                break;
            }

            // Verificar si la cédula existe en la lista
            Nodo* personaEncontrada = listaPrincipal.buscar(cedula);
            if (personaEncontrada == nullptr)
            {
                cout << "Error: La cedula no existe en el archivo.\n";
                break;
            }

            // Si la cédula existe, proceder con el cifrado del carácter
            cout << "Ingrese caracter a cifrar: ";
            caracter= capturarUnaLetra();

            cout << "\nIngrese el desplazamiento: ";
            desplazar=validarNumero1a25();

            listaPrincipal.cifrarCaracter(cedula, caracter, desplazar, listaAuxiliar);

            // Liberar el nodo encontrado ya que no será reutilizado
            delete personaEncontrada;

            break;
        }


        case 7:   // Mostrar lista auxiliar
        {
            listaAuxiliar.mostrar();
            break;
        }

        case 8:   // Ordenar lista por nombre (Distribución Sort)
        {
            vector<string> archivosCubetas;
            metodoOrdenamiento.distribuirDatos("personas.txt", archivosCubetas);  // Distribuir los datos en cubetas
            for (const auto& archivo : archivosCubetas)
            {
                metodoOrdenamiento.ordenarArchivo(archivo);  // Ordenar cada cubeta
            }
            metodoOrdenamiento.fusionarArchivos(archivosCubetas, "personas_ordenadas.txt");  // Fusionar los archivos
            cout << "La lista ha sido ordenada y guardada en 'personas_ordenadas.txt'.\n";
            break;
        }

        case 9:   // Mostrar archivo de distribución ordenado
        {
            metodoOrdenamiento.mostrarArchivo("personas_ordenadas.txt");
            break;
        }

        case 10:   // Salir
        {
            cout << "Saliendo...\n";
            break;
        }

        default:
        {
            cout << "Opcion invalida. Intente de nuevo.\n";

            break;
        }
        }
        system("pause");
    }
    while (opcion != 10);

    return 0;
}

