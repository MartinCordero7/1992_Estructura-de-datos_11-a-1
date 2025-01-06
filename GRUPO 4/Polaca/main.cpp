/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Dominguez Pablo, Egas Steven, Santos Estaban
 * FECHA CREACION: Domingo,  1 de enero de 2025
 * FECHA MODIFICACION: Domingo,  1 de enero de 2025
 * Asignatura:Estructura de datos
 * Nivel: TERCERO     NRC: 1992
 *************************/

#include <iostream>
#include <conio.h> // Para getch()
#include "CalculadoraPolaca.cpp"

using namespace std;

int main() {
    string infijoExpresion;
    char tecla;
    char ultimaTecla = '\0'; // Almacena el último carácter ingresado

    do {
        infijoExpresion.clear(); // Reiniciar la expresión infija
        ultimaTecla = '\0';      // Reiniciar la última tecla

        cout << "Ingrese una expresion infija valida (solo se permiten numeros, +, -, *, /, (, )):";

        while (true) {
            tecla = getch(); // Captura una tecla sin mostrarla en consola

            if (tecla == '\r') { // Enter para finalizar la entrada
                cout << endl;
                break;
            } else if (tecla == '\b') { // Retroceso
                if (!infijoExpresion.empty()) {
                    infijoExpresion.pop_back();
                    ultimaTecla = infijoExpresion.empty() ? '\0' : infijoExpresion.back();
                    cout << "\b \b"; // Borra el último carácter en consola
                }
            } else if (isdigit(tecla) || tecla == '(' || tecla == ')') {
                infijoExpresion += tecla;
                ultimaTecla = tecla;
                cout << tecla; // Imprime caracteres válidos
            } else if (Calculadora::esOperador(tecla) && !Calculadora::esOperador(ultimaTecla)) {
                infijoExpresion += tecla;
                ultimaTecla = tecla;
                cout << tecla; // Imprime el operador si el último carácter no es otro operador
            }
        }

        if (!Calculadora::esExpresionValida(infijoExpresion)) {
            cout << "\nExpresion invalida. Asegurese de usar al menos dos numeros con un operador y que los operadores no esten consecutivos.\n";
            system("pause");
            system("cls");
            continue; // Volver a pedir la expresión
        }

        // Procesar la expresión válida
        string posfijaExpresion = Calculadora::infijaAPosfija(infijoExpresion);
        string prefijaExpresion = Calculadora::infijaAPrefija(infijoExpresion);

        cout << "Expresion infija: " << infijoExpresion << endl;
        cout << "Expresion posfija: " << posfijaExpresion << endl;
        cout << "Expresion prefija: " << prefijaExpresion << endl;

        // Preguntar si desea ingresar otra expresión
        cout << "\nPresione Enter para ingresar otra expresion o cualquier otra tecla para salir." << endl;
        tecla = getch();
        if (tecla != '\r') { // Si no es Enter, salir
            cout << "Saliendo del programa..." << endl;
            break;
        }

        system("cls"); // Limpiar la pantalla para una nueva entrada
    } while (true);

    return 0;
}
