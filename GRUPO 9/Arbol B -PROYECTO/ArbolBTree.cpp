#include "ArbolBTree.h"
#include "Persona.h"
#include "BackupManager.h"
#include <iostream>
#include <fstream>
#include <functional>
#include <sstream>
#include <iomanip>

ArbolBTree::ArbolBTree(int t) : raiz(nullptr), t(t) {
    // Inicialización del árbol
}

void ArbolBTree::insertar(const Libro& libro) {
    if (raiz == nullptr) {
        raiz = new NodoBTree(true);
        raiz->claves.push_back(libro);
    } else {
        insertarEnNodo(raiz, libro);
    }
    std::cout << "Libro agregado: " << libro.getTitulo() << std::endl;
    // Guardar solo si no se está restaurando un backup
    if (!evitarGuardar) {
        guardarLibrosEnArchivo();
    }
}

void ArbolBTree::insertarEnNodo(NodoBTree* nodo, const Libro& libro) {
    int i = nodo->claves.size() - 1;

    if (nodo->esHoja) {
        nodo->claves.push_back(libro);
        while (i >= 0 && nodo->claves[i].getIsbn() > libro.getIsbn()) {
            nodo->claves[i + 1] = nodo->claves[i];
            i--;
        }
        nodo->claves[i + 1] = libro;
    } else {
        while (i >= 0 && nodo->claves[i].getIsbn() > libro.getIsbn()) {
            i--;
        }
        i++;
        if (nodo->hijos[i]->claves.size() == 2 * t - 1) {
            dividirNodo(nodo, i);
            if (nodo->claves[i].getIsbn() < libro.getIsbn()) {
                i++;
            }
        }
        insertarEnNodo(nodo->hijos[i], libro);
    }
}

void ArbolBTree::dividirNodo(NodoBTree* nodo, int i) {
    NodoBTree* hijoDerecho = new NodoBTree(nodo->hijos[i]->esHoja);
    NodoBTree* hijoIzquierdo = nodo->hijos[i];
    hijoDerecho->claves.resize(t - 1);

    for (int j = 0; j < t - 1; j++) {
        hijoDerecho->claves[j] = hijoIzquierdo->claves[j + t];
    }

    if (!hijoIzquierdo->esHoja) {
        hijoDerecho->hijos.resize(t);
        for (int j = 0; j < t; j++) {
            hijoDerecho->hijos[j] = hijoIzquierdo->hijos[j + t];
        }
    }

    hijoIzquierdo->claves.resize(t - 1);
    nodo->hijos.insert(nodo->hijos.begin() + i + 1, hijoDerecho);
    nodo->claves.insert(nodo->claves.begin() + i, hijoIzquierdo->claves[t - 1]);
}

NodoBTree* ArbolBTree::buscar(const std::string& /*titulo*/) {
    // Implementación pendiente
    return nullptr;
}

NodoBTree* ArbolBTree::buscarPorIsbn(const std::string& /*isbn*/) {
    // Implementación pendiente
    return nullptr;
}

NodoBTree* ArbolBTree::buscarEnNodo(NodoBTree* /*nodo*/, const std::string& /*isbn*/) {
    // Implementación pendiente
    return nullptr;
}

NodoBTree* ArbolBTree::buscarLibroPorIsbn(const std::string& isbn) {
    if (!raiz) return nullptr;
    NodoBTree* actual = raiz;
    while (actual) {
        for (const auto& libro : actual->claves) {
            if (libro.getIsbn() == isbn) {
                return actual;
            }
        }
        // Move to the next node based on the B-Tree properties
        int i = 0;
        while (i < actual->claves.size() && isbn > actual->claves[i].getIsbn()) {
            i++;
        }
        if (actual->esHoja) {
            return nullptr;
        } else {
            actual = actual->hijos[i];
        }
    }
    return nullptr;
}

Persona ArbolBTree::buscarAutorPorIsni(const std::string& isni) {
    if (!raiz) return Persona();
    NodoBTree* actual = raiz;
    while (actual) {
        for (const auto& libro : actual->claves) {
            if (libro.getAutor().getIsni() == isni) {
                return libro.getAutor();
            }
        }
        // Move to the next node based on the B-Tree properties
        int i = 0;
        while (i < actual->claves.size() && isni > actual->claves[i].getAutor().getIsni()) {
            i++;
        }
        if (actual->esHoja) {
            return Persona();
        } else {
            actual = actual->hijos[i];
        }
    }
    return Persona();
}

