/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Dominguez Pablo, Egas Steven, Santos Estaban
 * FECHA CREACION: Domingo,  1 de enero de 2025
 * FECHA MODIFICACION: Domingo,  1 de enero de 2025
 * Asignatura:Estructura de datos
 * Nivel: TERCERO     NRC: 1992
 *************************/


#include <iostream>
#include <string>
#include <limits>
#include <conio.h>
#include "Lista_Doble.cpp"
#include "Validation.cpp"

using namespace std;

int menu()
{
    int opcion;
    do{

        Validation<int> validation_int;
        cout << "\n--- Menu ---" << endl;
        cout << "1. Insertar Persona" << endl;
        cout << "2. Buscar Persona" << endl;
        cout << "3. Eliminar Persona" << endl;
        cout << "4. Mostrar Lista" << endl;
        cout << "5. Ordenar Lista" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opcion: ";

        opcion = validation_int.enter_a_number("int");

        if (opcion < 1 || opcion > 6){
            cout<<"\n\nOpcion incorrecta. Intente de nuevo..."<<endl;
            system("pause");
            system("cls");
        }
    } while(opcion < 1 || opcion > 6);

    return opcion;
}

int menuOrdenamiento()
{
    int opcionOrden;
    do {
        Validation<int> validation_int;
        cout << "\n--- Opciones de Ordenamiento ---" << endl;
        cout << "1. Ordenar por Primer Nombre" << endl;
        cout << "2. Ordenar por Apellido" << endl;
        cout << "3. Ordenar por Cedula" << endl;
        cout << "Seleccione una opcion de ordenamiento: ";
        opcionOrden = validation_int.enter_a_number("int");

        if (opcionOrden < 1 || opcionOrden > 3) {
            cout << "Opcion invalida. Intente de nuevo." << endl;
            system("pause");
            system("cls");
        }
    } while (opcionOrden < 1 || opcionOrden > 3);
    return opcionOrden;
}

int main() {
    Lista_Doble lista;
    Validation<string> validation_string;
    Validation<int> validation_int;
    int count = 0;
    bool datosCargados = lista.cargarDesdeArchivo("datos.txt");
    int opcion;
    do {
        opcion = menu();

        switch (opcion) {
            case 1:
            {
                string nombre1, nombre2, ape, id;

                system("cls");
                do{
                    // Ingresar y validar la cédula primero
                    cout << "\nIngrese la cedula: ";
                    id = validation_string.enter_a_string_as_num(10);
                    if(lista.validarCedula(id) == false || lista.cedulaExistente(id)) {
                        cout << "\nCedula invalida o ya ingresada. Intente de nuevo...\n";
                        system("pause");
                        system("cls");
                    }
                } while(lista.validarCedula(id) == false || lista.cedulaExistente(id));

                // Si la cédula es válida, se procede a solicitar los demás datos
                do {
                    cout << "\nIngrese el primer nombre: ";
                    nombre1 = validation_string.enter_a_char_or_string_with_may(20);
                    cout << "\nIngrese el segundo nombre: ";
                    nombre2 = validation_string.enter_a_char_or_string_with_may(20);
                    cout << "\nIngrese el apellido: ";
                    ape = validation_string.enter_a_char_or_string_with_may(20);

                    if(nombre1.empty() || nombre2.empty() || ape.empty()) {
                        cout << "\nDatos mal ingresados. Intente de nuevo...\n";
                        system("pause");
                        system("cls");
                    }
                    cout << endl;
                } while(nombre1.empty() || nombre2.empty() || ape.empty());

                cout << endl;
                lista.Insertar(nombre1, nombre2, ape, count, id);  // Se usa la cédula validada
                cout << "Persona ingresada correctamente" << endl;
                if (lista.guardarEnArchivo("datos.txt")) {
                    cout << "Datos guardados correctamente en el archivo." << endl;
                } else {
                    cout << "Hubo un error al guardar los datos en el archivo." << endl;
                }
                break;
            }

            case 2:
            {
                string id;
                system("cls");

                // Validar cédula para búsqueda
                do {
                    cout << "\nIngrese la cedula de la persona a buscar: ";
                    id = validation_string.enter_a_string_as_num(10);
                    if (!lista.validarCedula(id)) {
                        cout << "\nCedula invalida. Intente de nuevo...\n";
                    }
                } while (!lista.validarCedula(id));

                cout << endl;
                lista.Buscar(id);
                break;
            }

            case 3:
            {
                string id;
                system("cls");

                // Validar cédula para eliminar
                do {
                    cout << "\nIngrese la cedula de la persona a eliminar: ";
                    id = validation_string.enter_a_string_as_num(10);
                    if (!lista.validarCedula(id)) {
                        cout << "\nCedula invalida. Intente de nuevo...\n";
                    }
                } while (!lista.validarCedula(id));

                cout << endl;
                lista.Eliminar(id);  // Usamos la función Eliminar con cédula
                break;
            }

            case 4:
            {
                system("cls");
                lista.Mostrar();
                break;
            }

            case 5:
            {
                system("cls");
                int opcionOrden = menuOrdenamiento();
                lista.ordenarLista(opcionOrden);
                lista.guardarListaOrdenada("datos_ordenados.txt", opcionOrden);
                cout << "Lista ordenada y guardada exitosamente." << endl;
                break;
            }

            case 6:
            {
                cout << "\n\nSaliendo del programa...." << endl;
                lista.guardarEnArchivo("datos.txt");
                break;
            }
        }

    } while (opcion != 6);

    return 0;
}
