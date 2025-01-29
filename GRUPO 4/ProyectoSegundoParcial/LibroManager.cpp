/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Util de entrada de datos                                 *
 * Autor:                          Steven Egas, Esteban Santos,Pablo Dominguez       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "LibroManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <direct.h>  // Para mkdir en Windows
#include <sys/stat.h>  // Para usar _stat
#include "BackupManager.h"  // Incluir el archivo de cabecera con la declaración de la función
#include <algorithm> 
#include <cctype>
#include <locale>
#include <conio.h> // For _getch() and _kbhit()
#include <cstdlib> // For system()
#include "Util.cpp"  // Incluir el archivo de cabecera con la declaración de la función


using namespace std;



// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// Agregar libro
void LibroManager::agregarLibro(const Libro& libro) {
    if (libro.getTitulo().empty() || libro.getIsbn().empty() || libro.getAutor().getIsni().empty()) {
        return; // Validación: No agregar si los datos están incompletos
    }
    radix.insert(libro.getTitulo(), new Libro(libro));
    cout << "Libro agregado: " << libro.getTitulo() << endl;
    if (!evitarGuardar) {
        guardarLibrosEnArchivo();
    }
}

// Limpiar la lista actual
void LibroManager::limpiarLista() {
    // Implementar si es necesario
}

// Imprimir todos los libros
void LibroManager::imprimirLibros() {
    vector<Libro*> libros = radix.collectAllBooks();
    
    if (libros.empty()) {
        cout << "No hay libros para mostrar.\n";
        return;
    }

    cout << left << setw(41) << "Título" 
        << setw(25) << "Autor" 
        << setw(25) << "ISNI" 
        << setw(20) << "ISBN"
        << setw(15) << "Publicación" 
        << setw(15) << "Nac. Autor" << endl;
    cout << string(140, '-') << endl;

    for (const Libro* libro : libros) {
        cout << left << setw(40) << libro->getTitulo()
            << setw(25) << libro->getAutor().getNombre()
            << setw(25) << libro->getAutor().getIsni() 
            << setw(20) << libro->getIsbn()
            << setw(15) << libro->getFechaPublicacion().mostrar()
            << setw(15) << libro->getAutor().getFechaNacimiento().mostrar() << endl;
    }
}

// Buscar libro por título
Libro* LibroManager::buscarLibro(const string& titulo) {
    return radix.search(titulo);
}

// Buscar libro por ISBN
Libro* LibroManager::buscarLibroPorIsbn(const string& isbn) {
    if (isbn.empty()) {
        return nullptr; // Validación: No buscar si el ISBN está vacío
    }
    vector<Libro*> libros = radix.collectAllBooks();
    for (Libro* libro : libros) {
        if (libro->getIsbn() == isbn) {
            return libro;
        }
    }
    return nullptr;
}

// Buscar autor por ISNI
Persona LibroManager::buscarAutorPorIsni(const string& isni) {
    if (isni.empty()) {
        return Persona(); // Validación: No buscar si el ISNI está vacío
    }
    vector<Libro*> libros = radix.collectAllBooks();
    for (Libro* libro : libros) {
        if (libro->getAutor().getIsni() == isni) {
            return libro->getAutor();
        }
    }
    return Persona();
}

// Eliminar libro y actualizar archivo
void LibroManager::eliminarLibro(const string& titulo) {
    if (titulo.empty()) {
        return; // Validación: No eliminar si el título está vacío
    }
    radix.remove(titulo);
    cout << "Libro eliminado: " << titulo << endl;
    guardarLibrosEnArchivo();  
}

// Guardar los libros en el archivo (actualizado)
void LibroManager::guardarLibrosEnArchivo() {
    ofstream archivo("libros_temp.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo temporal para guardar.\n\n";
        return;
    }

    radix.printAll(archivo);

    archivo.close();

    if (FILE* file = fopen("libros_temp.txt", "r")) {
        fclose(file);
    } else {
        cout << "No se pudo crear el archivo temporal correctamente.\n";
        return;
    }

    if (remove(archivoLibros.c_str()) != 0) {
        cout << "Error al eliminar el archivo de destino: " << archivoLibros << endl;
    }

    if (rename("libros_temp.txt", archivoLibros.c_str()) != 0) {
        perror("Error al renombrar el archivo temporal");
    } else {
        cout << "Libros guardados en el archivo: " << archivoLibros << endl;
    }
}

