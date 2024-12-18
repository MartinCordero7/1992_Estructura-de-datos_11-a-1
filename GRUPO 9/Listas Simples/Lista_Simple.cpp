/***********************************************************************
 * Module:  Lista_Simple.cpp
 * Author:  Erika Guayanay,Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "Lista_Simple.h"
#include <iostream>
#include <string>
#include <algorithm> // Aseg�rate de incluir este encabezado
#include <cctype>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

ListaSimple::ListaSimple() : cabeza(nullptr) {}

ListaSimple::~ListaSimple()
{
    Nodo* temp;
    while (cabeza != nullptr)
    {
        temp = cabeza;
        cabeza = cabeza->getSiguiente();
        delete temp;
    }
}

bool ListaSimple::validarCedulaUnica(string cedula)
{
    Nodo* temp = cabeza;
    while (temp != nullptr)
    {
        if (temp->getCedula() == cedula)
        {
            return false;
        }
        temp = temp->getSiguiente();
    }
    return true;
}

void ListaSimple::insertarACola(string cedula, string nombre, string apellido)
{
    if (!validarCedulaUnica(cedula))
    {
        cout << "Error: La cedula ya existe en la lista.\n";
        return;
    }

    Nodo* nuevo = new Nodo(cedula, nombre, apellido);
    if (cabeza == nullptr)
    {
        cabeza = nuevo;
    }
    else
    {
        Nodo* temp = cabeza;
        while (temp->getSiguiente() != nullptr)
        {
            temp = temp->getSiguiente();
        }
        temp->setSiguiente(nuevo);
    }
}

Nodo* ListaSimple::buscar(string cedula)
{
    // Intentamos abrir el archivo
    ifstream archivo("personas.txt");
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo personas.txt.\n";
        return nullptr;
    }

    string linea, archivoCedula, nombre, apellido;
    while (getline(archivo, linea))
    {
        // Limpiar espacios en blanco al principio y al final de la línea
        linea.erase(remove_if(linea.begin(), linea.end(), ::isspace), linea.end());

        // Suponiendo que el archivo tiene formato: cedula,nombre,apellido
        stringstream ss(linea);
        getline(ss, archivoCedula, ',');  // Leer la cédula
        getline(ss, nombre, ',');         // Leer el nombre
        getline(ss, apellido);            // Leer el apellido

        // Verificamos si la cédula leída del archivo coincide con la cédula proporcionada
        if (archivoCedula == cedula)
        {
            archivo.close();
            Nodo* nodo = new Nodo(archivoCedula, nombre, apellido);  // Crear nodo con los datos encontrados
            cout << "\n--Persona encontrada--\nCedula: " << archivoCedula << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "Apellido: " << apellido << endl;
            return nodo;
        }
    }

    archivo.close();
    cout << "La cedula " << cedula << " no existe en el archivo personas.txt.\n";
    return nullptr;  // Si no se encuentra la cédula
}

bool ListaSimple::eliminar(string cedula)
{
    Nodo* temp = cabeza;
    Nodo* anterior = nullptr;

    // Primero eliminamos el nodo de la lista
    while (temp != nullptr)
    {
        if (temp->getCedula() == cedula)
        {
            if (anterior == nullptr)
            {
                cabeza = temp->getSiguiente();
            }
            else
            {
                anterior->setSiguiente(temp->getSiguiente());
            }
            delete temp;

            // Actualizamos el archivo personas.txt
            ifstream archivoEntrada("personas.txt");
            ofstream archivoTemporal("personas_temp.txt");

            if (!archivoEntrada.is_open() || !archivoTemporal.is_open())
            {
                cout << "Error al abrir los archivos.\n";
                return false;
            }

            string linea, archivoCedula, nombre, apellido;
            bool encontrado = false;

            // Leemos cada línea del archivo original
            while (getline(archivoEntrada, linea))
            {
                stringstream ss(linea);
                getline(ss, archivoCedula, ',');
                getline(ss, nombre, ',');
                getline(ss, apellido);

                if (archivoCedula != cedula)
                {
                    // Si la cédula no coincide, la escribimos en el archivo temporal
                    archivoTemporal << archivoCedula << "," << nombre << "," << apellido << endl;
                }
                else
                {
                    // Si encontramos la cédula que estamos eliminando
                    encontrado = true;
                }
            }

            archivoEntrada.close();
            archivoTemporal.close();

            if (encontrado)
            {
                // Reemplazamos el archivo original por el temporal
                remove("personas.txt");
                rename("personas_temp.txt", "personas.txt");
                return true;
            }
            else
            {
                //cout << "No se encontró la persona en el archivo.\n";
                return false;
            }
        }
        anterior = temp;
        temp = temp->getSiguiente();
    }

    //cout << "Persona con cedula " << cedula << " no encontrada.\n";
    return false;
}

void ListaSimple::mostrar()
{
    Nodo* temp = cabeza;
    if (temp == nullptr)
    {
        cout << "\nNULL\n";
        return;
    }
    while (temp != nullptr)
    {
        cout << "\nCedula: " << temp->getCedula()
             << "\nNombre: " << temp->getNombre()
             << "\nApellido: " << temp->getApellido() << " -> ";
        temp = temp->getSiguiente();
    }
    cout << "\nNULL\n";
}



void ListaSimple::eliminarCaracter(string cedula, char caracter, ListaSimple& listaAuxiliar)
{
    // Buscar el nodo correspondiente a la cédula (ya se validó en el main)
    Nodo* temp = buscar(cedula);

    // Obtener el nombre y apellido actuales
    string nuevoNombre = temp->getNombre();
    string nuevoApellido = temp->getApellido();

    // Eliminar el carácter del nombre y apellido
    nuevoNombre.erase(remove(nuevoNombre.begin(), nuevoNombre.end(), caracter), nuevoNombre.end());
    nuevoApellido.erase(remove(nuevoApellido.begin(), nuevoApellido.end(), caracter), nuevoApellido.end());

    // Actualizar los valores en el nodo encontrado
    temp->setNombre(nuevoNombre);
    temp->setApellido(nuevoApellido);

    // Insertar en la lista auxiliar con los valores actualizados
    listaAuxiliar.insertarACola(temp->getCedula(), nuevoNombre, nuevoApellido);

    // Actualizar el archivo personas.txt
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


void ListaSimple::cifrarCaracter(string cedula, char caracter, int desplazamiento, ListaSimple& listaAuxiliar)
{
    // Buscar el nodo correspondiente a la cédula
    Nodo* temp = buscar(cedula);

    if (temp == nullptr)
    {
        cout << "Cedula no encontrada.\n";
        return;
    }

    // Obtener el nombre y apellido actuales
    string nuevoNombre = temp->getNombre();
    string nuevoApellido = temp->getApellido();

    // Definición de la lambda para cifrar caracteres
    auto cifrar = [caracter, desplazamiento](char c) -> char
    {
        if (c == caracter && isalpha(c))   // Verifica si el carácter coincide y es una letra
        {
            char base = islower(c) ? 'a' : 'A'; // Determina si es minúscula o mayúscula
            return (c - base + desplazamiento) % 26 + base; // Aplica el cifrado César
        }
        return c; // Devuelve el carácter sin modificar si no cumple la condición
    };

    // Aplicar cifrado al nombre y apellido
    std::transform(nuevoNombre.begin(), nuevoNombre.end(), nuevoNombre.begin(), cifrar);
    std::transform(nuevoApellido.begin(), nuevoApellido.end(), nuevoApellido.begin(), cifrar);

    // Actualizar los valores en el nodo encontrado
    temp->setNombre(nuevoNombre);
    temp->setApellido(nuevoApellido);

    // Insertar en la lista auxiliar con los valores cifrados
    listaAuxiliar.insertarACola(temp->getCedula(), nuevoNombre, nuevoApellido);

    // Actualizar el archivo personas.txt
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
void ListaSimple::guardarEnArchivo(const std::string& cedula, const std::string& nombre, const std::string& apellido, const std::string& nombreArchivo)
{
    ofstream archivo(nombreArchivo, ios::app); // Agregar al final del archivo
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo para escritura.\n";
        return;
    }
    // Guardar en formato: cedula,nombre,apellido
    archivo << cedula << "," << nombre << "," << apellido << "\n";
    archivo.close();
}



void ListaSimple::cargarDesdeArchivo(const string& nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    while (getline(archivo, linea))
    {
        // Dividir la línea en tres partes: cedula, nombre, apellido
        stringstream ss(linea);
        string cedula, nombre, apellido;

        getline(ss, cedula, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido);

        if (!cedula.empty() && !nombre.empty() && !apellido.empty())
        {
            insertarACola(cedula, nombre, apellido);
        }
    }

    archivo.close();
}

