#include "trie.cpp"
#include <iostream>
#include <limits>
#include <locale>
#include <cctype>
#include <cstdlib>
#include <graphics.h>
#include <conio.h> // Para _getch()

using namespace std;

// Función para limpiar el búfer de entrada
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Función para leer una palabra sin números
string leerPalabraSinNumeros() {
    string palabra;
    char c;
    cout << "Ingrese una palabra (solo letras, los demás caracteres serán ignorados): ";
    while (true) {
        c = cin.get(); // Lee un carácter
        if (c == '\n') { // Termina la lectura al presionar Enter
            break;
        }
        if (isalpha(c)) { // Solo permite letras
            palabra += toupper(c); // Convierte a mayúscula
        }
    }
    return palabra;
}

// Función para mostrar el menú principal
void mostrarMenu() {
    cout << "\n--- Menu del Trie ---\n";
    cout << "1. Insertar Titulo\n";
    cout << "2. Eliminar Titulo\n";
    cout << "3. Imprimir Arbol (Modo Grafico)\n";
    cout << "4. Recorrido infijo (ordenado)\n";
    cout << "5. Imprimir datos (Altura, Profundidad, Nivel)\n";
    cout << "6. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    setlocale(LC_ALL, "");
    Trie root; // Instancia del Trie
    int opcion; // Opción seleccionada por el usuario
    int contador = 0; // Contador de elementos en el Trie
    string palabra; // Variable para almacenar las palabras ingresadas

    system("cls");

    do {
        mostrarMenu();
        cin >> opcion;
        clearInputBuffer(); // Limpia el búfer después de leer la opción
        system("cls");

        switch (opcion) {
            case 1: // Insertar Título
                palabra = leerPalabraSinNumeros();
                if (!palabra.empty()) {
                    root.insert(palabra);
                    contador++;
                    cout << "Palabra '" << palabra << "' insertada correctamente.\n";
                } else {
                    cout << "Error: No se ingresaron letras válidas.\n";
                }
                break;

            case 2: // Eliminar Título
                palabra = leerPalabraSinNumeros();
                if (!palabra.empty()) {
                    if (root.deletion(palabra)) {
                        contador--;
                        cout << "Palabra '" << palabra << "' eliminada correctamente.\n";
                    } else {
                        cout << "La palabra '" << palabra << "' no existe en el Trie.\n";
                    }
                } else {
                    cout << "Error: No se ingresaron letras válidas.\n";
                }
                break;

            case 3: // Imprimir Árbol (Modo Gráfico)
                if (contador >= 2) {
                    cout << "Mostrando arbol en modo grafico...\n";
                    root.printTree();
                    cout << "Presione cualquier tecla para continuar...\n";
                    _getch(); // Pausa hasta que se presione una tecla
                } else {
                    cout << "Error: El arbol debe tener al menos 2 elementos para mostrarlo.\n";
                }
                break;

            case 4: // Recorrido infijo (ordenado)
                if (contador >= 2) {
                    cout << "Recorrido infijo (ordenado):\n";
                    root.printInOrder();
                } else {
                    cout << "Error: El arbol debe tener al menos 2 elementos para mostrar el recorrido.\n";
                }
                break;

            case 5: // Imprimir datos (Altura, Profundidad, Nivel)
                if (contador >= 2) {
                    cout << "Altura del arbol: " << root.getHeight() << endl;
                    cout << "Profundidad del arbol: " << root.getDepth() << endl;
                    cout << "Nivel maximo del arbol: " << root.getLevel() << endl;
                } else {
                    cout << "Error: El arbol debe tener al menos 2 elementos para mostrar sus datos.\n";
                }
                break;

            case 6: // Salir
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion invalida. Por favor, intente nuevamente.\n";
        }

        if (opcion != 6) {
            cout << "\nPresione Enter para continuar...";
            cin.get(); // Espera a que el usuario presione Enter
            system("cls");
        }

    } while (opcion != 6);

    return 0;
}
