#include "ListasCirculares.h"
#include <stdlib.h>
using namespace std;

bool esEntero(string linea) {
    if (linea.empty()) return false;
    
    // Permite que el primer carácter sea un signo negativo
    size_t inicio = (linea[0] == '-') ? 1 : 0;
    
    // Verifica que todos los caracteres sean dígitos
    for (size_t i = inicio; i < linea.length(); i++) {
        if (!isdigit(linea[i])) return false;
    }
    
    return true;
}

int main() {
    ListaCircular* lista = new ListaCircular();
    int opcion, dato;
    string linea;
    bool repite;

    do {
        system("cls");
        cout << "***********Listas Circulares***********" << endl;
        cout << "1. Insertar" << endl;
        cout << "2. Buscar" << endl;
        cout << "3. Eliminar" << endl;
        cout << "4. Mostrar" << endl;
        cout << "5. Ordenar con Radix Sort" << endl;
        cout << "6. Salir" << endl;
        
        repite = true;
        while (repite) {
            cout << "Opcion: ";
            getline(cin, linea);

            if (esEntero(linea)) {
                opcion = atoi(linea.c_str());
                if (opcion >= 1 && opcion <= 6) {
                    repite = false;
                } else {
                    cout << "Opcion invalida. Debe ser un numero entre 1 y 6." << endl;
                }
            } else {
                cout << "No has ingresado un valor entero. Intentalo nuevamente" << endl;
            }
        }

        switch (opcion) {
        case 1: {
            repite = true;
            while (repite) {
                cout << "Ingrese el dato a insertar: ";
                getline(cin, linea);

                if (esEntero(linea)) {
                    dato = atoi(linea.c_str());
                    lista->Insertar(dato);
                    repite = false;
                } else {
                    cout << "No has ingresado un valor entero. Intentalo nuevamente" << endl;
                }
            }
            break;
        }
        case 2: {
            repite = true;
            while (repite) {
                cout << "Ingrese el dato a buscar: ";
                getline(cin, linea);

                if (esEntero(linea)) {
                    dato = atoi(linea.c_str());
                    lista->Buscar(dato);
                    repite = false;
                } else {
                    cout << "No has ingresado un valor entero. Intentalo nuevamente" << endl;
                }
            }
            break;
        }
        case 3: {
            repite = true;
            while (repite) {
                cout << "Ingrese el dato a eliminar: ";
                getline(cin, linea);

                if (esEntero(linea)) {
                    dato = atoi(linea.c_str());
                    lista->Eliminar(dato);
                    repite = false;
                } else {
                    cout << "No has ingresado un valor entero. Intentalo nuevamente" << endl;
                }
            }
            break;
        }
        case 4:
            lista->Mostrar();
            break;
        case 5:
            lista->RadixSort();
            cout << "Lista ordenada con Radix Sort." << endl;
            lista->Mostrar();
            break;
        }
        system("pause");
    } while (opcion != 6);

    delete lista;
    return 0;
}