void ArbolBTree::guardarLibrosEnArchivo() {
    std::ofstream archivo("libros_temp.txt");
    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo temporal para guardar.\n\n";
        return;
    }

    // Helper function to traverse the B-Tree and save books
    std::function<void(NodoBTree*)> guardarNodo = [&](NodoBTree* nodo) {
        if (nodo) {
            for (const auto& libro : nodo->claves) {
                archivo << libro.getTitulo() << ";"
                        << libro.getAutor().getNombre() << ";"
                        << libro.getAutor().getIsni() << ";"
                        << libro.getAutor().getFechaNacimiento().mostrar() << ";"
                        << libro.getIsbn() << ";"
                        << libro.getFechaPublicacion().mostrar() << std::endl;
            }
            for (auto hijo : nodo->hijos) {
                guardarNodo(hijo);
            }
        }
    };

    guardarNodo(raiz);

    archivo.close();

    // Verificar si el archivo temporal se creó correctamente
    if (FILE* file = fopen("libros_temp.txt", "r")) {
        fclose(file);
    } else {
        std::cout << "No se pudo crear el archivo temporal correctamente.\n";
        return;
    }

    // Eliminar el archivo de destino si ya existe
    if (remove(archivoLibros.c_str()) != 0) {
        // Si el archivo no se puede eliminar, mostrar error
        std::cout << "Error al eliminar el archivo de destino: " << archivoLibros << std::endl;
    }

    // Renombrar el archivo temporal a la ubicación final
    if (rename("libros_temp.txt", archivoLibros.c_str()) != 0) {
        // Mostrar error si renombrar falla
        perror("Error al renombrar el archivo temporal");
    } else {
        std::cout << "Libros guardados en el archivo: " << archivoLibros << std::endl;
    }
}

void ArbolBTree::cargarLibrosDesdeArchivo() {
    std::ifstream archivo(archivoLibros);
    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo para cargar los libros.\n";
        return;
    }

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
        insertar(libro);
    }
    archivo.close();
    std::cout << "Libros cargados desde el archivo.\n";
}

void ArbolBTree::eliminar(const std::string& titulo) {
    if (!raiz) return;

    // Helper function to find and remove the book
    std::function<bool(NodoBTree*, const std::string&)> eliminarEnNodo = [&](NodoBTree* nodo, const std::string& titulo) -> bool {
        int i = 0;
        while (i < nodo->claves.size() && nodo->claves[i].getTitulo() < titulo) {
            i++;
        }

        if (i < nodo->claves.size() && nodo->claves[i].getTitulo() == titulo) {
            if (nodo->esHoja) {
                nodo->claves.erase(nodo->claves.begin() + i);
                return true;
            } else {
                // Eliminar en nodo no hoja
                Libro libroReemplazo;
                if (nodo->hijos[i]->claves.size() >= t) {
                    libroReemplazo = obtenerPredecesor(nodo, i);
                    nodo->claves[i] = libroReemplazo;
                    eliminarEnNodo(nodo->hijos[i], libroReemplazo.getTitulo());
                } else if (nodo->hijos[i + 1]->claves.size() >= t) {
                    libroReemplazo = obtenerSucesor(nodo, i);
                    nodo->claves[i] = libroReemplazo;
                    eliminarEnNodo(nodo->hijos[i + 1], libroReemplazo.getTitulo());
                } else {
                    fusionarNodos(nodo, i);
                    eliminarEnNodo(nodo->hijos[i], titulo);
                }
                return true;
            }
        } else if (!nodo->esHoja) {
            bool eliminado = eliminarEnNodo(nodo->hijos[i], titulo);
            if (eliminado && nodo->hijos[i]->claves.size() < t - 1) {
                balancearNodo(nodo, i);
            }
            return eliminado;
        }
        return false;
    };

    bool eliminado = eliminarEnNodo(raiz, titulo);
    if (eliminado) {
        if (raiz->claves.empty()) {
            NodoBTree* temp = raiz;
            if (raiz->esHoja) {
                raiz = nullptr;
            } else {
                raiz = raiz->hijos[0];
            }
            delete temp;
        }
        std::cout << "Libro eliminado: " << titulo << std::endl;
        guardarLibrosEnArchivo();
    } else {
        std::cout << "Libro no encontrado: " << titulo << std::endl;
    }
}

Libro ArbolBTree::obtenerPredecesor(NodoBTree* nodo, int i) {
    NodoBTree* actual = nodo->hijos[i];
    while (!actual->esHoja) {
        actual = actual->hijos.back();
    }
    return actual->claves.back();
}

Libro ArbolBTree::obtenerSucesor(NodoBTree* nodo, int i) {
    NodoBTree* actual = nodo->hijos[i + 1];
    while (!actual->esHoja) {
        actual = actual->hijos.front();
    }
    return actual->claves.front();
}

