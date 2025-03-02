/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Realizar una Lista circular doble                        *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "ListaCircularDoble.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <direct.h>  // Para mkdir en Windows
#include <sys/stat.h>  // Para usar _stat
#include "BackupManager.h"  // Incluir el archivo de cabecera con la declaración de la función

using namespace std;

ListaCircularDoble::ListaCircularDoble() : cabeza(nullptr), evitarGuardar(false) {
    ifstream archivo("entregas.txt");
    if (!archivo.is_open()) {
        ofstream nuevoArchivo("entregas.txt");
        nuevoArchivo.close();
    } else {
        archivo.close();
    }
}

// Agregar entrega

bool ListaCircularDoble::estaVacia() const {
    return cabeza == nullptr;
}

void ListaCircularDoble::agregarEntrega(const Entrega& entrega) {
    NodoEntrega* nuevo = new NodoEntrega{ entrega, nullptr, nullptr };
    if (!cabeza) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        NodoEntrega* ultimo = cabeza->anterior;
        nuevo->siguiente = cabeza;
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        cabeza->anterior = nuevo;
    }
    cout << "Entrega registrada para el cliente: " << entrega.cliente.nombre << endl;
    if (!evitarGuardar) {
        guardarEntregasEnArchivo();
    }
}

// Limpiar la lista actual
void ListaCircularDoble::limpiarLista() {
    if (!cabeza) return;

    NodoEntrega* actual = cabeza;
    do {
        NodoEntrega* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    } while (actual != cabeza);

    cabeza = nullptr;
}

// Imprimir todas las entregas
void ListaCircularDoble::imprimirEntregas() {
    if (!cabeza) {
        cout << "No hay entregas registradas.\n";
        return;
    }

    cout << "\n=== LISTA DE ENTREGAS ===\n";
    cout << left << setw(30) << "Cliente"
         << setw(15) << "Cédula"
         << setw(15) << "Celular"    // Añadida columna para celular
         << setw(30) << "Zona" << endl;
    cout << string(90, '-') << endl;  // Aumentado el ancho de la línea

    NodoEntrega* actual = cabeza;
    do {
        cout << left << setw(30) << actual->entrega.cliente.nombre
             << setw(15) << actual->entrega.cliente.cedula
             << setw(15) << actual->entrega.cliente.celular  // Añadido el celular
             << setw(30) << actual->entrega.zona << endl;
        actual = actual->siguiente;
    } while(actual != cabeza);
    cout << string(90, '-') << endl;  // Aumentado el ancho de la línea
}


// Buscar entrega por cédula
NodoEntrega* ListaCircularDoble::buscarEntregaPorCedula(const string& cedula) {
    if (!cabeza) return nullptr;
    NodoEntrega* actual = cabeza;
    do {
        if (actual->entrega.cliente.cedula == cedula)
            return actual;
        actual = actual->siguiente;
    } while(actual != cabeza);
    return nullptr;
}

