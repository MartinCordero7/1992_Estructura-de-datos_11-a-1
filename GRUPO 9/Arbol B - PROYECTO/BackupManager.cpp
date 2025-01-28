/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Gestionar Backups                                        *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "BackupManager.h"
#include <iostream>
#include <windows.h> // Para las funciones de Windows
#include <direct.h>  // Para mkdir en Windows
#include <sys/stat.h> // Para _stat
#include <fstream>   // Para trabajar con archivos
#include <vector>
#include <string>
#include <sstream>
#include "ArbolBTree.h"
#include "Validaciones.h"

using namespace std;

// Implementación de los métodos de BackupManager

void BackupManager::crearCarpetaSiNoExiste(const string& ruta) {
    try {
        struct _stat st;

        // Verificar si la carpeta existe
        if (_stat(ruta.c_str(), &st) != 0) {
            // Si la carpeta no existe, la creamos
            if (_mkdir(ruta.c_str()) == 0) {
                cout << "Carpeta creada: " << ruta << endl;
            } else {
                cerr << "Error al crear la carpeta: " << ruta << endl;
            }
        } else {
            cout << "La carpeta ya existe: " << ruta << endl;
        }
    } catch (const exception& e) {
        cerr << "Error al crear la carpeta: " << e.what() << endl;
    }
}

vector<string> BackupManager::listarArchivosEnCarpeta(const string& carpeta) {
    try {
        vector<string> archivos;
        string path = carpeta + "\\*"; // Agregar comodín para buscar todos los archivos
        WIN32_FIND_DATAA findFileData;
        HANDLE hFind = FindFirstFileA(path.c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE) {
            cerr << "Error al acceder a la carpeta: " << carpeta << endl;
            return archivos;
        }

        do {
            string archivo = findFileData.cFileName;
            if (archivo != "." && archivo != "..") { // Ignorar "." y ".."
                archivos.push_back(archivo);
            }
        } while (FindNextFileA(hFind, &findFileData) != 0);

        FindClose(hFind);
        return archivos;
    } catch (const exception& e) {
        cerr << "Error al listar archivos en la carpeta: " << e.what() << endl;
        return {};
    }
}

void BackupManager::restaurarBackup(ArbolBTree& arbol) {
    try {
        std::string carpetaBackup = "backup"; // Carpeta donde se almacenan los backups
        std::vector<std::string> archivos = listarArchivosEnCarpeta(carpetaBackup);

        if (archivos.empty()) {
            std::cout << "No se encontraron archivos de backup en la carpeta " << carpetaBackup << ".\n";
            return;
        }

        // Mostrar los archivos disponibles
        std::cout << "Archivos disponibles para restaurar:\n";
        for (size_t i = 0; i < archivos.size(); ++i) {
            std::cout << i + 1 << ". " << archivos[i] << std::endl;
        }

        // Seleccionar archivo
        int seleccion;
        while (true) {
            std::cout << "Seleccione un archivo para restaurar (ingrese el número) o \"0\" para cancelar: ";
            std::string input = Validaciones::leerSoloNumeros();

            if (input.empty()) {
                std::cout << "Error: La entrada no puede estar vacía.\n";
                continue;
            }

            seleccion = stoi(input);

            if (seleccion == 0) {
                std::cout << "Restauración cancelada.\n";
                return;
            }

            if (seleccion >= 1 && seleccion <= archivos.size()) {
                break;
            } else {
                std::cout << "Selección invalida. Intente nuevamente.\n";
            }
        }

        std::string archivoSeleccionado = carpetaBackup + "\\" + archivos[seleccion - 1];
        std::ifstream archivo(archivoSeleccionado);
        if (!archivo.is_open()) {
            std::cout << "No se pudo abrir el archivo de backup.\n";
            return;
        }

        // Limpiar el árbol actual
        arbol = ArbolBTree(arbol.getT());

        // Leer los datos del archivo y restaurar el árbol
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string titulo, nombreAutor, isni, fechaNacAutor, isbn, fechaPublicacion;
            std::getline(ss, titulo, ';');
            std::getline(ss, nombreAutor, ';');
            std::getline(ss, isni, ';');
            std::getline(ss, fechaNacAutor, ';');
            std::getline(ss, isbn, ';');
            std::getline(ss, fechaPublicacion, ';');

            // Procesar fechas
            Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNacAutor);
            Fecha fechaPublicacionLibro = Fecha::crearDesdeCadena(fechaPublicacion);

            Persona autorPersona(nombreAutor, isni, fechaNacimientoAutor);
            Libro libro(titulo, isbn, autorPersona, fechaPublicacionLibro);
            arbol.insertar(libro);
        }

        archivo.close();
        std::cout << "Backup restaurado correctamente desde: " << archivoSeleccionado << std::endl;
    } catch (const exception& e) {
        cerr << "Error al restaurar el backup: " << e.what() << endl;
    }
}
