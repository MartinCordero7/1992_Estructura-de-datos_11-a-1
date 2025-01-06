/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Menu principal                                           *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "Menu.h"
#include "BackupManager.cpp"
#include <iostream>
#include "Validaciones.cpp" 
#include <conio.h> 
#include <vector>
#include <sstream>
#include <ctime>
#include "pdf_generator.h"
#include <windows.h>
#include "funciones.h"
#include <algorithm>

using namespace std;

std::wstring getExecutablePath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH); 
    std::wstring path(buffer);
    return path.substr(0, path.find_last_of(L"\\/"));
}

int ingresarAnio(const string& mensaje) {
    int anio;
    string input;
    while (true) {
        cout << mensaje;
        getline(cin, input);  // Usamos getline para permitir validación de la entrada completa

        // Eliminar espacios al inicio y al final de la entrada
        input.erase(0, input.find_first_not_of(' '));
        input.erase(input.find_last_not_of(' ') + 1);

        // Validar si la entrada está vacía
        if (input.empty()) {
            cout << "Error: Debe ingresar un dato (no puede estar vacío o contener solo espacios)." << endl;
            continue;
        }

        // Validar si la entrada contiene espacios en medio
        if (input.find(' ') != string::npos) {
            cout << "Error: No debe ingresar espacios, solo números enteros." << endl;
            continue;
        }

        // Validar que el año sea numérico y tenga 4 dígitos
        try {
            anio = stoi(input);  // Convertimos la entrada a entero
            if (anio < 1 || anio > 2024) {
                throw invalid_argument("Año fuera de rango.");
            }
            break;  // Salimos del bucle si el año es válido
        } catch (const invalid_argument& e) {
            cout << "Error: Ingrese un año válido de 4 dígitos entre 0001 y 2024." << endl;
        }
    }
    return anio;
}

