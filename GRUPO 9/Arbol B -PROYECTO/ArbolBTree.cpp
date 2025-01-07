/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Archivo principal de proyecto                            *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          01/01/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

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
    try {
        if (raiz == nullptr) {
            raiz = new NodoBTree(true);
            raiz->claves.push_back(libro);
        } else {
            if (raiz->claves.size() == 2 * t - 1) {
                NodoBTree* nuevaRaiz = new NodoBTree(false);
                nuevaRaiz->hijos.push_back(raiz);
                dividirNodo(nuevaRaiz, 0);
                raiz = nuevaRaiz;
            }
            insertarEnNodo(raiz, libro);
        }
        std::cout << "Libro agregado: " << libro.getTitulo() << std::endl;
        if (!evitarGuardar) {
            guardarLibrosEnArchivo();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error al insertar el libro: " << e.what() << std::endl;
    }
}

void ArbolBTree::insertarEnNodo(NodoBTree* nodo, const Libro& libro) {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error al insertar en nodo: " << e.what() << std::endl;
    }
}

void ArbolBTree::dividirNodo(NodoBTree* nodo, int i) {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error al dividir nodo: " << e.what() << std::endl;
    }
}

NodoBTree* ArbolBTree::buscarLibroPorIsbn(const std::string& isbn) {
    try {
        if (!raiz) return nullptr;
        NodoBTree* actual = raiz;

        while (actual) {
            int i = 0;
            while (i < actual->claves.size() && isbn > actual->claves[i].getIsbn()) {
                i++;
            }

            if (i < actual->claves.size() && actual->claves[i].getIsbn() == isbn) {
                return actual;  // Encontrado
            }

            if (actual->esHoja) {
                return nullptr;  // No encontrado en hojas
            } else {
                actual = actual->hijos[i];
            }
        }

        return nullptr;
    } catch (const std::exception& e) {
        std::cerr << "Error al buscar libro por ISBN: " << e.what() << std::endl;
        return nullptr;
    }
}


Persona ArbolBTree::buscarAutorPorIsni(const std::string& isni) {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error al buscar autor por ISNI: " << e.what() << std::endl;
        return Persona();
    }
}

void ArbolBTree::guardarLibrosEnArchivo() {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error al guardar libros en archivo: " << e.what() << std::endl;
    }
}

void ArbolBTree::cargarLibrosDesdeArchivo() {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error al cargar libros desde archivo: " << e.what() << std::endl;
    }
}

void ArbolBTree::eliminar(const std::string& isbn) {
    if (!raiz) return;

    // Helper function to find and remove the book
    std::function<bool(NodoBTree*, const std::string&)> eliminarEnNodo = [&](NodoBTree* nodo, const std::string& isbn) -> bool {
        int i = 0;
        while (i < nodo->claves.size() && nodo->claves[i].getIsbn() < isbn) {
            i++;
        }

        if (i < nodo->claves.size() && nodo->claves[i].getIsbn() == isbn) {
            if (nodo->esHoja) {
                nodo->claves.erase(nodo->claves.begin() + i);
                return true;
            } else {
                // Eliminar en nodo no hoja
                Libro libroReemplazo;
                if (nodo->hijos[i]->claves.size() >= t) {
                    libroReemplazo = obtenerPredecesor(nodo, i);
                    nodo->claves[i] = libroReemplazo;
                    eliminarEnNodo(nodo->hijos[i], libroReemplazo.getIsbn());
                } else if (nodo->hijos[i + 1]->claves.size() >= t) {
                    libroReemplazo = obtenerSucesor(nodo, i);
                    nodo->claves[i] = libroReemplazo;
                    eliminarEnNodo(nodo->hijos[i + 1], libroReemplazo.getIsbn());
                } else {
                    fusionarNodos(nodo, i);
                    eliminarEnNodo(nodo->hijos[i], isbn);
                }
                return true;
            }
        } else if (!nodo->esHoja) {
            if (i == nodo->claves.size() || nodo->claves[i].getIsbn() > isbn) {
                i--;
            }
            bool eliminado = eliminarEnNodo(nodo->hijos[i + 1], isbn);
            if (eliminado && nodo->hijos[i + 1]->claves.size() < t - 1) {
                balancearNodo(nodo, i + 1);
            }
            return eliminado;
        }
        return false;
    };

    bool eliminado = eliminarEnNodo(raiz, isbn);
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
        std::cout << "Libro eliminado con ISBN: " << isbn << std::endl;
        guardarLibrosEnArchivo();
    } else {
        std::cout << "Libro no encontrado con ISBN: " << isbn << std::endl;
    }
}

Libro ArbolBTree::obtenerPredecesor(NodoBTree* nodo, int i) {
    try {
        NodoBTree* actual = nodo->hijos[i];
        while (!actual->esHoja) {
            actual = actual->hijos.back();
        }
        return actual->claves.back();
    } catch (const std::exception& e) {
        std::cerr << "Error al obtener predecesor: " << e.what() << std::endl;
        return Libro();
    }
}

Libro ArbolBTree::obtenerSucesor(NodoBTree* nodo, int i) {
    try {
        NodoBTree* actual = nodo->hijos[i + 1];
        while (!actual->esHoja) {
            actual = actual->hijos.front();
        }
        return actual->claves.front();
    } catch (const std::exception& e) {
        std::cerr << "Error al obtener sucesor: " << e.what() << std::endl;
        return Libro();
    }
}

void ArbolBTree::fusionarNodos(NodoBTree* nodo, int i) {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error al fusionar nodos: " << e.what() << std::endl;
    }
}

void ArbolBTree::balancearNodo(NodoBTree* nodo, int i) {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error al balancear nodo: " << e.what() << std::endl;
    }
}

void ArbolBTree::imprimirLibros() {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error al imprimir libros: " << e.what() << std::endl;
    }
}

void ArbolBTree::crearBackup(const std::string& nombreArchivo) {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error al crear backup: " << e.what() << std::endl;
    }
}

bool ArbolBTree::verificarArchivoLibros() {
    std::ifstream archivo("libros.txt");
    if (!archivo.is_open()) {
        std::cout << "Libros no registrados.\n";
        return false;
    }
    archivo.close();
    return true;
}

int ArbolBTree::getT() const {
    return t;
}
