/***********************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                  *
 * Proposito:                      Lista Simple                        *
 * Autor:                          Esteban Santos                      *
 * Fecha de creacion:              20/11/2024                          *
 * Fecha de modificacion:          10/12/2024                          *
 * Materia:                        Estructura de datos                 *
 * NRC :                           1992                                *
 ***********************************************************************/
#include <iostream>
#include <conio.h>

using namespace std;

template<typename T>
class Validation
{
private:
    T data;
public:
    Validation();
    
    T enter_a_number(char *data_type);
    T enter_a_char_or_string_with_may(int data_size);
    T enter_a_char_or_string(int data_size);
    T data_convertion_to_number(char *cad, char *data_type);
    T primera_letra_a_mayuscula();
    T enter_a_string_as_num(int data_size);
    T enter_only_a_char();
};