// Eliminar entrega por cédula
bool ListaCircularDoble::eliminarEntrega(const string& cedula) {
    if (!cabeza) return false;
    NodoEntrega* actual = cabeza;
    do {
        if (actual->entrega.cliente.cedula == cedula) {
            if (actual->siguiente == actual) { // Única entrega
                cabeza = nullptr;
            } else {
                NodoEntrega* anterior = actual->anterior;
                NodoEntrega* siguiente = actual->siguiente;
                anterior->siguiente = siguiente;
                siguiente->anterior = anterior;
                if (actual == cabeza) cabeza = siguiente;
            }
            delete actual;
            cout << "Entrega eliminada exitosamente.\n";
            guardarEntregasEnArchivo();
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    return false;
}

// Guardar entregas en archivo
void ListaCircularDoble::guardarEntregasEnArchivo() {
    ofstream archivo("entregas.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo entregas.txt\n";
        return;
    }
    
    if (cabeza) {
        NodoEntrega* actual = cabeza;
        do {
            archivo << actual->entrega.cliente.nombre << ";"
                << actual->entrega.cliente.cedula << ";"
                << actual->entrega.cliente.celular << ";"
                << actual->entrega.zona << "\n";
            actual = actual->siguiente;
        } while (actual != cabeza);
    }
    archivo.close();
}

void ListaCircularDoble::cargarEntregasDesdeArchivo() {
    ifstream archivo("entregas.txt");
    if (!archivo.is_open()) {
        cout << "No hay entregas previas para cargar.\n";
        return;
    }

    limpiarLista();
    evitarGuardar = true;

    string linea;
    while (getline(archivo, linea)) {
        if(linea.empty()) continue;
        
        stringstream ss(linea);
        string nombre, cedula, celular, zona;
        
        getline(ss, nombre, ';');
        getline(ss, cedula, ';');
        getline(ss, celular, ';');
        getline(ss, zona);

        if(!nombre.empty() && !cedula.empty() && !celular.empty() && !zona.empty()) {
            Cliente cliente(nombre, cedula, celular);
            Entrega entrega(cliente, zona);
            agregarEntrega(entrega);
        }
    }
    
    evitarGuardar = false;
    archivo.close();
}

// Backup
void ListaCircularDoble::crearBackup(const string& nombreArchivo) {
    string carpetaBackup = "backup";
    BackupManager::crearCarpetaSiNoExiste(carpetaBackup);
    string rutaCompleta = carpetaBackup + "\\" + nombreArchivo;

    ofstream archivo(rutaCompleta);
    if (!archivo.is_open()) {
        cout << "Error al crear el archivo de backup en la ruta: " << rutaCompleta << endl;
        return;
    }

    NodoEntrega* actual = cabeza;
    if (actual) {
        do {
            const Entrega& entrega = actual->entrega;
            const Cliente& cliente = entrega.cliente;

            archivo << cliente.nombre << ";"
                << cliente.cedula << ";"
                << cliente.celular << ";"  // Añadido el celular
                << entrega.zona << "\n";
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    archivo.close();
    cout << "Backup creado correctamente en: " << rutaCompleta << endl;
}

// Restaurar backup y sobreescribir archivo
void ListaCircularDoble::restaurarBackup(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de backup.\n";
        return;
    }

    cout << "Cargando backup desde: " << nombreArchivo << endl;

    limpiarLista();
    evitarGuardar = true;

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, cedula, celular, zona;

        getline(ss, nombre, ';');
        getline(ss, cedula, ';');
        getline(ss, celular, ';');  // Añadido el celular
        getline(ss, zona);

        Cliente cliente(nombre, cedula, celular);  // Actualizado el constructor
        Entrega entrega(cliente, zona);
        agregarEntrega(entrega);
    }

    evitarGuardar = false;
    archivo.close();

    guardarEntregasEnArchivo();
    cout << "Backup restaurado: " << nombreArchivo << endl;
}

bool ListaCircularDoble::existeCedula(const string& cedula) const {
    if (!cabeza) return false;
    NodoEntrega* actual = cabeza;
    do {
        if (actual->entrega.cliente.cedula == cedula)
            return true;
        actual = actual->siguiente;
    } while (actual != cabeza);
    return false;
}

bool ListaCircularDoble::existeCelular(const string& celular) const {
    if (!cabeza) return false;
    NodoEntrega* actual = cabeza;
    do {
        if (actual->entrega.cliente.celular == celular)
            return true;
        actual = actual->siguiente;
    } while (actual != cabeza);
    return false;
}

Cliente* ListaCircularDoble::obtenerClientePorCedula(const string& cedula) {
    if (!cabeza) return nullptr;
    NodoEntrega* actual = cabeza;
    do {
        if (actual->entrega.cliente.cedula == cedula)
            return &(actual->entrega.cliente);
        actual = actual->siguiente;
    } while (actual != cabeza);
    return nullptr;
}

NodoEntrega* ListaCircularDoble::buscarTodasLasEntregasPorCedula(const string& cedula, int& cantidad) {
    cantidad = 0;
    NodoEntrega* primerNodo = nullptr;
    
    if (!cabeza) return nullptr;
    
    NodoEntrega* actual = cabeza;
    do {
        if (actual->entrega.cliente.cedula == cedula) {
            if (!primerNodo) primerNodo = actual;
            cantidad++;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    return primerNodo;
}

bool ListaCircularDoble::eliminarEntrega(const string& cedula, NodoEntrega* nodoAEliminar) {
    if (!cabeza || !nodoAEliminar) return false;
    
    if (nodoAEliminar->siguiente == nodoAEliminar) { // Única entrega
        cabeza = nullptr;
    } else {
        NodoEntrega* anterior = nodoAEliminar->anterior;
        NodoEntrega* siguiente = nodoAEliminar->siguiente;
        anterior->siguiente = siguiente;
        siguiente->anterior = anterior;
        if (nodoAEliminar == cabeza) cabeza = siguiente;
    }
    delete nodoAEliminar;
    guardarEntregasEnArchivo();
    return true;
}