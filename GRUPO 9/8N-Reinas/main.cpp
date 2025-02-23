/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      main8Reinas                                              *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              12/02/2025                                               *
 * Fecha de modificacion:          12/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include <iostream>
#include "ChessBoard.h"
#include "Validaciones.h"


int main() {
    while (true) {
        try {
            int size = Validaciones::validarEntero("=== Programa de Resolucion de N-Reinas ===\nIngrese el tamano del tablero de ajedrez (1-8) o 'X' para salir: ");

            if (size == -1) {
                std::cout << "Saliendo del programa." << std::endl;
                break;
            }

            system("clear"); // or "cls" for Windows
            ChessBoard tablero(size);
            if (tablero.resolver()) {
                tablero.mostrarSoluciones();
                tablero.dibujar();
            } else {
                std::cerr << "No se encontro solucion para " << size << " reinas." << std::endl;
            }
        } catch (const std::exception &e) {
            std::cerr << "Excepcion: " << e.what() << std::endl;
        }
    }
    return 0;
}
