/***********************************************************************
 * Module:  ListasCirculares.cpp
 * Author:  Erika Guayanay, Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "ListasCirculares.h"
#include "Utilidades.h"
#include "Validaciones.h"
#include <iostream>
#include <algorithm>

ListaCircular::ListaCircular() : primero(nullptr), ultimo(nullptr) {}

bool ListaCircular::validarCedulaUnica(string cedula) {
    Nodo* actual = primero;
    if (actual == nullptr) return true;

    do {
        if (actual->getCedula() == cedula) {
            return false;
        }
        actual = actual->getSiguiente();
    } while (actual != primero);

    return true;
}

void ListaCircular::insertar(std::string cedula, std::string nombre, std::string apellido, bool mostrarMensaje) {
    if (!validarCedulaUnica(cedula)) {
        if (mostrarMensaje) {
            std::cout << "ERROR: La cedula ya existe en la lista.\n";
        }
        return;
    }

    // Validar el nombre
    while (!validarNombre(nombre)) {
        std::cout << "ERROR: Ingrese un nombre valido: ";
        std::getline(std::cin, nombre);
    }

    // Validar el apellido
    while (!validarNombre(apellido)) {
        std::cout << "ERROR: Ingrese un apellido valido: ";
        std::getline(std::cin, apellido);
    }

    // Normalizar el nombre y apellido
    nombre = normalizarNombre(nombre);
    apellido = normalizarNombre(apellido);

    Nodo* nuevo = new Nodo(cedula, nombre, apellido);
    if (primero == nullptr) {
        primero = nuevo;
        ultimo = nuevo;
        nuevo->setSiguiente(nuevo);
    } else {
        ultimo->setSiguiente(nuevo);
        nuevo->setSiguiente(primero);
        ultimo = nuevo;
    }

    if (mostrarMensaje) {
        std::cout << "Persona registrada correctamente.\n";
    }
}

Nodo* ListaCircular::buscar(string cedula) {
    Nodo* actual = primero;
    if (actual == nullptr) return nullptr;

    do {
        if (actual->getCedula() == cedula) {
            return actual;
        }
        actual = actual->getSiguiente();
    } while (actual != primero);

    return nullptr;
}

bool ListaCircular::eliminar(string cedula) {
    if (primero == nullptr) {
        cout << "La lista esta vacia.\n";
        return false;
    }

    Nodo* actual = primero;
    Nodo* anterior = nullptr;
    bool encontrado = false;

    do {
        if (actual->getCedula() == cedula) {
            encontrado = true;
            break;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    } while (actual != primero);

    if (!encontrado) {
        cout << "Cedula no encontrada.\n";
        return false;
    }

    if (actual == primero) {
        if (primero == ultimo) {
            primero = nullptr;
            ultimo = nullptr;
        } else {
            primero = primero->getSiguiente();
            ultimo->setSiguiente(primero);
        }
    } else if (actual == ultimo) {
        anterior->setSiguiente(primero);
        ultimo = anterior;
    } else {
        anterior->setSiguiente(actual->getSiguiente());
    }

    delete actual;
    cout << "Persona eliminada correctamente.\n";
    return true;
}

void ListaCircular::mostrar() {
    Nodo* actual = primero;
    if (actual == nullptr) {
        std::cout << "NULL\n";
        return;
    }

    do {
        std::cout << "<Cedula: " << actual->getCedula()
                  << ", Nombre: " << actual->getNombre()
                  << ", Apellido: " << actual->getApellido() << ">\n"; // Salto de l�nea aqu�
        actual = actual->getSiguiente();
    } while (actual != primero);

    std::cout << "(Regresa al inicio)\n";
}

void ListaCircular::eliminarCaracter(std::string cedula, char caracter) {
    Nodo* actual = buscar(cedula);
    if (actual == nullptr) {
        std::cout << "Cedula no encontrada.\n";
        return;
    }

    std::string nuevoNombre = actual->getNombre();
    std::string nuevoApellido = actual->getApellido();

    nuevoNombre.erase(std::remove(nuevoNombre.begin(), nuevoNombre.end(), caracter), nuevoNombre.end());
    nuevoApellido.erase(std::remove(nuevoApellido.begin(), nuevoApellido.end(), caracter), nuevoApellido.end());

    // Normalizar despu�s de eliminar el car�cter
    actual->setNombre(normalizarNombre(nuevoNombre));
    actual->setApellido(normalizarNombre(nuevoApellido));

    std::cout << "Caracter eliminado correctamente.\n";
}


