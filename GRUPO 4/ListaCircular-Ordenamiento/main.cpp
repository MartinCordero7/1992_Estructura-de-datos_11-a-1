/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Dominguez Pablo, Egas Steven, Santos Estaban
 * FECHA CREACION: Domingo,  1 de enero de 2025
 * FECHA MODIFICACION: Domingo,  1 de enero de 2025
 * Asignatura:Estructura de datos
 * Nivel: TERCERO     NRC: 1992
 *************************/
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Autor.h"
#include "Libro.h"
#include "Fecha.h"
#include "Backup.h"
#include "ListaDobleCircular.h"
#include "Validaciones.cpp"
#include "Sorting.h"

#include <vector>
#include <filesystem>
#include <cstdlib>
using namespace std;

namespace fs = std::filesystem;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setBoldText() {
    setColor(15); // Default color (White)
}

// Función para mostrar el menú de ayuda interactiva
void mostrarMenuAyuda() {
    system("cls");
    cout << "\n\n\n";
    cout << "\t\t\t\t*** Ayuda Interactiva ***\n\n";
    cout << "Seleccione una de las siguientes opciones:\n\n";
    cout << "1. Introduccion al Programa\n";
    cout << "2. Ingresar Datos\n";
    cout << "3. Buscar Datos\n";
    cout << "4. Eliminar Datos\n";
    cout << "5. Gestionar Backups\n";
    cout << "6. Preguntas Frecuentes\n";
    cout << "7. Volver al Menu Principal\n";
    cout << "\nUsa las flechas para moverte, Enter para seleccionar.\n";
}

