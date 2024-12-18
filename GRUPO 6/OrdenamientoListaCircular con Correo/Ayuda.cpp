/*******************************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                                  *
 * Proposito:                      Ayuda para manejar el sistema                                       *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz                    *
 * Fecha de creacion:              17/12/2024                                                          *
 * Fecha de modificacion:          18/12/2024                                                          *
 * Materia:                        Estructura de datos                                                 *
 * NRC :                           1992                                                                *
 *******************************************************************************************************/

#include "Ayuda.h"
#include <iostream>
#include <conio.h>

using namespace std;

void mostrarAyuda() {
    system("cls");

    // Encabezado
    cout << "=======================================" << endl;
    cout << "              Uso Básico              " << endl;
    cout << "=======================================" << endl;

    // Sección de uso básico
    cout << "\n1. Registrar un libro:" << endl;
    cout << "   Para registrar un nuevo libro, seleccione la opción" << endl;
    cout << "   'Agregar libro' desde el menú principal. Ingrese los" << endl;
    cout << "   datos requeridos como título, autor, año de publicación" << endl;
    cout << "   y género, y haga clic en 'GUARDAR'."<< endl;

    cout << "\n2. Buscar un libro:" << endl;
    cout << "   Utilice la opción 'Buscar libro' e ingrese los parámetros" << endl;
    cout << "   de búsqueda (como título o autor) para encontrar un libro en el registro." << endl;

    cout << "\n3. Eliminar un libro:" << endl;
    cout << "   Seleccione el libro que desea eliminar de la lista de libros" << endl;
    cout << "   y haga clic en 'ELIMINAR'. Confirme la acción para borrar el libro del registro." << endl;

    cout << "\n4. Imprimir lista de libros:" << endl;
    cout << "   Puede imprimir la lista de libros registrados seleccionando" << endl;
    cout << "   la opción 'IMPRIMIR' en el menú principal." << endl;

    // Separador
    cout << "\n=======================================" << endl;
    cout << "           Funciones Avanzadas         " << endl;
    cout << "=======================================" << endl;

    // Sección de funciones avanzadas
    cout << "\n1. Realizar un Backup:" << endl;
    cout << "   Para realizar un backup de los datos, seleccione la" << endl;
    cout << "   opción 'BACKUP' desde el menú. El sistema guardará" << endl;
    cout << "   una copia de seguridad de los datos en formato de fecha y hora" << endl;
    cout << "   (año-mes-día-hora-minuto-segundo)." << endl;

    cout << "\n2. Restaurar desde un Backup:" << endl;
    cout << "   Para restaurar un backup, seleccione 'RESTAURAR BACKUP'" << endl;
    cout << "   desde el menú y elija el archivo de backup correspondiente." << endl;
    cout << "   El sistema recuperará los datos a partir de esa copia de seguridad." << endl;

    // Instrucción para continuar
    cout << "\n=======================================" << endl;
    cout << "Presione 'Enter' para continuar..." << endl;
    cout << "=======================================" << endl;

    // Pausa para el usuario
    _getch();
}
