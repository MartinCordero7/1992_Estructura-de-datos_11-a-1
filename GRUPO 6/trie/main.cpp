#include "trie.cpp"
#include <iostream>
#include <limits>
#include <locale>
#include <cctype> // Para usar isalpha y toupper
#include <cstdlib> // Para usar system("cls") y system("pause")

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Función para leer una palabra sin números
string leerPalabraSinNumeros() {
    string palabra;
    char c;
    while (true) {
        c = cin.get(); // Lee un carácter
        if (c == '\n') { // Si el usuario presiona Enter, termina la lectura
            break;
        }
        if (isalpha(c)) { // Solo permite letras
            palabra += toupper(c); // Convierte a mayúscula y agrega a la palabra
        }
        // Los números y otros caracteres simplemente se ignoran
    }
    return palabra;
}

void mostrarMenu() {
    cout << "\n--- Menu del Trie ---\n";
    cout << "1. Insertar palabra\n";
    cout << "2. Eliminar palabra\n";
    cout << "3. Imprimir Arbol\n";
    cout << "4. Recorrido infijo (ordenado)\n";
    cout << "5. Imprimir datos (Altura, Profundidad, Nivel)\n";
    cout << "6. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    // Configurar la consola para usar la configuración regional predeterminada del sistema
    setlocale(LC_ALL, "");
    Trie root;
    int opcion;
    string palabra;
    int contador = 0;

    system("cls"); // Limpiar la consola al iniciar el programa

    do {
        mostrarMenu();
        cin >> opcion;
        clearInputBuffer(); // Limpiar el buffer después de leer la opción
        system("cls"); // Limpiar la consola después de seleccionar una opción

        switch (opcion) {
            case 1: {
                cout << "Ingrese el titulo a insertar: ";
                palabra = leerPalabraSinNumeros(); // Lee la palabra sin números

                if (palabra.empty()) {
                    cout << "Error: La palabra no puede estar vacia. Intente nuevamente.\n";
                } else if (root.search(palabra)) {
                    cout << "Error: La palabra '" << palabra << "' ya existe en el Trie.\n";
                } else {
                    root.insert(palabra);
                    cout << "Palabra '" << palabra << "' insertada.\n";
                    contador++;
                }
                break;
            }

            case 2: {
                if (contador == 0) {
                    cout << "No hay titulos para eliminar\n";
                } else {
                    cout << "Ingrese el titulo a eliminar: ";
                    palabra = leerPalabraSinNumeros(); // Lee la palabra sin números

                    if (palabra.empty()) {
                        cout << "Error: La palabra no puede estar vacia. Intente nuevamente.\n";
                    } else if (root.search(palabra)) {
                        root.deletion(palabra);
                        cout << "Palabra '" << palabra << "' eliminada.\n";
                        contador--;
                    } else {
                        cout << "La palabra '" << palabra << "' no existe en el árbol.\n";
                    }
                }
                break;
            }

            case 3:
                if (contador >= 2) {
                    cout << "\nEstructura del Arbol:\n";
                    root.printTree();
                } else {
                    cout << "No se puede imprimir el arbol con menos de 2 palabras\n";
                }
                break;

            case 4:
                if (contador >= 2) {
                    cout << "\nPalabras en orden infijo:\n";
                    root.printInOrder();
                } else {
                    cout << "No se puede imprimir el orden con menos de 2 palabras\n";
                }
                break;

            case 5:
                if (contador >= 2) {
                    cout << "\nDatos del Trie:\n";
                    cout << "Altura: " << root.getHeight() << endl;
                    cout << "Profundidad: " << root.getDepth() << endl;
                    cout << "Nivel: " << root.getLevel() << endl;
                } else {
                    cout << "No se puede imprimir los datos con menos de 2 palabras\n";
                }
                break;

            case 6:
                cout << "Saliendo...\n";
                break;

            default:
                wcout << L"Opción inválida. Intente nuevamente.\n";
        }

    } while (opcion != 6);

    return 0;
}