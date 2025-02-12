#include "n_reinas.cpp"
#include <stdlib.h>

using namespace std;

void limpiarPantalla() {
    system("cls");
}

void mostrarMenu() {
    cout << "\n=== MENU PRINCIPAL - N REINAS ===\n";
    cout << "1. Resolver problema de N reinas\n";
    cout << "2. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    int opcion;
    string entrada;
    bool continuar = true;

    while (continuar) {
        limpiarPantalla();
        mostrarMenu();
        cin >> entrada;

        // Validar que la entrada sea un número
        bool esNumero = true;
        for (char c : entrada) {
            if (!isdigit(c)) {
                esNumero = false;
                break;
            }
        }

        if (!esNumero) {
            cout << "\nOpcion invalida. Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            continue;
        }

        opcion = stoi(entrada);

        switch (opcion) {
            case 1: {
                limpiarPantalla();
                int N = obtenerN();
                int tablero[MAX_N][MAX_N] = {0};

                if (resolverNReinas(tablero, 0, N)) {
                    dibujarTablero(tablero, N);
                } else {
                    cout << "No hay solucion para N = " << N << endl;
                    cout << "\nPresione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                }
                break;
            }
            case 2:
                continuar = false;
                cout << "\nFinalizando el programa...\n";
                break;
            default:
                cout << "\nOpcion invalida. Presione Enter para continuar...";
                cin.ignore();
                cin.get();
                break;
        }
    }

    return 0;
}