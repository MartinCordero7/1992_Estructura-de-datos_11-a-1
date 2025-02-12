/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Lista_Simple.cpp
#include "ListaCircular.h"

template <typename T>
ListaCircular<T>::ListaCircular() : cabeza(nullptr) {}

template <typename T>
ListaCircular<T>::~ListaCircular() {
    limpiar();
}

template <typename T>
void ListaCircular<T>::insertar(const T& elemento) {
    Nodo<T>* nuevo = new Nodo<T>(elemento);
    if (!cabeza) {
        cabeza = nuevo;
        cabeza->setSiguiente(cabeza); // Nodo apunta a sí mismo
    } else {
        Nodo<T>* temp = cabeza;
        while (temp->getSiguiente() != cabeza) {
            temp = temp->getSiguiente();
        }
        temp->setSiguiente(nuevo);
        nuevo->setSiguiente(cabeza); // Cierre circular
    }
}

template <typename T>
void ListaCircular<T>::eliminar(const std::string& criterio, const std::string& valor) {
    if (!cabeza) return;

    Nodo<T>* actual = cabeza;
    Nodo<T>* anterior = nullptr;

    do {
        if ((criterio == "cedula" && actual->getDato().get_cedula() == valor) ||
            (criterio == "nombre" && actual->getDato().get_nombre() == valor) ||
            (criterio == "apellido" && actual->getDato().get_apellido() == valor)) {
            if (actual == cabeza && actual->getSiguiente() == cabeza) {
                // Único nodo en la lista
                delete actual;
                cabeza = nullptr;
            } else {
                if (actual == cabeza) {
                    cabeza = cabeza->getSiguiente();
                }
                anterior->setSiguiente(actual->getSiguiente());
                delete actual;
            }
            std::cout << "Elemento eliminado.\n";
            return;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    std::cout << "No se encontró ningún elemento con el " << criterio << ": " << valor << "\n";
}

template <typename T>
void ListaCircular<T>::buscar(const std::string& criterio, const std::string& valor) const {
    if (!cabeza) return;

    Nodo<T>* actual = cabeza;
    do {
        const T& elemento = actual->getDato();
        if ((criterio == "cedula" && elemento.get_cedula() == valor) ||
            (criterio == "nombre" && elemento.get_nombre() == valor) ||
            (criterio == "apellido" && elemento.get_apellido() == valor)) {
            std::cout << "Elemento encontrado:\n"
                      << "Cédula: " << elemento.get_cedula() << "\n"
                      << "Nombre: " << elemento.get_nombre() << "\n"
                      << "Apellido: " << elemento.get_apellido() << "\n";
            return;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    std::cout << "No se encontró ningún elemento con el " << criterio << ": " << valor << "\n";
}

template <typename T>
void ListaCircular<T>::mostrar() const {
    if (!cabeza) return;

    Nodo<T>* actual = cabeza;
    do {
        const T& elemento = actual->getDato();
        std::cout << "Cédula: " << elemento.get_cedula()
                  << ", Nombre: " << elemento.get_nombre()
                  << ", Apellido: " << elemento.get_apellido() << "\n";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
}

template <typename T>
void ListaCircular<T>::limpiar() {
    if (!cabeza) return;

    Nodo<T>* actual = cabeza;
    do {
        Nodo<T>* temp = actual;
        actual = actual->getSiguiente();
        delete temp;
    } while (actual != cabeza);

    cabeza = nullptr;
}

template <typename T>
void ListaCircular<T>::cifrar(std::string criterio, char caracter, int desplazamiento, ListaCircular<T>& listaAuxiliar) {
    auto cifrarCaracter = [caracter, desplazamiento](char c) -> char {
        if (c == caracter) {
            return static_cast<char>((c + desplazamiento) % 256); // Cifrado circular dentro del rango ASCII
        }
        return c;
    };

    listaAuxiliar.limpiar();

    if (!cabeza) return; // Lista vacía

    Nodo<T>* temp = cabeza;
    do {
        T datoOriginal = temp->getDato();
        T datoCifrado = datoOriginal; // Crear copia del dato

        std::string palabraCifrada;

        if (criterio == "nombre") {
            palabraCifrada = datoOriginal.get_nombre();
            for (char& c : palabraCifrada) {
                c = cifrarCaracter(c);
            }
            datoCifrado.set_nombre(palabraCifrada);
        } else if (criterio == "apellido") {
            palabraCifrada = datoOriginal.get_apellido();
            for (char& c : palabraCifrada) {
                c = cifrarCaracter(c);
            }
            datoCifrado.set_apellido(palabraCifrada);
        }

        listaAuxiliar.insertar(datoCifrado);

        temp = temp->getSiguiente();
    } while (temp != cabeza); // Detenerse cuando vuelva a la cabeza
}

//ordenar por merge sort
template <typename T>
Nodo<T>* dividirLista(Nodo<T>* cabeza) {
    if (!cabeza || !cabeza->getSiguiente()) return cabeza;

    Nodo<T>* left = cabeza;
    Nodo<T>* right = cabeza->getSiguiente();

    while (right && right->getSiguiente()) {
        left = left->getSiguiente();
        right = right->getSiguiente()->getSiguiente();
    }

    Nodo<T>* mitad = left->getSiguiente();
    left->setSiguiente(nullptr); // Dividir en dos listas
    return mitad;
}


template <typename T>
Nodo<T>* fusionarListas(Nodo<T>* izquierda, Nodo<T>* derecha, const int& criterio, const int& orden) {
    if (!izquierda) return derecha;
    if (!derecha) return izquierda;

    Nodo<T>* resultado = nullptr;
    bool condicion = false;

    // Establecer la condición según el criterio y el orden
    if (criterio == 1) { // Ordenar por nombre
        condicion = (orden == 1) ? 
                    (izquierda->getDato().get_cedula() <= derecha->getDato().get_cedula()) :
                    (izquierda->getDato().get_cedula() > derecha->getDato().get_cedula());
    } else if (criterio == 2) { // Ordenar por apellido
        condicion = (orden == 1) ? 
                    (izquierda->getDato().get_nombre() <= derecha->getDato().get_nombre()) :
                    (izquierda->getDato().get_nombre() > derecha->getDato().get_nombre());
    } else if (criterio == 3) { // Ordenar por cédula
        condicion = (orden == 1) ? 
                    (izquierda->getDato().get_apellido() <= derecha->getDato().get_apellido()) :
                    (izquierda->getDato().get_apellido() > derecha->getDato().get_apellido());
    }

    // Elegir qué nodo irá primero en la lista fusionada
    if (condicion) {
        resultado = izquierda;
        resultado->setSiguiente(fusionarListas(izquierda->getSiguiente(), derecha, criterio, orden));
    } else {
        resultado = derecha;
        resultado->setSiguiente(fusionarListas(izquierda, derecha->getSiguiente(), criterio, orden));
    }
    return resultado;
}


template <typename T>
Nodo<T>* mergeSort(Nodo<T>* cabeza, const int& criterio, const int& orden) {
    if (!cabeza || !cabeza->getSiguiente()) return cabeza;

    Nodo<T>* mitad = dividirLista(cabeza);

    Nodo<T>* izquierda = mergeSort(cabeza, criterio, orden);
    Nodo<T>* derecha = mergeSort(mitad, criterio, orden);

    return fusionarListas(izquierda, derecha, criterio, orden);
}


template <typename T>
void ListaCircular<T>::ordenar(const int& criterio, const int& orden) {
    cabeza = mergeSort(cabeza, criterio, orden);
}