// Mostrar detalles sobre cada sección
void mostrarDetalleAyuda(int opcion) {
    // Definir algunos símbolos más simples para evitar problemas de interpretación
    const string linea = "------------------------------------------------------------";
    const string flecha = "-> ";
    const string asterisco = "* ";
    
    switch (opcion) {
        case 1:
            cout << "\n\t\t" << asterisco << "*** Introduccion al Programa ***" << asterisco << "\n";
            cout << linea << "\n";
            cout << "Bienvenido al Sistema de Gestion de Autores y Libros!\n\n";
            cout << "Este programa permite gestionar autores, libros y realizar copias de seguridad. Sus principales caracteristicas son:\n";
            cout << flecha << "Aniadir, buscar, eliminar autores y libros\n";
            cout << flecha << "Gestionar backups de datos\n";
            cout << flecha << "Realizar consultas detalladas\n\n";
            cout << "Para comenzar, puedes elegir entre varias opciones disponibles en el menu. ¡Explora la ayuda y descubre mas!\n";
            cout << linea << "\n";
            break;

        case 2:
            cout << "\n\t\t" << asterisco << "*** Ingresar Datos ***" << asterisco << "\n";
            cout << linea << "\n";
            cout << "Para ingresar datos (Autores o Libros), sigue estos pasos:\n\n";
            cout << flecha << "1. Selecciona 'Ingresar' desde el menu principal.\n";
            cout << flecha << "2. Elige si deseas agregar un 'Autor' o un 'Libro'.\n";
            cout << flecha << "3. Completa los campos requeridos (Cedula, Nombre, Titulo, etc.).\n";
            cout << flecha << "4. Haz clic en 'Guardar' para almacenar los datos.\n\n";
            cout << "Recuerda que cada autor debe tener una cedula unica y cada libro un ID unico!\n";
            cout << linea << "\n";
            break;

        case 3:
            cout << "\n\t\t" << asterisco << "*** Buscar Datos ***" << asterisco << "\n";
            cout << linea << "\n";
            cout << "Para buscar un autor o libro, sigue estos pasos:\n\n";
            cout << flecha << "1. Selecciona 'Buscar' desde el menu principal.\n";
            cout << flecha << "2. Introduce el ID o cedula del autor/libro que deseas buscar.\n";
            cout << flecha << "3. El sistema mostrara los detalles relacionados con el ID ingresado.\n\n";
            cout << "Consejos para busquedas eficientes:\n";
            cout << flecha << "Usa los ID o cedulas correctas para obtener resultados precisos.\n";
            cout << flecha << "Si no recuerdas el ID, consulta la lista de autores o libros disponibles.\n";
            cout << linea << "\n";
            break;

        case 4:
            cout << "\n\t\t" << asterisco << "*** Eliminar Datos ***" << asterisco << "\n";
            cout << linea << "\n";
            cout << "Para eliminar un autor o libro, sigue estos pasos:\n\n";
            cout << flecha << "1. Selecciona 'Eliminar' desde el menu principal.\n";
            cout << flecha << "2. Ingresa el ID o cedula del autor/libro que deseas eliminar.\n";
            cout << flecha << "3. Confirma la eliminacion cuando el sistema te lo pida.\n\n";
            cout << "Advertencia: Esta accion es irreversible. Asegurate de que deseas eliminar estos datos.\n";
            cout << linea << "\n";
            break;

        case 5:
            cout << "\n\t\t" << asterisco << "*** Gestionar Backups ***" << asterisco << "\n";
            cout << linea << "\n";
            cout << "Para gestionar copias de seguridad de los datos, sigue estos pasos:\n\n";
            cout << flecha << "1. Selecciona 'Guardar Backup' para crear un nuevo backup.\n";
            cout << flecha << "2. Selecciona 'Restaurar Backup' para recuperar los datos desde un archivo de backup.\n\n";
            cout << "Recuerda que los backups son fundamentales para la seguridad de tus datos.\n";
            cout << "Se recomienda realizar copias de seguridad de manera regular.\n";
            cout << linea << "\n";
            break;

        case 6:
            cout << "\n\t\t" << asterisco << "*** Preguntas Frecuentes (FAQ) ***" << asterisco << "\n";
            cout << linea << "\n";
            cout << "Preguntas Frecuentes:\n\n";
            cout << "Q: Como agrego un autor?\n";
            cout << "A: Ve al menu 'Ingresar', selecciona 'Autor' y completa la informacion requerida.\n\n";
            cout << "Q: Como elimino un libro?\n";
            cout << "A: Ve al menu 'Eliminar', ingresa el ID del libro y confirma la eliminacion.\n\n";
            cout << "Q: Puedo recuperar datos eliminados?\n";
            cout << "A: No, una vez eliminados, los datos no pueden ser recuperados a menos que tengas un backup disponible.\n\n";
            cout << "Q: Como hago un backup de mis datos?\n";
            cout << "A: Selecciona 'Guardar Backup' desde el menu principal. El sistema creara una copia de seguridad de los datos actuales.\n\n";
            cout << "Q: Como restauro un backup?\n";
            cout << "A: Selecciona 'Restaurar Backup' y elige el archivo de backup que deseas restaurar.\n\n";
            cout << "Q: El sistema guarda automaticamente los cambios?\n";
            cout << "A: No. Debes guardar manualmente los cambios al ingresar o modificar datos.\n\n";
            cout << "Q: Que debo hacer si no encuentro un autor o libro en la base de datos?\n";
            cout << "A: Verifica que el ID o la cedula sea correcta. Si aun no aparece, puede que los datos no esten registrados.\n\n";
            cout << "--------------------------------------------------\n";
            break;

        default:
            cout << "Opción no valida. Por favor, selecciona una opcion del menu de ayuda.\n";
            break;
    }
}


