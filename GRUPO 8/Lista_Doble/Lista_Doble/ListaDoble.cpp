/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
// Lista_Doble.cpp
#include "ListaDoble.h"

template <typename T>
ListaDoble<T>::ListaDoble() : cabeza(nullptr), cola(nullptr) {}

template <typename T>
ListaDoble<T>::~ListaDoble() {
    limpiar();
}

template <typename T>
void ListaDoble<T>::insertar(const T& elemento) {
    Nodo<T>* nuevo = new Nodo<T>(elemento);
    if (!cabeza) {
        cabeza = cola = nuevo;
    } else {
        cola->setSiguiente(nuevo);
        nuevo->setAnterior(cola);
        cola = nuevo;
    }
}

template <typename T>
void ListaDoble<T>::eliminar(const std::string& criterio, const std::string& valor) {
    Nodo<T>* actual = cabeza;
    while (actual) {
        if ((criterio == "cedula" && actual->getDato().get_cedula() == valor) ||
            (criterio == "nombre" && actual->getDato().get_nombre() == valor) ||
            (criterio == "apellido" && actual->getDato().get_apellido() == valor)) {
            
            if (actual == cabeza) {
                cabeza = actual->getSiguiente();
                if (cabeza) cabeza->setAnterior(nullptr);
            } else if (actual == cola) {
                cola = actual->getAnterior();
                if (cola) cola->setSiguiente(nullptr);
            } else {
                actual->getAnterior()->setSiguiente(actual->getSiguiente());
                actual->getSiguiente()->setAnterior(actual->getAnterior());
            }
            
            delete actual;
            std::cout << "Elemento eliminado.\n";
            return;
        }
        actual = actual->getSiguiente();
    }

    std::cout << "No se encontró ningún elemento con el " << criterio << ": " << valor << "\n";
}

template <typename T>
void ListaDoble<T>::buscar(const std::string& criterio, const std::string& valor) const {
    Nodo<T>* actual = cabeza;
    while (actual) {
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
    }

    std::cout << "No se encontró ningún elemento con el " << criterio << ": " << valor << "\n";
}

template <typename T>
void ListaDoble<T>::mostrar() const {
    Nodo<T>* actual = cabeza;
    while (actual) {
        const T& elemento = actual->getDato();
        std::cout << "Cédula: " << elemento.get_cedula()
                  << ", Nombre: " << elemento.get_nombre()
                  << ", Apellido: " << elemento.get_apellido() << "\n";
        actual = actual->getSiguiente();
    }
}

template <typename T>
void ListaDoble<T>::limpiar() {
    Nodo<T>* actual = cabeza;
    while (actual) {
        Nodo<T>* temp = actual;
        actual = actual->getSiguiente();
        delete temp;
    }
    cabeza = cola = nullptr;
}
template <typename T>
void ListaDoble<T>::cifrar(std::string criterio, char caracter, int desplazamiento, ListaDoble<T>& listaAuxiliar) {
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
template <typename T>
Nodo<T>* dividirLista(Nodo<T>* cabeza) {
    if (!cabeza || !cabeza->getSiguiente()) return cabeza;

    Nodo<T>* lento = cabeza;
    Nodo<T>* rapido = cabeza;

    while (rapido->getSiguiente() && rapido->getSiguiente()->getSiguiente()) {
        lento = lento->getSiguiente();
        rapido = rapido->getSiguiente()->getSiguiente();
    }

    Nodo<T>* mitad = lento->getSiguiente();
    lento->setSiguiente(nullptr);
    if (mitad) mitad->setAnterior(nullptr); // Romper el enlace previo

    return mitad;
}
template <typename T>
Nodo<T>* fusionarListas(Nodo<T>* izquierda, Nodo<T>* derecha, const int& criterio, const int& orden) {
    if (!izquierda) return derecha;
    if (!derecha) return izquierda;

    Nodo<T>* resultado = nullptr;

    bool condicion = false;
    if (criterio == 1) {
        condicion = (orden == 1) ? 
                    (izquierda->getDato().get_cedula() <= derecha->getDato().get_cedula()) :
                    (izquierda->getDato().get_cedula() > derecha->getDato().get_cedula());
    } else if (criterio == 2) {
        condicion = (orden == 1) ? 
                    (izquierda->getDato().get_nombre() <= derecha->getDato().get_nombre()) :
                    (izquierda->getDato().get_nombre() > derecha->getDato().get_nombre());
    } else if (criterio == 3) {
        condicion = (orden == 1) ? 
                    (izquierda->getDato().get_apellido() <= derecha->getDato().get_apellido()) :
                    (izquierda->getDato().get_apellido() > derecha->getDato().get_apellido());
    }

    if (condicion) {
        resultado = izquierda;
        resultado->setSiguiente(fusionarListas(izquierda->getSiguiente(), derecha, criterio, orden));
        if (resultado->getSiguiente()) resultado->getSiguiente()->setAnterior(resultado);
    } else {
        resultado = derecha;
        resultado->setSiguiente(fusionarListas(izquierda, derecha->getSiguiente(), criterio, orden));
        if (resultado->getSiguiente()) resultado->getSiguiente()->setAnterior(resultado);
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
void ListaDoble<T>::ordenar(const int& criterio, const int& orden) {
    cabeza = mergeSort(cabeza, criterio, orden);
}
