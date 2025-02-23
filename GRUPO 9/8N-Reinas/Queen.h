/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 *                                                                                          *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              12/02/2025                                               *
 * Fecha de modificacion:          12/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#ifndef QUEEN_H
#define QUEEN_H

class Queen {
public:
    Queen(int fila, int col);
    ~Queen(); // Destructor para liberar memoria dinámica
    int obtenerFila() const;
    int obtenerCol() const;

private:
    int* fila; // Puntero a la fila
    int* col;  // Puntero a la columna
};

#endif // QUEEN_H
