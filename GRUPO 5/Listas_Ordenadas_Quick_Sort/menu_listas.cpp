#include "menu_listas.h"

MenuListas::MenuListas(){}

void MenuListas::limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string MenuListas::obtenerCedula() {
    std::string cedula;
    while (true) {
        std::cout << "Ingrese cédula: ";
        std::getline(std::cin >> std::ws, cedula);
        
        if (!cedula.empty()) {
            return cedula;
        }
        std::cout << "Cédula no puede estar vacía. Intente de nuevo.\n";
    }
}

std::string MenuListas::obtenerNombre(const std::string& tipo) {
    std::string nombre;
    while (true) {
        std::cout << "Ingrese " << tipo << ": ";
        std::getline(std::cin >> std::ws, nombre);
        
        if (!nombre.empty()) {
            return nombre;
        }
        std::cout << tipo << " no puede estar vacío. Intente de nuevo.\n";
    }
}

void menuListaSimple() {
    MenuListas menuListas;
    ListaSimple<Persona> lista;
    int opcion;

    do {
        std::cout << "\n--- LISTA SIMPLE ---\n";
        std::cout << "1. Insertar Persona por Cabeza\n";
        std::cout << "2. Insertar Persona por Cola\n";
        std::cout << "3. Eliminar Persona por Cabeza\n";
        std::cout << "4. Eliminar Persona por Cédula\n";
        std::cout << "5. Buscar Persona por Cédula\n";
        std::cout << "6. Mostrar Lista\n";
        std::cout << "7. Eliminar Carácter de los Datos\n";
        std::cout << "8. Reemplazar Carácter en los Datos\n";
        std::cout << "9. Ordenar datos\n";
        std::cout << "10. Regresar\n";
        std::cout << "Ingrese su opción: ";
        std::cin >> opcion;
        menuListas.limpiarBuffer(); // Limpiar buffer después de leer la opción

        switch(opcion) {
            case 1: {
                std::string cedula = menuListas.obtenerCedula();
                std::string nombre = menuListas.obtenerNombre("nombre");
                std::string apellido = menuListas.obtenerNombre("apellido");
                
                Persona persona(cedula, nombre, apellido);
                lista.insertarPorCabeza(persona);
                std::cout << "Persona agregada por cabeza exitosamente.\n";
                break;
            }
            case 2: {
                std::string cedula = menuListas.obtenerCedula();
                std::string nombre = menuListas.obtenerNombre("nombre");
                std::string apellido = menuListas.obtenerNombre("apellido");
                
                Persona persona(cedula, nombre, apellido);
                lista.insertarPorCola(persona);
                std::cout << "Persona agregada por cola exitosamente.\n";
                break;
            }
            case 3: {
                lista.eliminarPorCabeza();
                break;
            }
            case 4: {
                std::string cedula = menuListas.obtenerCedula();
                lista.eliminarPorCedula(cedula);
                break;
            }
            case 5: {
                std::string cedula = menuListas.obtenerCedula();
                lista.buscarPorCedula(cedula);
                break;
            }
            case 6: {
                std::cout << "Contenido de la Lista:\n";
                lista.mostrarLista();
                break;
            }
            case 7: {
                char c;
                std::cout << "Ingrese el carácter a eliminar: ";
                std::cin >> c;
                lista.eliminarCaracter(c);
                std::cout << "Carácter eliminado de todos los datos.\n";
                break;
            }
            case 8: {
                char original, reemplazo;
                std::cout << "Ingrese el carácter original: ";
                std::cin >> original;
                std::cout << "Ingrese el carácter de reemplazo: ";
                std::cin >> reemplazo;
                lista.reemplazarCaracter(original, reemplazo);
                std::cout << "Carácter reemplazado en todos los datos.\n";
                break;
            }
            case 9: {
                int ordenamientoOpcion;
                std::cout << "\n--- ORDENAR LISTA ---\n";
                std::cout << "1. Ordenar por Cédula\n";
                std::cout << "2. Ordenar por Nombre\n";
                std::cout << "3. Ordenar por Apellido\n";
                std::cout << "Ingrese su opción de ordenamiento: ";
                std::cin >> ordenamientoOpcion;
                menuListas.limpiarBuffer();

                switch(ordenamientoOpcion) {
                    case 1: {
                        lista.ordenarPorCedula();
                        std::cout << "Lista ordenada por Cédula.\n";
                        break;
                    }
                    case 2: {
                        lista.ordenarPorNombre();
                        std::cout << "Lista ordenada por Nombre.\n";
                        break;
                    }
                    case 3: {
                        lista.ordenarPorApellido();
                        std::cout << "Lista ordenada por Apellido.\n";
                        break;
                    }
                    default: {
                        std::cout << "Opción de ordenamiento inválida.\n";
                        break;
                    }
                }
                break;
            }
        }
    } while (opcion != 10);
}