// Cargar los libros desde el archivo
void LibroManager::cargarLibrosDesdeArchivo() {
    ifstream archivo(archivoLibros);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para cargar los libros.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string titulo, nombreAutor, isni, fechaNacAutor, isbn, fechaPublicacion;
        getline(ss, titulo, ';');
        getline(ss, nombreAutor, ';');
        getline(ss, isni, ';');
        getline(ss, fechaNacAutor, ';');
        getline(ss, isbn, ';');
        getline(ss, fechaPublicacion, ';');

        if (titulo.empty() || nombreAutor.empty() || isni.empty() || fechaNacAutor.empty() || isbn.empty() || fechaPublicacion.empty()) {
            continue; // Validación: Saltar si algún dato está vacío
        }

        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNacAutor);
        Fecha fechaPublicacionLibro = Fecha::crearDesdeCadena(fechaPublicacion);

        Persona autorPersona(nombreAutor, isni, fechaNacimientoAutor);
        Libro libro(titulo, isbn, autorPersona, fechaPublicacionLibro);
        agregarLibro(libro);
    }
    archivo.close();
    cout << "Libros cargados desde el archivo.\n";
}

// Backup
void LibroManager::crearBackup(const string& nombreArchivo) {
    if (nombreArchivo.empty()) {
        return; // Validación: No crear backup si el nombre del archivo está vacío
    }
    string carpetaBackup = "backup";  
    BackupManager::crearCarpetaSiNoExiste(carpetaBackup);
    string rutaCompleta = carpetaBackup + "\\" + nombreArchivo;

    ofstream archivo(rutaCompleta);
    if (!archivo.is_open()) {
        cout << "Error al crear el archivo de backup en la ruta: " << rutaCompleta << endl;
        return;
    }

    radix.printAll(archivo);
    archivo.close();
    cout << "Backup creado correctamente en: " << rutaCompleta << endl;
}

// Restaurar backup y sobreescribir archivo
void LibroManager::restaurarBackup(const string& nombreArchivo) {
    if (nombreArchivo.empty()) {
        return; // Validación: No restaurar si el nombre del archivo está vacío
    }
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
        string titulo, nombreAutor, isni, fechaNacStr, isbn, fechaPubStr;

        getline(ss, titulo, ';');
        getline(ss, nombreAutor, ';');
        getline(ss, isni, ';');
        getline(ss, fechaNacStr, ';');
        getline(ss, isbn, ';');
        getline(ss, fechaPubStr, ';');

        if (titulo.empty() || nombreAutor.empty() || isni.empty() || fechaNacStr.empty() || isbn.empty() || fechaPubStr.empty()) {
            continue; // Validación: Saltar si algún dato está vacío
        }

        int diaNac, mesNac, anioNac;
        sscanf(fechaNacStr.c_str(), "%d/%d/%d", &diaNac, &mesNac, &anioNac);
        Fecha fechaNacimientoAutor(diaNac, mesNac, anioNac);

        int diaPub, mesPub, anioPub;
        sscanf(fechaPubStr.c_str(), "%d/%d/%d", &diaPub, &mesPub, &anioPub);
        Fecha fechaPublicacion(diaPub, mesPub, anioPub);

        Persona autor(nombreAutor, isni, fechaNacimientoAutor);
        Libro libro(titulo, isbn, autor, fechaPublicacion);
        agregarLibro(libro);
    }

    evitarGuardar = false;
    archivo.close();
    guardarLibrosEnArchivo();
    cout << "Backup restaurado: " << nombreArchivo << endl;
}

// Buscar libro por título
Libro* LibroManager::buscarLibroPorTitulo(const string& titulo) {
    if (titulo.empty()) {
        return nullptr; // Validación: No buscar si el título está vacío
    }
    vector<Libro*> libros = radix.collectAllBooks();
    for (Libro* libro : libros) {
        if (libro->getTitulo() == titulo) {
            return libro;
        }
    }
    return nullptr;
}

// Buscar libro por autor
Libro* LibroManager::buscarLibroPorAutor(const string& autor) {
    if (autor.empty()) {
        return nullptr; // Validación: No buscar si el autor está vacío
    }
    vector<Libro*> libros = radix.collectAllBooks();
    for (Libro* libro : libros) {
        if (libro->getAutor().getNombre() == autor) {
            return libro;
        }
    }
    return nullptr;
}

