/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Menu principal                                           *
 * Autor:                          Steven Egas, Esteban Santos,Pablo Dominguez       *
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
            cout << "\033[A\33[2K\r\033[A\33[2K\rError: Debe ingresar un dato (no puede estar vacío o contener solo espacios).\n";
            continue;
        }

        // Validar si la entrada contiene espacios en medio
        if (input.find(' ') != string::npos) {
            cout << "\033[A\33[2K\r\033[A\33[2K\rError: No debe ingresar espacios, solo números enteros.\n";
            continue;
        }

        // Validar que el año sea numérico y tenga 4 dígitos
        try {
            anio = stoi(input);  // Convertimos la entrada a entero
            if (anio < 1901 || anio > 2024) {
                throw invalid_argument("Año fuera de rango.");
            }
            break;  // Salimos del bucle si el año es válido
        } catch (const invalid_argument& e) {
            cout << "\033[A\33[2K\r\033[A\33[2K\rError: Ingrese un año válido de 4 dígitos entre 1901 y 2024.\n";
        }
    }
    return anio;
}

void mostrarMenu(LibroManager& lista) {
    vector<string> opciones = {
        "Agregar libro",
        "Buscar libro",
        "Eliminar libro",
        "Ver todos los libros",
        "Exportar en archivo PDF",
        "Crear backup",
        "Restaurar backup",
        "Buscar por rango",
        "Funciones de búsqueda adicionales",
        "Generar gráfico",
        "Orden",
        "Ordenar libros", // Nueva opción para ordenar libros
        "Salir"
    };

    vector<string> submenuOpciones = {
        "Búsqueda por autocompletado Radix",
        "Búsqueda por autocompletado Radix Sin Vista Previa",
        "Búsqueda por autocompletado Radix Avanzado",
        "Búsqueda por autocompletado Radix Avanzado Sin Vista Previa",
        "Buscar libros con cierto margin de error",
        "Imprimir libros por primer carácter",
        "Buscar libro por prefijos",
        "Buscar el libro más corto y el más largo",
        "Encontrar libros cercanos a un título",
        "Varios",
        "Volver al menú principal"
    };

    vector<string> variosOpciones = {
        "Buscar libro con autocompletado",
        "Buscar libro por ISBN con autocompletado",
        "Volver al menú anterior"
    };

    vector<string> ordenOpciones = {
        "Imprimir en orden",
        "Imprimir en preorden",
        "Imprimir en posorden",
        "Volver al menú principal"
    };

    size_t seleccion = 0;
    string ruta = "libros.txt"; // Ruta del archivo
    size_t anioInicio, anioFin;

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
            if (opciones[seleccion] == "Ordenar libros") {
                lista.ordenarLibros();
            } else if (opciones[seleccion] == "Agregar libro") {
                string titulo, isbn, isni;
                string fechaPub, fechaNac;
                Persona autor;

                // Solicitar titulo del libro
                cout<<endl;
                do {
                    cout << "Ingrese título del libro: ";
                    getline(cin, titulo);
                    if (titulo.empty()) {
                        cout << "Regresando al menú principal...\n";
                        break; // Regresa al menú principal
                    }

                } while (!Validaciones::validarTitulo(titulo, "Título"));
                if (titulo.empty()) continue;
                // Solicitar ISBN
                do {
                    cout << "Ingrese ISBN: ";
                    getline(cin, isbn);
                    if (isbn.empty()) {
                        cout << "Regresando al menú principal...\n";
                        break; // Regresa al menú principal
                    }
                } while (!Validaciones::validarIsbn(isbn));
                 if (isbn.empty()) continue;
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
                        if (isni.empty()) {
                            cout << "Regresando al menú principal...\n";
                            break; // Regresa al menú principal
                        }
                    } while (!Validaciones::validarIsni(isni));
                     if (isni.empty()) continue;
                    // Verificar si el ISNI ya existe
                    Persona autorExistente = lista.buscarAutorPorIsni(isni);
                    if (autorExistente.getNombre() != "") {
                        cout << "Autor existente encontrado. Usando información del autor.\n";
                        autor = autorExistente;
                        fechaNac = autorExistente.getFechaNacimiento().toString();
                    } else {
                        string nombreAutor;

                        // Solicitar nombre del autor
                        do {
                            cout << "Ingrese nombre del autor: ";
                            getline(cin, nombreAutor);
                            if (nombreAutor.empty()) {
                                cout << "Regresando al menú principal...\n";
                                break; // Regresa al menú principal
                            }
                        } while (!Validaciones::validarTituloNombre(nombreAutor, "Nombre del Autor"));

                        if (nombreAutor.empty()) continue;
                        // Solicitar fecha de nacimiento del autor
                        do {
                            cout << "Ingrese fecha de nacimiento del autor (DD-MM-YYYY):(Desde 1900 hasta 2020) ";
                            getline(cin, fechaNac);
                            if (fechaNac.empty()) {
                                cout << "Regresando al menú principal...\n";
                                break; // Regresa al menú principal
                            }
                        } while (!Validaciones::validarFecha(fechaNac));
                         if (fechaNac.empty()) continue;
                        // Crear el autor
                        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNac);
                        autor = Persona(nombreAutor, isni, fechaNacimientoAutor);
                    }

                    // Solicitar fecha de publicación del libro
                    do {
                        cout << "Ingrese fecha de publicación del libro (DD-MM-YYYY):(Desde 1900 hasta 2025) ";
                        getline(cin, fechaPub);
                        if (fechaPub.empty()) {
                            cout << "Regresando al menú principal...\n";
                            break; // Regresa al menú principal
                        }
                    } while (!Validaciones::validarFechaPublicacion(fechaPub, fechaNac));
                    if (fechaPub.empty()) continue;
                    // Crear el libro
                    Fecha fechaPublicacion = Fecha::crearDesdeCadena(fechaPub);
                    Libro libro(titulo, isbn, autor, fechaPublicacion);

                    // Agregar libro a la lista
                    lista.agregarLibro(libro);
                }
            } else if (opciones[seleccion] == "Buscar libro") {
                string isbn;
                cout << "Ingrese el ISBN del libro a buscar: ";
                getline(cin, isbn);
                if (isbn.empty()) {
                    cout << "Regresando al menú principal...\n";
                    system("cls"); // Limpia la consola antes de regresar
                    continue;      // Regresa al menú principal
                }
                Libro* libro = lista.buscarLibroPorIsbn(isbn);
                if (libro) {
                    libro->mostrar();
                } else {
                    cout << "Libro no encontrado.\n";
                }
            } else if (opciones[seleccion] == "Eliminar libro") {
                string isbn;
                cout << "Ingrese el ISBN del libro a eliminar: ";
                getline(cin, isbn);
                if (isbn.empty()) {
                    cout << "Regresando al menú principal...\n";
                    system("cls"); // Limpia la consola antes de regresar
                    continue;      // Regresa al menú principal
                }
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
                cout<<endl;
                const std::string inputFile12 = "libros.txt";

                while (true) {
                    anioFin = ingresarAnio("Ingrese el año de fin (1901 a 2024): ");
                    
                    anioInicio = ingresarAnio("Ingrese el año de inicio (1901 a 2024): ");

                    // Validar que el año final sea mayor al inicial
                    if (anioInicio <= anioFin) {
                        break;
                    } else {
                        cout << "\033[A\33[2K\rError: El año de fin debe ser mayor al año de inicio, y no pueden ser iguales.\n";
                    }
                }

                cout << "Registros encontrados entre " << anioInicio << " y " << anioFin << ":\n";
                buscarPorRango(ruta, anioInicio, anioFin);
            } else if (opciones[seleccion] == "Funciones de búsqueda adicionales") {
                size_t subSeleccion = 0;
                while (true) {
                    system("cls");
                    cout << "=== Funciones de Búsqueda Adicionales ===\n";
                    for (size_t i = 0; i < submenuOpciones.size(); ++i) {
                        if (i == subSeleccion)
                            cout << ">> " << submenuOpciones[i] << " <<\n";
                        else
                            cout << "   " << submenuOpciones[i] << endl;
                    }

                    tecla = _getch();
                    if (tecla == 72) { // Flecha Arriba
                        subSeleccion = (subSeleccion - 1 + submenuOpciones.size()) % submenuOpciones.size();
                    } else if (tecla == 80) { // Flecha Abajo
                        subSeleccion = (subSeleccion + 1) % submenuOpciones.size();
                    } else if (tecla == '\r') { // Enter
                        if (submenuOpciones[subSeleccion] == "Varios") {
                            size_t variosSeleccion = 0;
                            while (true) {
                                system("cls");
                                cout << "=== Varios ===\n";
                                for (size_t i = 0; i < variosOpciones.size(); ++i) {
                                    if (i == variosSeleccion)
                                        cout << ">> " << variosOpciones[i] << " <<\n";
                                    else
                                        cout << "   " << variosOpciones[i] << endl;
                                }

                                tecla = _getch();
                                if (tecla == 72) { // Flecha Arriba
                                    variosSeleccion = (variosSeleccion - 1 + variosOpciones.size()) % variosOpciones.size();
                                } else if (tecla == 80) { // Flecha Abajo
                                    variosSeleccion = (variosSeleccion + 1) % variosOpciones.size();
                                } else if (tecla == '\r') { // Enter
                                    if (variosOpciones[variosSeleccion] == "Buscar libro con autocompletado") {
                                        string prefijo;
                                        cout << "Ingrese el prefijo del título del libro a buscar: ";
                                        cin >> ws; getline(cin, prefijo);
                                        vector<string> sugerencias = lista.buscarLibroConAutocompletado(prefijo);
                                    } else if (variosOpciones[variosSeleccion] == "Buscar libro por ISBN con autocompletado") {
                                        lista.busquedaPorAutocompletado();
                                        string prefijo;
                                        cout << "Ingrese el prefijo del ISBN del libro a buscar: ";
                                        cin >> ws; getline(cin, prefijo);
                                        lista.buscarLibroPorIsbnConAutocompletado(prefijo);
                                    } else if (variosOpciones[variosSeleccion] == "Volver al menú anterior") {
                                        break;
                                    }
                                    cout << "Presione cualquier tecla para continuar...\n";
                                    _getch();
                                }
                            }
                        } else if (submenuOpciones[subSeleccion] == "Búsqueda por autocompletado Radix") {
                            lista.busquedaPorAutocompletado();
                            break;
                        } else if (submenuOpciones[subSeleccion] == "Búsqueda por autocompletado Radix Sin Vista Previa") {
                            lista.busquedaPorAutocompletado1();
                            break;    
                        } else if (submenuOpciones[subSeleccion] == "Búsqueda por autocompletado Radix Avanzado") {
                            lista.busquedaCompleta();
                            break;
                        } else if (submenuOpciones[subSeleccion] == "Búsqueda por autocompletado Radix Avanzado Sin Vista Previa") {
                            lista.busquedaCompleta1();
                            break;
                        } else if (submenuOpciones[subSeleccion] == "Buscar libros con cierto margin de error") {
                            string prefijo;
                            cout << "Ingrese el prefijo del título del libro a buscar: ";
                            cin >> ws; getline(cin, prefijo);
                            vector<string> sugerencias = lista.buscarLibroConErroresTipograficos(prefijo);
                            cout << "Presione cualquier tecla para continuar...\n";
                            _getch();
                        } else if (submenuOpciones[subSeleccion] == "Imprimir libros por primer carácter") {
                            char letra;
                            do {
                                cout << "Ingrese la letra por la que desea buscar: ";
                                cin.get(letra);  // Usamos cin.get() para capturar el primer carácter ingresado
                            
                                // Limpiar el buffer de entrada en caso de que se ingrese más de un carácter
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                // Verificar si se ingresó un dato vacío
                                if (letra == '\n') {
                                    cout << "Regresando al menú principal...\n";
                                    break;
                                }

                                // Verificar que sea una letra y que no sea un espacio
                                if (!isalpha(letra) || letra == ' ' || !isupper(letra)) {
                                    cout << "\033[A\33[2K\r\033[A\33[2K\rError: Ingrese una letra válida (A-Z).\n";
                                }
                            } while (!isalpha(letra) || letra == ' ' || !isupper(letra));  // Rechaza espacios y caracteres no alfabéticos

                            lista.listarLibrosPorLetra(letra);
                            cout << "Presione cualquier tecla para continuar...\n";
                            _getch();
                        } else if (submenuOpciones[subSeleccion] == "Buscar libro por prefijos") {
                            string prefijo;
                            cout << "Ingrese el prefijo del título del libro a buscar: ";
                            cin >> ws; getline(cin, prefijo);
                            vector<string> sugerencias = lista.buscarLibroConAutocompletado(prefijo);
                            cout << "Presione cualquier tecla para continuar...\n";
                            _getch();
                        } else if (submenuOpciones[subSeleccion] == "Buscar libro por subcadena") {
                          string subcadena;
            while (true) {
                cout << "Ingrese la subcadena a buscar (sin espacios): ";
                getline(cin, subcadena);
                
                if (subcadena.empty()) {
                    cout << "Regresando al menú principal...\n";
                    break;
                }
                
                // Verificar si hay espacios
                if (subcadena.find(' ') != string::npos) {
                    cout << "\033[A\33[2K\rError: La subcadena no debe contener espacios.\n";
                    continue;
                }
                
                lista.buscarLibroPorSubcadena(subcadena);
                break;
            }
                        } else if (submenuOpciones[subSeleccion] == "Buscar el libro más corto y el más largo") {
                            lista.buscarLibroCortoLargo();
                        } else if (submenuOpciones[subSeleccion] == "Encontrar libros cercanos a un título") {
                            const std::string inputFile = "libros.txt";
                            while (true) {
                                anioFin = ingresarAnio("Ingrese el año de fin (0001 a 2024): ");
                                anioInicio = ingresarAnio("Ingrese el año de inicio (0001 a 2024): ");

                                // Validar que el año final sea mayor al inicial
                                if (anioFin > anioInicio) {
                                    break;
                                } else {
                                    cout << "\033[A\33[2K\rError: El año de fin debe ser mayor al año de inicio, y no pueden ser iguales.\n";
                                }
                            }

                            cout << "Registros encontrados entre " << anioInicio << " y " << anioFin << ":\n";
                            lista.buscarLibroCercano(ruta, anioInicio, anioFin);
                        } else if (submenuOpciones[subSeleccion] == "Búsqueda por autocompletado") {
                            lista.busquedaPorAutocompletado();
                        } else if (submenuOpciones[subSeleccion] == "Volver al menú principal") {
                            break;
                        }
                        cout << "Presione cualquier tecla para continuar...\n";
                        _getch();
                    }
                }
            } else if (opciones[seleccion] == "Generar gráfico") {
                lista.generarGraficoRadixTree("radix_tree_graph");
            } else if (opciones[seleccion] == "Orden") {
                size_t ordenSeleccion = 0;
                while (true) {
                    system("cls");
                    cout << "=== Orden ===\n";
                    for (size_t i = 0; i < ordenOpciones.size(); ++i) {
                        if (i == ordenSeleccion)
                            cout << ">> " << ordenOpciones[i] << " <<\n";
                        else
                            cout << "   " << ordenOpciones[i] << endl;
                    }

                    tecla = _getch();
                    if (tecla == 72) { // Flecha Arriba
                        ordenSeleccion = (ordenSeleccion - 1 + ordenOpciones.size()) % ordenOpciones.size();
                    } else if (tecla == 80) { // Flecha Abajo
                        ordenSeleccion = (ordenSeleccion + 1) % ordenOpciones.size();
                    } else if (tecla == '\r') { // Enter
                        if (ordenOpciones[ordenSeleccion] == "Imprimir en orden") {
                            lista.imprimirEnOrden();
                        } else if (ordenOpciones[ordenSeleccion] == "Imprimir en preorden") {
                            lista.imprimirEnPreOrden();
                        } else if (ordenOpciones[ordenSeleccion] == "Imprimir en posorden") {
                            lista.imprimirEnPosOrden();
                        } else if (ordenOpciones[ordenSeleccion] == "Volver al menú principal") {
                            break;
                        }
                        cout << "Presione cualquier tecla para continuar...\n";
                        _getch();
                    }
                }
            } else if (opciones[seleccion] == "Salir") {
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