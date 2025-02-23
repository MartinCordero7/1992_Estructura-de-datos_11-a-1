/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Realizar una Lista circular doble          *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/



#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H

#include <string>
#include "Entrega.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct NodoEntrega {
    Entrega entrega;
    NodoEntrega* siguiente;
    NodoEntrega* anterior;
};

class ListaCircularDoble {
public:
    NodoEntrega* cabeza;
    bool evitarGuardar;  // Para evitar guardado automático en procesos como backup

    ListaCircularDoble();
    bool estaVacia() const;

    // Métodos para entregas
    void agregarEntrega(const Entrega& entrega);
    NodoEntrega* buscarEntregaPorCedula(const string& cedula);
    bool eliminarEntrega(const string& cedula);
    void imprimirEntregas();

    // Lanza el error: agregar la función limpiarLista
    void limpiarLista();

    // Métodos de archivo
    void guardarEntregasEnArchivo();
    void cargarEntregasDesdeArchivo();

    // Backup (se reutiliza la lógica, adaptada a entregas)
    void crearBackup(const string& nombreArchivo);
    void restaurarBackup(const string& nombreArchivo);

    // ...otros métodos existentes si fuere necesario...
};

#endif
