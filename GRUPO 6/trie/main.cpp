#include "trie.cpp"
#include <iostream>
#include <limits>

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void mostrarMenu() {
    cout << "\n--- MenU del Trie ---\n";
    cout << "1. Insertar palabra\n";
    cout << "2. Eliminar palabra\n";
    cout << "3. Imprimir Arbol\n";
    cout << "4. Recorrido infijo (ordenado)\n";
    cout << "5. Imprimir datos (Altura, Profundidad, Nivel)\n";
    cout << "6. Salir\n";
    cout << "Seleccione una opciOn: ";
}

int main() {
    Trie root;
    int opcion;
    string palabra;
    int contador=0;

    do {
        mostrarMenu();
        cin >> opcion;

        switch(opcion) {
            case 1:
                bool esValida;
                do {
                    cout << "Ingrese el titulo a insertar : ";
                    cin >> palabra;
                    esValida = true;
                    for (char &c : palabra) {
                        if (!isalnum(c)) {
                            esValida = false;
                            break;
                        }
                        c = toupper(c); // Convertir a mayúscula
                    }
                    if (!esValida || palabra.empty()) {
                        cout << "Error: La palabra contiene caracteres inválidos o está vacía. Intente nuevamente.\n";
                    }
                } while (!esValida || palabra.empty());
                
                if (root.search(palabra)) {
                    cout << "Error: La palabra '" << palabra << "' ya existe en el Trie.\n";
                } else {
                    root.insert(palabra);
                    cout << "Palabra '" << palabra << "' insertada.\n";
                    contador++;
                }
                break;

            case 2:
                if(contador==0){
                    cout << "No hay titulos para eliminar\n";
                } else {
 
                do {
                    cout << "Ingrese el titulo a eliminar: ";
                    cin >> palabra;
                    esValida = true;
                    for (char &c : palabra) {
                        if (!isalnum(c)) {
                            esValida = false;
                            break;
                        }
                        c = toupper(c); // Convertir a mayúscula
                    }
                    if (!esValida || palabra.empty()) {
                        cout << "Error: El titulo contiene caracteres inválidos o está vacía. Intente nuevamente.\n";
                    }
                } while (!esValida || palabra.empty());

                if (root.search(palabra)) {
                    root.deletion(palabra);
                    cout << "Palabra '" << palabra << "' eliminada.\n";
                    contador--;
                } else {
                    cout << "La palabra '" << palabra << "' no existe en el árbol.\n";
                }
         
                }
                break;

            case 3:
                if(contador>=2){
                cout << "\nEstructura del Arbol:\n";
                root.printTree();
                } else {
                    cout << "No se puede imprimir el arbol con menos de 2 palabras\n";
                }
                break;

            case 4:
                if (contador >= 2)
                {
                cout << "\nPalabras en orden infijo:\n";
                root.printInOrder(); 
                } else {
                    cout << "No se puede imprimir  el orden con menos de 2 palabras\n";
                }
                break;

            case 5:
                if (contador >= 2)
                {
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
                cout << "Opción inválida. Intente nuevamente.\n";
        }

        clearInputBuffer();

    } while(opcion != 6);

    return 0;
}