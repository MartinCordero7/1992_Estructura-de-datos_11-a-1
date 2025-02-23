/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              17/02/2025                                               *
 * Fecha de modificacion:          17/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#ifndef CABALLO_H
#define CABALLO_H

#include <vector> // Agregar esta línea

class Caballo {
public:
    Caballo(int fila, int col);
    ~Caballo();

    int obtenerFila() const;
    int obtenerCol() const;
    void mover(int nuevaFila, int nuevaCol);
    std::vector<std::pair<int, int>> obtenerMovimientosPosibles() const;

private:
    int* fila;
    int* col;
};

#endif // CABALLO_H
