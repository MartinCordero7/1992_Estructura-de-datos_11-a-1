#include "ILista.hpp"
#include "ListaSimple.hpp"
#include "ListaDoble.hpp"
#include "ListaCircular.hpp"
#include "Sort.hpp"
#include "Libro.hpp"
#include "Autor.hpp"
#include "Validaciones.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <functional>

//// GETCH ////
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#include <conio.h>

#else

#include <termios.h> 
#include <unistd.h> 
#include <stdio.h>
int getch()
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

#endif
//// GETCH ////

//// DEFINICIONES ////
#define KEY_UP 72
#define KEY_DOWN 80

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define KEY_ENTER 13
#define CLEAR_COMMAND "cls"
#else
#define KEY_ENTER 10
#define CLEAR_COMMAND "clear"
#endif
//// DEFINICIONES ////


void cargar(ILista<Libro>* ListaLibros, ILista<Autor>* listaAutores, std::string directorio = ".");
void guardar(ILista<Libro>* listaLibros, ILista<Autor>* listaAutores, std::string directorio = ".", bool backup = false);

// FUNCION PARA CONSEGUIR EL PUNTERO DE UN LIBRO/AUTOR EXISTENTE USANDO SU ID
Autor* punteroAutorEnLista(std::string cedula, ILista<Autor>* listaAutores);
Libro* punteroLibroEnLista(std::string id, ILista<Libro>* listaLibros);

