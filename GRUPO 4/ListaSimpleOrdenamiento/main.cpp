/***********************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                  *
 * Proposito:                      Lista Simple                        *
 * Autor:                          Esteban Santos                      *
 * Fecha de creacion:              20/11/2024                          *
 * Fecha de modificacion:          10/12/2024                          *
 * Materia:                        Estructura de datos                 *
 * NRC :                           1992                                *
 ***********************************************************************/
#include <iostream>
#include "lista.cpp"
#include "persona.cpp"
#include "Validation.cpp"
#include "validaciones.cpp"

using namespace std;

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    Validation<int> validation_int;
    Validation<string> validation_string;
    Validation<char> validation_char;
    Lista<Persona> listaOriginal;
    Lista<Persona> listaModificada; // Lista auxiliar para datos modificados
    int opcion;
    string cedula, apellido, nombre;

    do {
        limpiarPantalla();
        cout << "\n--- Menu ---\n";
        cout << "1. Insertar por cabeza\n";
        cout << "2. Insertar por cola\n";
        cout << "3. Mostrar lista original\n";
        cout << "4. Mostrar lista modificada\n";
        cout << "5. Eliminar caracter\n";
        cout << "6. Reemplazar caracter\n"; // Nueva opción
        cout << "7. Buscar persona\n";
        cout << "8. Eliminar persona\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opcion: ";
        opcion = validation_int.enter_a_number("int");

        switch (opcion) {
            case 1:
                cout << "\n\nIngrese cedula: ";
                cedula=validation_string.enter_a_string_as_num(10);
                cout << "\nIngrese apellido: ";
                apellido=validation_string.enter_a_char_or_string_with_may(20);
                cout << "\nIngrese nombre: ";
                nombre=validation_string.enter_a_char_or_string_with_may(20);

                if (validarCedula(cedula) && validarTexto(apellido) && validarTexto(nombre)) {
                    listaOriginal.insertarPorCabeza(Persona(cedula, apellido, nombre));
                } else {
                    cout << "\nDatos invalidos.\n";
                }
                break;

            case 2:
                cout << "\n\nIngrese cedula: ";
                cedula=validation_string.enter_a_string_as_num(10);
                cout << "\nIngrese apellido: ";
                apellido=validation_string.enter_a_char_or_string_with_may(20);
                cout << "\nIngrese nombre: ";
                nombre=validation_string.enter_a_char_or_string_with_may(10);

                if (validarCedula(cedula) && validarTexto(apellido) && validarTexto(nombre)) {
                    listaOriginal.insertarPorCola(Persona(cedula, apellido, nombre));
                } else {
                    cout << "\nDatos invalidos.\n";
                }
                break;

            case 3:
                cout << "\n\n--- Lista Original ---\n";
                listaOriginal.mostrarLista();
                break;

            case 4:
                cout << "\n\n--- Lista Modificada ---\n";
                listaModificada.mostrarLista();
                break;

            case 5: {
                char caracter;
                cout << "\n\nIngrese el caracter a eliminar: ";
                cin>>caracter;
                fflush(stdin);
                cout<<"Caracter a eliminar: "<<caracter<<endl;


                // Crear una copia de la lista original para modificarla
                listaModificada = listaOriginal;
                listaModificada.eliminarCaracter(caracter);

                cout << "\n\nCaracter eliminado en la lista modificada.\n";
                break;
            }

            case 6: { // Nueva funcionalidad para reemplazar caracteres
                char original, reemplazo;
                cout << "\n\nIngrese el caracter a reemplazar: ";
                cin>>original;
                fflush(stdin);
                cout << "\nCaracter a reemplazar: "<<original;
                cout << "\nIngrese el caracter por el cual reemplazar: ";
                cin>>reemplazo;
                fflush(stdin);
                cout << "\nCaracter a reemplazar: "<<reemplazo<<endl;

                // Crear una copia de la lista original para modificarla
                listaModificada = listaOriginal;
                listaModificada.reemplazarCaracter(original, reemplazo);

                cout << "\n\nCaracter reemplazado en la lista modificada.\n";
                break;
            }

            case 7:
                cout << "\n\nIngrese la cedula de la persona a buscar: ";
                cedula=validation_string.enter_a_string_as_num(10);
                if (validarCedula(cedula)) {
                    listaOriginal.buscarPorCedula(cedula);
                } else {
                    cout << "\nDatos no validos.\n";
                }
                break;

            case 8:
                cout << "\n\nIngrese la cedula de la persona a eliminar: ";
                cedula=validation_string.enter_a_string_as_num(10);
                if (validarCedula(cedula)) {
                    listaOriginal.eliminarPorCedula(cedula);
                } else {
                    cout << "\n\nDatos no validos.\n";
                }
                break;

            case 9:
                cout << "\nSaliendo del programa...\n";
                break;

            default:
                cout << "\nOpcion invalida.\n";
        }
        system("pause");
    } while (opcion != 9);

    return 0;
}
