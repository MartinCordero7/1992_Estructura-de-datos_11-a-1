/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO: Altamirano Xavier, Cordero Martin, Oña Isaac
 * FECHA CREACION: Lunes, 16 de diciembre de 2024
 * FECHA MODIFICACION: Lunes, 16 de diciembre de 2024
 * Enunciado del problema: Mediante el metodo de ordenacion externa RadixSort implementarlo en una lista doble
 * Nivel: TERCERO     NRC: 1992
 *************************/
#include "Lista_Doble.cpp"
#include "Validation.cpp"
#include <iostream>
#include <string>
#include <limits>


using namespace std;

int menu()
{
    int opcion;
    do
    {

        Validation<int> validation_int;
        cout << "\n--- Menu ---" << endl;
        cout << "1. Insertar Nodo" << endl;
        cout << "2. Eliminar Nodo" << endl;
        cout << "3. Buscar Nodo" << endl;
        cout << "4. Mostrar Lista" << endl;
        cout << "5. Ordenar Radix" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese su opcion: ";

        opcion = validation_int.enter_a_number("int");

        if (opcion < 1 || opcion > 5)
        {
            cout << "\n\nOpcion incorrecta. Intente de nuevo..." << endl;
            system("pause");
            system("cls");
        }
    } while (opcion < 1 || opcion > 6);

    return opcion;
}

int main()
{
    Lista_Doble lista;
    Validation<string> validation_string;
    int count = 0;

    int opcion;
    do
    {
        opcion = menu();

        switch (opcion)
        {
        case 1:
        {
            string nombre1, nombre2, ape, id;

            system("cls");
            do
            {
                lista.agregarCedula(id);
                cout << "\nIngrese primer nombre: ";
                nombre1 = validation_string.enter_a_char_or_string_with_may(20);
                cout << "\nIngrese segundo nombre: ";
                nombre2 = validation_string.enter_a_char_or_string_with_may(20);
                cout << "\nIngrese apellido: ";
                ape = validation_string.enter_a_char_or_string_with_may(20);
                cout << "\nIngrese cedula: ";
                id = validation_string.enter_a_string_as_num(10);
                if (lista.validarCedula(id) == false || (nombre1.empty() || nombre2.empty() || ape.empty()))
                {
                    cout << "\nDatos mal ingresados. Intente de nuevo...\n";
                    system("pause");
                    system("cls");
                }
                cout << endl;
            } while (lista.validarCedula(id) == false || (nombre1.empty() || nombre2.empty() || ape.empty()));
            cout << endl;
            lista.Insertar(nombre1, nombre2, ape, count, id);
            cout << endl;
            Passord(nombre1, nombre2, ape);
            break;
        }
        case 2:
        {
            string nombre1, nombre2, ape;
            system("cls");
            do
            {
                cout << "\nIngrese el primer nombre del nuevo nodo: ";
                nombre1 = validation_string.enter_a_char_or_string_with_may(20);
                cout << "\nIngrese el segundo nombre del nuevo nodo: ";
                nombre2 = validation_string.enter_a_char_or_string_with_may(20);
                cout << "\nIngrese el apellido del nuevo nodo: ";
                ape = validation_string.enter_a_char_or_string_with_may(20);

                if (nombre1.empty() || nombre2.empty() || ape.empty())
                {
                    cout << "\nDatos mal ingresados. Intente de nuevo...\n";
                    system("pause");
                    system("cls");
                }

            } while (nombre1.empty() || nombre2.empty() || ape.empty());

            cout << endl;
            lista.Eliminar(nombre1, nombre2, ape);
            break;
        }

        case 3:
        {
            string nombre1, nombre2, ape;
            system("cls");
            do
            {

                cout << "\nIngrese el primer nombre del nodo a buscar: ";
                nombre1 = validation_string.enter_a_char_or_string_with_may(20);
                cout << "\nIngrese el segundo nombre del nodo a buscar: ";
                nombre2 = validation_string.enter_a_char_or_string_with_may(20);
                cout << "\nIngrese el apellido del nodo a buscar: ";
                ape = validation_string.enter_a_char_or_string_with_may(20);

                if (nombre1.empty() || nombre2.empty() || ape.empty())
                {
                    cout << "\nDatos mal ingresados. Intente de nuevo...\n";
                    system("pause");
                    system("cls");
                }
            } while (nombre1.empty() || nombre2.empty() || ape.empty());
            cout << endl;
            lista.Buscar(nombre1, nombre2, ape);
            break;
        }
        case 4:
            system("cls");
            cout << "\nLista actual: ";
            lista.Mostrar();
            break;
        case 5:
        {
            system("cls");

            string archivoOriginal = "C:/Users/alejo/Programas U/ListasDobles/nodos.txt";
            string archivoOrdenado = "C:/Users/alejo/Programas U/ListasDobles/nodos_ordenados.txt";

            lista.exportarAArchivo(archivoOriginal);
            lista.radixSortExterno(archivoOriginal, archivoOrdenado, 10);
            

            cout << "Lista ordenada por cédulas utilizando RadixSort externo." << endl;
            break;
        }

        case 6:
            cout << "\n\nSaliendo del programa...." << endl;
            break;
        }
    } while (opcion != 6);

    return 0;
}