int main()
{
    ILista<Libro>* listaLibros = new ListaSimple<Libro>();
    ILista<Autor>* listaAutores = new ListaSimple<Autor>();


    cargar(listaLibros, listaAutores, ".");

    /////////////////////// COMPROBACIÓN DE EXISTENCIA DE UN ARCHIVO DE AUTOGUARDADO ////////////////////////
    
    if (std::filesystem::is_directory("unsaved"))
    {
        ListaSimple<Libro> listaLibrosTemp;
        ListaSimple<Autor> listaAutoresTemp;
        cargar(&listaLibrosTemp, &listaAutoresTemp, "unsaved");

        std::cout << "Lista de Libros guardada: " << std::endl;
        listaLibros->mostrar();
        std::cout << std::endl << "\033[1;30mLista de Libros sin guardar recuperada:" << std::endl;
        listaLibrosTemp.mostrar();

        std::cout << "\033[0m" << std::endl << std::endl;
        
        std::cout << "Lista de Autores guardada: " << std::endl;
        listaAutores->mostrar();
        std::cout << std::endl << "\033[1;30mLista de Autores sin guardar recuperada:" << std::endl;
        listaAutoresTemp.mostrar();

        std::cout << std::endl << std::endl << "\033[1;34mLa aplicación no se ha cerrado apropiadamente en la última sesión, ¿Desea restaurar los cambios sin guardar? (Y/n): \033[0m";
        char opcion = tolower(getch());

        if (opcion == 'y' || opcion == '\n' || opcion == '\r')
        {
            delete listaLibros;
            delete listaAutores;
            listaLibros = new ListaSimple<Libro>();
            listaAutores = new ListaSimple<Autor>();

            cargar(listaLibros, listaAutores, "unsaved");
            std::cout << std::endl << "DATOS RESTAURADOS";
            getch();
        }
    }

    /////////////////////// DECLARACIÓN DE LOS MENÚS ////////////////////////

    const std::string menuListas =
        "1. Libros\n"
        "2. Autores\n"
        "3. Cambiar Lista\n"
        "4. Salida\n";

    const std::string menuOpLibros =
        "1. Insertar\n"
        "2. Buscar\n"
        "3. Eliminar\n"
        "4. Mostrar\n"
        "5. Guardar\n"
        "6. Filtrar\n"
        "7. Ordenar Libros\n"
        "8. Volver\n";

    const std::string menuOpAutores =
        "1. Insertar\n"
        "2. Buscar\n"
        "3. Eliminar\n"
        "4. Mostrar\n"
        "5. Guardar\n"
        "6. Volver\n";

    const std::string menuCambio =
        "1. Lista Simple\n"
        "2. Lista Doble\n"
        "3. Lista Circular\n"
        "4. Cancelar\n";

    const std::string menuOrdenarLibros =
        "1. ID\n"
        "2. Titulo\n"
        "3. Autor\n"
        "4. Fecha\n"
        "5. Cancelar\n";
    
    const std::string menuMetodo =
        "1. Burbuja\n"
        "2. QuickSort\n"
        "3. ShellSort\n"
        "4. Insercion\n"
        "5. Distribucion\n"
        "6. Radix\n"
        "7. MergeSort\n"
        "8. MezclaDirecta\n"
        "9. MezclaNatural\n"
        "10. Cancelar\n";


    /////////////////////// FUNCIÓN LAMBDA QUE IMPRIME UN MENÚ ////////////////////////
    // Resalta el elemento seleccionado
    ///////////////////////////////////////////////////////////////////////////////////
    auto imprimirMenu = [](const std::string& menu, int eleccion)
        {
            std::stringstream ss(menu);
            std::string s;
            int cont = 0;
            while (getline(ss, s))
            {
                cont++;
                std::cout << ((cont == eleccion) ? "\033[5m>\033[25m \033[7;1m" : "  ") << s << std::endl;
                if (cont == eleccion)
                    std::cout << "\033[0m";
            }
        };

    /////////////////////// FUNCIÓN LAMBDA QUE RESTRINGE LOS VALORES DE ELECCION ////////////////////////
    // la entrada se realiza mediante las flechas arriba (aumentar), abajo (disminuir) y el botón enter
    // TODO: decidir si es apropiado cambiar el nombre de la función
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    auto procesarEntrada = [](int& eleccion, int entrada, int eleccionMax) -> bool
        {
            //
        // PARA LINUX, se procesan 3 caracteres al presionar las flechas: '\033', '[' y una letra
            if (entrada == '\033')
            {
                getch(); // lee el '['
                entrada = getch(); // lee la letra
                switch (entrada)
                {
                case 'A':   // KEY_UP
                    entrada = KEY_UP;
                    break;
                case 'B':   // KEY_DOWN
                    entrada = KEY_DOWN;
                    break;
                case 'C':   // KEY_LEFT
                    break;
                case 'D':   // KEY_RIGHT
                    break;

                default:
                    break;
                }
            }
            // FIN PARA LINUX
            //

            switch (entrada)
            {
            case KEY_UP:
                if (eleccion == 1)
                    eleccion = eleccionMax;
                else
                    eleccion--;

                break;
            case KEY_DOWN:
                if (eleccion == eleccionMax)
                    eleccion = 1;
                else
                    eleccion++;

                break;
            case KEY_ENTER:
                return true;
                break;

            default:
                if (entrada > '0' && entrada < eleccionMax + '0' + 1)
                {
                    eleccion = entrada - '0';
                    // return true;     // Remover comentario para que entre inmediatamente en la opción
                }
                }
            return false;
        };

    // ENUM PARA LA FUNCIÓN LAMBDA
    enum eleccionSort { SORT_BURBUJA = 1, SORT_QUICKSORT, SORT_SHELLSORT, SORT_INSERCION, SORT_DISTRIBUCION, SORT_RADIX, SORT_MERGESORT, SORT_MEZCLA_DIRECTA, SORT_MEZCLA_NATURAL, SORT_CANCELAR };
    /////////////////////// FUNCIÓN LAMBDA QUE MUESTRA UN MENÚ PARA ELEGIR MÉTODO DE SORTING ////////////////////////
    // la entrada se realiza mediante las flechas arriba (aumentar), abajo (disminuir) y el botón enter
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto elegirMetodo = [&imprimirMenu, &menuMetodo, &procesarEntrada]<typename T, typename U>(ILista<T>*lista, std::function<const U & (const T&)> attributeGetter)
    {
        int eleccion = 1;
        char entrada;
        bool salir;

        do
        {
            system(CLEAR_COMMAND);
            std::cout << "============ ELEGIR MÉTODO ============" << std::endl;
            imprimirMenu(menuMetodo, eleccion);
            entrada = getch();
            system("clear");
            std::cout << attributeGetter(lista->conseguirDato(0));

            salir = procesarEntrada(eleccion, entrada, SORT_CANCELAR);

            if (salir)
            {
                if (eleccion != SORT_CANCELAR)
                {
                    switch (eleccion)
                    {
                    case SORT_BURBUJA:
                        Sort::bubbleSortObj(*lista, attributeGetter);
                        break;
                    case SORT_QUICKSORT:
                        std::cout << "NO IMPLEMENTADO" << std::endl;
                        break;
                    case SORT_SHELLSORT:
                        std::cout << "NO IMPLEMENTADO" << std::endl;
                        break;
                    case SORT_INSERCION:
                        std::cout << "NO IMPLEMENTADO" << std::endl;
                        break;
                    case SORT_DISTRIBUCION:
                        std::cout << "NO IMPLEMENTADO" << std::endl;
                        break;
                    case SORT_RADIX:
                        std::cout << "NO IMPLEMENTADO" << std::endl;
                        break;
                    case SORT_MERGESORT:
                        std::cout << "NO IMPLEMENTADO" << std::endl;
                        break;
                    case SORT_MEZCLA_DIRECTA:
                        std::cout << "NO IMPLEMENTADO" << std::endl;
                        break;
                    case SORT_MEZCLA_NATURAL:
                        std::cout << "NO IMPLEMENTADO" << std::endl;
                        break;

                    default:
                        break;
                    }
                    std::cout << "LISTA ORDENADA " << std::endl;
                    getch();

                }
                else
                {
                    std::cout << "NO ORDENADO" << std::endl;
                    getch();
                }
            }

        } while (!salir);
    };

    /////////////////////// DECLARACIÓN DE ENUMERACIONES ////////////////////////
    // No son necesarias, pero hacen que el código sea más legible (no ha sido
    // suficiente), especialmente cuando existen varios submenús.
    /////////////////////////////////////////////////////////////////////////////
    enum eleccionListas { LIBROS = 1, AUTORES, CAMBIAR_LISTA, SALIR };
    enum eleccionOpLibros { INSERTAR_LIBROS = 1, BUSCAR_LIBROS, ELIMINAR_LIBROS, MOSTRAR_LIBROS, GUARDAR_LIBROS, FILTRAR_LIBROS, ORDENAR_LIBROS, SALIR_LIBROS };
    enum eleccionOpAutores { INSERTAR_AUTORES = 1, BUSCAR_AUTORES, ELIMINAR_AUTORES, MOSTRAR_AUTORES, GUARDAR_AUTORES, SALIR_AUTORES };
    enum eleccionCambio { LISTA_SIMPLE = 1, LISTA_DOBLE, LISTA_CIRCULAR, CANCELAR_CAMBIO };

    /////////////////////// FUNCIÓN LAMBDA QUE OPERA SOBRE LA LISTA DE AUTORES ////////////////////////
    // Es sólo un switch
    // Va primero porque las operaciones en libros necesita acceder a las de autores
    //////////////////////////////////////////////////////////////////////////////////////////////////
    auto operarAutores = [&menuOpLibros, &listaLibros, &listaAutores](int eleccion)
        {
            std::string cedula;

            
            std::function<const std::string& (const Autor&)> conseguirIdAutor = [](const Autor& a) -> const std::string&
                {
                    return a.getId();
                };

            switch (eleccion)
            {
            case INSERTAR_AUTORES:
            {
                std::cout << "Ingrese el cedula del autor a insertar (0 para cancelar): ";
                cedula = Validaciones::leerCedula();
                std::cout << std::endl;
                
                if (ILista<Autor>::buscar(*listaAutores, cedula, conseguirIdAutor))
                {
                    std::cout << "El cedula ya existe en la lista";
                    getch();
                    break;
                }

                if (cedula == "0" || cedula == "")
                {
                    std::cout << "No se ha insertado";
                    getch();
                    break;
                }

                if (!Validaciones::validarCedula(cedula))
                {
                    std::cout << "CÉDULA NO VÁLIDA";
                    getch();
                    break;
                }

                std::cout << "Ingrese el nombre a insertar (vacío para cancelar): ";
                std::string nombre = Validaciones::leerPalabra();
                std::cout << std::endl;

                if (nombre.empty())
                {
                    std::cout << "No se ha insertado";
                    getch();
                    break;
                }

                std::cout << "Ingrese el segundo nombre a insertar: ";
                std::string nombre2 = Validaciones::leerPalabra();
                std::cout << std::endl;
                

                std::cout << "Ingrese el apellido a insertar: ";
                std::string apellido = Validaciones::leerPalabra();
                std::cout << std::endl;

                listaAutores->insertarACola(Autor(cedula, nombre, nombre2, apellido));
                break;
            }
            case ELIMINAR_AUTORES:
            {
                std::cout << "Ingrese el cedula del autor a eliminar: ";
                cedula = Validaciones::leerCedula();
                std::cout << std::endl;

                if (!Validaciones::validarCedula(cedula))
                {
                    std::cout << "CÉDULA NO VÁLIDA";
                    getch();
                    break;
                }

                Autor* punteroAutor = punteroAutorEnLista(cedula, listaAutores);
                if (punteroAutor)
                {
                    Nodo<Libro*>* aux = punteroAutor->libros.getCabeza();
                    while (aux != NULL)
                    {
                        Nodo<Libro>* aux2 = listaLibros->getCabeza();
                        while (aux2 != NULL)
                        {
                            if (aux->dato == &(aux2->dato))
                            {
                                listaLibros->eliminar(aux2->getDato());
                                break;
                            }

                            aux2 = aux2->getSiguiente();
                            if (aux2 == listaLibros->getCabeza())    // PARA QUE EL BUCLE FUNCIONE CON LISTAS CIRCULARES
                                aux2 = NULL;

                        }

                        aux = aux->getSiguiente();
                        if (aux == punteroAutor->libros.getCabeza())    // PARA QUE EL BUCLE FUNCIONE CON LISTAS CIRCULARES
                            aux = NULL;
                    }

                    ILista<Autor>::eliminar(*listaAutores, cedula, conseguirIdAutor);
                    std::cout << "El autor con numero " << cedula << " ha sido eliminado de la lista";
                }
                else
                    std::cout << "El autor con numero " << cedula << " NO se encuentra en la lista";

                getch();
                break;
            }
            case MOSTRAR_AUTORES:
                std::cout << std::endl;
                listaAutores->mostrar();
                std::cout << std::endl;
                getch();
                break;
            case GUARDAR_AUTORES:
            {
                guardar(listaLibros, listaAutores, ".", 1);
                break;
            }
            case SALIR_AUTORES:
                std::cout << "Saliendo..." << std::endl;
                break;
            default:
                std::cout << "NO ES UNA OPCIÓN VÁLIDA" << std::endl;
                getch();
                break;
            }
        };

    
    /////////////////////// FUNCIÓN LAMBDA QUE OPERA SOBRE LA LISTA DE LIBROS ////////////////////////
    // Es sólo un switch
    // La lista de autores también está capturada, para la asignación de autores
    //////////////////////////////////////////////////////////////////////////////////////////////////
    
    auto operarLibros = [&](int eleccion)
        {
            std::string id;

            std::function<const std::string& (const Libro&)> conseguirIdLibro = [](const Libro& l) -> const std::string&
                {
                    return l.getId();
                };

            switch (eleccion)
            {
            case INSERTAR_LIBROS:
            {
                std::cout << "Ingrese el id del libro a insertar (0 para cancelar): ";
                id = Validaciones::leerNumero();
                std::cout << std::endl;
                
                if (ILista<Libro>::buscar(*listaLibros, id, conseguirIdLibro))
                {
                    std::cout << "El id ya existe en la lista";
                    getch();
                    break;
                }

                if (id == "0" || id == "")
                {
                    std::cout << "No se ha insertado";
                    getch();
                    break;
                }

                std::cout << "Ingrese el título del libro a insertar (vacío para cancelar): ";
                std::string titulo = Validaciones::leerPalabra();
                std::cout << std::endl;

                if (titulo.empty())
                {
                    std::cout << "No se ha insertado";
                    getch();
                    break;
                }

                std::cout << "Ingrese el año del libro a insertar: ";
                int year = Validaciones::leerInt() - 1900;
                std::cout << std::endl;

                if (year < 0)
                {
                    std::cout << "AÑO NO VALIDO" << std::endl;
                    getch();
                    break;
                }



                
                Autor* punteroAutorAEnlazar = NULL;
                // para comprobar que un autor se ha insertado (la cola ha cambiado)
                Autor* punteroAutorEnCola = &(listaAutores->getCola()->dato);

                std::cout << "Ingrese el cedula del autor del libro (0 para cancelar, vacío para nuevo autor): \033[s";
                
                do
                {
                    std::cout << "\033[u\033[J" << std::endl << std::endl;

                    Nodo<Autor>* aux = listaAutores->getCabeza();
                    while (aux != NULL)
                    {
                        std::cout << aux->getDato() << std::endl;
                        aux = aux->getSiguiente();
                        if (aux == listaAutores->getCabeza())    // PARA QUE EL BUCLE FUNCIONE CON LISTAS CIRCULARES
                            aux = NULL;
                    }

                    std::cout << "\033[u";
                    std::string idAutor = Validaciones::leerCedula();
                    std::cout << "\033[J";

                    std::cout << "\033[J" << std::endl;

                    if (idAutor == "0")
                    {
                        std::cout << "No se ha insertado";
                        getch();
                        return; // sale de la función lambda
                    }

                    if (idAutor.empty())    // si el campo del autor se ha dejado vacío
                    {
                        operarAutores(INSERTAR_AUTORES);    // llama la función para insertar un nuevo autor
                        
                        if (punteroAutorEnCola != &(listaAutores->getCola()->dato)) // comprueba que un nuevo autor sí haya sido insertado
                            punteroAutorAEnlazar = &(listaAutores->getCola()->dato);    // si es así, se lo asigna a punteroAutor
                    }
                    else    // si el campo de autor sí se ha rellenado
                    {
                        if (!Validaciones::validarCedula(idAutor))  // si no es una cédula válida
                        {
                            std::cout << "CÉDULA NO VÁLIDA";
                            getch();
                            return; // sale de la función lambda
                        }


                        Nodo<Autor>* aux = listaAutores->getCabeza();
                        while (aux != NULL) // itera por cada elemento la lista de autores
                        {
                            if (aux->getDato().getId() == idAutor)  // comprueba que el elemento coincide con el campo ingresado
                            {
                                punteroAutorAEnlazar = &(aux->dato);
                                break;  // si lo encuentra deja de iterar
                            }
                            aux = aux->getSiguiente();
                            if (aux == listaAutores->getCabeza())    // PARA QUE EL BUCLE FUNCIONE CON LISTAS CIRCULARES
                                aux = NULL;
                        }
                        // si no lo encuentra (aux ha llegado a null sin encontrar coincidencias)
                        if (aux == NULL)
                        {
                            std::cout << "El id ingresado no se encuentra en la lista, desea añadir un autor? (Y/n): ";
                            char c = getch();
                            std::cout << std::endl;
                            if (c == '\n' || c == '\r' || tolower(c) == 'y')
                            {
                                operarAutores(INSERTAR_AUTORES);    // llama la función para insertar autores

                                if (punteroAutorEnCola != &(listaAutores->getCola()->dato)) // comprueba que un nuevo autor sí haya sido insertado
                                    punteroAutorAEnlazar = &(listaAutores->getCola()->dato);
                            }

                        }
                    }
                } while (punteroAutorAEnlazar == NULL);

                listaLibros->insertarACola(Libro(id, titulo, punteroAutorAEnlazar, Fecha(0, 0, year)));
                punteroAutorAEnlazar->libros.insertarACola(&(listaLibros->getCola()->dato));

                                
                break;
            }
            case BUSCAR_LIBROS:
                std::cout << "Ingrese el numero del libro a buscar: ";
                id = Validaciones::leerNumero();
                std::cout << std::endl;
                
                if (ILista<Libro>::buscar(*listaLibros, id, conseguirIdLibro))
                    std::cout << "El libro con numero " << id << " se encuentra en la lista";
                else
                    std::cout << "El libro con numero " << id << " NO se encuentra en la lista";
                getch();
                break;
            case ELIMINAR_LIBROS:
            {
                std::cout << "Ingrese el numero del libro a eliminar: ";
                id = Validaciones::leerNumero();
                std::cout << std::endl;
                Libro* punteroLibro = punteroLibroEnLista(id, listaLibros);
                if (punteroLibro)
                {
                    punteroLibro->getAutor()->libros.eliminar(punteroLibro);
                    ILista<Libro>::eliminar(*listaLibros, id, conseguirIdLibro);
                    std::cout << "El libro con numero " << id << " ha sido eliminado de la lista";
                }
                else
                    std::cout << "El libro con numero " << id << " NO se encuentra en la lista";

                getch();
                break;
            }
            case MOSTRAR_LIBROS:
                std::cout << std::endl;
                listaLibros->mostrar();
                std::cout << std::endl;
                getch();
                break;
            case GUARDAR_LIBROS:
            {
                guardar(listaLibros, listaAutores, ".", 1);
                break;
            }
            case FILTRAR_LIBROS:
            {
                std::time_t anioInicio, anioFin;
                struct tm anioInicioStruct, anioFinStruct;

                // Solicitar al usuario el rango de años
                std::cout << "Ingrese el año inicial del rango: ";
                anioInicioStruct.tm_year = Validaciones::leerInt() - 1900;
                anioInicioStruct.tm_mon = 0;
                anioInicioStruct.tm_mday = 0;
                anioInicioStruct.tm_hour = 0;
                anioInicioStruct.tm_min = 0;
                anioInicioStruct.tm_sec = 0;
                anioInicio = mktime(&anioInicioStruct);

                std::cout << "Ingrese el año final del rango: ";
                anioFinStruct.tm_year = Validaciones::leerInt() - 1900;
                anioFinStruct.tm_mon = 0;
                anioFinStruct.tm_mday = 0;
                anioFinStruct.tm_hour = 0;
                anioFinStruct.tm_min = 0;
                anioFinStruct.tm_sec = 0;
                anioFin = mktime(&anioFinStruct);

                // Validar el rango
                if (anioInicio > anioFin) {
                    std::cout << "Rango de anios no valido. El anio inicial debe ser menor o igual al anio final." << std::endl;
                    getch();
                    break;
                }

                // Definir la lambda para filtrar los libros

                ListaSimple<Libro> listaRango;

                auto librosEnRango = [&listaRango, &listaLibros](std::time_t anioInicio, std::time_t anioFin)
                    {
                        Nodo<Libro>* aux = listaLibros->getCabeza();
                        while (aux != NULL)
                        {
                            std::time_t tiempoLibro = aux->dato.getFecha().getTiempo();
                            if (tiempoLibro > anioInicio && tiempoLibro < anioFin)
                            {
                                listaRango.insertarACola(aux->dato);
                            }
                            aux = aux->getSiguiente();
                            if (aux == listaLibros->getCabeza())    // PARA QUE EL BUCLE FUNCIONE CON LISTAS CIRCULARES
                                aux = NULL;
                        }
                    };

                librosEnRango(anioInicio, anioFin);
                listaRango.mostrar();

                getch();
                break;
            }
            case ORDENAR_LIBROS:
            {
                enum eleccionOrdenarLibro {ID = 1, TITULO, AUTOR, FECHA, CANCELAR};
                int eleccion = 1;
                char entrada;
                bool salir;

                do
                {
                    system(CLEAR_COMMAND);
                    std::cout << "============ POR MIEMBRO ============" << std::endl;
                    imprimirMenu(menuOrdenarLibros, eleccion);
                    entrada = getch();

                    salir = procesarEntrada(eleccion, entrada, CANCELAR);

                    if (salir && eleccion != CANCELAR)
                    {
                        switch (eleccion)
                        {
                        case ID:
                            elegirMetodo(listaLibros, (std::function<const std::string& (const Libro&)>)[](const Libro& l) -> const std::string& { return l.getId(); });
                            break;
                        case TITULO:
                            elegirMetodo(listaLibros, (std::function<const std::string & (const Libro&)>)[](const Libro& l) -> const std::string& {return l.getTitulo();});
                            break;
                        case AUTOR:
                            elegirMetodo(listaLibros, (std::function<const std::string & (const Libro&)>)[](const Libro& l) -> const std::string& {return l.getAutor()->getId();});
                            break;
                        case FECHA:
                            elegirMetodo(listaLibros, (std::function<const std::time_t & (const Libro&)>)[](const Libro& l) -> const std::time_t& {return l.getFecha().getTiempo();});
                            break;
                        default:
                            break;
                        }
                    }

                } while (!salir);

                break;
            }
            case SALIR_LIBROS:
                std::cout << "Saliendo..." << std::endl;
                break;
            default:
                std::cout << "NO ES UNA OPCIÓN VÁLIDA" << std::endl;
                getch();
                break;
            }
        };

    /*****************************************************************/
    /*███████████████████████████████████████████████████████████████*/
    /*////////////////////██ LÓGICA PRINCIPAL ██/////////////////////*/
    /*███████████████████████████████████████████████████████████████*/
    /*v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v*/

    int listaActual = LISTA_SIMPLE;
    int eleccion = 1;
    int entrada;
    bool salir = false;
    do
    {
        system(CLEAR_COMMAND);
        std::cout << "============ LISTAS ============" << std::endl;
        imprimirMenu(menuListas, eleccion);
        entrada = getch();

        if (procesarEntrada(eleccion, entrada, SALIR))
        {
            bool salir2 = false;
            int eleccion2 = 1;
                switch (eleccion)
                {
                case LIBROS:
                    do
                    {
                        system(CLEAR_COMMAND);
                        std::cout << "============ LISTA LIBROS ============" << std::endl;
                        imprimirMenu(menuOpLibros, eleccion2);
                        entrada = getch();

                        if (procesarEntrada(eleccion2, entrada, SALIR_LIBROS))
                        {
                            operarLibros(eleccion2);

                            if (eleccion2 == GUARDAR_LIBROS)
                                std::filesystem::remove_all("unsaved");

                            if (eleccion2 == INSERTAR_LIBROS || eleccion2 == ELIMINAR_LIBROS)
                                guardar(listaLibros, listaAutores, "unsaved");

                            if (eleccion2 == SALIR_LIBROS)
                                salir2 = true;
                        }

                    } while (!salir2);
                    break;
                case AUTORES:
                    do
                    {
                        system(CLEAR_COMMAND);
                        std::cout << "============ LISTA AUTOR ============" << std::endl;
                        imprimirMenu(menuOpAutores, eleccion2);
                        entrada = getch();

                        if (procesarEntrada(eleccion2, entrada, SALIR_AUTORES))
                        {
                            operarAutores(eleccion2);

                            if (eleccion2 == GUARDAR_AUTORES)
                                std::filesystem::remove_all("unsaved");

                            if (eleccion2 == INSERTAR_AUTORES || eleccion2 == ELIMINAR_AUTORES)
                                guardar(listaLibros, listaAutores, "unsaved");

                            if (eleccion2 == SALIR_AUTORES)
                                salir2 = true;
                        }

                    } while (!salir2);
                    break;
                case CAMBIAR_LISTA:
                    do
                    {
                        system(CLEAR_COMMAND);
                        std::cout << "============ ELEGIR LISTA ============" << std::endl;
                        imprimirMenu(menuCambio, eleccion2);
                        entrada = getch();

                        salir2 = procesarEntrada(eleccion2, entrada, CANCELAR_CAMBIO);

                        if (salir2 && eleccion2 != CANCELAR_CAMBIO)
                        {
                            if (listaActual != eleccion2)
                            {

                                guardar(listaLibros, listaAutores, "temp");
                                delete listaLibros;
                                delete listaAutores;

                                switch (eleccion2)
                                {
                                case LISTA_SIMPLE:
                                    listaLibros = new ListaSimple<Libro>();
                                    listaAutores = new ListaSimple<Autor>();
                                    cargar(listaLibros, listaAutores, "temp");
                                    listaActual = LISTA_SIMPLE;
                                    break;
                                case LISTA_DOBLE:
                                    listaLibros = new ListaDoble<Libro>();
                                    listaAutores = new ListaDoble<Autor>();
                                    cargar(listaLibros, listaAutores, "temp");
                                    listaActual = LISTA_DOBLE;
                                    break;
                                case LISTA_CIRCULAR:
                                    listaLibros = new ListaCircular<Libro>();
                                    listaAutores = new ListaCircular<Autor>();
                                    cargar(listaLibros, listaAutores, "temp");
                                    listaActual = LISTA_CIRCULAR;
                                    break;
                                default:
                                    break;
                                }

                                std::filesystem::remove_all("temp");
                                std::cout << "LISTA CAMBIADA";
                                getch();
                            }
                            else
                            {
                                std::cout << "LA LISTA ACTUAL YA ES DE ESE TIPO";
                                getch();
                            }
                        }

                    } while (!salir2);

                    break;
                case SALIR:
                    salir = true;
                    break;
                default:
                    break;
                }
        }

    } while (!salir);

    return 0;
}