void menuListaCircular() {
    MenuListas menuListas;
    ListaCircular<Persona> lista;
    int opcion;
    do {
        std::cout << "\n--- LISTA CIRCULAR ---\n";
        std::cout << "1. Insertar Persona por Cabeza\n";
        std::cout << "2. Insertar Persona por Cola\n";
        std::cout << "3. Eliminar Persona por Cabeza\n";
        std::cout << "4. Eliminar Persona por Cédula\n";
        std::cout << "5. Buscar Persona por Cédula\n";
        std::cout << "6. Mostrar Lista\n";
        std::cout << "7. Eliminar Carácter de los Datos\n";
        std::cout << "8. Reemplazar Carácter en los Datos\n";
        std::cout << "9. Regresar\n";
        std::cout << "Ingrese su opción: ";
        std::cin >> opcion;
        menuListas.limpiarBuffer();

        switch(opcion) {
            case 1: {
                std::string cedula = menuListas.obtenerCedula();
                std::string nombre = menuListas.obtenerNombre("nombre");
                std::string apellido = menuListas.obtenerNombre("apellido");
                Persona persona(cedula, nombre, apellido);
                lista.insertarPorCabeza(persona);
                std::cout << "Persona agregada por cabeza exitosamente.\n";
                break;
            }
            case 2: {
                std::string cedula = menuListas.obtenerCedula();
                std::string nombre = menuListas.obtenerNombre("nombre");
                std::string apellido = menuListas.obtenerNombre("apellido");
                Persona persona(cedula, nombre, apellido);
                lista.insertarPorCola(persona);
                std::cout << "Persona agregada por cola exitosamente.\n";
                break;
            }
            case 3: {
                lista.eliminarPorCabeza();
                break;
            }
            case 4: {
                std::string cedula = menuListas.obtenerCedula();
                lista.eliminarPorCedula(cedula);
                break;
            }
            case 5: {
                std::string cedula = menuListas.obtenerCedula();
                lista.buscarPorCedula(cedula);
                break;
            }
            case 6: {
                std::cout << "Contenido de la Lista:\n";
                lista.mostrarLista();
                break;
            }
            case 7: {
                char c;
                std::cout << "Ingrese el carácter a eliminar: ";
                std::cin >> c;
                lista.eliminarCaracter(c);
                std::cout << "Carácter eliminado de todos los datos.\n";
                break;
            }
            case 8: {
                char original, reemplazo;
                std::cout << "Ingrese el carácter original: ";
                std::cin >> original;
                std::cout << "Ingrese el carácter de reemplazo: ";
                std::cin >> reemplazo;
                lista.reemplazarCaracter(original, reemplazo);
                std::cout << "Carácter reemplazado en todos los datos.\n";
                break;
            }
        }
    } while (opcion != 9);
}

void menuListaDoble() {
    MenuListas menuListas;
    ListaDoble<Persona> lista;
    int opcion;
    do {
        std::cout << "\n--- LISTA DOBLE ---\n";
        std::cout << "1. Insertar Persona por Cabeza\n";
        std::cout << "2. Insertar Persona por Cola\n";
        std::cout << "3. Eliminar Persona por Cabeza\n";
        std::cout << "4. Eliminar Persona por Cédula\n";
        std::cout << "5. Buscar Persona por Cédula\n";
        std::cout << "6. Mostrar Lista\n";
        std::cout << "7. Eliminar Carácter de los Datos\n";
        std::cout << "8. Reemplazar Carácter en los Datos\n";
        std::cout << "9. Regresar\n";
        std::cout << "Ingrese su opción: ";
        std::cin >> opcion;
        menuListas.limpiarBuffer();

        switch(opcion) {
            case 1: {
                std::string cedula = menuListas.obtenerCedula();
                std::string nombre = menuListas.obtenerNombre("nombre");
                std::string apellido = menuListas.obtenerNombre("apellido");
                Persona persona(cedula, nombre, apellido);
                lista.insertarPorCabeza(persona);
                std::cout << "Persona agregada por cabeza exitosamente.\n";
                break;
            }
            case 2: {
                std::string cedula = menuListas.obtenerCedula();
                std::string nombre = menuListas.obtenerNombre("nombre");
                std::string apellido = menuListas.obtenerNombre("apellido");
                Persona persona(cedula, nombre, apellido);
                lista.insertarPorCola(persona);
                std::cout << "Persona agregada por cola exitosamente.\n";
                break;
            }
            case 3: {
                lista.eliminarPorCabeza();
                break;
            }
            case 4: {
                std::string cedula = menuListas.obtenerCedula();
                lista.eliminarPorCedula(cedula);
                break;
            }
            case 5: {
                std::string cedula = menuListas.obtenerCedula();
                lista.buscarPorCedula(cedula);
                break;
            }
            case 6: {
                std::cout << "Contenido de la Lista:\n";
                lista.mostrarLista();
                break;
            }
            case 7: {
                char c;
                std::cout << "Ingrese el carácter a eliminar: ";
                std::cin >> c;
                lista.eliminarCaracter(c);
                std::cout << "Carácter eliminado de todos los datos.\n";
                break;
            }
            case 8: {
                char original, reemplazo;
                std::cout << "Ingrese el carácter original: ";
                std::cin >> original;
                std::cout << "Ingrese el carácter de reemplazo: ";
                std::cin >> reemplazo;
                lista.reemplazarCaracter(original, reemplazo);
                std::cout << "Carácter reemplazado en todos los datos.\n";
                break;
            }
        }
    } while (opcion != 9);
}


void MenuListas::menuPrincipal() {
    int opcion;

    do {
        std::cout << "\n--- MENÚ PRINCIPAL ---\n";
        std::cout << "1. Lista Simple\n";
        std::cout << "2. Lista Circular\n";
        std::cout << "3. Lista Doble\n";
        std::cout << "4. Salir\n";
        std::cout << "Ingrese su opción: ";
        std::cin >> opcion;
        limpiarBuffer();

        switch(opcion) {
            case 1: menuListaSimple(); break;
            case 2: menuListaCircular(); break;
            case 3: menuListaDoble(); break;
        }
    } while (opcion != 4);
}