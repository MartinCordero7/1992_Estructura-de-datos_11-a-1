/***********************************************************************
 * Module:  Ordenamiento.cpp
 * Author:  Erika Guayanay, Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "Ordenamiento.h"
#include "ListasCirculares.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <vector>
#include <sstream>
#include <algorithm> // Para std::sort
#include <fstream> // Para manejar archivos

void Ordenamiento::guardarEnArchivo(ListaCircular& lista, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo, std::ios::out);
    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo: " << nombreArchivo << "\n";
        return;
    }

    Nodo* actual = lista.getPrimero();
    if (actual == nullptr) {
        archivo << "NULL\n";
    } else {
        do {
            archivo << actual->getCedula() << ","
                    << actual->getNombre() << ","
                    << actual->getApellido() << "\n";
            actual = actual->getSiguiente();
        } while (actual != lista.getPrimero());
    }

    archivo.close();
    std::cout << "Datos guardados en " << nombreArchivo << "\n";
}

void Ordenamiento::ordenarPorCubetas(ListaCircular& lista) {
    Nodo* actual = lista.getPrimero();
    if (actual == nullptr) {
        std::cout << "La lista está vacía. No hay nada que ordenar.\n";
        return;
    }

    // Paso 1: Crear archivos temporales (cubetas)
    std::vector<std::vector<std::string>> cubetas(26);

    // Paso 2: Distribuir los nodos en las cubetas
    do {
        std::string nombre = actual->getNombre();
        char primeraLetra = std::toupper(nombre[0]);
        int indice = primeraLetra - 'A';

        if (indice >= 0 && indice < 26) {
            // Guardamos los datos como una sola cadena en formato "nombre,apellido,cedula"
            std::string datos = actual->getNombre() + "," + actual->getApellido() + "," + actual->getCedula();
            cubetas[indice].push_back(datos);
        }

        actual = actual->getSiguiente();
    } while (actual != lista.getPrimero());

    // Paso 3: Ordenar los datos dentro de cada cubeta
    for (auto& cubeta : cubetas) {
        std::sort(cubeta.begin(), cubeta.end(), [](const std::string& a, const std::string& b) {
            // Extraer nombres y apellidos de las cadenas "nombre,apellido,cedula"
            size_t coma1_a = a.find(',');
            size_t coma2_a = a.find(',', coma1_a + 1);
            size_t coma1_b = b.find(',');
            size_t coma2_b = b.find(',', coma1_b + 1);

            std::string nombreA = a.substr(0, coma1_a);
            std::string apellidoA = a.substr(coma1_a + 1, coma2_a - coma1_a - 1);
            std::string nombreB = b.substr(0, coma1_b);
            std::string apellidoB = b.substr(coma1_b + 1, coma2_b - coma1_b - 1);

            if (nombreA == nombreB) {
                return apellidoA < apellidoB; // Si los nombres son iguales, ordenar por apellido
            }
            return nombreA < nombreB; // Ordenar por nombre
        });
    }

    // Paso 4: Reconstruir la lista circular desde las cubetas
    lista = ListaCircular();
    for (const auto& cubeta : cubetas) {
        for (const auto& datos : cubeta) {
            size_t coma1 = datos.find(',');
            size_t coma2 = datos.find(',', coma1 + 1);

            std::string nombre = datos.substr(0, coma1);
            std::string apellido = datos.substr(coma1 + 1, coma2 - coma1 - 1);
            std::string cedula = datos.substr(coma2 + 1);

            lista.insertar(cedula, nombre, apellido, false);
        }
    }

    // Guardar los datos ordenados en personas_ordenadas.txt
    guardarEnArchivo(lista, "personas_ordenadas.txt");

    std::cout << "Nombres ordenados correctamente usando cubetas (archivos).\n";
}
