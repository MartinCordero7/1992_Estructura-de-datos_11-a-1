/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Dominguez Pablo, Egas Steven, Santos Estaban
 * FECHA CREACION: Domingo,  1 de enero de 2025
 * FECHA MODIFICACION: Domingo,  1 de enero de 2025
 * Asignatura:Estructura de datos
 * Nivel: TERCERO     NRC: 1992
 *************************/

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


