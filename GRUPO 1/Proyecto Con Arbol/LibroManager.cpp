#include "LibroManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <direct.h>        // Para mkdir en Windows
#include <sys/stat.h>      // Para usar _stat
#include "BackupManager.h" // Incluir el archivo de cabecera con la declaración de la función

using namespace std;

// Agregar libro
void LibroManager::agregarLibro(const Libro &libro)
{
    splayTree.insert(libro.getTitulo(), new Libro(libro));
    cout << "Libro agregado: " << libro.getTitulo() << endl;
    // Guardar solo si no se está restaurando un backup
    if (!evitarGuardar)
    {
        guardarLibrosEnArchivo();
    }
}

// Limpiar la lista actual
void LibroManager::limpiarLista()
{
    // Implementar si es necesario, dependiendo de la funcionalidad que requieras
}

// Imprimir todos los libros
void LibroManager::imprimirLibros()
{
    vector<Libro *> libros = splayTree.collectAllBooks();

    if (libros.empty())
    {
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

    for (const Libro *libro : libros)
    {
        cout << left << setw(40) << libro->getTitulo()
             << setw(25) << libro->getAutor().getNombre()
             << setw(25) << libro->getAutor().getIsni()
             << setw(20) << libro->getIsbn()
             << setw(15) << libro->getFechaPublicacion().mostrar()
             << setw(15) << libro->getAutor().getFechaNacimiento().mostrar() << endl;
    }
}

// Buscar libro por título
Libro *LibroManager::buscarLibro(const string &titulo)
{
    return splayTree.search(titulo);
}

// Buscar libro por ISBN
Libro *LibroManager::buscarLibroPorIsbn(const string &isbn)
{
    vector<Libro *> libros = splayTree.collectAllBooks();
    for (Libro *libro : libros)
    {
        if (libro->getIsbn() == isbn)
        {
            return libro;
        }
    }
    return nullptr;
}

// Buscar autor por ISNI
Persona LibroManager::buscarAutorPorIsni(const string &isni)
{
    vector<Libro *> libros = splayTree.collectAllBooks();
    for (Libro *libro : libros)
    {
        if (libro->getAutor().getIsni() == isni)
        {
            return libro->getAutor();
        }
    }
    return Persona();
}

// Eliminar libro
void LibroManager::eliminarLibro(const string &titulo)
{
    splayTree.remove(titulo);
    cout << "Libro eliminado: " << titulo << endl;
    // Actualizar el archivo después de la eliminación
    guardarLibrosEnArchivo();
}

// Guardar libros en archivo
void LibroManager::guardarLibrosEnArchivo()
{
    ofstream archivo("libros_temp.txt");
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo temporal para guardar.\n\n";
        return;
    }

    splayTree.printAll(archivo);

    archivo.close();

    // Verificar si el archivo temporal se creó correctamente
    if (FILE *file = fopen("libros_temp.txt", "r"))
    {
        fclose(file);
    }
    else
    {
        cout << "No se pudo crear el archivo temporal correctamente.\n";
        return;
    }

    // Eliminar el archivo de destino si ya existe
    if (remove(archivoLibros.c_str()) != 0)
    {
        cout << "Error al eliminar el archivo de destino: " << archivoLibros << endl;
    }

    // Renombrar el archivo temporal a la ubicación final
    if (rename("libros_temp.txt", archivoLibros.c_str()) != 0)
    {
        perror("Error al renombrar el archivo temporal");
    }
    else
    {
        cout << "Libros guardados en el archivo: " << archivoLibros << endl;
    }
}

// Cargar libros desde el archivo
void LibroManager::cargarLibrosDesdeArchivo()
{
    ifstream archivo(archivoLibros);
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo para cargar los libros.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string titulo, nombreAutor, isni, fechaNacAutor, isbn, fechaPublicacion;
        getline(ss, titulo, ';');
        getline(ss, nombreAutor, ';');
        getline(ss, isni, ';');
        getline(ss, fechaNacAutor, ';');
        getline(ss, isbn, ';');
        getline(ss, fechaPublicacion, ';');

        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNacAutor);
        Fecha fechaPublicacionLibro = Fecha::crearDesdeCadena(fechaPublicacion);

        Persona autorPersona(nombreAutor, isni, fechaNacimientoAutor);
        Libro libro(titulo, isbn, autorPersona, fechaPublicacionLibro);
        agregarLibro(libro);
    }
    archivo.close();
    cout << "Libros cargados desde el archivo.\n";
}

// Crear backup
void LibroManager::crearBackup(const string &nombreArchivo)
{
    string carpetaBackup = "backup"; // Carpeta donde se almacenan los backups

    // Asegurarnos de que la carpeta de backups exista
    BackupManager::crearCarpetaSiNoExiste(carpetaBackup);

    string rutaCompleta = carpetaBackup + "\\" + nombreArchivo;

    ofstream archivo(rutaCompleta);
    if (!archivo.is_open())
    {
        cout << "Error al crear el archivo de backup en la ruta: " << rutaCompleta << endl;
        return;
    }

    splayTree.printAll(archivo);

    archivo.close();
    cout << "Backup creado correctamente en: " << rutaCompleta << endl;
}

// Restaurar backup
void LibroManager::restaurarBackup(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo de backup.\n";
        return;
    }

    cout << "Cargando backup desde: " << nombreArchivo << endl;

    limpiarLista();
    evitarGuardar = true;

    string linea;
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string titulo, nombreAutor, isni, fechaNacStr, isbn, fechaPubStr;

        getline(ss, titulo, ';');
        getline(ss, nombreAutor, ';');
        getline(ss, isni, ';');
        getline(ss, fechaNacStr, ';');
        getline(ss, isbn, ';');
        getline(ss, fechaPubStr, ';');

        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNacStr);
        Fecha fechaPublicacionLibro = Fecha::crearDesdeCadena(fechaPubStr);

        Persona autor(nombreAutor, isni, fechaNacimientoAutor);
        Libro libro(titulo, isbn, autor, fechaPublicacionLibro);
        agregarLibro(libro);
    }

    evitarGuardar = false;

    archivo.close();
    cout << "Backup restaurado correctamente.\n";
}
