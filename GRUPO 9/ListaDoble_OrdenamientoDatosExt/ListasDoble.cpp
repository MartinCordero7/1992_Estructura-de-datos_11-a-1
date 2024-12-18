/***********************************************************************
 * Module:  ListaDoble.cpp
 * Author:  Erika Guayanay,Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "ListasDoble.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
using namespace std;

ListaDoble::ListaDoble() : primero(nullptr), ultimo(nullptr) {}

ListaDoble::~ListaDoble() {
    Nodo* temp;
    while (primero != nullptr) {
        temp = primero;
        primero = primero->getSiguiente();
        delete temp;
    }
}

bool ListaDoble::validarCedulaUnica(string cedula) {
    Nodo* temp = primero;
    while (temp != nullptr) {
        if (temp->getCedula() == cedula) {
            return false;
        }
        temp = temp->getSiguiente();
    }
    return true;
}

void ListaDoble::insertar(string cedula, string nombre, string apellido) {
    if (!validarCedulaUnica(cedula)) {
        cout << "Error: La cedula ya existe en la lista.\n";
        return;
    }

    // Insertamos en memoria
    Nodo* nuevo = new Nodo(cedula, nombre, apellido);
    if (primero == nullptr) {
        primero = nuevo;
        ultimo = nuevo;
    } else {
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        ultimo = nuevo;
    }

}

Nodo* ListaDoble::buscar(string cedula) {
    ifstream archivo("personas.txt");
    string linea, archivoCedula, nombre, apellido;

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo personas.txt.\n";
        return nullptr;
    }

    while (getline(archivo, linea)) {
         linea.erase(remove_if(linea.begin(), linea.end(), ::isspace), linea.end());
        stringstream ss(linea);
        getline(ss, archivoCedula, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido);

        if (archivoCedula == cedula) {
            archivo.close();
            Nodo* nodo = new Nodo(archivoCedula, nombre, apellido);  // Crear nodo con los datos encontrados
            cout << "¡Persona encontrada! Cédula: " << archivoCedula << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "Apellido: " << apellido << endl;
            return nodo;
        }
    }

    archivo.close();
    cout << "La cedula " << cedula << " no existe en el archivo personas.txt.\n";
    return nullptr;
}

bool ListaDoble::eliminar(string cedula)
{
    Nodo* temp = primero;
    while (temp != nullptr && temp->getCedula() != cedula) {
        temp = temp->getSiguiente();
    }

    if (temp == nullptr) {
        cout << "Persona con cédula " << cedula << " no encontrada.\n";
        return false;
    }

    // Si es el primer nodo
    if (temp == primero) {
        primero = temp->getSiguiente();
        if (primero != nullptr) {
            primero->setAnterior(nullptr);
        } else {
            ultimo = nullptr;  // Si es el único nodo, actualizamos también `ultimo`
        }
    }
    // Si es el último nodo
    else if (temp == ultimo) {
        ultimo = temp->getAnterior();
        if (ultimo != nullptr) {
            ultimo->setSiguiente(nullptr);
        } else {
            primero = nullptr;  // Si la lista queda vacía, actualizamos `primero`
        }
    }
    // Si está en medio de la lista
    else {
        temp->getAnterior()->setSiguiente(temp->getSiguiente());
        temp->getSiguiente()->setAnterior(temp->getAnterior());
    }

    // Liberar el nodo
    delete temp;

    // Actualizar archivo
    ifstream archivoEntrada("personas.txt");
    ofstream archivoTemporal("personas_temp.txt");

    if (!archivoEntrada.is_open() || !archivoTemporal.is_open()) {
        cout << "Error al abrir los archivos.\n";
        return false;
    }

    string linea, archivoCedula, nombre, apellido;
    bool encontrado = false;

    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        getline(ss, archivoCedula, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido);

        if (archivoCedula != cedula) {
            archivoTemporal << archivoCedula << "," << nombre << "," << apellido << endl;
        } else {
            encontrado = true;
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();

    if (encontrado) {
        remove("personas.txt");
        rename("personas_temp.txt", "personas.txt");
        cout << "Persona eliminada exitosamente del archivo.\n";
        return true;
    } else {
        cout << "No se encontró la persona en el archivo.\n";
        return false;
    }
}



void ListaDoble::eliminarCaracter(string cedula, char caracter, ListaDoble& listaAuxiliar) {
    Nodo* temp = buscar(cedula);
    if (temp == nullptr) {
        cout << "Cedula no encontrada.\n";
        return;
    }

    string nuevoNombre = temp->getNombre();
    string nuevoApellido = temp->getApellido();

    nuevoNombre.erase(remove(nuevoNombre.begin(), nuevoNombre.end(), caracter), nuevoNombre.end());
    nuevoApellido.erase(remove(nuevoApellido.begin(), nuevoApellido.end(), caracter), nuevoApellido.end());

    temp->setNombre(nuevoNombre);
    temp->setApellido(nuevoApellido);
    listaAuxiliar.insertar(temp->getCedula(), nuevoNombre, nuevoApellido);

     ifstream archivoEntrada("personas.txt");
    ofstream archivoTemporal("personas_temp.txt");

    if (!archivoEntrada.is_open() || !archivoTemporal.is_open())
    {
        cout << "Error al abrir los archivos.\n";
        return;
    }

    string linea, archivoCedula, nombre, apellido;

    // Leer línea por línea del archivo original
    while (getline(archivoEntrada, linea))
    {
        stringstream ss(linea);
        getline(ss, archivoCedula, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido);

        if (archivoCedula == cedula)
        {
            // Actualizar línea con los nuevos valores
            archivoTemporal << archivoCedula << "," << nuevoNombre << "," << nuevoApellido << "\n";
        }
        else
        {
            // Mantener las líneas que no coinciden
            archivoTemporal << archivoCedula << "," << nombre << "," << apellido << "\n";
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();

    // Reemplazar el archivo original por el temporal
    remove("personas.txt");
    rename("personas_temp.txt", "personas.txt");

    cout << "Caracter eliminado correctamente del archivo y lista auxiliar actualizada.\n";
}

void ListaDoble::cifrarCaracter(string cedula, char caracter, int desplazamiento, ListaDoble& listaAuxiliar) {
    Nodo* temp = buscar(cedula);
    if (temp == nullptr) {
        cout << "Cedula no encontrada.\n";
        return;
    }

    string nuevoNombre = temp->getNombre();
    string nuevoApellido = temp->getApellido();

    // Definici�n de la lambda para cifrar caracteres
    auto cifrar = [caracter, desplazamiento](char c) -> char {
        if (c == caracter && isalpha(c)) { // Verifica si el car�cter coincide y es una letra
            char base = islower(c) ? 'a' : 'A'; // Determina si es min�scula o may�scula
            return (c - base + desplazamiento) % 26 + base; // Aplica el cifrado C�sar
        }
        return c; // Devuelve el car�cter sin modificar si no cumple la condici�n
    };

    // Aplicar cifrado al nombre y apellido
    std::transform(nuevoNombre.begin(), nuevoNombre.end(), nuevoNombre.begin(), cifrar);
    std::transform(nuevoApellido.begin(), nuevoApellido.end(), nuevoApellido.begin(), cifrar);

    // Actualizar valores en el nodo original
    temp->setNombre(nuevoNombre);
    temp->setApellido(nuevoApellido);

    // Insertar en la lista auxiliar
    listaAuxiliar.insertar(temp->getCedula(), nuevoNombre, nuevoApellido);

   ifstream archivoEntrada("personas.txt");
    ofstream archivoTemporal("personas_temp.txt");

    if (!archivoEntrada.is_open() || !archivoTemporal.is_open())
    {
        cout << "Error al abrir los archivos.\n";
        return;
    }

    string linea, archivoCedula, nombre, apellido;

    // Leer línea por línea del archivo original
    while (getline(archivoEntrada, linea))
    {
        stringstream ss(linea);
        getline(ss, archivoCedula, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido);

        if (archivoCedula == cedula)
        {
            // Actualizar línea con los valores cifrados
            archivoTemporal << archivoCedula << "," << nuevoNombre << "," << nuevoApellido << "\n";
        }
        else
        {
            // Mantener las líneas que no coinciden
            archivoTemporal << archivoCedula << "," << nombre << "," << apellido << "\n";
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();

    // Reemplazar el archivo original por el temporal
    remove("personas.txt");
    rename("personas_temp.txt", "personas.txt");

    cout << "Caracter cifrado correctamente con desplazamiento " << desplazamiento << ". Archivo actualizado y lista auxiliar actualizada.\n";
}


// Función para guardar los datos en un archivo
void ListaDoble::guardarEnArchivo(const std::string& cedula, const std::string& nombre, const std::string& apellido, const std::string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::app); // Agregar al final del archivo
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para escritura.\n";
        return;
    }
    // Guardar en formato: cedula,nombre,apellido
    archivo << cedula << "," << nombre << "," << apellido << "\n";
    archivo.close();
}

void ListaDoble::mostrar() {
    Nodo* temp = primero;
    if (temp == nullptr) {
        cout << "NULL\n";
        return;
    }
     while (temp != nullptr)
    {
        cout << "\nCedula: " << temp->getCedula()
             << "\nNombre: " << temp->getNombre()
             << "\nApellido: " << temp->getApellido() << " -> ";
        temp = temp->getSiguiente();
    }
}

void ListaDoble::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    while (getline(archivo, linea)) {
        // Dividir la línea en tres partes: cedula, nombre, apellido
        stringstream ss(linea);
        string cedula, nombre, apellido;

        getline(ss, cedula, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido);

        if (!cedula.empty() && !nombre.empty() && !apellido.empty()) {
            insertar(cedula, nombre, apellido);
        }
    }

    archivo.close();
}



