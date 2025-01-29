/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Realizar una Lista circular doble                        *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
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
#include <map>

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
    trie.insert(libro.getTitulo(), new Libro(libro));
    cout << "Libro agregado: " << libro.getTitulo() << endl;
    // Guardar solo si no se está restaurando un backup
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
    vector<Libro*> libros = trie.collectAllBooks();
    
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
    return trie.search(titulo);
}

// Buscar libro por ISBN
Libro* LibroManager::buscarLibroPorIsbn(const string& isbn) {
    vector<Libro*> libros = trie.collectAllBooks();
    for (Libro* libro : libros) {
        if (libro->getIsbn() == isbn) {
            return libro;
        }
    }
    return nullptr;
}

// Buscar autor por ISNI
Persona LibroManager::buscarAutorPorIsni(const string& isni) {
    vector<Libro*> libros = trie.collectAllBooks();
    for (Libro* libro : libros) {
        if (libro->getAutor().getIsni() == isni) {
            return libro->getAutor();
        }
    }
    return Persona();
}

// Eliminar libro y actualizar archivo
void LibroManager::eliminarLibro(const string& titulo) {
    trie.remove(titulo);
    cout << "Libro eliminado: " << titulo << endl;
    // Actualizar el archivo después de la eliminación
    guardarLibrosEnArchivo();  
}

// Guardar los libros en el archivo (actualizado)
void LibroManager::guardarLibrosEnArchivo() {
    ofstream archivo("libros_temp.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo temporal para guardar.\n\n";
        return;
    }

    trie.printAll(archivo);

    archivo.close();

    // Verificar si el archivo temporal se creó correctamente
    if (FILE* file = fopen("libros_temp.txt", "r")) {
        fclose(file);
    } else {
        cout << "No se pudo crear el archivo temporal correctamente.\n";
        return;
    }

    // Eliminar el archivo de destino si ya existe
    if (remove(archivoLibros.c_str()) != 0) {
        // Si el archivo no se puede eliminar, mostrar error
        cout << "Error al eliminar el archivo de destino: " << archivoLibros << endl;
    }

    // Renombrar el archivo temporal a la ubicación final
    if (rename("libros_temp.txt", archivoLibros.c_str()) != 0) {
        // Mostrar error si renombrar falla
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

        // Procesar fechas
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

    trie.printAll(archivo);

    // Cerrar el archivo después de escribir los datos
    archivo.close();
    cout << "Backup creado correctamente en: " << rutaCompleta << endl;
}

// Restaurar backup y sobreescribir archivo
void LibroManager::restaurarBackup(const string& nombreArchivo) {
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
        string titulo, nombreAutor, isni, fechaNacStr, isbn, fechaPubStr;

        // Leer datos del archivo
        getline(ss, titulo, ';');
        getline(ss, nombreAutor, ';');
        getline(ss, isni, ';');
        getline(ss, fechaNacStr, ';');
        getline(ss, isbn, ';');
        getline(ss, fechaPubStr, ';');

        // Parsear la fecha de nacimiento del autor
        int diaNac, mesNac, anioNac;
        sscanf(fechaNacStr.c_str(), "%d/%d/%d", &diaNac, &mesNac, &anioNac);
        Fecha fechaNacimientoAutor(diaNac, mesNac, anioNac);

        // Parsear la fecha de publicación
        int diaPub, mesPub, anioPub;
        sscanf(fechaPubStr.c_str(), "%d/%d/%d", &diaPub, &mesPub, &anioPub);
        Fecha fechaPublicacion(diaPub, mesPub, anioPub);

        // Crear los objetos correspondientes
        Persona autor(nombreAutor, isni, fechaNacimientoAutor);
        Libro libro(titulo, isbn, autor, fechaPublicacion);

        // Agregar libro a la lista
        agregarLibro(libro);
    }

    evitarGuardar = false; // Volver a guardar normalmente
    archivo.close();

    guardarLibrosEnArchivo();
    cout << "Backup restaurado: " << nombreArchivo << endl;
}