void ArbolBTree::fusionarNodos(NodoBTree* nodo, int i) {
    NodoBTree* hijoIzquierdo = nodo->hijos[i];
    NodoBTree* hijoDerecho = nodo->hijos[i + 1];
    hijoIzquierdo->claves.push_back(nodo->claves[i]);

    for (auto& clave : hijoDerecho->claves) {
        hijoIzquierdo->claves.push_back(clave);
    }
    if (!hijoIzquierdo->esHoja) {
        for (auto& hijo : hijoDerecho->hijos) {
            hijoIzquierdo->hijos.push_back(hijo);
        }
    }

    nodo->claves.erase(nodo->claves.begin() + i);
    nodo->hijos.erase(nodo->hijos.begin() + i + 1);
    delete hijoDerecho;
}

void ArbolBTree::balancearNodo(NodoBTree* nodo, int i) {
    if (i != 0 && nodo->hijos[i - 1]->claves.size() >= t) {
        NodoBTree* hijoIzquierdo = nodo->hijos[i - 1];
        NodoBTree* hijo = nodo->hijos[i];

        hijo->claves.insert(hijo->claves.begin(), nodo->claves[i - 1]);
        nodo->claves[i - 1] = hijoIzquierdo->claves.back();
        hijoIzquierdo->claves.pop_back();

        if (!hijo->esHoja) {
            hijo->hijos.insert(hijo->hijos.begin(), hijoIzquierdo->hijos.back());
            hijoIzquierdo->hijos.pop_back();
        }
    } else if (i != nodo->claves.size() && nodo->hijos[i + 1]->claves.size() >= t) {
        NodoBTree* hijoDerecho = nodo->hijos[i + 1];
        NodoBTree* hijo = nodo->hijos[i];

        hijo->claves.push_back(nodo->claves[i]);
        nodo->claves[i] = hijoDerecho->claves.front();
        hijoDerecho->claves.erase(hijoDerecho->claves.begin());

        if (!hijo->esHoja) {
            hijo->hijos.push_back(hijoDerecho->hijos.front());
            hijoDerecho->hijos.erase(hijoDerecho->hijos.begin());
        }
    } else {
        if (i != nodo->claves.size()) {
            fusionarNodos(nodo, i);
        } else {
            fusionarNodos(nodo, i - 1);
        }
    }
}

void ArbolBTree::imprimirLibros() {
    if (!raiz) {
        std::cout << "No hay libros registrados.\n";
        return;
    }

    std::cout << std::left << std::setw(41) << "Título"
              << std::setw(25) << "Autor"
              << std::setw(25) << "ISNI"
              << std::setw(20) << "ISBN"
              << std::setw(15) << "Publicación"
              << std::setw(15) << "Nac. Autor" << std::endl;
    std::cout << std::string(140, '-') << std::endl;

    // Helper function to traverse the B-Tree and print books
    std::function<void(NodoBTree*)> imprimirNodo = [&](NodoBTree* nodo) {
        if (nodo) {
            for (const auto& libro : nodo->claves) {
                std::cout << std::left << std::setw(40) << libro.getTitulo()
                          << std::setw(25) << libro.getAutor().getNombre()
                          << std::setw(25) << libro.getAutor().getIsni()
                          << std::setw(20) << libro.getIsbn()
                          << std::setw(15) << libro.getFechaPublicacion().mostrar()
                          << std::setw(15) << libro.getAutor().getFechaNacimiento().mostrar() << std::endl;
            }
            for (auto hijo : nodo->hijos) {
                imprimirNodo(hijo);
            }
        }
    };

    imprimirNodo(raiz);
}

void ArbolBTree::crearBackup(const std::string& nombreArchivo) {
    std::string carpetaBackup = "backup";  // Carpeta donde se almacenan los backups
    
    // Asegurarnos de que la carpeta de backups exista
    BackupManager::crearCarpetaSiNoExiste(carpetaBackup);

    // Crear la ruta completa para el archivo de backup dentro de la carpeta "backup"
    std::string rutaCompleta = carpetaBackup + "\\" + nombreArchivo;

    // Crear el archivo de backup
    std::ofstream archivo(rutaCompleta);
    if (!archivo.is_open()) {
        std::cout << "Error al crear el archivo de backup en la ruta: " << rutaCompleta << std::endl;
        return;
    }

    // Helper function to traverse the B-Tree and save books
    std::function<void(NodoBTree*)> guardarNodo = [&](NodoBTree* nodo) {
        if (nodo) {
            for (const auto& libro : nodo->claves) {
                archivo << libro.getTitulo() << ";" 
                        << libro.getAutor().getNombre() << ";"
                        << libro.getAutor().getIsni() << ";"
                        << libro.getAutor().getFechaNacimiento().mostrar() << ";"
                        << libro.getIsbn() << ";"
                        << libro.getFechaPublicacion().mostrar() << "\n";
            }
            for (auto hijo : nodo->hijos) {
                guardarNodo(hijo);
            }
        }
    };

    guardarNodo(raiz);

    // Cerrar el archivo después de escribir los datos
    archivo.close();
    std::cout << "Backup creado correctamente en: " << rutaCompleta << std::endl;
}

int ArbolBTree::getT() const {
    return t;
}
