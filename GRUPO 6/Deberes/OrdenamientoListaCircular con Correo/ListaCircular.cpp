/*******************************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                                  *
 * Proposito:                      Lista circular                                                      *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz                    *
 * Fecha de creacion:              17/12/2024                                                          *
 * Fecha de modificacion:          18/12/2024                                                          *
 * Materia:                        Estructura de datos                                                 *
 * NRC :                           1992                                                                *
 *******************************************************************************************************/
#include "ListaCircular.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <direct.h>  // Para mkdir en Windows
#include <sys/stat.h>  // Para usar _stat
#include <algorithm>   // Para usar std::sort
#include "BackupManager.h"  // Incluir el archivo de cabecera con la declaración de la función

using namespace std;

// Agregar persona
void ListaCircular::agregarPersona(const Persona& persona) {
    // Verificar si la cédula ya existe
    if (buscarPersonaPorCedula(persona.getCedula())) {
        cout << "Error: La cédula " << persona.getCedula() << " ya existe.\n";
        return;
    }

    Nodo* nuevo = new Nodo{persona, cabeza};
    if (!cabeza) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza; // Hacer circular
    } else {
        Nodo* actual = cabeza;
        while (actual->siguiente != cabeza) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
        nuevo->siguiente = cabeza; // Hacer circular
    }
    cout << "Persona agregada: " << persona.getNombre() << endl;
    // Guardar solo si no se está restaurando un backup
    if (!evitarGuardar) {
        guardarPersonasEnArchivo();
    }
}

// Limpiar la lista actual
void ListaCircular::limpiarLista() {
    if (!cabeza) return;
    Nodo* actual = cabeza;
    do {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    } while (actual != cabeza);
    cabeza = nullptr;
}

// Imprimir todas las personas
void ListaCircular::imprimirPersonas() {
    if (!cabeza) {
        cout << "No hay personas registradas.\n";
        return;
    }
    Nodo* actual = cabeza;
    cout << left << setw(20) << "Primer Nombre" 
        << setw(20) << "Segundo Nombre"
        << setw(15) << "Apellido"
        << setw(20) << "Cedula" 
        << setw(30) << "Correo"
        << setw(30) << "Fecha de Nacimiento" << endl;
    cout << string(130, '-') << endl;

    do {
        cout << left << setw(20) << actual->persona.getNombre()
            << setw(20) << actual->persona.getSegundoNombre()
            << setw(15) << actual->persona.getApellido()
            << setw(20) << actual->persona.getCedula()
            << setw(30) << actual->persona.getCorreo()
            << setw(30) << actual->persona.getFechaNacimiento().mostrar() << endl;
        actual = actual->siguiente;
    } while (actual != cabeza);
}

// Buscar persona por nombre
Nodo* ListaCircular::buscarPersona(const string& nombre) {
    if (!cabeza) return nullptr;
    Nodo* actual = cabeza;
    do {
        if (actual->persona.getNombre() == nombre) return actual;
        actual = actual->siguiente;
    } while (actual != cabeza);
    return nullptr;
}

// Buscar persona por cédula
Nodo* ListaCircular::buscarPersonaPorCedula(const string& cedula) {
    if (!cabeza) return nullptr;
    Nodo* actual = cabeza;
    do {
        if (actual->persona.getCedula() == cedula) return actual;
        actual = actual->siguiente;
    } while (actual != cabeza);
    return nullptr;
}