void mostrarAyudaEnConsola() {
    int opcion = 0;
    const int max_opciones = 7;
    
    while (true) {
        system("cls");  // Limpiar pantalla para mostrar el menú actualizado

        // Mostrar el menú de ayuda
        cout << "Menu de Ayuda\n";
        cout << "Use las teclas de flecha para navegar, Enter para seleccionar.\n\n";

        // Mostrar opciones
        for (int i = 0; i < max_opciones; i++) {
            if (opcion == i) cout << "> ";
            else cout << "  ";
            
            switch (i) {
                case 0: cout << "1. Introduccion al Programa\n"; break;
                case 1: cout << "2. Ingresar Datos\n"; break;
                case 2: cout << "3. Buscar Datos\n"; break;
                case 3: cout << "4. Eliminar Datos\n"; break;
                case 4: cout << "5. Gestionar Backups\n"; break;
                case 5: cout << "6. Preguntas Frecuentes (FAQ)\n"; break;
                case 6: cout << "7. Volver al Menu Principal\n"; break;
            }
        }

        // Manejo de entrada del usuario para navegar
        char key = _getch();
        if (key == 72) { // Flecha arriba
            opcion = (opcion > 0) ? opcion - 1 : max_opciones - 1;
        } else if (key == 80) { // Flecha abajo
            opcion = (opcion < max_opciones - 1) ? opcion + 1 : 0;
        } else if (key == '\r') { // Enter
            if (opcion == 6) { // Opción 7: Volver al menú principal
                return; // Salir del menú de ayuda y volver al menú principal
            } else {
                mostrarDetalleAyuda(opcion + 1); // Llamar a la ayuda con la opción correcta
                cout << "\nPresione cualquier tecla para volver al menu de ayuda.";
                _getch();  // Esperar entrada del usuario para continuar
            }
        }
    }
}

// Función para gestionar la ayuda interactiva
void mostrarAyuda() {
    int opcion = 1;
    //system("start cmd /k \"cls && echo *** Ayuda Interactiva *** && pause && mostrarAyudaEnConsola()\"");    

    while (true) {
        mostrarMenuAyuda();
        
        char key = _getch();
        if (key == 72) { // Flecha hacia arriba
            opcion = (opcion > 1) ? opcion - 1 : 7;
        } else if (key == 80) { // Flecha hacia abajo
            opcion = (opcion < 7) ? opcion + 1 : 1;
        } else if (key == '\r') { // Enter
            switch (opcion) {
                case 1:
                    mostrarDetalleAyuda(1);
                    break;
                case 2:
                    mostrarDetalleAyuda(2);
                    break;
                case 3:
                    mostrarDetalleAyuda(3);
                    break;
                case 4:
                    mostrarDetalleAyuda(4);
                    break;
                case 5:
                    mostrarDetalleAyuda(5);
                    break;
                case 6:
                    mostrarDetalleAyuda(6);
                    break;
                case 7:
                    cout << "Volviendo al menu principal...\n";
                    return;  // Salir y regresar al menú principal
            }
        }

        cout << "\nPresiona cualquier tecla para continuar...";
        _getch();
    }
}