// Función para imprimir todos los títulos de los libros
void LibroManager::imprimirTitulosLibros() const {
    cout << "Libros disponibles:" << endl;
    for (const auto& libro : libros) {
        cout << libro.getTitulo() << endl;
    }
}

// Buscar libro con autocompletado
vector<string> LibroManager::buscarLibroConAutocompletado(const string& prefijo) {
    if (prefijo.empty()) {
        return {}; // Validación: No buscar si el prefijo está vacío
    }
    vector<string> sugerencias = radix.getSuggestions(prefijo);
    
    if (sugerencias.empty()) {
        cout << "No se encontraron sugerencias para el prefijo: " << prefijo << endl;
        return sugerencias;
    }

    cout << "Sugerencias encontradas:" << endl;
    for (size_t i = 0; i < sugerencias.size(); ++i) {
        cout << i + 1 << ". " << sugerencias[i] << endl;
    }

    size_t seleccion;
    cout << "Seleccione una sugerencia (1-" << sugerencias.size() << "): ";
    cin >> seleccion;

    if (seleccion < 1 || seleccion > sugerencias.size()) {
        cout << "Selección inválida." << endl;
        return sugerencias;
    }

    string tituloSeleccionado = sugerencias[seleccion - 1];
    trim(tituloSeleccionado);
    cout << "Sugerencia seleccionada: " << tituloSeleccionado << endl;
    Libro* libro = buscarLibroPorTitulo(tituloSeleccionado);
    if (libro) {
        cout << "Información del libro: " << endl;
        libro->mostrar();
    } else {
        cout << "Libro no encontrado.\n";
    }
    
    return sugerencias;
}

