/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 *                                                                                          *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              17/02/2025                                               *
 * Fecha de modificacion:          17/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#ifndef HORSE_H
#define HORSE_H

class Horse {
public:
    Horse(int fila, int col);
    ~Horse(); // Destructor para liberar memoria dinámica
    int obtenerFila() const;
    int obtenerCol() const;

private:
    int* fila; // Puntero a la fila
    int* col;  // Puntero a la columna
};

#endif // HORSE_H
