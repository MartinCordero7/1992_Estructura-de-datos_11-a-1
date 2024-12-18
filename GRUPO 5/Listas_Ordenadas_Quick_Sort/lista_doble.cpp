#include <iostream>
#include <algorithm>
#include "lista_doble.h"

using namespace std;

template <typename T>
ListaDoble<T>::ListaDoble() : cabeza(nullptr), cola(nullptr) {}

template <typename T>
ListaDoble<T>::~ListaDoble() {
    while (cabeza != nullptr) {
        eliminarPorCabeza();
    }
}

template <typename T>
void ListaDoble<T>::insertarPorCabeza(T data) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(data);
    if (!cabeza) {
        cabeza = cola = nuevo;
    } else {
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
        cabeza = nuevo;
    }
}

template <typename T>
void ListaDoble<T>::insertarPorCola(T data) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(data);
    if (!cola) {
        cabeza = cola = nuevo;
    } else {
        nuevo->anterior = cola;
        cola->siguiente = nuevo;
        cola = nuevo;
    }
}

template <typename T>
void ListaDoble<T>::eliminarPorCabeza() {
    if (!cabeza) return;

    NodoDoble<T>* temp = cabeza;
    if (cabeza == cola) {
        cabeza = cola = nullptr;
    } else {
        cabeza = cabeza->siguiente;
        cabeza->anterior = nullptr;
    }
    delete temp;
}

template <typename T>
void ListaDoble<T>::eliminarPorCedula(string cedula) {
    NodoDoble<T>* actual = cabeza;
    while (actual != nullptr) {
        if (actual->data.getCedula() == cedula) {
            if (actual == cabeza) {
                eliminarPorCabeza();
            } else if (actual == cola) {
                cola = cola->anterior;
                cola->siguiente = nullptr;
                delete actual;
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
                delete actual;
            }
            cout << "Persona con cedula " << cedula << " eliminada exitosamente" << endl;
            return;
        }
        actual = actual->siguiente;
    }
    cout << "No se encontro ninguna persona con la cedula " << cedula << endl;
}

template <typename T>
void ListaDoble<T>::mostrarLista() const {
    NodoDoble<T>* actual = cabeza;
    while (actual != nullptr) {
        cout << actual->data.getCedula() << " "
             << actual->data.getApellido() << " "
             << actual->data.getNombre() << endl;
        actual = actual->siguiente;
    }
}

template <typename T>
void ListaDoble<T>::mostrarListaInversa() const {
    NodoDoble<T>* actual = cola;
    while (actual != nullptr) {
        cout << actual->data.getCedula() << " "
             << actual->data.getApellido() << " "
             << actual->data.getNombre() << endl;
        actual = actual->anterior;
    }
}

template <typename T>
void ListaDoble<T>::eliminarCaracter(char c) {
    NodoDoble<T>* actual = cabeza;
    while (actual != nullptr) {
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
void ListaDoble<T>::reemplazarCaracter(char original, char reemplazo) {
    NodoDoble<T>* actual = cabeza;
    while (actual != nullptr) {
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
void ListaDoble<T>::buscarPorCedula(string cedula) {
    NodoDoble<T>* actual = cabeza;
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
ListaDoble<T>::ListaDoble(const ListaDoble& otra) : cabeza(nullptr), cola(nullptr) {
    copiarListaDoble(otra.cabeza);
}

template <typename T>
ListaDoble<T>& ListaDoble<T>::operator=(const ListaDoble& otra) {
    if (this != &otra) {
        while (cabeza != nullptr) {
            eliminarPorCabeza();
        }
        copiarListaDoble(otra.cabeza);
    }
    return *this;
}

template <typename T>
void ListaDoble<T>::copiarListaDoble(const NodoDoble<T>* otraCabeza) {
    const NodoDoble<T>* actual = otraCabeza;
    while (actual != nullptr) {
        insertarPorCola(actual->data);
        actual = actual->siguiente;
    }
}