// Buscar libro con autocompletado y sugerencias basadas en errores tipográficos
vector<string> LibroManager::buscarLibroConErroresTipograficos(const string& prefijo) {
    if (prefijo.empty()) {
        return {}; // Validación: No buscar si el prefijo está vacío
    }
    vector<string> sugerencias = radix.getSuggestions(prefijo);
    
    if (sugerencias.empty()) {
        cout << "No se encontraron sugerencias exactas para el prefijo: " << prefijo << endl;
        cout << "Buscando sugerencias basadas en errores tipográficos..." << endl;
        sugerencias = radix.getTypoSuggestions(prefijo, 2);
    }

    if (sugerencias.empty()) {
        cout << "No se encontraron sugerencias para el prefijo: " << prefijo << endl;
        return sugerencias;
    }

    cout << "Sugerencias encontradas:" << endl;
    for (size_t i = 0; i < sugerencias.size(); ++i) {
        cout << i + 1 << ". " << sugerencias[i] << endl;
    }

    size_t seleccion;
    cout << "Seleccione una sugerencia (1-" << sugerencias.size() << "): ";
    cin >> seleccion;

    if (seleccion < 1 || seleccion > sugerencias.size()) {
        cout << "Selección inválida." << endl;
        return sugerencias;
    }

    string tituloSeleccionado = sugerencias[seleccion - 1];
    trim(tituloSeleccionado);
    cout << "Sugerencia seleccionada: " << tituloSeleccionado << endl;
    Libro* libro = buscarLibroPorTitulo(tituloSeleccionado);
    if (libro) {
        cout << "Información del libro: " << endl;
        libro->mostrar();
    } else {
        cout << "Libro no encontrado.\n";
    }
    
    return sugerencias;
}
//Listar libros por primer letra del título
void LibroManager::listarLibrosPorLetra(const char letra) {
    if (!isalpha(letra)) {
        return; // Validación: No listar si el carácter no es una letra
    }
    vector<Libro*> libros = radix.collectAllBooks();
    bool encontrado = false;
    for (Libro* libro : libros) {
        if (toupper(libro->getTitulo()[0]) == toupper(letra)) {
            cout << "Título: " << libro->getTitulo() << endl;
            cout << "Autor: " << libro->getAutor().getNombre() << endl;
            cout << "ISNI: " << libro->getAutor().getIsni() << endl;
            cout << "ISBN: " << libro->getIsbn() << endl;
            cout << "Fecha de publicación: " << libro->getFechaPublicacion().mostrar() << endl;
            cout << "Fecha de nacimiento del autor: " << libro->getAutor().getFechaNacimiento().mostrar() << endl;
            cout << "-----------------------------------" << endl;
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "No se encontraron libros con la letra: " << letra << endl;
    }
}
//Buscar el libro más corto y el más largo
void LibroManager::buscarLibroCortoLargo() {
    vector<Libro*> libros = radix.collectAllBooks();
    if (libros.empty()) {
        cout << "No hay libros para mostrar.\n";
        return;
    }
    Libro* libroCorto = libros[0];
    Libro* libroLargo = libros[0];
    for (Libro* libro : libros) {
        if (libro->getTitulo().length() < libroCorto->getTitulo().length()) {
            libroCorto = libro;
        }
        if (libro->getTitulo().length() > libroLargo->getTitulo().length()) {
            libroLargo = libro;
        }
    }
    cout << "Libro más corto: " << libroCorto->getTitulo() << endl;
    cout << "Libro más largo: " << libroLargo->getTitulo() << endl;
}
//Buscar libros que contengan una subcadena
void LibroManager::buscarLibroPorSubcadena(const string& subcadena) {
    if (subcadena.empty()) {
        return; // Validación: No buscar si la subcadena está vacía
    }
    vector<Libro*> libros = radix.collectAllBooks();
    bool encontrado = false;
    for (Libro* libro : libros) {
        if (libro->getTitulo().find(subcadena) != string::npos) {
            cout << "Título: " << libro->getTitulo() << endl;
            cout << "Autor: " << libro->getAutor().getNombre() << endl;
            cout << "ISNI: " << libro->getAutor().getIsni() << endl;
            cout << "ISBN: " << libro->getIsbn() << endl;
            cout << "Fecha de publicación: " << libro->getFechaPublicacion().mostrar() << endl;
            cout << "Fecha de nacimiento del autor: " << libro->getAutor().getFechaNacimiento().mostrar() << endl;
            cout << "-----------------------------------" << endl;
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "No se encontraron libros con la subcadena: " << subcadena << endl;
    }
}
//Buscar por ISBN con autocompletado
void LibroManager::buscarLibroPorIsbnConAutocompletado(const string& prefijo) {
    if (prefijo.empty()) {
        return; // Validación: No buscar si el prefijo está vacío
    }
    vector<string> sugerencias;
    vector<Libro*> libros = radix.collectAllBooks();
    for (Libro* libro : libros) {
        if (libro->getIsbn().find(prefijo) != string::npos) {
            sugerencias.push_back(libro->getIsbn());
        }
    }
    if (sugerencias.empty()) {
        cout << "No se encontraron sugerencias para el prefijo: " << prefijo << endl;
        return;
    }
    cout << "Sugerencias encontradas:" << endl;
    for (size_t i = 0; i < sugerencias.size(); ++i) {
        cout << i + 1 << ". " << sugerencias[i] << endl;
    }
    size_t seleccion;
    cout << "Seleccione una sugerencia (1-" << sugerencias.size() << "): ";
    cin >> seleccion;
    if (seleccion < 1 || seleccion > sugerencias.size()) {
        cout << "Selección inválida." << endl;
        return;
    }
    string isbnSeleccionado = sugerencias[seleccion - 1];
    trim(isbnSeleccionado);
    cout << "Sugerencia seleccionada: " << isbnSeleccionado << endl;
    Libro* libro = buscarLibroPorIsbn(isbnSeleccionado);
    if (libro) {
        cout << "Información del libro: " << endl;
        libro->mostrar();
    } else {
        cout << "Libro no encontrado.\n";
    }
}

// Función para encontrar libros cercanos a un título
void LibroManager::buscarLibroCercano(const string& ruta, const int anioInicio, const int anioFin) {
    if (anioInicio > anioFin) {
        return; // Validación: No buscar si el rango de años es inválido
    }
    vector<Libro*> libros = radix.collectAllBooks();
    vector<Libro*> librosCercanos;
    for (Libro* libro : libros) {
        if (libro->getFechaPublicacion().getAnio() >= anioInicio && libro->getFechaPublicacion().getAnio() <= anioFin) {
            librosCercanos.push_back(libro);
        }
    }
    if (librosCercanos.empty()) {
        cout << "No se encontraron libros en el rango de años especificado.\n";
        return;
    }
    ofstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar los libros cercanos.\n";
        return;
    }
    for (Libro* libro : librosCercanos) {
        archivo << "Título: " << libro->getTitulo() << endl;
        archivo << "Autor: " << libro->getAutor().getNombre() << endl;
        archivo << "ISNI: " << libro->getAutor().getIsni() << endl;
        archivo << "ISBN: " << libro->getIsbn() << endl;
        archivo << "Fecha de publicación: " << libro->getFechaPublicacion().mostrar() << endl;
        archivo << "Fecha de nacimiento del autor: " << libro->getAutor().getFechaNacimiento().mostrar() << endl;
        archivo << "-----------------------------------" << endl;
    }
    archivo.close();
    cout << "Libros guardados en el archivo: " << ruta << endl;
}

void LibroManager::busquedaPorAutocompletado() {
    cout << "Seleccione el tipo de búsqueda:\n";
    cout << "1. Autor\n";
    cout << "2. ISBN\n";
    cout << "3. Nombre\n";
    cout << "Ingrese su opción: ";
    int opcion;
    opcion=Util::validarNumero(1,3);

    if (opcion < 1 || opcion > 3) {
        cout << "Opción inválida.\n";
        return;
    }

    string input;
    vector<string> sugerencias;
    char tecla;
    size_t seleccion = 0;
    bool actualizarPantalla = true;

    while (true) {
        if (actualizarPantalla) {
            system("cls"); // Limpiar la pantalla
            cout << "Ingrese el texto de búsqueda: " << input << endl;

            // Obtener sugerencias basadas en el input
            switch (opcion) {
                case 1:
                    sugerencias = radix.getSuggestionsByAuthor(input);
                    break;
                case 2:
                    sugerencias = radix.getSuggestionsByIsbn(input);
                    break;
                case 3:
                    sugerencias = radix.getSuggestions(input);
                    break;
                default:
                    cout << "Opción inválida.\n";
                    return;
            }

            // Mostrar sugerencias
            for (size_t i = 0; i < sugerencias.size(); ++i) {
                if (i == seleccion) {
                    cout << "> " << sugerencias[i] << endl;
                } else {
                    cout << "  " << sugerencias[i] << endl;
                }
            }
            actualizarPantalla = false;
        }

        // Leer una tecla sin bloquear
        if (_kbhit()) {
            tecla = _getch();

            // Si la tecla es Enter, salir del bucle
            if (tecla == 13) {
                break;
            }

            // Si la tecla es Backspace, eliminar el último carácter del input
            if (tecla == 8 && !input.empty()) {
                input.pop_back();
                actualizarPantalla = true;
            } else if (tecla >= 32 && tecla <= 126) { // Caracteres imprimibles
                input += tecla;
                actualizarPantalla = true;
            } else if (tecla == -32) { // Detectar teclas de flecha
                tecla = _getch();
                if (tecla == 72 && seleccion > 0) { // Flecha arriba
                    seleccion--;
                    actualizarPantalla = true;
                } else if (tecla == 80 && seleccion < sugerencias.size() - 1) { // Flecha abajo
                    seleccion++;
                    actualizarPantalla = true;
                }
            }
        }
    }

    // Obtener el libro correspondiente a la sugerencia seleccionada
    if (!sugerencias.empty()) {
        string seleccionada = sugerencias[seleccion];
        trim(seleccionada); // Eliminar espacios en blanco

        Libro* libro = nullptr;
        switch (opcion) {
            case 1:
                libro = buscarLibroPorAutor(seleccionada);
                break;
            case 2:
                libro = buscarLibroPorIsbn(seleccionada);
                break;
            case 3:
                libro = buscarLibroPorTitulo(seleccionada);
                break;
        }

        if (libro) {
            cout << "Información del libro: " << endl;
            libro->mostrar();
        } else {
            cout << "Libro no encontrado.\n";
        }
    } else {
        cout << "No se encontraron sugerencias para el texto ingresado.\n";
    }
}

void LibroManager::busquedaCompleta1() {
    cout << "Seleccione el tipo de búsqueda:\n";
    cout << "1. Autor\n";
    cout << "2. ISBN\n";
    cout << "3. Nombre\n";
    cout << "Ingrese su opción: ";
    int opcion;
    opcion = Util::validarNumero(1, 3);

    if (opcion < 1 || opcion > 3) {
        cout << "Opción inválida.\n";
        return;
    }

    string prefijo;
    vector<string> sugerencias;
    char tecla;
    size_t seleccion = 0;
    bool actualizarPantalla = true;

    while (true) {
        if (actualizarPantalla) {
            system("cls"); // Limpiar la pantalla
            cout << "Ingrese el prefijo de búsqueda: " << prefijo << endl;

            // Obtener sugerencias basadas en el prefijo solo si hay texto
            if (!prefijo.empty()) {
                switch (opcion) {
                    case 1:
                        sugerencias = radix.getSuggestionsByCharacter(prefijo);
                        break;
                    case 2:
                        sugerencias = radix.getSuggestionsByCharacter(prefijo);
                        break;
                    case 3:
                        sugerencias = radix.getSuggestionsByCharacter(prefijo);
                        break;
                    default:
                        cout << "Opción inválida.\n";
                        return;
                }

                // Mostrar sugerencias
                if (sugerencias.empty()) {
                    cout << "No se encontraron sugerencias para el prefijo: " << prefijo << endl;
                } else {
                    for (size_t i = 0; i < sugerencias.size(); ++i) {
                        if (i == seleccion) {
                            cout << "> " << sugerencias[i] << endl;
                        } else {
                            cout << "  " << sugerencias[i] << endl;
                        }
                    }
                }
            }
            actualizarPantalla = false;
        }

        // Leer una tecla sin bloquear
        if (_kbhit()) {
            tecla = _getch();

            // Si la tecla es Enter, salir del bucle
            if (tecla == 13) {
                break;
            }

            // Si la tecla es Backspace, eliminar el último carácter del prefijo
            if (tecla == 8 && !prefijo.empty()) {
                prefijo.pop_back();
                actualizarPantalla = true;
            } else if (tecla == -32) { // Detectar teclas de flecha
                tecla = _getch();
                if (tecla == 72 && seleccion > 0) { // Flecha arriba
                    seleccion--;
                    actualizarPantalla = true;
                } else if (tecla == 80 && seleccion < sugerencias.size() - 1) { // Flecha abajo
                    seleccion++;
                    actualizarPantalla = true;
                }
            } else if (isalnum(tecla)) {
                // Agregar el carácter al prefijo si es alfanumérico
                prefijo += tecla;
                seleccion = 0; // Reiniciar la selección
                actualizarPantalla = true;
            }
        }
    }

    // Obtener el libro correspondiente a la sugerencia seleccionada
    if (!sugerencias.empty()) {
        string seleccionada = sugerencias[seleccion];
        trim(seleccionada); // Eliminar espacios en blanco

        Libro* libro = nullptr;
        switch (opcion) {
            case 1:
                libro = buscarLibroPorAutor(seleccionada);
                break;
            case 2:
                libro = buscarLibroPorIsbn(seleccionada);
                break;
            case 3:
                libro = buscarLibroPorTitulo(seleccionada);
                break;
        }

        if (libro) {
            cout << "Información del libro: " << endl;
            libro->mostrar();
        } else {
            cout << "Libro no encontrado.\n";
        }
    } else {
        cout << "No se encontraron sugerencias para el prefijo ingresado.\n";
    }
}

void LibroManager::generarGraficoRadixTree(const string& outputFile) {
    string dotFile = "graph.dot";
    string jpgFile = outputFile + ".jpg";

    // Generate the DOT file
    radix.generateGraph(dotFile);
    cout << "Archivo DOT generado en: " << dotFile << endl;

    // Specify the full path to the Graphviz dot executable
    string dotPath = "C:\\Program Files\\Graphviz\\bin\\dot.exe"; // Adjust the path as necessary

    // Convert the DOT file to a JPG image
    string command = "\"" + dotPath + "\" -Tjpg " + dotFile + " -o " + jpgFile;
    system(command.c_str());
    cout << "Gráfico del Radix Tree generado en: " << jpgFile << endl;

    // Open the generated JPG image
    command = "start " + jpgFile;
    system(command.c_str());
}

void LibroManager::imprimirEnOrden() {
    cout << "Libros en orden:\n";
    radix.printInOrder();
}

void LibroManager::imprimirEnPreOrden() {
    cout << "Libros en preorden:\n";
    radix.printPreOrder();
}

void LibroManager::imprimirEnPosOrden() {
    cout << "Libros en posorden:\n";
    radix.printPostOrder();
}

void LibroManager::busquedaPorAutocompletado1() {
    cout << "Seleccione el tipo de búsqueda:\n";
    cout << "1. Autor\n";
    cout << "2. ISBN\n";
    cout << "3. Nombre\n";
    cout << "Ingrese su opción: ";
    int opcion;
    opcion = Util::validarNumero(1, 3);

    if (opcion < 1 || opcion > 3) {
        cout << "Opción inválida.\n";
        return;
    }

    string input;
    vector<string> sugerencias;
    char tecla;
    size_t seleccion = 0;
    bool actualizarPantalla = true;

    while (true) {
        if (actualizarPantalla) {
            system("cls"); // Limpiar la pantalla
            cout << "Ingrese el texto de búsqueda: " << input << endl;

            // Obtener sugerencias basadas en el input solo si hay texto
            if (!input.empty()) {
                switch (opcion) {
                    case 1:
                        sugerencias = radix.getSuggestionsByAuthor(input);
                        break;
                    case 2:
                        sugerencias = radix.getSuggestionsByIsbn(input);
                        break;
                    case 3:
                        sugerencias = radix.getSuggestions(input);
                        break;
                    default:
                        cout << "Opción inválida.\n";
                        return;
                }

                // Mostrar sugerencias
                for (size_t i = 0; i < sugerencias.size(); ++i) {
                    if (i == seleccion) {
                        cout << "> " << sugerencias[i] << endl;
                    } else {
                        cout << "  " << sugerencias[i] << endl;
                    }
                }
            }
            actualizarPantalla = false;
        }

        // Leer una tecla sin bloquear
        if (_kbhit()) {
            tecla = _getch();

            // Si la tecla es Enter, salir del bucle
            if (tecla == 13) {
                break;
            }

            // Si la tecla es Backspace, eliminar el último carácter del input
            if (tecla == 8 && !input.empty()) {
                input.pop_back();
                actualizarPantalla = true;
            } else if (tecla >= 32 && tecla <= 126) { // Caracteres imprimibles
                input += tecla;
                actualizarPantalla = true;
            } else if (tecla == -32) { // Detectar teclas de flecha
                tecla = _getch();
                if (tecla == 72 && seleccion > 0) { // Flecha arriba
                    seleccion--;
                    actualizarPantalla = true;
                } else if (tecla == 80 && seleccion < sugerencias.size() - 1) { // Flecha abajo
                    seleccion++;
                    actualizarPantalla = true;
                }
            }
        }
    }

    // Obtener el libro correspondiente a la sugerencia seleccionada
    if (!sugerencias.empty()) {
        string seleccionada = sugerencias[seleccion];
        trim(seleccionada); // Eliminar espacios en blanco

        Libro* libro = nullptr;
        switch (opcion) {
            case 1:
                libro = buscarLibroPorAutor(seleccionada);
                break;
            case 2:
                libro = buscarLibroPorIsbn(seleccionada);
                break;
            case 3:
                libro = buscarLibroPorTitulo(seleccionada);
                break;
        }

        if (libro) {
            cout << "Información del libro: " << endl;
            libro->mostrar();
        } else {
            cout << "Libro no encontrado.\n";
        }
    } else {
        cout << "No se encontraron sugerencias para el texto ingresado.\n";
    }
}

void LibroManager::busquedaCompleta() {
    cout << "Seleccione el tipo de búsqueda:\n";
    cout << "1. Autor\n";
    cout << "2. ISBN\n";
    cout << "3. Nombre\n";
    cout << "Ingrese su opción: ";
    int opcion;
    opcion = Util::validarNumero(1, 3);

    if (opcion < 1 || opcion > 3) {
        cout << "Opción inválida.\n";
        return;
    }

    string prefijo;
    vector<string> sugerencias;
    char tecla;
    size_t seleccion = 0;
    bool actualizarPantalla = true;

    while (true) {
        if (actualizarPantalla) {
            system("cls"); // Limpiar la pantalla
            cout << "Ingrese el prefijo de búsqueda: " << prefijo << endl;

            // Obtener sugerencias basadas en el prefijo
            switch (opcion) {
                case 1:
                    sugerencias = radix.getSuggestionsByCharacter(prefijo);
                    break;
                case 2:
                    sugerencias = radix.getSuggestionsByCharacter(prefijo);
                    break;
                case 3:
                    sugerencias = radix.getSuggestionsByCharacter(prefijo);
                    break;
                default:
                    cout << "Opción inválida.\n";
                    return;
            }

            // Mostrar sugerencias
            if (sugerencias.empty()) {
                cout << "No se encontraron sugerencias para el prefijo: " << prefijo << endl;
            } else {
                for (size_t i = 0; i < sugerencias.size(); ++i) {
                    if (i == seleccion) {
                        cout << "> " << sugerencias[i] << endl;
                    } else {
                        cout << "  " << sugerencias[i] << endl;
                    }
                }
            }
            actualizarPantalla = false;
        }

        // Leer una tecla sin bloquear
        if (_kbhit()) {
            tecla = _getch();

            // Si la tecla es Enter, salir del bucle
            if (tecla == 13) {
                break;
            }

            // Si la tecla es Backspace, eliminar el último carácter del prefijo
            if (tecla == 8 && !prefijo.empty()) {
                prefijo.pop_back();
                actualizarPantalla = true;
            } else if (tecla == -32) { // Detectar teclas de flecha
                tecla = _getch();
                if (tecla == 72 && seleccion > 0) { // Flecha arriba
                    seleccion--;
                    actualizarPantalla = true;
                } else if (tecla == 80 && seleccion < sugerencias.size() - 1) { // Flecha abajo
                    seleccion++;
                    actualizarPantalla = true;
                }
            } else if (isalnum(tecla)) {
                // Agregar el carácter al prefijo si es alfanumérico
                prefijo += tecla;
                seleccion = 0; // Reiniciar la selección
                actualizarPantalla = true;
            }
        }
    }

    // Obtener el libro correspondiente a la sugerencia seleccionada
    if (!sugerencias.empty()) {
        string seleccionada = sugerencias[seleccion];
        trim(seleccionada); // Eliminar espacios en blanco

        Libro* libro = nullptr;
        switch (opcion) {
            case 1:
                libro = buscarLibroPorAutor(seleccionada);
                break;
            case 2:
                libro = buscarLibroPorIsbn(seleccionada);
                break;
            case 3:
                libro = buscarLibroPorTitulo(seleccionada);
                break;
        }

        if (libro) {
            cout << "Información del libro: " << endl;
            libro->mostrar();
        } else {
            cout << "Libro no encontrado.\n";
        }
    } else {
        cout << "No se encontraron sugerencias para el prefijo ingresado.\n";
    }
}

void LibroManager::ordenarLibros() {
    cout << "Seleccione el criterio de ordenación:\n";
    cout << "1. ISBN\n";
    cout << "2. Título\n";
    cout << "3. Nombre del autor\n";
    cout << "4. Fecha de publicación\n";
    cout << "Ingrese su opción: ";
    int opcion;
    opcion = Util::validarNumero(1, 4);

    vector<Libro*> libros = radix.collectAllBooks();

    switch (opcion) {
        case 1:
            sort(libros.begin(), libros.end(), [](Libro* a, Libro* b) {
                return a->getIsbn() < b->getIsbn();
            });
            break;
        case 2:
            sort(libros.begin(), libros.end(), [](Libro* a, Libro* b) {
                return a->getTitulo() < b->getTitulo();
            });
            break;
        case 3:
            sort(libros.begin(), libros.end(), [](Libro* a, Libro* b) {
                return a->getAutor().getNombre() < b->getAutor().getNombre();
            });
            break;
        case 4:
            sort(libros.begin(), libros.end(), [](Libro* a, Libro* b) {
                return a->getFechaPublicacion().getAnio() < b->getFechaPublicacion().getAnio();
            });
            break;
        default:
            cout << "Opción inválida.\n";
            return;
    }

    cout << left << setw(41) << "Título" 
        << setw(25) << "Autor" 
        << setw(25) << "ISNI" 
        << setw(20) << "ISBN"
        << setw(15) << "Publicación" 
        << setw(15) << "Nac. Autor" << endl;
    cout << string(140, '-') << endl;

    for (const Libro* libro : libros) {
        cout << left << setw(40) << libro->getTitulo()
            << setw(25) << libro->getAutor().getNombre()
            << setw(25) << libro->getAutor().getIsni() 
            << setw(20) << libro->getIsbn()
            << setw(15) << libro->getFechaPublicacion().mostrar()
            << setw(15) << libro->getAutor().getFechaNacimiento().mostrar() << endl;
    }
}




