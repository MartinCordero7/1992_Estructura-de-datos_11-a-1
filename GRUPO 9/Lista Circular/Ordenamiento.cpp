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


void Ordenamiento::ordenarPorCubetas(ListaCircular& lista) {
    Nodo* actual = lista.getPrimero();
    if (actual == nullptr) {
        std::cout << "La lista está vacía. No hay nada que ordenar.\n";
        return;
    }

    // Paso 1: Crear archivos temporales (cubetas)
    std::vector<std::ofstream> cubetas(26);
    for (int i = 0; i < 26; ++i) {
        std::string nombreArchivo = "cubeta_" + std::string(1, 'A' + i) + ".txt";
        cubetas[i].open(nombreArchivo, std::ios::out);
    }

    // Paso 2: Distribuir los nodos en las cubetas
    do {
        std::string nombre = actual->getNombre();
        char primeraLetra = std::toupper(nombre[0]);
        int indice = primeraLetra - 'A';

        if (indice >= 0 && indice < 26) {
            cubetas[indice] << actual->getCedula() << ","
                            << actual->getNombre() << ","
                            << actual->getApellido() << "\n";
        }

        actual = actual->getSiguiente();
    } while (actual != lista.getPrimero());

    for (auto& cubeta : cubetas) {
        cubeta.close();
    }

    // Paso 3: Leer y reconstruir la lista circular
    lista = ListaCircular();
    for (int i = 0; i < 26; ++i) {
        std::string nombreArchivo = "cubeta_" + std::string(1, 'A' + i) + ".txt";
        std::ifstream cubeta(nombreArchivo, std::ios::in);

        std::string linea;
        while (std::getline(cubeta, linea)) {
            std::istringstream stream(linea);
            std::string cedula, nombre, apellido;

            std::getline(stream, cedula, ',');
            std::getline(stream, nombre, ',');
            std::getline(stream, apellido, ',');

            lista.insertar(cedula, nombre, apellido, false);
        }

        cubeta.close();
        // remove(nombreArchivo.c_str()); // Comentar para no borrar los archivos
    }

    std::cout << "Nombres ordenados correctamente usando cubetas (archivos).\n";
}
