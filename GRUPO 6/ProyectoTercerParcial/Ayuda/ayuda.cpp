/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Archivo principal de ayuda                               *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include <iostream>
#include <conio.h>

using namespace std;

void mostrarAyuda()
{
    system("cls");

    // Encabezado
    cout << "=======================================" << endl;
    cout << "              Uso Basico              " << endl;
    cout << "=======================================" << endl;

    // Sección de ayuda del menú principal
    cout << "\n1. Registrar entrega:" << endl;
    cout << "   - Permite registrar una nueva entrega." << endl;
    cout << "   - Se solicita la cédula del cliente." << endl;
    cout << "   - Si la cédula ya está registrada, se pregunta si desea agregar otra entrega para el mismo cliente." << endl;
    cout << "   - Si no está registrada, se solicita el nombre y número de celular del cliente." << endl;
    cout << "   - Se selecciona la zona de entrega en un mapa." << endl;

    cout << "\n2. Buscar entrega:" << endl;
    cout << "   - Permite buscar una entrega por la cédula del cliente." << endl;
    cout << "   - Se muestra la información de la entrega si se encuentra." << endl;

    cout << "\n3. Eliminar entrega:" << endl;
    cout << "   - Permite eliminar una entrega registrada." << endl;
    cout << "   - Se solicita la cédula del cliente." << endl;
    cout << "   - Si hay múltiples entregas para la misma cédula, se muestra una lista para seleccionar cuál eliminar." << endl;

    cout << "\n4. Ver todas las entregas:" << endl;
    cout << "   - Muestra una lista de todas las entregas registradas." << endl;
    cout << "   - Incluye información del cliente y la zona de entrega." << endl;

    cout << "\n5. Realizar entregas:" << endl;
    cout << "   - Calcula la ruta óptima para realizar las entregas pendientes." << endl;
    cout << "   - Se solicita la ubicación del local en un mapa." << endl;

    cout << "\n6. Exportar entregas a PDF:" << endl;
    cout << "   - Exporta todas las entregas registradas a un archivo PDF." << endl;
    cout << "   - El archivo PDF se abre automáticamente después de ser generado." << endl;

    cout << "\n7. Crear backup:" << endl;
    cout << "   - Crea una copia de seguridad de las entregas registradas." << endl;
    cout << "   - El archivo de backup se guarda con la fecha y hora actuales." << endl;

    cout << "\n8. Restaurar backup:" << endl;
    cout << "   - Restaura las entregas desde un archivo de backup previamente creado." << endl;

    cout << "\n9. Salir:" << endl;
    cout << "   - Sale del menú principal y cierra la aplicación." << endl;

    // Sección de atajos
    cout << "\n=== Atajos ===" << endl;
    cout << "- F1: Abre la ayuda del menú." << endl;

    // Instrucción para continuar
    cout << "\n=============================================" << endl;
    cout << "Presione 'Enter' dos veces para continuar..." << endl;
    cout << "=============================================" << endl;

    // Pausa para el usuario
    cin.ignore(); // Limpia el buffer de entrada
    cin.get();    // Espera Enter
}

int main()
{
    mostrarAyuda();
    return 0; // Cierra el programa inmediatamente
}