/////////////////////// FUNCIÓN DE CARGADO ////////////////////////
// Toma por defecto el directorio actual (ver declaración)
// Puede elegirse cualquier carpeta en la que se haya usado la
// función guardar (tendrá un archivo autores.txt y libros.txt)
////////////////////////////////////////////////////////////////////
void cargar(ILista<Libro>* ListaLibros, ILista<Autor>* listaAutores, std::string directorio)
{
     // CARGA AUTORES, va primero porque en el archivo de autores no están listados sus libros
    std::ifstream archivoAutores(directorio + '/' + "autores.txt");

    std::string lineaArchivo;

    while (getline(archivoAutores, lineaArchivo))
    {
        std::istringstream ss(lineaArchivo);
        std::string cedula, nombre, nombre2, apellido;

        getline(ss, cedula, ',');
        getline(ss, nombre, ',');
        getline(ss, nombre2, ',');
        getline(ss, apellido);

        listaAutores->insertarACola(Autor(cedula, nombre, nombre2, apellido));
    }

    archivoAutores.close();

    //  CARGA LIBROS en el archivo de libros se encuentran los cedula de sus autores
    std::ifstream archivoLibros(directorio + '/' + "libros.txt");


    while (getline(archivoLibros, lineaArchivo))
    {
        std::istringstream ss(lineaArchivo);
        std::string id, titulo, idAutor, tiempoS;
        Autor* autor;

        getline(ss, id, ',');
        getline(ss, titulo, ',');
        getline(ss, idAutor, ',');
        getline(ss, tiempoS);
        std::time_t tiempo = 0;
        if (!tiempoS.empty())
        {
            tiempo = std::stoll(tiempoS);
        }
        autor = punteroAutorEnLista(idAutor, listaAutores);

        // BUSCA EL PUNTERO DEL AUTOR Y LO ASIGNA AL LIBRO
        ListaLibros->insertarACola(Libro(id, titulo, autor, tiempo));
        // TOMA EL PUNTERO DEL LIBRO INGRESADO MÁS RECIENTEMENTE Y LO AÑADE A LOS LIBROS DEL AUTOR
        autor->libros.insertarACola(&(ListaLibros->getCola()->dato));
    }

    archivoLibros.close();
    // ENLAZA LIBROS Y AUTORES
}

