/*********
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNOS: Xavier Altamirano, Martin Cordero, Isaac Oña
 * FECHA CREACION: Viernes, 31 de Enero de 2025
 * FECHA MODIFICACION: Lunes, 03 de Febrero de 2025
 * Enunciado del problema: Splaytree
 * Nivel: TERCERO     NRC: 1992
 *********/
#include <iostream>
#include <iomanip>
#include "splaytree.cpp" 
using namespace std;

class Application {
private:
    void runRecursive(SplayTree& tree) {
        int option, value;

        if (menu(option)) {
            switch (option) {
                case 1:
                    cout << "Ingrese un numero: ";
                    cin >> value;
                    tree.insert(value);
                    tree.display();
                    break;
                case 2:
                    cout << "Recorrido Inorden: ";
                    tree.displayInorder();
                    cout << "Recorrido Preorden: ";
                    tree.displayPreorder();
                    cout << "Recorrido Postorden: ";
                    tree.displayPostorder();
                    break;
                case 3:
                    cout << "Ingrese un numero para calcular su profundidad y nivel: ";
                    cin >> value;
                    cout << "Altura del arbol: " << tree.getHeight() << endl;
                    cout << "Profundidad del nodo " << value << ": " << tree.getDepth(value) << endl;
                    cout << "Nivel del nodo " << value << ": " << tree.getLevel(value) << endl;
                    break;
                case 4:
                    tree.drawTree(); // Llamada al dibujo responsive del árbol
                    break;
                default:
                    cout << "Opcion no valida. Intente de nuevo." << endl;
            }
            runRecursive(tree);
        }
    }

    bool menu(int& option) {
        cout << "\nOpciones:\n1. plis 1 key\n2. Mostrar recorridos\n3. Calcular altura, profundidad y nivel\n4. Dibujar arbol\n5. Salir\nElija una opcion: ";
        cin >> option;
        return option != 5;
    }

public:
    void run() {
        SplayTree tree;
        runRecursive(tree);
    }
};

// Eliminar el main() de aquí ya que está en mainsplay.cpp
