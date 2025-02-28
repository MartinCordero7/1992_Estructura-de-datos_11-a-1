
// **********************************************************
// * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
// * ALUMNO:  Steven Egas,Pablo Dominguez, Esteban Santos
// * FECHA CREACION: Viernes,  28 de febrero de 2025
// * FECHA MODIFICACION: Viernes,  28 de febrero de 2025
// * Nivel: TERCERO     NRC: 1992
// **********************************************************



#include <iostream>
#include "CalculoDemo.h"

int main()
{
    try
    {
        DemostracionComplejidad demo;
        demo.demostrar();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    // Call MATLAB script
    int result = std::system("matlab -batch \"run('C:/Users/neste/OneDrive/Documentos/Trabajo/PruebaParcial3/graficar.m')\"");
    if (result != 0)
    {
        std::cerr << "Error: MATLAB script execution failed." << std::endl;
        return 1;
    }

    return 0;
}