#include <iostream>
#include "DemostracionComplejidad.h"
#include <cstdlib>

int main()
{
    try
    {
        DemostracionComplejidad demo;
        demo.demostrar();
        
        // Llamar al script de MATLAB para graficar
        #ifdef _WIN32
            system("matlab -nosplash -nodesktop -r \"cd('C:/Users/User/Desktop/Prueba3P'); run('graficar.m'); pause(20); exit;\"");
        #else
            system("matlab -nosplash -nodesktop -r \"cd('C:/Users/User/Desktop/Prueba3P'); run('graficar.m'); pause(20); exit;\"");
        #endif
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}