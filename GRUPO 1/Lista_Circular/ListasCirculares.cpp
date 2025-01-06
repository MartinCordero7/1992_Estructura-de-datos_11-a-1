#include "ListasCirculares.h"

ListaCircular::ListaCircular() {
    primero = NULL;
    ultimo = NULL;
}

void ListaCircular::Insertar(int dato) {
    Nodo* nuevo = new Nodo(dato);
    
    if (primero == NULL) {
        primero = nuevo;
        ultimo = nuevo;
        nuevo->setSiguiente(primero);
    } else {
        ultimo->setSiguiente(nuevo);
        nuevo->setSiguiente(primero);
        ultimo = nuevo;
    }
}

void ListaCircular::Buscar(int dato) {
    if (primero == NULL) {
        cout << "Lista vacia" << endl;
        return;
    }

    Nodo* actual = primero;
    bool encontrado = false;
    
    do {
        if (actual->getDato() == dato) {
            cout << "Dato " << dato << " encontrado" << endl;
            encontrado = true;
            break;
        }
        actual = actual->getSiguiente();
    } while (actual != primero);

    if (!encontrado) {
        cout << "Dato " << dato << " no encontrado" << endl;
    }
}

void ListaCircular::Eliminar(int dato) {
    if (primero == NULL) {
        cout << "Lista vacia" << endl;
        return;
    }

    Nodo* actual = primero;
    Nodo* anterior = ultimo;
    bool encontrado = false;

    do {
        if (actual->getDato() == dato) {
            if (actual == primero) {
                primero = primero->getSiguiente();
                ultimo->setSiguiente(primero);
                
                if (primero == actual) {
                    primero = NULL;
                    ultimo = NULL;
                }
            } else {
                anterior->setSiguiente(actual->getSiguiente());
                if (actual == ultimo) {
                    ultimo = anterior;
                }
            }
            
            delete actual;
            cout << "Dato " << dato << " eliminado" << endl;
            encontrado = true;
            break;
        }
        
        anterior = actual;
        actual = actual->getSiguiente();
    } while (actual != primero);

    if (!encontrado) {
        cout << "Dato " << dato << " no encontrado" << endl;
    }
}

void ListaCircular::Mostrar() {
    if (primero == NULL) {
        cout << "Lista vacia" << endl;
        return;
    }

    Nodo* actual = primero;
    cout << "Lista: ";
    
    do {
        cout << actual->getDato() << " -> ";
        actual = actual->getSiguiente();
    } while (actual != primero);
    
    cout << "vuelta al inicio" << endl;
}

int ListaCircular::obtenerNumeroDigitos(int numero) {
    if (numero == 0) return 1;
    return floor(log10(abs(numero))) + 1;
}

int ListaCircular::obtenerDigito(int numero, int posicion) {
    return (abs(numero) / static_cast<int>(pow(10, posicion))) % 10;
}

int ListaCircular::ObtenerMaximo() {
    if (primero == NULL) return 0;

    int maximo = primero->getDato();
    Nodo* actual = primero->getSiguiente();

    do {
        maximo = max(maximo, actual->getDato());
        actual = actual->getSiguiente();
    } while (actual != primero);

    return maximo;
}

void ListaCircular::RadixSort() {
    if (primero == NULL || primero->getSiguiente() == primero) {
        return;
    }

    // Separar números positivos y negativos
    ListaCircular positivos;
    ListaCircular negativos;

    Nodo* actual = primero;
    do {
        int dato = actual->getDato();
        if (dato >= 0) {
            positivos.Insertar(dato);
        } else {
            negativos.Insertar(-dato); // Guardamos el valor absoluto
        }
        actual = actual->getSiguiente();
    } while (actual != primero);

    // Función lambda para ordenar una lista circular usando Radix Sort
    auto ordenarLista = [this](ListaCircular& lista) {
        if (lista.primero == NULL) return;

        int maximo = lista.ObtenerMaximo();
        int numDigitos = obtenerNumeroDigitos(maximo);
        vector<ListaCircular> colas(10);

        for (int pos = 0; pos < numDigitos; pos++) {
            Nodo* actual = lista.primero;
            do {
                int dato = actual->getDato();
                int digito = obtenerDigito(dato, pos);
                colas[digito].Insertar(dato);
                actual = actual->getSiguiente();
            } while (actual != lista.primero);

            lista = ListaCircular(); // Limpiar lista
            for (int i = 0; i < 10; i++) {
                while (colas[i].primero != NULL) {
                    int dato = colas[i].primero->getDato();
                    lista.Insertar(dato);
                    colas[i].Eliminar(dato);
                }
            }
        }
    };

    // Ordenar positivos y negativos por separado
    ordenarLista(positivos);
    ordenarLista(negativos);

    // Limpiar lista original
    while (primero != NULL) {
        Eliminar(primero->getDato());
    }

    // Insertar primero los negativos (en orden inverso)
    if (negativos.primero != NULL) {
        Nodo* actual = negativos.primero;
        do {
            Insertar(-actual->getDato()); // Restaurar el signo negativo
            actual = actual->getSiguiente();
        } while (actual != negativos.primero);
    }

    // Luego insertar los positivos
    if (positivos.primero != NULL) {
        Nodo* actual = positivos.primero;
        do {
            Insertar(actual->getDato());
            actual = actual->getSiguiente();
        } while (actual != positivos.primero);
    }
}