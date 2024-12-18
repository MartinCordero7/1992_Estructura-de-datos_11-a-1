/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Lista_Simple.cpp

#include "Lista_Simple.h"

template <typename T>
ListaSimple<T>::ListaSimple() : cabeza(nullptr) {}

template <typename T>
ListaSimple<T>::~ListaSimple() {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        Nodo<T>* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
}

template <typename T>
void ListaSimple<T>::insertar(const T& elemento) {
    Nodo<T>* nuevo = new Nodo<T>(elemento);
    if (cabeza == nullptr) {
        cabeza = nuevo;
    } else {
        Nodo<T>* actual = cabeza;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
    }
}

template <typename T>
void ListaSimple<T>::eliminar(const std::string& criterio, const std::string& valor) {
    if (cabeza == nullptr) return;

    // Caso especial: eliminar la cabeza
    if ((criterio == "cedula" && cabeza->getDato().get_cedula() == valor) ||
        (criterio == "nombre" && cabeza->getDato().get_nombre() == valor) ||
        (criterio == "apellido" && cabeza->getDato().get_apellido() == valor)) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->getSiguiente();
        delete temp;
        std::cout << "Elemento eliminado.\n";
        return;
    }

    // Caso general: buscar el nodo en la lista
    Nodo<T>* actual = cabeza;
    while (actual->getSiguiente() != nullptr) {
        if ((criterio == "cedula" && actual->getSiguiente()->getDato().get_cedula() == valor) ||
            (criterio == "nombre" && actual->getSiguiente()->getDato().get_nombre() == valor) ||
            (criterio == "apellido" && actual->getSiguiente()->getDato().get_apellido() == valor)) {
            Nodo<T>* temp = actual->getSiguiente();
            actual->setSiguiente(temp->getSiguiente());
            delete temp;
            std::cout << "Elemento eliminado.\n";
            return;
        }
        actual = actual->getSiguiente();
    }

    std::cout << "No se encontró ningún elemento con el " << criterio << ": " << valor << "\n";
}

template <typename T>
void ListaSimple<T>::buscar(const std::string& criterio, const std::string& valor) const {
    Nodo<T>* actual = cabeza;
    bool encontrado = false;

    while (actual != nullptr) {
        const T& elemento = actual->getDato();
        if ((criterio == "cedula" && elemento.get_cedula() == valor) ||
            (criterio == "nombre" && elemento.get_nombre() == valor) ||
            (criterio == "apellido" && elemento.get_apellido() == valor)) {
            std::cout << "Elemento encontrado:\n"
                      << "Cédula: " << elemento.get_cedula() << "\n"
                      << "Nombre: " << elemento.get_nombre() << "\n"
                      << "Apellido: " << elemento.get_apellido() << "\n";
            encontrado = true;
            break;
        }
        actual = actual->getSiguiente();
    }

    if (!encontrado) {
        std::cout << "No se encontró ningún elemento con el " << criterio << ": " << valor << "\n";
    }
}

template <typename T>
void ListaSimple<T>::mostrar() const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        const T& elemento = actual->getDato();
        std::cout << "Cédula: " << elemento.get_cedula()
                  << ", Nombre: " << elemento.get_nombre()
                  << ", Apellido: " << elemento.get_apellido() << "\n";
        actual = actual->getSiguiente();
    }
}

template <typename T>
void ListaSimple<T>::limpiar() {
    Nodo<T>* actual = cabeza;
    while (actual) {
        Nodo<T>* temp = actual;
        actual = actual->getSiguiente();
        delete temp; // Libera la memoria
    }
    cabeza = nullptr;
}


template <typename T>
void ListaSimple<T>::cifrar(std::string criterio, char caracter, int desplazamiento, ListaSimple<T>& listaAuxiliar) {
    // Función lambda para cifrar un carácter
    auto cifrarCaracter = [caracter, desplazamiento](char c) -> char {
        if (c == caracter) {
            return static_cast<char>((c + desplazamiento) % 256); // Cifrado circular dentro del rango ASCII
        }
        return c;
    };

    // Limpiar la lista auxiliar antes de cifrar
    listaAuxiliar.limpiar();

    Nodo<T>* temp = cabeza;
    while (temp) {
        // Obtener el dato del nodo original
        T datoOriginal = temp->getDato();
        T datoCifrado = datoOriginal;  // Crear una copia de manera directa (asumiendo que T tiene un constructor por copia)

        std::string palabraCifrada; // String temporal para almacenar la palabra cifrada

        // Modificar el atributo según el criterio
        if (criterio == "nombre") {
            palabraCifrada = datoOriginal.get_nombre(); // Obtener el nombre
            for (char& c : palabraCifrada) {
                c = cifrarCaracter(c); // Cifrar cada carácter
            }
            datoCifrado.set_nombre(palabraCifrada); // Actualizar el nombre cifrado en el objeto
        } else if (criterio == "apellido") {
            palabraCifrada = datoOriginal.get_apellido(); // Obtener el apellido
            for (char& c : palabraCifrada) {
                c = cifrarCaracter(c); // Cifrar cada carácter
            }
            datoCifrado.set_apellido(palabraCifrada); // Actualizar el apellido cifrado en el objeto
        }

        // Insertar el nodo modificado en la lista auxiliar
        listaAuxiliar.insertar(datoCifrado);

        // Pasar al siguiente nodo
        temp = temp->getSiguiente();
    }
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
void ListaSimple<T>::ordenar(const int& criterio, const int& orden) {
    cabeza = mergeSort(cabeza, criterio, orden);
}

