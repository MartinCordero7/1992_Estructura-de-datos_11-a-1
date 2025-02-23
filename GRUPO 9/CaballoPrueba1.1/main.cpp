/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      mainCaballo                                              *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              17/02/2025                                               *
 * Fecha de modificacion:          17/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include <iostream>
#include "ChessBoard.h"
#include "Validaciones.h"

int main() {
    while (true) {
        try {
            int fila, col;
            if (Validaciones::validarEntradaCaballo(fila, col)) {
                ChessBoard tablero(8);
                tablero.moverCaballo(fila, col); // Adjust input to 0-based index
                tablero.dibujarCaballo(fila, col); // Adjust input to 0-based index
            } else {
                std::cout << "Saliendo del programa." << std::endl;
                break;
            }
        } catch (const std::exception &e) {
            std::cerr << "Excepcion: " << e.what() << std::endl;
        }
    }
    return 0;
}