/////////////////////// FUNCIÓN DE GUARDADO ////////////////////////
// Se explica sólo
// Toma por defecto el directorio actual (ver declaración)
// Generará libros.txt y autores.txt en el directorio señalado
// Puede eligirse si crear un backup a partir del archivo guardado
// El backup se genera en una carpera llamada backup, donde existen
// subcarpetas con la fecha y hora de su creación
////////////////////////////////////////////////////////////////////
void guardar(ILista<Libro>* listaLibros, ILista<Autor>* listaAutores, std::string directorio, bool backup)
{
    if (!directorio.empty())
        std::filesystem::create_directories(directorio);

    // GUARDA LIBROS AL ARCHIVO
    std::ofstream archivoLibros(directorio + '/' + "libros.txt");

    Nodo<Libro>* aux = listaLibros->getCabeza();
    while (aux != NULL)
    {
        archivoLibros << aux->getDato().getId() << ","
            << aux->getDato().getTitulo() << ","
            << aux->getDato().getAutor()->getId() << ","
            << aux->getDato().getFecha().getTiempo()
            << std::endl;

        aux = aux->getSiguiente();
        if (aux == listaLibros->getCabeza())    // PARA QUE EL BUCLE FUNCIONE CON LISTAS CIRCULARES
            aux = NULL;
    }
    archivoLibros.close();

    // GUARDA AUTORES AL LIBRO
    std::ofstream archivoAutores(directorio + '/' + "autores.txt");

    Nodo<Autor>* aux2 = listaAutores->getCabeza();

    while (aux2 != NULL)
    {
        archivoAutores << aux2->getDato().getId() << ","
            << aux2->getDato().getNombre() << ","
            << aux2->getDato().getNombre2() << ","
            << aux2->getDato().getApellido()
            << std::endl;

        aux2 = aux2->getSiguiente();
        if (aux2 == listaAutores->getCabeza())    // PARA QUE EL BUCLE FUNCIONE CON LISTAS CIRCULARES
            aux2 = NULL;
    }

    archivoAutores.close();

    if (backup)
    {
        time_t tiempo = time(NULL);
        std::string nombreCarpeta(ctime(&tiempo));
        nombreCarpeta.pop_back();   // elimina el salto de línea
        std::replace(nombreCarpeta.begin(), nombreCarpeta.end(), ':', '.');

        std::string direccionBackup = "backup/" + nombreCarpeta;

        if (!std::filesystem::is_directory(direccionBackup))
        {
            std::filesystem::create_directories(direccionBackup);
            std::filesystem::copy_file(directorio + '/' + "libros.txt", direccionBackup + '/' + "libros.txt");
            std::filesystem::copy_file(directorio + '/' + "autores.txt", direccionBackup + '/' + "autores.txt");
        }
    }
}

Autor* punteroAutorEnLista(std::string id, ILista<Autor>* listaAutores)
{
    Nodo<Autor>* aux = listaAutores->getCabeza();
    while (aux != NULL)
    {
        if (aux->getDato().getId() == id)
            return &(aux->dato);

        aux = aux->getSiguiente();
        if (aux == listaAutores->getCabeza())    // PARA QUE EL BUCLE FUNCIONE CON LISTAS CIRCULARES
            aux = NULL;
    }

    return (Autor*)nullptr;
};

Libro* punteroLibroEnLista(std::string id, ILista<Libro>* listaLibros)
{
    Nodo<Libro>* aux = listaLibros->getCabeza();
    while (aux != NULL)
    {
        if (aux->getDato().getId() == id)
            return &(aux->dato);

        aux = aux->getSiguiente();
        if (aux == listaLibros->getCabeza())    // PARA QUE EL BUCLE FUNCIONE CON LISTAS CIRCULARES
            aux = NULL;
    }

    return (Libro*)nullptr;
};