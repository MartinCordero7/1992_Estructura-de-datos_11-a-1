/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO: Altamirano Xavier, Cordero Martin, Oña Isaac
 * FECHA CREACION: Lunes, 16 de diciembre de 2024
 * FECHA MODIFICACION: Lunes, 16 de diciembre de 2024
 * Enunciado del problema: Mediante el metodo de ordenacion externa RadixSort implementarlo en una lista simple
 * Nivel: TERCERO     NRC: 1992
 *************************/

#include "lista.h"
#include "persona.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

template <typename T>
void Lista<T>::radixSortExterna(const string &archivoEntrada, const string &archivoSalida)
{

    ifstream entrada(archivoEntrada);
    if (!entrada.is_open())
    {
        cout << "Error al abrir el archivo de entrada: " << archivoEntrada << endl;
        return;
    }

    vector<Persona> registros;
    string cedula, apellido, nombre;

    while (entrada >> cedula >> apellido >> nombre)
    {
        registros.push_back(Persona(cedula, apellido, nombre));
    }
    entrada.close();

    size_t maxLength = 10;
    for (int pos = maxLength - 1; pos >= 0; --pos)
    {
        vector<vector<Persona>> buckets(10);
        for (const auto &persona : registros)
        {
            if (pos < persona.getCedula().size())
            {
                char digito = persona.getCedula()[pos];
                buckets[digito - '0'].push_back(persona);
            }
            else
            {
                buckets[0].push_back(persona);
            }
        }

        registros.clear();
        for (const auto &bucket : buckets)
        {
            registros.insert(registros.end(), bucket.begin(), bucket.end());
        }
    }

    ofstream salida(archivoSalida, ios::trunc);
    if (!salida.is_open())
    {
        cout << "Error al abrir el archivo de salida: " << archivoSalida << endl;
        return;
    }

    for (const auto &persona : registros)
    {
        salida << persona.getCedula() << " "
               << persona.getApellido() << " "
               << persona.getNombre() << endl;
    }
    salida.close();
    cout << "Datos ordenados y guardados en: " << archivoSalida << endl;
}

template <typename T>
void Lista<T>::guardarEnArchivo(const std::string &nombreArchivo) const
{
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    Nodo<T> *actual = cabeza;
    while (actual != nullptr)
    {

        archivo << actual->data.getCedula() << " "
                << actual->data.getNombre() << " "
                << actual->data.getApellido() << std::endl;
        actual = actual->siguiente;
    }

    archivo.close();
    std::cout << "La lista se guardó exitosamente en el archivo: " << nombreArchivo << std::endl;
}

template <typename T>
Lista<T>::Lista() : cabeza(nullptr) {}

template <typename T>
Lista<T>::~Lista()
{
    while (cabeza != nullptr)
    {
        eliminarPorCabeza();
    }
}

template <typename T>
void Lista<T>::insertarPorCabeza(T data)
{
    Nodo<T> *nuevo = new Nodo<T>(data);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

template <typename T>
void Lista<T>::insertarPorCola(T data)
{
    Nodo<T> *nuevo = new Nodo<T>(data);
    if (!cabeza)
    {
        cabeza = nuevo;
    }
    else
    {
        Nodo<T> *actual = cabeza;
        while (actual->siguiente != nullptr)
        {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

template <typename T>
void Lista<T>::eliminarPorCabeza()
{
    if (!cabeza)
        return;
    Nodo<T> *temp = cabeza;
    cabeza = cabeza->siguiente;
    delete temp;
}

template <typename T>
void Lista<T>::eliminarPorCedula(string cedula)
{
    if (cabeza == NULL)
    {
        cout << "La lista esta vacia" << endl;
        return;
    }

    if (cabeza->data.getCedula() == cedula)
    {
        Nodo<T> *temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        cout << "Persona con cedula " << cedula << " eliminada exitosamente" << endl;
        return;
    }

    Nodo<T> *actual = cabeza;
    Nodo<T> *anterior = NULL;

    while (actual != NULL && actual->data.getCedula() != cedula)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != NULL)
    {
        anterior->siguiente = actual->siguiente;
        delete actual;
        cout << "Persona con cedula " << cedula << " eliminada exitosamente" << endl;
    }
    else
    {
        cout << "No se encontro ninguna persona con la cedula " << cedula << endl;
    }
}

template <typename T>
void Lista<T>::buscarPorCedula(string cedula)
{
    if (cabeza == NULL)
    {
        cout << "La lista esta vacia" << endl;
        return;
    }

    Nodo<T> *actual = cabeza;
    while (actual != NULL)
    {
        if (actual->data.getCedula() == cedula)
        {
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
void Lista<T>::mostrarLista() const
{
    Nodo<T> *actual = cabeza;
    while (actual != nullptr)
    {
        cout << actual->data.getCedula() << " "
             << actual->data.getApellido() << " "
             << actual->data.getNombre() << endl;
        actual = actual->siguiente;
    }
}

template <typename T>
void Lista<T>::eliminarCaracter(char c)
{
    Nodo<T> *actual = cabeza;
    while (actual != nullptr)
    {
        
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
Lista<T>::Lista(const Lista &otra) : cabeza(nullptr)
{
    copiarLista(otra.cabeza);
}

template <typename T>
Lista<T> &Lista<T>::operator=(const Lista &otra)
{
    if (this != &otra)
    {
        while (cabeza != nullptr)
        {
            eliminarPorCabeza();
        }
        copiarLista(otra.cabeza);
    }
    return *this;
}

template <typename T>
void Lista<T>::copiarLista(const Nodo<T> *otraCabeza)
{
    const Nodo<T> *actual = otraCabeza;
    while (actual != nullptr)
    {
        insertarPorCola(actual->data);
        actual = actual->siguiente;
    }
}

template <typename T>
void Lista<T>::reemplazarCaracter(char original, char reemplazo)
{
    Nodo<T> *actual = cabeza;
    while (actual != nullptr)
    {
        
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
