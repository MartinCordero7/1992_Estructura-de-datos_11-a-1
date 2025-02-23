/***********************************************************************
 * Module:  main.cpp
 * Author:  Erika Guayanay,Jerson Llumiquinga M, Maycol Celi.
 * Purpose: Cuadro Latino con grafico.
 * University: Universidad de las Fuerzas Armadas - ESPE
 ***********************************************************************/
#include <iostream>
#include <windows.h> // Necesario para SetConsoleOutputCP y SetConsoleCP
#include "CuadroLatino.h"
#include "Graficador.h"
#include "Validaciones.h"

int main() {
    // Establecer la configuración regional a UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    while (true) {
        std::cout << "=============================\n\tCuadro Latino\n=============================\nIngrese el tamaño del cuadro latino (1-14) o 'X' para salir: ";
        std::string input = Validaciones::leerSoloNumerosOX();

        if (input == "X" || input == "x") {
            std::cout << "Saliendo del programa." << std::endl;
            break;
        }

        try {
            int n = std::stoi(input);
            Validaciones::validarEntero(n);

            CuadroLatino cuadro(n);
            cuadro.generar();

            std::cout << "Cuadro Latino generado:\n";
            for (const auto& fila : cuadro.getMatriz()) {
                for (int num : fila) {
                    std::cout << num << " ";
                }
                std::cout << std::endl;
            }

            Graficador::dibujarCuadroLatino(cuadro.getMatriz());

            // Limpiar la consola después de cada gráfico
            system("cls");
            
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
