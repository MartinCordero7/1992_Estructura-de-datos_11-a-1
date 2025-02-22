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

ListaCircularDoble::ListaCircularDoble() : cabeza(nullptr), evitarGuardar(false) {}

// Agregar entrega
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
    NodoEntrega* actual = cabeza;
    cout << left << setw(30) << "Cliente"
         << setw(20) << "Cédula"
         << setw(20) << "Zona"
         << setw(10) << "Prioridad" << endl;
    cout << string(80, '-') << endl;
    do {
        cout << left << setw(30) << actual->entrega.cliente.nombre
             << setw(20) << actual->entrega.cliente.cedula
             << setw(20) << actual->entrega.zona
             << setw(10) << actual->entrega.prioridad << endl;
        actual = actual->siguiente;
    } while(actual != cabeza);
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
    ofstream archivo("entregas_temp.txt");
    if (!archivo.is_open()){
        cout << "Error al abrir el archivo temporal para guardar.\n";
        return;
    }
    NodoEntrega* actual = cabeza;
    if (actual) {
        do {
            archivo << actual->entrega.cliente.nombre << ";"
                    << actual->entrega.cliente.cedula << ";"
                    << actual->entrega.zona << ";"
                    << actual->entrega.prioridad << "\n";
            actual = actual->siguiente;
        } while (actual != cabeza);
    }
    archivo.close();

    // Se elimina el archivo anterior y se renombra el temporal
    remove("entregas.txt");
    if (rename("entregas_temp.txt", "entregas.txt") != 0) {
        perror("Error al renombrar el archivo temporal");
    } else {
        cout << "Entregas guardadas en el archivo: entregas.txt\n";
    }
}

// Cargar las entregas desde el archivo
void ListaCircularDoble::cargarEntregasDesdeArchivo() {
    ifstream archivo("entregas.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para cargar las entregas.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if(linea.empty()) continue;
        stringstream ss(linea);
        string nombre, cedula, zona, prioridadStr;
        getline(ss, nombre, ';');
        getline(ss, cedula, ';');
        getline(ss, zona, ';');
        getline(ss, prioridadStr, ';');
        int prioridad = stoi(prioridadStr);

        // Se crea la entrega y se agrega a la lista
        Cliente cli(nombre, cedula);
        Entrega entr(cli, zona, prioridad);
        agregarEntrega(entr);
    }
    archivo.close();
    cout << "Entregas cargadas desde el archivo.\n";
}

// Backup
void ListaCircularDoble::crearBackup(const string& nombreArchivo) {
    string carpetaBackup = "backup";  // Carpeta donde se almacenan los backups
    
    // Asegurarnos de que la carpeta de backups exista
    BackupManager::crearCarpetaSiNoExiste(carpetaBackup);

    // Crear la ruta completa para el archivo de backup dentro de la carpeta "backup"
    string rutaCompleta = carpetaBackup + "\\" + nombreArchivo;

    // Crear el archivo de backup
    ofstream archivo(rutaCompleta);
    if (!archivo.is_open()) {
        cout << "Error al crear el archivo de backup en la ruta: " << rutaCompleta << endl;
        return;
    }

    // Iterar sobre los elementos de la lista circular y guardar los datos de cada libro en el archivo
    NodoEntrega* actual = cabeza;
    if (actual) {
        do {
            // Obtener información del libro y sus componentes
            const Entrega& entrega = actual->entrega;
            const Cliente& cliente = entrega.cliente;

            // Guardar los datos en el archivo en un formato delimitado
            archivo << cliente.nombre << ";"
                    << cliente.cedula << ";"
                    << entrega.zona << ";"
                    << entrega.prioridad << "\n";
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    // Cerrar el archivo después de escribir los datos
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
    evitarGuardar = true; // Evitar guardar durante la restauración

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, cedula, zona, prioridadStr;

        // Leer datos del archivo
        getline(ss, nombre, ';');
        getline(ss, cedula, ';');
        getline(ss, zona, ';');
        getline(ss, prioridadStr, ';');
        int prioridad = stoi(prioridadStr);

        // Crear los objetos correspondientes
        Cliente cliente(nombre, cedula);
        Entrega entrega(cliente, zona, prioridad);

        // Agregar libro a la lista
        agregarEntrega(entrega);
    }

    evitarGuardar = false; // Volver a guardar normalmente
    archivo.close();

    guardarEntregasEnArchivo();
    cout << "Backup restaurado: " << nombreArchivo << endl;
}
