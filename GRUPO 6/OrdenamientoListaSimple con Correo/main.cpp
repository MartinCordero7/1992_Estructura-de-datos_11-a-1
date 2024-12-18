/*******************************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                                  *
 * Proposito:                      Programa Principal                                                  *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz                    *
 * Fecha de creacion:              17/12/2024                                                          *
 * Fecha de modificacion:          18/12/2024                                                          *
 * Materia:                        Estructura de datos                                                 *
 * NRC :                           1992                                                                *
 *******************************************************************************************************/
#include "ListaSimple.cpp"
#include "Menu.cpp"

int main() {
    // Configurar la consola para usar UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // Verifica y crea la carpeta de backups si no existe
    BackupManager::crearCarpetaSiNoExiste("backup");

    ListaSimple lista;
    // Cargar las personas desde el archivo al iniciar
    try {
        lista.cargarPersonasDesdeArchivo();
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error al cargar las personas desde el archivo: " << e.what() << std::endl;
        return 1;
    }

    mostrarMenu(lista);
    return 0;
}
