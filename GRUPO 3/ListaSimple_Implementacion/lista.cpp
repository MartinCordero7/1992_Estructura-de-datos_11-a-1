#include "lista.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template <typename T>
Lista<T>::Lista() : cabeza(nullptr) {}

template <typename T>
Lista<T>::~Lista() {
    while (cabeza != nullptr) {
        eliminarPorCabeza();
    }
}

template <typename T>
void Lista<T>::insertarPorCabeza(T data) {
    Nodo<T>* nuevo = new Nodo<T>(data);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

template <typename T>
void Lista<T>::insertarPorCola(T data) {
    Nodo<T>* nuevo = new Nodo<T>(data);
    if (!cabeza) {
        cabeza = nuevo;
    } else {
        Nodo<T>* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

template <typename T>
void Lista<T>::eliminarPorCabeza() {
    if (!cabeza) return;
    Nodo<T>* temp = cabeza;
    cabeza = cabeza->siguiente;
    delete temp;
}

template<typename T>
void Lista<T>::eliminarPorCedula(string cedula) {
    if (cabeza == nullptr) {
        cout << "La lista esta vacia" << endl;
        return;
    }

    // Caso especial: si es el primer nodo
    if (cabeza->data.getCedula() == cedula) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        cout << "Persona con cedula " << cedula << " eliminada exitosamente" << endl;
        return;
    }

    // Buscar en el resto de la lista
    Nodo<T>* actual = cabeza;
    Nodo<T>* anterior = nullptr;

    while (actual != nullptr && actual->data.getCedula() != cedula) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != nullptr) {
        anterior->siguiente = actual->siguiente;
        delete actual;
        cout << "Persona con cedula " << cedula << " eliminada exitosamente" << endl;
    } else {
        cout << "No se encontro ninguna persona con la cedula " << cedula << endl;
    }
}

template<typename T>
void Lista<T>::buscarPorCedula(string cedula) {
    if (cabeza == nullptr) {
        cout << "La lista esta vacia" << endl;
        return;
    }

    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.getCedula() == cedula) {
            cout << "Persona encontrada:" << endl;
            cout << "Cedula: " << actual->data.getCedula() << endl;
            cout << "Nombre: " << actual->data.getNombre() << endl;
            cout << "Apellido: " << actual->data.getApellido() << endl;
            return;
        }
        actual = actual->siguiente;
    }
    cout << "No se encontro ninguna persona con la cedula " << cedula << endl;
}

template <typename T>
void Lista<T>::mostrarLista() const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        cout << actual->data.getCedula() << " "
             << actual->data.getApellido() << " "
             << actual->data.getNombre() << endl;
        actual = actual->siguiente;
    }
}

template <typename T>
void Lista<T>::eliminarCaracter(char c) {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        // Eliminar carácter de cédula, apellido y nombre
        string cedula = actual->data.getCedula();
        cedula.erase(remove(cedula.begin(), cedula.end(), c), cedula.end());
        actual->data.setCedula(cedula);

        string apellido = actual->data.getApellido();
        apellido.erase(remove(apellido.begin(), apellido.end(), c), apellido.end());
        actual->data.setApellido(apellido);

        string nombre = actual->data.getNombre();
        nombre.erase(remove(nombre.begin(), nombre.end(), c), nombre.end());
        actual->data.setNombre(nombre);

        actual = actual->siguiente;
    }
}

template <typename T>
Lista<T>::Lista(const Lista& otra) : cabeza(nullptr) {
    copiarLista(otra.cabeza);
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista& otra) {
    if (this != &otra) {
        while (cabeza != nullptr) {
            eliminarPorCabeza();
        }
        copiarLista(otra.cabeza);
    }
    return *this;
}

template <typename T>
void Lista<T>::copiarLista(const Nodo<T>* otraCabeza) {
    const Nodo<T>* actual = otraCabeza;
    while (actual != nullptr) {
        insertarPorCola(actual->data);
        actual = actual->siguiente;
    }
}

template <typename T>
void Lista<T>::reemplazarCaracter(char original, char reemplazo) {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        // Reemplazar carácter en cédula, apellido y nombre
        string cedula = actual->data.getCedula();
        replace(cedula.begin(), cedula.end(), original, reemplazo);
        actual->data.setCedula(cedula);

        string apellido = actual->data.getApellido();
        replace(apellido.begin(), apellido.end(), original, reemplazo);
        actual->data.setApellido(apellido);

        string nombre = actual->data.getNombre();
        replace(nombre.begin(), nombre.end(), original, reemplazo);
        actual->data.setNombre(nombre);

        actual = actual->siguiente;
    }
}

template <typename T>
void Lista<T>::ordenarPorApellido() {
    // Calcular el tamaño de la lista
    int n = 0;
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        n++;
        actual = actual->siguiente;
    }

    // Convertir la lista en un vector para facilitar el acceso
    vector<Nodo<T>*> nodos(n);
    actual = cabeza;
    for (int i = 0; i < n; i++) {
        nodos[i] = actual;
        actual = actual->siguiente;
    }

    // Shell Sort en el vector de punteros
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Nodo<T>* temp = nodos[i];
            int j;
            for (j = i; j >= gap && nodos[j - gap]->data.getApellido() > temp->data.getApellido(); j -= gap) {
                nodos[j] = nodos[j - gap];
            }
            nodos[j] = temp;
        }
    }

    // Reconstruir la lista enlazada desde el vector ordenado
    cabeza = nodos[0];
    actual = cabeza;
    for (int i = 1; i < n; i++) {
        actual->siguiente = nodos[i];
        actual = actual->siguiente;
    }
    actual->siguiente = nullptr; // Finalizar la lista correctamente
}