// Buscar libro por título
Libro* LibroManager::buscarLibroPorTitulo(const string& titulo) {
    vector<Libro*> libros = trie.collectAllBooks();
    for (Libro* libro : libros) {
        if (libro->getTitulo() == titulo) {
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
    vector<string> sugerencias = trie.getSuggestions(prefijo);
    
    if (sugerencias.empty()) {
        cout << "No se encontraron sugerencias para el prefijo: " << prefijo << endl;
        return sugerencias;
    }

    // Mostrar todas las sugerencias
    cout << "Sugerencias encontradas:" << endl;
    for (size_t i = 0; i < sugerencias.size(); ++i) {
        cout << i + 1 << ". " << sugerencias[i] << endl;
    }

    // Permitir al usuario seleccionar una sugerencia
    int seleccion;
    cout << "Seleccione una sugerencia (1-" << sugerencias.size() << "): ";
    cin >> seleccion;

    // Validar la selección del usuario
    if (seleccion < 1 || seleccion > sugerencias.size()) {
        cout << "Selección inválida." << endl;
        return sugerencias;
    }

    // Obtener el libro correspondiente a la sugerencia seleccionada
    string tituloSeleccionado = sugerencias[seleccion - 1];
    trim(tituloSeleccionado); // Eliminar espacios en blanco
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
    vector<string> sugerencias = trie.getTypoSuggestions(prefijo, 2);
    map<string, vector<Libro*>> librosPorAutor;
    vector<Libro*> todosLosLibros = trie.collectAllBooks();
    
    // Group books by author
    for (Libro* libro : todosLosLibros) {
        string nombreAutor = libro->getAutor().getNombre();
        librosPorAutor[nombreAutor].push_back(libro);
    }
    
    if (sugerencias.empty()) {
        cout << "No se encontraron autores similares a: " << prefijo << endl;
        return sugerencias;
    }

    cout << "Autores encontrados:" << endl;
    for (size_t i = 0; i < sugerencias.size(); ++i) {
        cout << i + 1 << ". " << sugerencias[i] << endl;
    }

    while (true) {
        cout << "Seleccione un autor (1-" << sugerencias.size() << ") o 0 para cancelar: ";
        int seleccion;
        cin >> seleccion;
        cin.ignore();

        if (seleccion == 0) {
            cout << "Búsqueda cancelada." << endl;
            break;
        }

        if (seleccion < 1 || seleccion > sugerencias.size()) {
            cout << "Selección inválida. Intente nuevamente." << endl;
            continue;
        }

        string autorSeleccionado = sugerencias[seleccion - 1];
        cout << "\nLibros del autor " << autorSeleccionado << ":" << endl;
        
        for (Libro* libro : librosPorAutor[autorSeleccionado]) {
            cout << "Título: " << libro->getTitulo() << endl;
            cout << "Autor: " << libro->getAutor().getNombre() << endl;
            cout << "ISNI: " << libro->getAutor().getIsni() << endl;
            cout << "ISBN: " << libro->getIsbn() << endl;
            cout << "Fecha de publicación: " << libro->getFechaPublicacion().mostrar() << endl;
            cout << "Fecha de nacimiento del autor: " << libro->getAutor().getFechaNacimiento().mostrar() << endl;
            cout << "-----------------------------------" << endl;
        }
        break;
    }
    
    return sugerencias;
}
//Listar libros por primer letra del título
void LibroManager::listarLibrosPorLetra(const char letra) {
    vector<Libro*> libros = trie.collectAllBooks();
    bool encontrado = false;
    for (Libro* libro : libros) {
        if (libro->getTitulo()[0] == letra) {
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

//Buscar libros que contengan una subcadena
void LibroManager::buscarLibroPorSubcadena(const string& subcadena) {
    vector<Libro*> libros = trie.collectAllBooks();
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