void mostrarMenu(LibroManager& lista) {
    vector<string> opciones = {
        "Agregar libro",
        "Buscar libro",
        "Buscar libro con autocompletado",
        "Buscar libro con errores tipograficos",
        "Función para listar libros por primer letra del título",
        "Buscar libro por subcadena",
        "Buscar el libro más corto y el más largo",
        "Buscar libro por ISBN con autocompletado",
        "Encontrar libros cercanos a un título",
        "Eliminar libro",
        "Ver todos los libros",
        "Exportar en archivo PDF",
        "Crear backup",
        "Restaurar backup",
        "Buscar por rango",
        "Salir"
    };
    int seleccion = 0;
    string ruta = "libros.txt"; // Ruta del archivo
    int anioInicio, anioFin;

    while (true) {
        system("cls");
        cout << "=== Menu Principal ===\n";
        for (size_t i = 0; i < opciones.size(); ++i) {
            if (i == seleccion)
                cout << ">> " << opciones[i] << " <<\n";
            else
                cout << "   " << opciones[i] << endl;
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
                } while (!Validaciones::validarTitulo(titulo, "Título"));

                // Solicitar ISBN
                do {
                    cout << "Ingrese ISBN: ";
                    getline(cin, isbn);
                } while (!Validaciones::validarIsbn(isbn));

                // Verificar si el ISBN ya existe
                Libro* libroExistente = lista.buscarLibroPorIsbn(isbn);
                if (libroExistente) {
                    cout << "El ISBN ya existe. Información del libro existente:\n";
                    libroExistente->mostrar();
                } else {
                    // Solicitar ISNI del autor
                    do {
                        cout << "Ingrese ISNI del autor: ";
                        getline(cin, isni);
                    } while (!Validaciones::validarIsni(isni));

                    // Verificar si el ISNI ya existe
                    Persona autorExistente = lista.buscarAutorPorIsni(isni);
                    if (autorExistente.getNombre() != "") {
                        cout << "Autor existente encontrado. Usando información del autor.\n";
                        autor = autorExistente;
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

                    // Agregar libro a la lista
                    lista.agregarLibro(libro);
                }
            } else if (opciones[seleccion] == "Buscar libro") {
                string isbn;
                cout << "Ingrese el ISBN del libro a buscar: ";
                cin >> ws; getline(cin, isbn);
                Libro* libro = lista.buscarLibroPorIsbn(isbn);
                if (libro) {
                    libro->mostrar();
                } else {
                    cout << "Libro no encontrado.\n";
                }
            } else if (opciones[seleccion] == "Eliminar libro") {
                string isbn;
                cout << "Ingrese el ISBN del libro a eliminar: ";
                cin >> ws; getline(cin, isbn);
                // Eliminar usando ISBN
                Libro* libroAEliminar = lista.buscarLibroPorIsbn(isbn);
                if (libroAEliminar) {
                    string titulo = libroAEliminar->getTitulo();
                    lista.eliminarLibro(titulo);
                } else {
                    cout << "Libro no encontrado con ISBN: " << isbn << endl;
                }
            } else if (opciones[seleccion] == "Ver todos los libros") {
                lista.imprimirLibros();
            } else if (opciones[seleccion] == "Exportar en archivo PDF") {
                const std::string inputFile = "libros.txt";
                createPDF(inputFile);
            } else if (opciones[seleccion] == "Crear backup") {
                time_t ahora = time(0);
                tm* tiempo = localtime(&ahora);
                stringstream ss;
                ss << (1900 + tiempo->tm_year) << "_" << (1 + tiempo->tm_mon) << "_" << tiempo->tm_mday << "_"
                << tiempo->tm_hour << "_" << tiempo->tm_min << "_" << tiempo->tm_sec << ".txt";
                lista.crearBackup(ss.str());
            } else if (opciones[seleccion] == "Restaurar backup") {
                BackupManager::restaurarBackup(lista);  // Llama a la función para restaurar el backup
            } else if (opciones[seleccion] == "Buscar por rango") {
                const std::string inputFile12 = "libros.txt";

                while (true) {
                    anioFin = ingresarAnio("Ingrese el año de fin (0001 a 2024): ");
                    anioInicio = ingresarAnio("Ingrese el año de inicio (0001 a 2024): ");

                    // Validar que el año final sea mayor al inicial
                    if (anioFin > anioInicio) {
                        break;
                    } else {
                        cout << "Error: El año de fin debe ser mayor al año de inicio, y no pueden ser iguales." << endl;
                    }
                }

                cout << "Registros encontrados entre " << anioInicio << " y " << anioFin << ":\n";
                buscarPorRango(ruta, anioInicio, anioFin);
            } else if (opciones[seleccion] == "Buscar libro con autocompletado") {
                string prefijo;
                cout << "Ingrese el prefijo del título del libro a buscar: ";
                cin >> ws; getline(cin, prefijo);
                vector<string> sugerencias = lista.buscarLibroConAutocompletado(prefijo);
            } else if (opciones[seleccion] == "Buscar libro con errores tipograficos") {
                string prefijo;
                cout << "Ingrese el prefijo del título del libro a buscar: ";
                cin >> ws; getline(cin, prefijo);
                vector<string> sugerencias = lista.buscarLibroConErroresTipograficos(prefijo);
            } else if (opciones[seleccion] == "Función para listar libros por primer letra del título") {
                char letra;
                do {
                    cout << "Ingrese la letra por la que desea buscar: ";
                    cin.get(letra);  // Usamos cin.get() para capturar el primer carácter ingresado
                
                    // Limpiar el buffer de entrada en caso de que se ingrese más de un carácter
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    // Verificar que sea una letra y que no sea un espacio
                } while (!isalpha(letra) || letra == ' '|| cin.gcount() != 1 || !isupper(letra));  // Rechaza espacios y caracteres no alfabéticos

                lista.listarLibrosPorLetra(letra);
            }else if (opciones[seleccion] == "Buscar el libro más corto y el más largo") {
                lista.buscarLibroCortoLargo();
            }else if (opciones[seleccion] == "Buscar libro por subcadena") {
                string subcadena;
                bool esValida = false;
                
                do {
                    cout << "Ingrese la subcadena a buscar (sin espacios, caracteres especiales ni números): ";
                    cin >> ws; getline(cin, subcadena);
                    
                    esValida = true;
                    
                    // Validación de subcadena
                    for (int i = 0; i < subcadena.length(); i++) {
                        if (!isalpha(subcadena[i])) { // Si no es una letra
                            esValida = false;
                            break;
                        }
                    }
                    
                    if (!esValida) {
                        cout << "La subcadena contiene caracteres inválidos. Intente de nuevo." << endl;
                    }
                    
                } while (!esValida);  // Repetir mientras no sea válida


                lista.buscarLibroPorSubcadena(subcadena);
            }  
            else if (opciones[seleccion] == "Buscar libro por ISBN con autocompletado") {
                string prefijo;
                cout << "Ingrese el prefijo del ISBN del libro a buscar: ";
                cin >> ws; getline(cin, prefijo);
                lista.buscarLibroPorIsbnConAutocompletado(prefijo);
            
                 
            }  else if (opciones[seleccion] == "Encontrar libros cercanos a un título") {
                const std::string inputFile = "libros.txt";
                while (true) {
                    anioFin = ingresarAnio("Ingrese el año de fin (0001 a 2024): ");
                    anioInicio = ingresarAnio("Ingrese el año de inicio (0001 a 2024): ");

                    // Validar que el año final sea mayor al inicial
                    if (anioFin > anioInicio) {
                        break;
                    } else {
                        cout << "Error: El año de fin debe ser mayor al año de inicio, y no pueden ser iguales." << endl;
                    }
                }

                cout << "Registros encontrados entre " << anioInicio << " y " << anioFin << ":\n";
                lista.buscarLibroCercano(ruta, anioInicio, anioFin);
            } else if (opciones[seleccion] == "Salir") {
                break;
            }
            else if (opciones[seleccion] == "Salir") {
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