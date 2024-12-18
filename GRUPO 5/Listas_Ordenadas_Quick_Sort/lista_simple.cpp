#include <iostream>
#include <algorithm>
#include "lista_simple.h"
using namespace std;

template <typename T>
ListaSimple<T>::ListaSimple() : cabeza(nullptr) {}

template <typename T>
ListaSimple<T>::~ListaSimple() {
    while (cabeza != nullptr) {
        eliminarPorCabeza();
    }
}

template <typename T>
void ListaSimple<T>::insertarPorCabeza(T data) {
    Nodo<T>* nuevo = new Nodo<T>(data);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

template <typename T>
void ListaSimple<T>::insertarPorCola(T data) {
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
void ListaSimple<T>::eliminarPorCabeza() {
    if (!cabeza) return;
    Nodo<T>* temp = cabeza;
    cabeza = cabeza->siguiente;
    delete temp;
}

template<typename T>
void ListaSimple<T>::eliminarPorCedula(string cedula) {
    if (cabeza == NULL) {
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

    // Buscar en el resto de la ListaSimple
    Nodo<T>* actual = cabeza;
    Nodo<T>* anterior = NULL;

    while (actual != NULL && actual->data.getCedula() != cedula) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != NULL) {
        anterior->siguiente = actual->siguiente;
        delete actual;
        cout << "Persona con cedula " << cedula << " eliminada exitosamente" << endl;
    } else {
        cout << "No se encontro ninguna persona con la cedula " << cedula << endl;
    }
}

template<typename T>
void ListaSimple<T>::buscarPorCedula(string cedula) {
    if (cabeza == NULL) {
        cout << "La ListaSimple esta vacia" << endl;
        return;
    }

    Nodo<T>* actual = cabeza;
    while (actual != NULL) {
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
void ListaSimple<T>::mostrarLista() const {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }

    cout << "Lista de personas:" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "| Cédula     | Apellido        | Nombre       |" << endl;
    cout << "---------------------------------------------" << endl;

    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        printf("| %-10s | %-15s | %-12s |\n", 
            actual->data.getCedula().c_str(), 
            actual->data.getApellido().c_str(), 
            actual->data.getNombre().c_str());
        actual = actual->siguiente;
    }
    
    cout << "---------------------------------------------" << endl;
}

template <typename T>
void ListaSimple<T>::eliminarCaracter(char c) {
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
ListaSimple<T>::ListaSimple(const ListaSimple& otra) : cabeza(nullptr) {
    copiarListaSimple(otra.cabeza);
}

template <typename T>
ListaSimple<T>& ListaSimple<T>::operator=(const ListaSimple& otra) {
    if (this != &otra) {
        while (cabeza != nullptr) {
            eliminarPorCabeza();
        }
        copiarListaSimple(otra.cabeza);
    }
    return *this;
}

template <typename T>
void ListaSimple<T>::copiarListaSimple(const Nodo<T>* otraCabeza) {
    const Nodo<T>* actual = otraCabeza;
    while (actual != nullptr) {
        insertarPorCola(actual->data);
        actual = actual->siguiente;
    }
}

template <typename T>
void ListaSimple<T>::reemplazarCaracter(char original, char reemplazo) {
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

// Método para obtener el último nodo de la lista
template <typename T>
Nodo<T>* ListaSimple<T>::getLastNode() {
    if (!cabeza) return nullptr;
    
    Nodo<T>* actual = cabeza;
    while (actual->siguiente != nullptr) {
        actual = actual->siguiente;
    }
    return actual;
}

template <typename T>
Nodo<T>* ListaSimple<T>::partitionByCedula(Nodo<T>* low, Nodo<T>* high) {
    // Seleccionar el último elemento como pivote
    T pivot = high->data;
    
    // Nodo anterior al pivote de partición
    Nodo<T>* partitionPrev = nullptr;
    Nodo<T>* current = low;
    Nodo<T>* tail = high;
    
    // Recorrer y particionar la lista
    while (current != high) {
        if (current->data.getCedula() <= pivot.getCedula()) {
            // Si es el primer elemento que cumple la condición
            if (!partitionPrev) {
                partitionPrev = low;
            } else {
                partitionPrev = partitionPrev->siguiente;
            }
            
            // Intercambiar datos
            std::swap(current->data, partitionPrev->data);
        }
        current = current->siguiente;
    }
    
    // Colocar el pivote en la posición correcta
    if (!partitionPrev) {
        partitionPrev = low;
    } else {
        partitionPrev = partitionPrev->siguiente;
    }
    
    // Intercambiar pivote
    std::swap(partitionPrev->data, tail->data);
    
    return partitionPrev;
}

// Método de partición por nombre
template <typename T>
Nodo<T>* ListaSimple<T>::partitionByNombre(Nodo<T>* low, Nodo<T>* high) {
    T pivot = high->data;
    
    Nodo<T>* partitionPrev = nullptr;
    Nodo<T>* current = low;
    Nodo<T>* tail = high;
    
    while (current != high) {
        if (current->data.getNombre() <= pivot.getNombre()) {
            if (!partitionPrev) {
                partitionPrev = low;
            } else {
                partitionPrev = partitionPrev->siguiente;
            }
            
            std::swap(current->data, partitionPrev->data);
        }
        current = current->siguiente;
    }
    
    if (!partitionPrev) {
        partitionPrev = low;
    } else {
        partitionPrev = partitionPrev->siguiente;
    }
    
    std::swap(partitionPrev->data, tail->data);
    
    return partitionPrev;
}


template <typename T>
Nodo<T>* ListaSimple<T>::partitionByApellido(Nodo<T>* low, Nodo<T>* high) {
    T pivot = high->data;
    
    Nodo<T>* partitionPrev = nullptr;
    Nodo<T>* current = low;
    Nodo<T>* tail = high;
    
    while (current != high) {
        if (current->data.getApellido() <= pivot.getApellido()) {
            if (!partitionPrev) {
                partitionPrev = low;
            } else {
                partitionPrev = partitionPrev->siguiente;
            }
            
            std::swap(current->data, partitionPrev->data);
        }
        current = current->siguiente;
    }
    
    if (!partitionPrev) {
        partitionPrev = low;
    } else {
        partitionPrev = partitionPrev->siguiente;
    }
    
    std::swap(partitionPrev->data, tail->data);
    
    return partitionPrev;
}

// Método quicksort recursivo por cédula
template <typename T>
void ListaSimple<T>::quicksortCedula(Nodo<T>* low, Nodo<T>* high) {
    // Condición de terminación
    if (high && low != high && low != high->siguiente) {
        // Particionar la lista
        Nodo<T>* pivot = partitionByCedula(low, high);
        
        // Encontrar el nodo anterior al pivote
        Nodo<T>* prevPivot = low;
        while (prevPivot->siguiente != pivot) {
            prevPivot = prevPivot->siguiente;
        }
        
        // Ordenar recursivamente las sublistas
        if (pivot != low) {
            quicksortCedula(low, prevPivot);
        }
        if (pivot->siguiente != high) {
            quicksortCedula(pivot->siguiente, high);
        }
    }
}

// Método quicksort recursivo por nombre
template <typename T>
void ListaSimple<T>::quicksortNombre(Nodo<T>* low, Nodo<T>* high) {
    if (high && low != high && low != high->siguiente) {
        Nodo<T>* pivot = partitionByNombre(low, high);
        
        // Encontrar el nodo anterior al pivote
        Nodo<T>* prevPivot = low;
        while (prevPivot->siguiente != pivot) {
            prevPivot = prevPivot->siguiente;
        }
        
        if (pivot != low) {
            quicksortNombre(low, prevPivot);
        }
        if (pivot->siguiente != high) {
            quicksortNombre(pivot->siguiente, high);
        }
    }
}

// Método quicksort recursivo por apellido
template <typename T>
void ListaSimple<T>::quicksortApellido(Nodo<T>* low, Nodo<T>* high) {
    if (high && low != high && low != high->siguiente) {
        Nodo<T>* pivot = partitionByApellido(low, high);
        
        // Encontrar el nodo anterior al pivote
        Nodo<T>* prevPivot = low;
        while (prevPivot->siguiente != pivot) {
            prevPivot = prevPivot->siguiente;
        }
        
        if (pivot != low) {
            quicksortApellido(low, prevPivot);
        }
        if (pivot->siguiente != high) {
            quicksortApellido(pivot->siguiente, high);
        }
    }
}

template <typename T>
void ListaSimple<T>::ordenarPorCedula() {
    if (!cabeza) return;
    Nodo<T>* last = getLastNode();
    quicksortCedula(cabeza, last);
}

template <typename T>
void ListaSimple<T>::ordenarPorNombre() {
    if (!cabeza) return;
    Nodo<T>* last = getLastNode();
    quicksortNombre(cabeza, last);
}

template <typename T>
void ListaSimple<T>::ordenarPorApellido() {
    if (!cabeza) return;
    Nodo<T>* last = getLastNode();
    quicksortApellido(cabeza, last);
}