// Eliminar persona por nombre y actualizar archivo
void ListaCircular::eliminarPersona(const string& nombre) {
    if (!cabeza) return;
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;
    bool encontrado = false;
    do {
        if (actual->persona.getNombre() == nombre) {
            encontrado = true;
            if (anterior) {
                anterior->siguiente = actual->siguiente;
            } else {
                Nodo* temp = cabeza;
                while (temp->siguiente != cabeza) {
                    temp = temp->siguiente;
                }
                cabeza = actual->siguiente;
                temp->siguiente = cabeza;
            }
            delete actual;
            cout << "Persona eliminada: " << nombre << endl;
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
    } while (actual != cabeza);

    if (!encontrado) {
        cout << "Persona no encontrada: " << nombre << endl;
    }

    // Actualizar el archivo después de la eliminación
    guardarPersonasEnArchivo();  
}

// Eliminar persona por cédula y actualizar archivo
void ListaCircular::eliminarPersonaPorCedula(const string& cedula) {
    if (!cabeza) return;
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;
    bool encontrado = false;
    do {
        if (actual->persona.getCedula() == cedula) {
            encontrado = true;
            if (anterior) {
                anterior->siguiente = actual->siguiente;
            } else {
                Nodo* temp = cabeza;
                while (temp->siguiente != cabeza) {
                    temp = temp->siguiente;
                }
                cabeza = actual->siguiente;
                temp->siguiente = cabeza;
            }
            delete actual;
            cout << "Persona eliminada: " << cedula << endl;
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
    } while (actual != cabeza);

    if (!encontrado) {
        cout << "Persona no encontrada: " << cedula << endl;
    }

    // Actualizar el archivo después de la eliminación
    guardarPersonasEnArchivo();  
}

// Guardar las personas en el archivo (actualizado)
void ListaCircular::guardarPersonasEnArchivo() {
    ofstream archivo("personas_temp.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo temporal para guardar.\n\n";
        return;
    }

    if (!cabeza) return;
    Nodo* actual = cabeza;
    do {
        archivo << actual->persona.getNombre() << ";"
                << actual->persona.getSegundoNombre() << ";"
                << actual->persona.getApellido() << ";"
                << actual->persona.getCedula() << ";"
                << actual->persona.getCorreo() << ";"
                << actual->persona.getFechaNacimiento().mostrar() << endl;
        actual = actual->siguiente;
    } while (actual != cabeza);

    archivo.close();

    // Verificar si el archivo temporal se creó correctamente
    if (FILE* file = fopen("personas_temp.txt", "r")) {
        fclose(file);
    } else {
        cout << "No se pudo crear el archivo temporal correctamente.\n";
        return;
    }

    // Eliminar el archivo de destino si ya existe
    if (remove(archivoPersonas.c_str()) != 0) {
    }

    // Renombrar el archivo temporal a la ubicación final
    if (rename("personas_temp.txt", archivoPersonas.c_str()) != 0) {
    } else {
        cout << "Personas guardadas en el archivo: " << archivoPersonas << endl;
    }
}

// Cargar las personas desde el archivo
void ListaCircular::cargarPersonasDesdeArchivo() {
    ifstream archivo(archivoPersonas);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para cargar las personas.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, segundoNombre, apellido, cedula, correo, fechaNacimientoStr;
        getline(ss, nombre, ';');
        getline(ss, segundoNombre, ';');
        getline(ss, apellido, ';');
        getline(ss, cedula, ';');
        getline(ss, correo, ';');
        getline(ss, fechaNacimientoStr, ';');

        // Procesar fecha de nacimiento
        Fecha fechaNacimiento = Fecha::crearDesdeCadena(fechaNacimientoStr);

        Persona persona(nombre, segundoNombre, apellido, cedula, fechaNacimiento, correo);
        agregarPersona(persona);
    }
    archivo.close();
    cout << "Personas cargadas desde el archivo.\n";
}

// Backup
void ListaCircular::crearBackup(const string& nombreArchivo) {
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

    // Iterar sobre los elementos de la lista y guardar los datos de cada persona en el archivo
    if (!cabeza) return;
    Nodo* actual = cabeza;
    do {
        // Obtener información de la persona y sus componentes
        const Persona& persona = actual->persona;
        const Fecha& fechaNac = persona.getFechaNacimiento();

        // Guardar los datos en el archivo en un formato delimitado
        archivo << persona.getNombre() << ";" 
                << persona.getSegundoNombre() << ";"
                << persona.getApellido() << ";"
                << persona.getCedula() << ";"
                << persona.getCorreo() << ";"
                << fechaNac.getDia() << "-" << fechaNac.getMes() << "-" << fechaNac.getAnio() << "\n";
        actual = actual->siguiente;
    } while (actual != cabeza);

    // Cerrar el archivo después de escribir los datos
    archivo.close();
    cout << "Backup creado correctamente en: " << rutaCompleta << endl;
}

// Restaurar backup y sobreescribir archivo
void ListaCircular::restaurarBackup(const string& nombreArchivo) {
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
        string nombre, segundoNombre, apellido, cedula, correo, fechaNacStr;

        // Leer datos del archivo
        getline(ss, nombre, ';');
        getline(ss, segundoNombre, ';');
        getline(ss, apellido, ';');
        getline(ss, cedula, ';');
        getline(ss, correo, ';');
        getline(ss, fechaNacStr, ';');

        // Parsear la fecha de nacimiento
        int diaNac, mesNac, anioNac;
        sscanf(fechaNacStr.c_str(), "%d-%d-%d", &diaNac, &mesNac, &anioNac);
        Fecha fechaNacimiento(diaNac, mesNac, anioNac);

        // Crear el objeto correspondiente
        Persona persona(nombre, segundoNombre, apellido, cedula, fechaNacimiento, correo);

        // Agregar persona a la lista
        agregarPersona(persona);
    }

    evitarGuardar = false; // Volver a guardar normalmente
    archivo.close();

    guardarPersonasEnArchivo();
    cout << "Backup restaurado: " << nombreArchivo << endl;
}

// Ordenar la lista por cédula usando merge sort externo
void ListaCircular::ordenarPorCedula() {
    // Guardar las personas en el archivo
    guardarPersonasEnArchivo();

    // Abrir el archivo de personas
    ifstream archivo(archivoPersonas);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para ordenar las personas.\n";
        return;
    }

    // Crear un vector para almacenar las personas
    vector<Persona> personas;

    // Leer las personas del archivo
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, segundoNombre, apellido, cedula, correo, fechaNacimientoStr;
        getline(ss, nombre, ';');
        getline(ss, segundoNombre, ';');
        getline(ss, apellido, ';');
        getline(ss, cedula, ';');
        getline(ss, correo, ';');
        getline(ss, fechaNacimientoStr, ';');

        // Procesar fecha de nacimiento
        Fecha fechaNacimiento = Fecha::crearDesdeCadena(fechaNacimientoStr);

        Persona persona(nombre, segundoNombre, apellido, cedula, fechaNacimiento, correo);
        personas.push_back(persona);
    }
    archivo.close();

    // Ordenar las personas por cédula usando merge sort
    sort(personas.begin(), personas.end(), [](const Persona& a, const Persona& b) {
        return a.getCedula() < b.getCedula();
    });

    // Guardar las personas ordenadas en el archivo
    ofstream archivoOrdenado(archivoPersonas);
    if (!archivoOrdenado.is_open()) {
        cout << "Error al abrir el archivo para guardar las personas ordenadas.\n";
        return;
    }

    for (const auto& persona : personas) {
        archivoOrdenado << persona.getNombre() << ";"
                        << persona.getSegundoNombre() << ";"
                        << persona.getApellido() << ";"
                        << persona.getCedula() << ";"
                        << persona.getCorreo() << ";"
                        << persona.getFechaNacimiento().mostrar() << endl;
    }
    archivoOrdenado.close();

    // Cargar las personas ordenadas en la lista
    limpiarLista(); // Limpiar la lista actual antes de recargar
    cargarPersonasDesdeArchivo();
}