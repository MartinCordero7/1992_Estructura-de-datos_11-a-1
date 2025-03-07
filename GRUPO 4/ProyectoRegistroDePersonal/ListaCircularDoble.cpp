#include "ListaCircularDoble.h"
#include <fstream>
#include <sstream>
#include <iostream> 

ListaCircularDoble::ListaCircularDoble() {
    primero = nullptr;
    ultimo = nullptr;
}

ListaCircularDoble::~ListaCircularDoble() {
    while (primero != nullptr) {
        Nodo* temp = primero;
        primero = primero->siguiente;
        delete temp;
    }
}

bool ListaCircularDoble::estaVacia() {
    return primero == nullptr;
}

void ListaCircularDoble::insertarAlInicio(Empleado* empleado) {
    Nodo* nuevoNodo = new Nodo(empleado);

    if (estaVacia()) {
        primero = nuevoNodo;
        ultimo = nuevoNodo;
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
    } else {
        nuevoNodo->siguiente = primero;
        nuevoNodo->anterior = ultimo;
        primero->anterior = nuevoNodo;
        ultimo->siguiente = nuevoNodo;
        primero = nuevoNodo;
    }

}

void ListaCircularDoble::insertarAlFinal(Empleado* empleado) {
    Nodo* nuevoNodo = new Nodo(empleado);

    if (estaVacia()) {
        primero = nuevoNodo;
        ultimo = nuevoNodo;
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
    } else {
        nuevoNodo->siguiente = primero;
        nuevoNodo->anterior = ultimo;
        primero->anterior = nuevoNodo;
        ultimo->siguiente = nuevoNodo;
        ultimo = nuevoNodo;
    }
}


void ListaCircularDoble::eliminarAlInicio() {
    if (!estaVacia()) {
        if (primero == ultimo) {
            delete primero;
            primero = nullptr;
            ultimo = nullptr;
        } else {
            Nodo* temp = primero;
            primero = primero->siguiente;
            primero->anterior = ultimo;
            ultimo->siguiente = primero;
            delete temp;
        }
    }
}

void ListaCircularDoble::eliminarAlFinal() {
    if (!estaVacia()) {
        if (primero == ultimo) {
            delete primero;
            primero = nullptr;
            ultimo = nullptr;
        } else {
            Nodo* temp = ultimo;
            ultimo = ultimo->anterior;
            ultimo->siguiente = primero;
            primero->anterior = ultimo;
            delete temp;
        }
    }
}


void ListaCircularDoble::imprimirLista() const {
    if (primero == nullptr) {
        std::cout << "La lista esta vacia." << std::endl;
        return;
    }

    Nodo* actual = primero;
    int contador = 1;

    do {
        Empleado* empleado = actual->dato;
        std::cout << "||||||||||||||||||||||||||||||||||||" << std::endl;
        std::cout << "Empleado " << contador << ":" << std::endl;
        std::cout << "Cedula: " << empleado->getCedula() << std::endl;
        std::cout << "Nombre: " << empleado->getNombre() << std::endl;
        std::cout << "Apellido: " << empleado->getApellido() << std::endl;
        std::cout << "cargo: " << empleado->getCargo() << std::endl;
        std::cout << "sueldo: " << empleado->getSalario() << std::endl;
        std::cout << "Fecha de nacimiento: " << empleado->getFechaNacimiento().toString() << std::endl;
        std::cout << "||||||||||||||||||||||||||||||||||||\n" << std::endl;

        actual = actual->siguiente;
        contador++;
    } while (actual != primero);

    std::cout << "Fin de la lista." << std::endl;
    std::cout << "||||||||||||||||||||||||||||||||||||" << std::endl;
}



Empleado* ListaCircularDoble::buscarPersona(const std::string& cedula) {
    Nodo* actual = primero;

    while (actual != nullptr) {
        if (actual->dato->getCedula() == cedula) {
            return actual->dato; 
        }
        actual = actual->siguiente;
        if (actual == primero) {
            break; 
    }
}
    return nullptr;

}

void ListaCircularDoble::eliminarPersona(Empleado* empleado) {
    if (!estaVacia()) {
        Nodo* actual = primero;
        Nodo* anterior = nullptr;
        bool encontrado = false;

        do {
            if (actual->dato == empleado) {
                encontrado = true;
                break;
            }

            anterior = actual;
            actual = actual->siguiente;
        } while (actual != primero);

        if (encontrado) {
            if (actual == primero) {
                eliminarAlInicio();
            } else if (actual == ultimo) {
                eliminarAlFinal();
            } else {
                anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = anterior;
                delete actual->dato;
                delete actual;
            }
            std::cout << "Persona eliminada del nodo.\n"; // Mensaje de salida dentro del bloque 'if (encontrado)'
        }
    }
}


void ListaCircularDoble::cargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string cedula, nombre, apellido, fechaNacimientoStr, cargo, salario;

        if (ss >> cedula >> nombre >> apellido >> fechaNacimientoStr >> cargo >> salario) {

            Fecha fechaNacimiento = Fecha::convertirStringAFecha(fechaNacimientoStr);

            Empleado* empleado = new Empleado(cedula, nombre, apellido, fechaNacimiento, cargo, salario);

            insertarAlFinal(empleado);
        }
    }

    archivo.close();
}

void cargarListaEnArbol(ListaCircularDoble& lista, ArbolRadix& arbol) {
    if (lista.estaVacia()) {
        std::cout << "La lista esta vacia. No se han cargado empleados al arbol." << std::endl;
        return;
    }

    ListaCircularDoble::Nodo* nodoActual = lista.primero;
    do {
        Empleado* empleado = nodoActual->dato;
        arbol.insertarEmpleado(empleado);
        nodoActual = nodoActual->siguiente;
    } while (nodoActual != lista.primero);
}

int ListaCircularDoble::contarElementos() {
    if (primero == nullptr) {
        return 0;
    }

    int count = 0;
    Nodo* actual = primero;
    do {
        count++;
        actual = actual->siguiente;
    } while (actual != primero);

    return count;
}

void ListaCircularDoble::quickSort() {
    if (primero != nullptr && primero != ultimo) {
        quickSortRecursivo(primero, ultimo);
    }
}

ListaCircularDoble::Nodo* ListaCircularDoble::particion(ListaCircularDoble::Nodo* bajo, ListaCircularDoble::Nodo* alto) {
    std::string pivote = alto->dato->getCedula();
    Nodo* i = bajo->anterior;

    for (Nodo* j = bajo; j != alto; j = j->siguiente) {
        if (j->dato->getCedula() <= pivote) {
            i = (i == nullptr) ? bajo : i->siguiente;
            std::swap(i->dato, j->dato);
        }
    }
    i = (i == nullptr) ? bajo : i->siguiente;
    std::swap(i->dato, alto->dato);
    return i;
}

void ListaCircularDoble::quickSortRecursivo(Nodo* bajo, Nodo* alto) {
    if (alto != nullptr && bajo != alto && bajo != alto->siguiente) {
        Nodo* p = particion(bajo, alto);
        quickSortRecursivo(bajo, p->anterior);
        quickSortRecursivo(p->siguiente, alto);
    }
}