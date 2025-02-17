#include "CuadradoMagico.cpp"

int main() {
    int opcion;
    do {
        system("cls"); // o "clear" si usas Linux
        cout << "=====================================\n";
        cout << "         MENU CUADRADO MAGICO        \n";
        cout << "=====================================\n";
        cout << "1. Cuadrado 3x3\n";
        cout << "2. Cuadrado 4x4\n";
        cout << "3. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        if(cin.fail() || opcion < 1 || opcion > 3) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nEntrada invalida.\n";
            system("pause");
            continue;
        }
        if(opcion == 1) {
            int mode;
            cout << "\nSeleccione el modo para el cuadrado 3x3:\n";
            cout << "1. Generar automaticamente\n";
            cout << "2. Ingresar manualmente\n";
            cout << "Opcion: ";
            while(!(cin >> mode)) {  // Validación para 3x3
                cout << "Entrada invalida. Ingrese un numero valido: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            int cuadrado[3][3];
            bool ok = false;
            if(mode == 1) {
                generar3x3(cuadrado);
                ok = true;
            } else if(mode == 2) {
                ok = solveManual3x3(cuadrado);
            } else {
                cout << "\nModo invalido. Se generara automaticamente.\n";
                generar3x3(cuadrado);
                ok = true;
            }
            if(ok) {
                imprimir3x3(cuadrado);
                system("pause");
                mostrarGrafico3x3(cuadrado);
            }
        } else if(opcion == 2) {
            int mode;
            cout << "\nSeleccione el modo para el cuadrado 4x4:\n";
            cout << "1. Generar automaticamente\n";
            cout << "2. Ingresar manualmente (solo si los numeros forman progresion aritmetica)\n";
            cout << "Opcion: ";
            while(!(cin >> mode)) {  // Validación para 4x4
                cout << "Entrada invalida. Ingrese un numero valido: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            int cuadrado[4][4];
            bool ok = false;
            if(mode == 1) {
                generar4x4(cuadrado);
                ok = true;
            } else if(mode == 2) {
                ok = solveManual4x4(cuadrado);
            } else {
                cout << "\nModo invalido. Se generara automaticamente.\n";
                generar4x4(cuadrado);
                ok = true;
            }
            if(ok) {
                imprimir4x4(cuadrado);
                system("pause");
                mostrarGrafico4x4(cuadrado);
            }
        }
    } while(opcion != 3);
    return 0;
}
