/***********************************************************************
 * Module:  Ordenamiento.cpp
 * Author:  Erika Guayanay, Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "Ordenamiento.h"
#include "json.hpp"
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype> // Para std::tolower

using json = nlohmann::json;

void Ordenamiento::ordenarNombresExterno(ListaCircular& lista, const std::string& archivo) {
    Nodo* actual = lista.getPrimero();
    if (actual == nullptr) {
        std::cout << "La lista está vacía. No hay nada que ordenar.\n";
        return;
    }

    // Paso 1: Exportar la lista circular a un archivo JSON.
    json datos = json::array();
    do {
        datos.push_back({
            {"cedula", actual->getCedula()},
            {"nombre", actual->getNombre()},
            {"apellido", actual->getApellido()}
        });
        actual = actual->getSiguiente();
    } while (actual != lista.getPrimero());

    std::ofstream out(archivo);
    out << datos.dump(4); // Guarda el JSON con formato legible.
    out.close();

    // Paso 2: Leer y ordenar los datos en el archivo JSON.
    std::ifstream in(archivo);
    json datosOrdenados;
    in >> datosOrdenados;
    in.close();

    // Ordenar de manera insensible a mayúsculas/minúsculas
    std::sort(datosOrdenados.begin(), datosOrdenados.end(), [](const json& a, const json& b) {
    std::string nombreA = a["nombre"];
    std::string nombreB = b["nombre"];
    std::string apellidoA = a["apellido"];
    std::string apellidoB = b["apellido"];
        // Convertir ambos nombres a minúsculas para la comparación
    std::transform(nombreA.begin(), nombreA.end(), nombreA.begin(), ::tolower);
    std::transform(nombreB.begin(), nombreB.end(), nombreB.begin(), ::tolower);
    std::transform(apellidoA.begin(), apellidoA.end(), apellidoA.begin(), ::tolower);
    std::transform(apellidoB.begin(), apellidoB.end(), apellidoB.begin(), ::tolower);
    if (nombreA == nombreB) {
    return apellidoA < apellidoB; // Si los nombres son iguales, comparar por apellidos
    }
    return nombreA < nombreB; // Comparar por nombres normalmente
});

    // Guardar el JSON ordenado.
    std::ofstream outOrdenado(archivo);
    outOrdenado << datosOrdenados.dump(4);
    outOrdenado.close();

    // Paso 3: Reconstruir la lista circular a partir del archivo JSON ordenado.
    lista = ListaCircular(); // Limpia la lista actual.
    for (const auto& item : datosOrdenados) {
        lista.insertar(item["cedula"], item["nombre"], item["apellido"], false); // Suprimir el mensaje
    }

    // Imprimir la lista ordenada
    std::cout << "Nombres ordenados correctamente. Lista ordenada:\n";
    lista.mostrar(); // Llama a la función mostrar para imprimir la lista ordenada
}
