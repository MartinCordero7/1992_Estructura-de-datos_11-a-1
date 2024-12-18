/***********************************************************************
 * Module:  MetodoOrdenamientoExterno.cpp
 * Author:  Erika Guayanay,Jerson Llumiquinga M, Maycol Celi.
 * Date: 17/12/2024
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include "MetodoOrdenamientoExterno.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

void MetodoOrdenamientoExterno::distribuirDatos(const string& archivoEntrada, vector<string>& archivosSalida) {
    ifstream archivo(archivoEntrada);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de entrada.\n";
        return;
    }

    // Crear archivos de salida para las 26 letras
    vector<ofstream> cubetas(26);
    for (int i = 0; i < 26; ++i) {
        string nombreArchivo = "cubeta_" + string(1, 'A' + i) + ".txt";
        cubetas[i].open(nombreArchivo);
        archivosSalida.push_back(nombreArchivo);
    }

    string linea;
    while (getline(archivo, linea)) {
        // Dividir la l�nea en columnas: cedula, nombre, apellido
        stringstream ss(linea);
        string cedula, nombre, apellido;

        getline(ss, cedula, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido);

        // Usar la primera letra del nombre para determinar la cubeta
        if (!nombre.empty()) {
            char letra = tolower(nombre[0]);
            int indice = letra - 'a';
            if (indice >= 0 && indice < 26) {
                cubetas[indice] << linea << "\n";
            }
        }
    }

    archivo.close();

    // Cerrar todos los archivos de salida
    for (auto& cubeta : cubetas) {
        cubeta.close();
    }

    cout << "Datos distribuidos correctamente en las cubetas.\n";
}

void MetodoOrdenamientoExterno::ordenarArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo " << nombreArchivo << " para lectura.\n";
        return;
    }

    vector<string> datos;
    string linea;
    while (getline(archivo, linea)) {
        datos.push_back(linea);
    }
    archivo.close();

    // Funci�n de comparaci�n personalizada para ordenar por nombre y luego por apellido
    sort(datos.begin(), datos.end(), [](const string& a, const string& b) {
        stringstream ssA(a), ssB(b);
        string cedulaA, nombreA, apellidoA;
        string cedulaB, nombreB, apellidoB;

        // Extraer los datos de la l�nea para ambos registros
        getline(ssA, cedulaA, ',');
        getline(ssA, nombreA, ',');
        getline(ssA, apellidoA);

        getline(ssB, cedulaB, ',');
        getline(ssB, nombreB, ',');
        getline(ssB, apellidoB);

        // Primero comparar por nombre
        if (nombreA != nombreB) {
            return nombreA < nombreB;
        }

        // Si los nombres son iguales, comparar por apellido
        return apellidoA < apellidoB;
    });

    ofstream archivoSalida(nombreArchivo);
    for (const auto& dato : datos) {
        archivoSalida << dato << "\n";
    }
    archivoSalida.close();
}


void MetodoOrdenamientoExterno::fusionarArchivos(const vector<string>& archivosCubetas, const string& archivoFinal) {
    ofstream archivoSalida(archivoFinal);
    if (!archivoSalida.is_open()) {
        cout << "Error al abrir el archivo de salida.\n";
        return;
    }

    for (const auto& archivoCubeta : archivosCubetas) {
        ifstream archivo(archivoCubeta);
        string linea;
        while (getline(archivo, linea)) {
            archivoSalida << linea << "\n";
        }
        archivo.close();
    }

    archivoSalida.close();
    cout << "Archivos fusionados en " << archivoFinal << ".\n";
}

void MetodoOrdenamientoExterno::mostrarArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();
}