void submenuRestaurarBackup(ListaDobleCircular<Autor> &listaAutores, ListaDobleCircular<Libro> &listaLibros, const std::string &backupFolder) {
    std::vector<std::string> archivos;

    // Cargar los archivos de la carpeta de backups
    try {
        for (const auto &entry : fs::directory_iterator(backupFolder)) {
            if (entry.is_regular_file()) {
                archivos.push_back(entry.path().filename().string());
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error al acceder a la carpeta de backups: " << e.what() << std::endl;
        system("pause");
        return;
    }

    if (archivos.empty()) {
        std::cout << "No se encontraron archivos de backup en la carpeta especificada.\n";
        system("pause");
        return;
    }

    int opcion = 0;

    while (true) {
        system("cls");
        std::cout << "\n\n\n\n";
        std::cout << "\t\t\t\t*** Submenu: Restaurar Backup ***\n\n";

        for (size_t i = 0; i < archivos.size(); ++i) {
            if (static_cast<int>(i) == opcion) {
                setColor(14);
                setBoldText();
                std::cout << "\t\t\t\t> " << archivos[i] << " <\n";
                setColor(15);
            } else {
                setColor(8);
                std::cout << "\t\t\t\t  " << archivos[i] << "\n";
                setColor(15);
            }
        }

        // Opción para volver al menú principal
        if (static_cast<int>(archivos.size()) == opcion) {
            setColor(14);
            setBoldText();
            std::cout << "\t\t\t\t> Volver al Menu Principal <\n";
            setColor(15);
        } else {
            setColor(8);
            std::cout << "\t\t\t\t  Volver al Menu Principal\n";
            setColor(15);
        }

        // Navegación del menú
        char key = _getch();
        if (key == 72) { // Flecha hacia arriba
            opcion = (opcion > 0) ? opcion - 1 : archivos.size();
        } else if (key == 80) { // Flecha hacia abajo
            opcion = (opcion < static_cast<int>(archivos.size())) ? opcion + 1 : 0;
        } else if (key == '\r') { // Enter
            if (opcion == static_cast<int>(archivos.size())) {
                return; // Volver al menú principal
            } else {
                // Restaurar el archivo seleccionado
                std::string archivoSeleccionado = archivos[opcion];
                restaurarBackup(listaAutores, listaLibros,archivoSeleccionado);
                std::cout << "Backup restaurado desde: " << archivoSeleccionado << "\n";
                system("pause");
                return;
            }
        }
    }
}


void mostrarMenu(int opcionSeleccionada) {
    const string opciones[] = {
        "1. Ingresar",
        "2. Buscar",
        "3. Eliminar",
        "4. Imprimir",
        "5. Guardar Backup",
        "6. Restaurar Backup",
        "7. Filtrar Libros por Anio",  // Nueva opción agregada
        "8. Ordenar",  // Nueva opción agregada
        "9. Salir",
        "10. Ayuda"
    };

    system("cls");
    cout << "\n\n\n\n\n";
    cout << "\t\t\t\t*** Menu de operaciones ***\n\n";

    for (int i = 0; i < 10; i++) {
        if (i == opcionSeleccionada) {
            setColor(14);
            setBoldText();
            cout << "\t\t\t\t> " << opciones[i] << " <\n";
            setColor(15);
        } else {
            setColor(8);
            cout << "\t\t\t\t  " << opciones[i] << "\n";
            setColor(15);
        }
    }
    cout << "\n";
}

void submenuIngresar(ListaDobleCircular<Autor> &listaAutores, ListaDobleCircular<Libro> &listaLibros) {
    int opcion = 0;
    const string opciones[] = {
        "1. Ingresar Autor",
        "2. Ingresar Libro",
        "3. Volver al Menu Principal"
    };

    while (true) {
        system("cls");
        cout << "\n\n\n\n";
        cout << "\t\t\t\t*** Submenu: Ingresar ***\n\n";

        for (int i = 0; i < 3; i++) {
            if (i == opcion) {
                setColor(14);
                setBoldText();
                cout << "\t\t\t\t> " << opciones[i] << " <\n";
                setColor(15);
            } else {
                setColor(8);
                cout << "\t\t\t\t  " << opciones[i] << "\n";
                setColor(15);
            }
        }

        char key = _getch();
        if (key == 72) { // Up arrow
            opcion = (opcion > 0) ? opcion - 1 : 2;
        } else if (key == 80) { // Down arrow
            opcion = (opcion < 2) ? opcion + 1 : 0;
        } else if (key == '\r') { // Enter
            switch (opcion) {
                case 0: {
                    Autor nuevoAutor = ingresarAutor(listaAutores);
                    listaAutores.insertar(nuevoAutor);
                    cout << endl<<"Autor ingresado con exito.\n";
                    system("pause");
                    break;
                }
                case 1: {
                    if (listaAutores.vacia()) {
                        cout << "Primero debe ingresar un autor.\n";
                    } else {
                        Libro nuevoLibro = ingresarLibro(listaAutores,listaLibros);
                        listaLibros.insertar(nuevoLibro);
                        cout << "Libro ingresado con exito.\n";
                    }
                    system("pause");
                    break;
                }
                case 2: return;
            }
        }
    }
}

void submenuBuscar(ListaDobleCircular<Autor> &listaAutores, ListaDobleCircular<Libro> &listaLibros) {
    int opcion = 0;
    const string opciones[] = {
        "1. Buscar Autor",
        "2. Buscar Libro",
        "3. Volver al Menu Principal"
    };

    while (true) {
        system("cls");
        cout << "\n\n\n\n";
        cout << "\t\t\t\t*** Submenu: Buscar ***\n\n";

        for (int i = 0; i < 3; i++) {
            if (i == opcion) {
                setColor(14);
                setBoldText();
                cout << "\t\t\t\t> " << opciones[i] << " <\n";
                setColor(15);
            } else {
                setColor(8);
                cout << "\t\t\t\t  " << opciones[i] << "\n";
                setColor(15);
            }
        }

        char key = _getch();
        if (key == 72) { // Up arrow
            opcion = (opcion > 0) ? opcion - 1 : 2;
        } else if (key == 80) { // Down arrow
            opcion = (opcion < 2) ? opcion + 1 : 0;
        } else if (key == '\r') { // Enter
            switch (opcion) {
                case 0: {
                    string cedulaAutor;
                    cedulaAutor= validarCedula( "Ingrese la cedula del autor a buscar: ");
                    Autor autorBuscado(cedulaAutor, "", "", Fecha());
                    Nodo<Autor> *nodoAutor = listaAutores.buscar(autorBuscado);
                    if (nodoAutor) {
                        cout << "Autor encontrado: ";
                        nodoAutor->dato.imprimirAutor();
                    } else {
                        cout << "Autor no encontrado.\n";
                    }
                    break;
                }
                case 1: {
                    int idLibro;
                    
                    idLibro=ingresarIntt("Ingrese el ID del libro a buscar: ",2,'0');
                    Libro libroBuscado(idLibro, "", Autor(),"","","",0.0, Fecha());
                    Nodo<Libro> *nodoLibro = listaLibros.buscar(libroBuscado);
                    if (nodoLibro) {
                        cout << "\nLibro encontrado: ";
                        nodoLibro->dato.imprimirLibro();
                    } else {
                        cout << "\nLibro no encontrado.\n";
                    }
                    break;
                }
                case 2: return;
            }
            system("pause");
        }
    }
}

void submenuEliminar(ListaDobleCircular<Autor> &listaAutores, ListaDobleCircular<Libro> &listaLibros) {
    int opcion = 0;
    const string opciones[] = {
        "1. Eliminar Autor",
        "2. Eliminar Libro",
        "3. Volver al Menu Principal"
    };

    while (true) {
        system("cls");
        cout << "\n\n\n\n";
        cout << "\t\t\t\t*** Submenu: Eliminar ***\n\n";

        for (int i = 0; i < 3; i++) {
            if (i == opcion) {
                setColor(14);
                setBoldText();
                cout << "\t\t\t\t> " << opciones[i] << " <\n";
                setColor(15);
            } else {
                setColor(8);
                cout << "\t\t\t\t  " << opciones[i] << "\n";
                setColor(15);
            }
        }

        char key = _getch();
        if (key == 72) { // Up arrow
            opcion = (opcion > 0) ? opcion - 1 : 2;
        } else if (key == 80) { // Down arrow
            opcion = (opcion < 2) ? opcion + 1 : 0;
        } else if (key == '\r') { // Enter
            switch (opcion) {
                case 0: { // Eliminar Autor
                    string cedula;
                    cedula = validarCedula("Ingrese la cedula del autor a eliminar : ");

                    Autor autorBuscado(cedula, "", "", "", Fecha());
                    Nodo<Autor> *nodoAutor = listaAutores.buscar(autorBuscado);
                    if (nodoAutor) {
                        cout << "Se encontro al autor: ";
                        nodoAutor->dato.imprimirAutor();

                        cout << "Elija una opcion:\n";
                        cout << "1. Eliminar los libros asociados al autor.\n";
                        cout << "2. Marcar los libros como 'sin autor'.\n";
                        cout << "Opcion: ";
                        int opcionEliminar=ingresarIntt("",1,'1','2');

                        if (opcionEliminar == 1) {
                            // Eliminar los libros asociados al autor
                            listaLibros.eliminarLibrosPorAutor(autorBuscado);
                            cout << "\nSe eliminaron los libros asociados al autor.\n";
                        } else if (opcionEliminar == 2) {
                            // Actualizar los libros asociados para que queden sin autor
                            listaLibros.actualizarAutorEnLibros(autorBuscado);
                            cout << "\nLos libros asociados al autor fueron marcados como 'sin autor'.\n";
                        } else {
                            cout << "\nOpcion invalida. No se realizaron cambios en los libros.\n";
                        }

                        listaAutores.eliminar(autorBuscado);
                        cout << "\nSe elimino al autor.\n";
                    } else {
                        cout << "No se encontro ningun autor con la cedula: " << cedula << ".\n";
                    }
                    system("pause");
                    break;
                }
                case 1: { // Eliminar Libro
                    int id;
                    cout << "Ingrese el ID del libro a eliminar: ";
                    cin >> id;

                    Libro libroBuscado(id, "", Autor(), "", "", "", 0.0, Fecha());
                    Nodo<Libro> *nodoLibro = listaLibros.buscar(libroBuscado);
                    if (nodoLibro) {
                        cout << "Se elimino el libro: ";
                        nodoLibro->dato.imprimirLibro();
                        listaLibros.eliminar(libroBuscado);
                    } else {
                        cout << "No se encontro ningun libro con el ID: " << id << ".\n";
                    }
                    system("pause");
                    break;
                }
                case 2: // Volver al menu principal
                    return;
            }
        }
    }
}



void submenuMostrar(ListaDobleCircular<Autor> &listaAutores, ListaDobleCircular<Libro> &listaLibros) {
    int opcion = 0;
    const string opciones[] = {
        "1. Mostrar Autores",
        "2. Mostrar Libros",
        "3. Volver al Menu Principal"
    };

    while (true) {
        system("cls");
        cout << "\n\n\n\n";
        cout << "\t\t\t\t*** Submenu: Mostrar ***\n\n";

        for (int i = 0; i < 3; i++) {
            if (i == opcion) {
                setColor(14);
                setBoldText();
                cout << "\t\t\t\t> " << opciones[i] << " <\n";
                setColor(15);
            } else {
                setColor(8);
                cout << "\t\t\t\t  " << opciones[i] << "\n";
                setColor(15);
            }
        }

        char key = _getch();
        if (key == 72) { // Up arrow
            opcion = (opcion > 0) ? opcion - 1 : 2;
        } else if (key == 80) { // Down arrow
            opcion = (opcion < 2) ? opcion + 1 : 0;
        } else if (key == '\r') { // Enter
            switch (opcion) {
                case 0: {
                    cout << "Lista de Autores:\n";
                    listaAutores.imprimir();
                    system("pause");
                    break;
                }
                case 1: {
                    cout << "Lista de Libros:\n";
                    listaLibros.imprimir();
                    system("pause");
                    break;
                }
                case 2: return;
            }

        }
    }
}

void filtrarLibrosPorAnio(ListaDobleCircular<Libro> &listaLibros) {
    int anioInicio = 0;
    int anioFin = 0;

    // Validar entrada del rango de años
    do {
        anioInicio = ingresarIntt("Ingrese el anio de inicio (>= 1900): ", 4, '0');
        anioFin = ingresarIntt("\nIngrese el anio de fin (<= 2025): ", 4, '0');

        if (anioInicio > anioFin || anioInicio < 1900 || anioFin > 2025) {
            cout << "\nRango de anios invalido. Asegurese de que el anio de inicio sea menor o igual al anio de fin, y que esten entre 1900 y 2025.\n";
        }
    } while (anioInicio > anioFin || anioInicio < 1900 || anioFin > 2025);

    cout << "\nLibros publicados entre " << anioInicio << " y " << anioFin << ":\n";

    // Iterar manualmente sobre la lista de libros
    Nodo<Libro>* nodoActual = listaLibros.getCabeza();
    bool encontrado = false;

    if (nodoActual != nullptr) {
        do {
            const Libro& libro = nodoActual->dato;
            int anioPublicacion = libro.getFechaPublicacion().getAnio();
            if (anioPublicacion >= anioInicio && anioPublicacion <= anioFin) {
                libro.imprimirLibro();
                encontrado = true;
            }
            nodoActual = nodoActual->siguiente;
        } while (nodoActual != listaLibros.getCabeza());  // Recorrer toda la lista circular
    }

    if (!encontrado) {
        cout << "No se encontraron libros en ese rango de anios.\n";
    }
    system("pause");
}


void sorting(ListaDobleCircular<Autor> &listaAutores, ListaDobleCircular<Libro> &listaLibros, string backupFolder){
 std::vector<std::string> archivos;

    // Cargar los archivos de la carpeta de backups
    try {
        for (const auto &entry : fs::directory_iterator(backupFolder)) {
            if (entry.is_regular_file()) {
                archivos.push_back(entry.path().filename().string());
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error al acceder a la carpeta de backups: " << e.what() << std::endl;
        system("pause");
        return;
    }

    if (archivos.empty()) {
        std::cout << "No se encontraron archivos de backup en la carpeta especificada.\n";
        system("pause");
        return;
    }

    int opcion = 0;

    while (true) {
        system("cls");
        std::cout << "\n\n\n\n";
        std::cout << "\t\t\t\t*** Submenu: Ordenar ***\n\n";

        for (size_t i = 0; i < archivos.size(); ++i) {
            if (static_cast<int>(i) == opcion) {
                setColor(14);
                setBoldText();
                std::cout << "\t\t\t\t> " << archivos[i] << " <\n";
                setColor(15);
            } else {
                setColor(8);
                std::cout << "\t\t\t\t  " << archivos[i] << "\n";
                setColor(15);
            }
        }

        // Opción para volver al menú principal
        if (static_cast<int>(archivos.size()) == opcion) {
            setColor(14);
            setBoldText();
            std::cout << "\t\t\t\t> Volver al Menu Principal <\n";
            setColor(15);
        } else {
            setColor(8);
            std::cout << "\t\t\t\t  Volver al Menu Principal\n";
            setColor(15);
        }

        // Navegación del menú
        char key = _getch();
        if (key == 72) { // Flecha hacia arriba
            opcion = (opcion > 0) ? opcion - 1 : archivos.size();
        } else if (key == 80) { // Flecha hacia abajo
            opcion = (opcion < static_cast<int>(archivos.size())) ? opcion + 1 : 0;
        } else if (key == '\r') { // Enter
            if (opcion == static_cast<int>(archivos.size())) {
                return; // Volver al menú principal
            } else {
                // Restaurar el archivo seleccionado
                std::string inputFile  = archivos[opcion];
                std::string outputFile = "Backup/sorted_backup.txt";
                cout<<"Se va a ordernar las Personas:";
    std::string section = "Autores"; // or "Libros"
    cout<<"Eliga que campo desea.\n1.-Nombre.\n2.-Apellido\n3.-Cedula";
    int choice=ingresarIntt("",1,'1','3');
    std::string field="";
    switch(choice){
        case 1:
    field = "Nombre"; // Sort by this field
        case 2:
    field="Apellido";
        case 3:
    field="Cedula";    
    }

    Sorting::sortBackup(inputFile, outputFile, section, field);

    std::cout << section << " sorted by " << field << " and saved to " << outputFile << "." << std::endl;
            }
        }
    }
}

int main() {
    ListaDobleCircular<Autor> listaAutores;
    ListaDobleCircular<Libro> listaLibros;
    int opcion = 0;

    while (true) {
        mostrarMenu(opcion);

        char key = _getch();
        if (key == 72) { // Up arrow
            opcion = (opcion > 0) ? opcion - 1 : 9;  // Cambiar a 8 porque ahora hay 9 opciones
        } else if (key == 80) { // Down arrow
            opcion = (opcion < 9) ? opcion + 1 : 0;  // Cambiar a 8 porque ahora hay 9 opciones
        } else if (key == '\r') { // Enter
            switch (opcion) {
                case 0: submenuIngresar(listaAutores, listaLibros); break;
                case 1: submenuBuscar(listaAutores, listaLibros); break;
                case 2: submenuEliminar(listaAutores, listaLibros); break;
                case 3: submenuMostrar(listaAutores, listaLibros); break;
                case 4: guardarBackup(listaAutores, listaLibros); getch(); break;
                case 5: submenuRestaurarBackup(listaAutores, listaLibros, "Backup"); break;
                case 6: filtrarLibrosPorAnio(listaLibros); break;  // Llamada a la función para filtrar
                case 7: sorting(listaAutores, listaLibros,"Backup"); break;
                case 8: cout << "Saliendo del programa.\n"; return 0;
                case 9: mostrarAyudaEnConsola(); break;
            }
        }
    }
    return 0;
}