/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Menu principal                                           *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          01/01/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "Menu.h"
#include "BackupManager.cpp"
#include <iostream>
#include "Validaciones.cpp"
#include <conio.h> 
#include <vector>
#include <ctime>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <ctime>
#include "Validaciones.h"
#include "pdf_generator.h"
#include <windows.h>
#include "funciones.h"
#include <algorithm>
#include "ArbolBTree.h"

using namespace std;

std::wstring getExecutablePath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH); 
    std::wstring path(buffer);
    return path.substr(0, path.find_last_of(L"\\/"));
}

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void mostrarMenu(ArbolBTree& arbol) {
    vector<string> opciones = {
        "Agregar libro",
        "Buscar libro",
        "Eliminar libro",
        "Ver todos los libros",
        "Exportar en archivo PDF",
        "Crear backup",
        "Restaurar backup",
        "Buscar por rango",
        "Ordenar lista por nombre (Distribution Sort)",
        "Mostrar archivo de distribución ordenado",
        "Busqueda de autores por año", // Nueva opción
        "Busqueda binaria por título", // Nueva opción
        "Busqueda de autores por caracter", // Nueva opción
        "Salir"
    };
    int seleccion = 0;
    string ruta = "libros.txt"; // Ruta del archivo

    while (true) {
        system("cls");
        cout << "=== Menu Principal ===\n";
        for (size_t i = 0; i < opciones.size(); ++i) {
            if (i == static_cast<int>(seleccion)) {
                setConsoleColor(11); // Set color to blue
                cout << ">> " << opciones[i] << " <<\n";
                setConsoleColor(7); // Reset to default color
            } else {
                cout << "   " << opciones[i] << endl;
            }
        }

        char tecla = _getch();
        if (tecla == 72) { // Flecha Arriba
            seleccion = (seleccion - 1 + opciones.size()) % opciones.size();
        } else if (tecla == 80) { // Flecha Abajo
            seleccion = (seleccion + 1) % opciones.size();
        } else if (tecla == '\r') { // Enter
            if (opciones[seleccion] == "Agregar libro") {
                string titulo, isbn, isni;
                string fechaPub, fechaNac;
                Persona autor;

                // Solicitar titulo del libro
                do {
                    cout << "Ingrese título del libro: ";
                    getline(cin, titulo);
                    if (!Validaciones::contieneLetra(titulo)) {
                        cout << "Error: El título debe contener al menos una letra." << endl;
                    }
                } while (!Validaciones::validarTitulo(titulo, "Título") || !Validaciones::contieneLetra(titulo));

                // Solicitar ISBN
                do {
                cout << "Ingrese ISBN: ";
                isbn = Validaciones::leerIsbnIsni();
                if (!Validaciones::validarIsbn(isbn)) {
                cout << "El ISBN no es válido, por favor ingrese de nuevo.\n";
                     }
                } while (!Validaciones::validarIsbn(isbn));

                // Verificar si el ISBN ya existe
                cout << "Verificando si el ISBN ya existe...\n";
                NodoBTree* libroExistente = arbol.buscarLibroPorIsbn(isbn);
                if (libroExistente) {
                    cout << "El ISBN ya existe. Información del libro existente:\n";
                    for (const auto& libro : libroExistente->claves) {
                        if (libro.getIsbn() == isbn) {
                            libro.mostrar();
                            break;
                        }
                    }
                } else {
                    // Solicitar ISNI del autor
                    do {
                        cout << "Ingrese ISNI del autor: ";
                        isni = Validaciones::leerIsbnIsni();
                    } while (!Validaciones::validarIsni(isni));

                    // Verificar si el ISNI ya existe
                    cout << "Verificando si el ISNI ya existe...\n";
                    Persona autorExistente = arbol.buscarAutorPorIsni(isni);
                    if (autorExistente.getNombre() != "") {
                        cout << "Autor existente encontrado. Usando información del autor.\n";
                        autor = autorExistente;
                        fechaNac = autor.getFechaNacimiento().mostrar();
                    } else {
                        string nombreAutor;

                        // Solicitar nombre del autor
                        do {
                            cout << "Ingrese nombre del autor: ";
                            getline(cin, nombreAutor);
                        } while (!Validaciones::validarTituloNombre(nombreAutor, "Nombre del Autor"));

                        // Solicitar fecha de nacimiento del autor
                        do {
                            cout << "Ingrese fecha de nacimiento del autor (DD-MM-YYYY): ";
                            getline(cin, fechaNac);
                        } while (!Validaciones::validarFecha(fechaNac));

                        // Crear el autor
                        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNac);
                        autor = Persona(nombreAutor, isni, fechaNacimientoAutor);
                    }

                    // Solicitar fecha de publicación del libro
                    do {
                        cout << "Ingrese fecha de publicación del libro (DD-MM-YYYY): ";
                        getline(cin, fechaPub);
                    } while (!Validaciones::validarFechaPublicacion(fechaPub, fechaNac));

                    // Crear el libro
                    Fecha fechaPublicacion = Fecha::crearDesdeCadena(fechaPub);
                    Libro libro(titulo, isbn, autor, fechaPublicacion);

                    // Agregar libro al árbol
                    arbol.insertar(libro);
                }
            } else if (opciones[seleccion] == "Buscar libro") {
                if (!arbol.verificarArchivoLibros()) {
                    cout << "No hay libros registrados para buscar.\n";
                    cout << "Presione cualquier tecla para continuar...\n";
                    _getch();
                    continue;
                }

                string isbn;
                while (true) {
                    cout << "Ingrese el ISBN del libro a buscar: ";
                    isbn= Validaciones::leerIsbnIsni();
                    if (isbn.empty()) {
                        cout << "Error: La entrada no puede estar vacía.\n";
                        break;
                    } else {
                        break;
                    }
                }
                if (!isbn.empty()) {
                    NodoBTree* libroNodo = arbol.buscarLibroPorIsbn(isbn);
                    if (libroNodo) {
                        for (const auto& libro : libroNodo->claves) {
                            if (libro.getIsbn() == isbn) {
                                libro.mostrar();
                                break;
                            }
                        }
                    } else {
                        cout << "Libro no encontrado.\n";
                    }
                }
            } else if (opciones[seleccion] == "Eliminar libro") {
                if (!arbol.verificarArchivoLibros()) {
                    cout << "No hay libros registrados para eliminar.\n";
                    cout << "Presione cualquier tecla para continuar...\n";
                    _getch();
                    continue;
                }

                string isbn;
                while (true) {
                    cout << "Ingrese el ISBN del libro a eliminar: ";
                    isbn= Validaciones::leerIsbnIsni();
                    if (isbn.empty()) {
                        cout << "Error: La entrada no puede estar vacía.\n";
                        break;
                    } else {
                        break;
                    }
                }
                if (!isbn.empty()) {
                    // Eliminar usando ISBN
                    NodoBTree* libroAEliminar = arbol.buscarLibroPorIsbn(isbn);
                    if (libroAEliminar) {
                        arbol.eliminar(isbn);
                        eliminarDeCubeta(isbn); // Use the new function
                    } else {
                        cout << "Libro no encontrado con ISBN: " << isbn << endl;
                    }
                }
            } else if (opciones[seleccion] == "Ver todos los libros") {
                arbol.imprimirLibros();
            } else if (opciones[seleccion] == "Exportar en archivo PDF") {
                if (!arbol.verificarArchivoLibros()) {
                    cout << "No hay libros registrados para exportar.\n";
                    cout << "Presione cualquier tecla para continuar...\n";
                    _getch();
                    continue;
                }

                arbol.guardarLibrosEnArchivo(); // Asegurarse de que los datos estén actualizados en el archivo
                const std::string inputFile = "libros.txt";
                createPDF(inputFile);
                
            } else if (opciones[seleccion] == "Crear backup") {
                time_t ahora = time(0);
                tm* tiempo = localtime(&ahora);
                char buffer[80];
                strftime(buffer, sizeof(buffer), "%a %b %d %H.%M.%S %Y", tiempo);
                std::string nombreArchivo(buffer);
                arbol.crearBackup(nombreArchivo);
            } else if (opciones[seleccion] == "Restaurar backup") {
                if (!arbol.verificarArchivoLibros()) {
                    cout << "No hay archivos registrados para restaurar.\n";
                    cout << "Presione cualquier tecla para continuar...\n";
                    _getch();
                    continue;
                }

                BackupManager::restaurarBackup(arbol);  // Llama a la función para restaurar el backup
            } else if (opciones[seleccion] == "Buscar por rango") {
                const std::string inputFile12 = "libros.txt";
                int anioInicio, anioFin;

                while (true) {
                    anioFin = Validaciones::ingresarAnio("Ingrese el año de fin (desde 1900 hasta el año actual): ");
                    anioInicio = Validaciones::ingresarAnio("Ingrese el año de inicio (desde 1900 hasta el año actual): ");

                    // Validar que el año final sea mayor al inicial
                    if (anioFin > anioInicio) {
                        break;
                    } else {
                        cout << "Error: El año de fin debe ser mayor al año de inicio, y no pueden ser iguales." << endl;
                    }
                }

                cout << "Registros encontrados entre " << anioInicio << " y " << anioFin << ":\n";
                buscarPorRango(ruta, anioInicio, anioFin);
            } else if (opciones[seleccion] == "Ordenar lista por nombre (Distribution Sort)") {
                distribuirDatos("libros.txt");
                fusionarArchivos("libros_ordenados.txt");
            } else if (opciones[seleccion] == "Mostrar archivo de distribución ordenado") {
                mostrarArchivo("libros_ordenados.txt");
            } else if (opciones[seleccion] == "Busqueda de autores por año") {
                const std::string inputFile = "libros.txt";
                int anioInicio, anioFin;

                while (true) {
                    anioFin = Validaciones::ingresarAnio("Ingrese el año de fin (desde 1900 hasta el año actual): ");
                    anioInicio = Validaciones::ingresarAnio("Ingrese el año de inicio (desde 1900 hasta el año actual): ");

                    // Validar que el año final sea mayor al inicial
                    if (anioFin > anioInicio) {
                        break;
                    } else {
                        cout << "Error: El año de fin debe ser mayor al año de inicio, y no pueden ser iguales." << endl;
                    }
                }

                cout << "Autores nacidos entre " << anioInicio << " y " << anioFin << ":\n";
                buscarAutoresPorRango(inputFile, anioInicio, anioFin);
            } else if (opciones[seleccion] == "Busqueda binaria por título") {
                const std::string inputFile = "libros.txt";
                string titulo;
                // Solicitar título del libro
                do {
                    cout << "Ingrese el título del libro a buscar: ";
                    getline(cin, titulo);
                    if (!Validaciones::contieneLetra(titulo)) {
                        cout << "Error: El título debe contener al menos una letra." << endl;
                    }
                } while (!Validaciones::validarTitulo(titulo, "Título") || !Validaciones::contieneLetra(titulo));

                buscarPorTitulo(inputFile, titulo);
            } else if (opciones[seleccion] == "Busqueda de autores por caracter") {
                const std::string inputFile = "libros.txt";
                char caracter;
                cout << "Ingrese el caracter por el cual buscar autores: ";
                std::string input = Validaciones::leerSoloCaracteres();
                if (!input.empty()) {
                    caracter = toupper(input[0]); // Convertir el primer carácter a mayúscula
                    buscarAutoresPorCaracter(inputFile, caracter);
                } else {
                    cout << "Error: No se ingresó un carácter válido.\n";
                }
            } else if (opciones[seleccion] == "Salir") {
                cout << "Saliendo...\n";
                break;
            }
            cout << "Presione cualquier tecla para continuar...\n";
            _getch();
        } else if (tecla == 59) { // F1
            std::wstring base_path = getExecutablePath();
            std::wstring ayuda_path = base_path + L"\\output\\ayuda.exe";
            std::string command = "start cmd /C \"" + std::string(ayuda_path.begin(), ayuda_path.end()) + "\"";
            system(command.c_str());
        }
    }
}
