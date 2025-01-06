#include "Autor.h"
#include "Libro.h"
#include "ListaDobleCircular.h"
#include <fstream>
#include <ctime>
#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

#ifdef _WIN32
#include <windows.h> // For CreateDirectory on Windows
#else
#include <sys/stat.h> // For mkdir on Unix-based systems (Linux/macOS)
#endif

void crearCarpetaBackup(const std::string &carpeta)
{
#ifdef _WIN32
    if (CreateDirectory(carpeta.c_str(), NULL) == 0)
    {
        if (GetLastError() != ERROR_ALREADY_EXISTS)
        {
            std::cout << "No se pudo crear la carpeta " << carpeta << ".\n";
        }
    }
#else
    if (mkdir(carpeta.c_str(), 0777) == -1)
    {
        if (errno != EEXIST)
        {
            std::cout << "No se pudo crear la carpeta " << carpeta << ".\n";
        }
    }
#endif
}

void guardarBackup(const ListaDobleCircular<Autor> &listaAutores, const ListaDobleCircular<Libro> &listaLibros)
{
    std::string carpetaBackup = "Backup";
    crearCarpetaBackup(carpetaBackup);

    time_t now = time(0);
    tm *ltm = localtime(&now);

    char nombreArchivo[100];
    strftime(nombreArchivo, sizeof(nombreArchivo), "backup_%Y-%m-%d_%H-%M-%S.txt", ltm);

    std::string rutaArchivo = carpetaBackup + "/" + nombreArchivo;

    std::ofstream archivo(rutaArchivo);
    if (!archivo.is_open())
    {
        std::cout << "No se pudo abrir el archivo para guardar el backup.\n";
        return;
    }

    archivo << "Autores:\n";
    Nodo<Autor> *actualAutor = listaAutores.vacia() ? nullptr : listaAutores.buscar(listaAutores.getCabeza()->dato);
    if (actualAutor)
    {
        do
        {
            archivo << actualAutor->dato.getCedula() << "\n"
                    << actualAutor->dato.getNombre() << "\n"
                    << actualAutor->dato.getApellido() << "\n"
                    << actualAutor->dato.getNacionalidad() << "\n"
                    << actualAutor->dato.getFechaNacimiento().toString() << "\n";
            actualAutor = actualAutor->siguiente;
        } while (actualAutor != listaAutores.getCabeza());
    }

    archivo << "Libros:\n";
    Nodo<Libro> *actualLibro = listaLibros.vacia() ? nullptr : listaLibros.buscar(listaLibros.getCabeza()->dato);
    if (actualLibro)
    {
        do
        {
            archivo << actualLibro->dato.getId() << "\n"
                    << actualLibro->dato.getNombre() << "\n"
                    << actualLibro->dato.getAutor().getCedula() << "\n"
                    << actualLibro->dato.getEditorial() << "\n"
                    << actualLibro->dato.getGenero() << "\n"
                    << actualLibro->dato.getSerie() << "\n"
                    << actualLibro->dato.getRating() << "\n"
                    << actualLibro->dato.getFechaPublicacion().toString() << "\n";
            actualLibro = actualLibro->siguiente;
        } while (actualLibro != listaLibros.getCabeza());
    }

    archivo.close();
    std::cout << "Backup guardado con exito en " << rutaArchivo << std::endl;
}

void restaurarBackup(ListaDobleCircular<Autor> &listaAutores, ListaDobleCircular<Libro> &listaLibros, const std::string &nombreArchivo)
{
    std::string carpetaBackup = "Backup";

    if (!fs::exists(carpetaBackup) || !fs::is_directory(carpetaBackup))
    {
        std::cout << "No se encontro la carpeta de backup." << std::endl;
        return;
    }

    std::string rutaArchivo = carpetaBackup + "/" + nombreArchivo;
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open())
    {
        std::cout << "No se pudo abrir el archivo para restaurar el backup." << std::endl;
        return;
    }

    std::cout << "Restaurando desde: " << rutaArchivo << "\n";
    std::string linea;
    listaAutores.clear();
    listaLibros.clear();

    while (getline(archivo, linea))
    {
        if (linea == "Autores:")
        {
            while (getline(archivo, linea))
            {
                if (linea == "Libros:" || linea.empty())
                    break;

                std::string cedula = linea, nombre, apellido, nacionalidad, fechaNacimientoStr;

                getline(archivo, nombre);
                getline(archivo, apellido);
                getline(archivo, nacionalidad);
                getline(archivo, fechaNacimientoStr);

                try
                {
                    Fecha fechaNacimiento = Fecha::fromString(fechaNacimientoStr);
                    Autor autor(cedula, nombre, apellido, nacionalidad, fechaNacimiento);
                    listaAutores.insertar(autor);
                    std::cout << "Autor restaurado: " << nombre << " " << apellido << "\n";
                }
                catch (const std::invalid_argument &e)
                {
                    std::cout << "Error al convertir la fecha para el autor " << cedula << ": " << e.what() << "\n";
                }
            }
        }

        if (linea == "Libros:")
        {
            while (getline(archivo, linea))
            {
                if (linea.empty())
                    continue;

                try
                {
                    int id = std::stoi(linea);
                    std::string nombre, cedulaAutor, editorial, genero, serie;
                    double rating;
                    std::string fechaPublicacionStr;

                    getline(archivo, nombre);
                    getline(archivo, cedulaAutor);
                    getline(archivo, editorial);
                    getline(archivo, genero);
                    getline(archivo, serie);
                    getline(archivo, linea);
                    rating = std::stod(linea);
                    getline(archivo, fechaPublicacionStr);

                    Fecha fechaPublicacion = Fecha::fromString(fechaPublicacionStr);

                    Nodo<Autor> *nodoAutor = listaAutores.buscar(Autor(cedulaAutor, "", "", "", Fecha()));
                    Autor autorRestaurado = nodoAutor ? nodoAutor->dato
                                                      : Autor("-----", "Sin autor", "", "", Fecha(1, 1, 1900));

                    if (!nodoAutor)
                    {
                        std::cout << "Autor con cedula " << cedulaAutor << " no encontrado. Usando autor generico.\n";
                    }

                    Libro libro(id, nombre, autorRestaurado, editorial, genero, serie, rating, fechaPublicacion);
                    listaLibros.insertar(libro);
                    std::cout << "Libro restaurado: " << nombre << " (Autor: " << autorRestaurado.getNombre() << ")\n";
                }
                catch (const std::exception &e)
                {
                    std::cout << "Error procesando libro: " << e.what() << "\n";
                }
            }
        }
    }

    archivo.close();
}
