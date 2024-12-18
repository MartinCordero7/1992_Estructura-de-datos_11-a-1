/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Conversion de infija a prefija o posfija            *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              17/12/2024                                          *
 * Fecha de modificacion:          18/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/

#include <iostream>
#include <string>
#include <conio.h> // Para _getch() en Windows
#include "conversion.cpp"
#include "validaciones.cpp"

using namespace std;

// Función para obtener una opción utilizando solo teclas numéricas del 1 al 5
int obtenerOpcionNumerica() {
    char tecla;

    while (true) {
        tecla = _getch(); // Captura una tecla sin necesidad de presionar Enter

        // Verificar si la tecla está en el rango numérico (1-5)
        if (tecla >= '1' && tecla <= '5') {
            return tecla - '0'; // Convierte el char en int y lo retorna
        }
        // Si no es un número válido, simplemente no hace nada
    }
}

int main() {
    string infix;
    string prefix;
    string postfix;

    while (true) {
        int opcion;

        // Mostrar menú
        cout << "\nMenu:\n";
        cout << "1. Ingresar expresion infija\n";
        cout << "2. Mostrar expresion infija\n";
        cout << "3. Convertir a prefijo\n";
        cout << "4. Convertir a posfijo\n";
        cout << "5. Salir\n";

        // Obtener opción usando únicamente las teclas 1-5
        cout << "Seleccione una opcion (1-5): ";
        opcion = obtenerOpcionNumerica();
        cout << opcion << endl; // Mostrar la opción seleccionada

        // Procesar la opción seleccionada
        switch (opcion) {
            case 1: {
                cout << "Ingrese la expresion infija (sin espacios, con formato adecuado): ";
                getline(cin, infix);

                if (infix.find(' ') != string::npos) {
                    cout << "Error: La expresion no debe contener espacios. Intenta de nuevo." << endl;
                    infix = "";
                } else if (!isValidExpression(infix)) {
                    cout << "La expresion ingresada no es valida. Intenta de nuevo." << endl;
                    infix = "";
                } else {
                    cout << "Expresion infija registrada correctamente." << endl;
                }
                break;
            }
            case 2: {
                if (infix.empty()) {
                    cout << "Error: No se ha ingresado una expresion infija." << endl;
                } else {
                    cout << "Expresion infija: " << infix << endl;
                }
                break;
            }
            case 3: {
                 if (infix.empty()) {
                    cout << "Error: No se ha ingresado una expresion infija." << endl;
                } else {
                    prefix = infixToPrefix(infix);
                    cout << "Expresion prefija: " << prefix << endl;
                }
                break;
            }
            
            case 4: {
                if (infix.empty()) {
                    cout << "Error: No se ha ingresado una expresion infija." << endl;
                } else {
                    postfix = infixToPostfix(infix);
                    cout << "Expresion posfija: " << postfix << endl;
                }
                break;
            }
            case 5:
                cout << "Saliendo del programa..." << endl;
                return 0;
        }
    }

    return 0;
}
