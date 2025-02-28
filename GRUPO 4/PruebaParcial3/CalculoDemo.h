// **********************************************************
// * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
// * ALUMNO:  Steven Egas,Pablo Dominguez, Esteban Santos
// * FECHA CREACION: Viernes,  28 de febrero de 2025
// * FECHA MODIFICACION: Viernes,  28 de febrero de 2025
// * Nivel: TERCERO     NRC: 1992
// **********************************************************


#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <regex>
#include <conio.h>
#include "Calculo.h"

class DemostracionComplejidad
{
private:
    struct ParametrosDemo
    {
        double inicio;
        double fin;
        double paso;
    };

    // Validar la entrada de datos
    bool validarEntrada(double &valor, const std::string &mensaje)
    {
        std::string input;
        char ch;
        std::regex pattern("^(?!0$)([0-9]{1,4})(\\.[0-9]{0,5})?$"); // Allow up to 4 digits before and up to 5 digits after the decimal point, no single 0

        while (true)
        {
            std::cout << mensaje;
            input.clear();

            while (true)
            {
                ch = _getch();
                if (ch == '\r') // Enter key
                {
                    break;
                }
                else if (ch == '\b') // Backspace key
                {
                    if (!input.empty())
                    {
                        std::cout << "\b \b";
                        input.pop_back();
                    }
                }
                else if ((isdigit(ch) || ch == '.') && input.size() < 10) // Only digits, decimal point, and up to 10 characters
                {
                    std::cout << ch;
                    input += ch;
                }
            }
            std::cout << std::endl;

            // Check if input matches the pattern
            if (!std::regex_match(input, pattern))
            {
                std::cout << "Entrada no valida. Intentalo de nuevo.\n";
                continue;
            }

            // Convert input to double
            try
            {
                valor = std::stod(input);
            }
            catch (const std::invalid_argument &)
            {
                std::cout << "Entrada no valida. Intentalo de nuevo.\n";
                continue;
            }

            break;
        }

        return true;
    }

    // Obtener parámetros del usuario
    ParametrosDemo obtenerParametros()
    {
        ParametrosDemo params;
        bool entradaValida = false;

        do
        {
            std::cout << "\nIngrese los valores para la demonstracion:\n";

            // Valor inicial
            if (!validarEntrada(params.inicio, "Valor inicial(mayor que 0): ") ||
                params.inicio <= 0)
            {
                std::cout << "Error: El valor inicial debe ser mayor que 0.\n";
                continue;
            }

            // Valor final
            if (!validarEntrada(params.fin, "Valor final(mayor que el valor inicial): ") ||
                params.fin <= params.inicio)
            {
                std::cout << "Error: El valor final debe ser mayor que el inicial.\n";
                continue;
            }

            // Paso
            if (!validarEntrada(params.paso, "Intervalo: ") ||
                params.paso <= 0 || params.paso > (params.fin - params.inicio))
            {
                std::cout << "Error: El intervalo debe ser positivo y menor que el rango.\n";
                continue;
            }

            entradaValida = true;
        } while (!entradaValida);

        return params;
    }

    // Función para guardar los datos en un archivo .txt
    void guardarDatos(const ParametrosDemo &params, const std::string &nombreArchivo)
    {
        std::ofstream archivo(nombreArchivo); // Abrir archivo en modo escritura
        if (!archivo.is_open())
        {
            throw std::runtime_error("No se pudo abrir el archivo para guardar los datos.");
        }

        // Escribir encabezado en el archivo
        archivo << "n,e*log(n),n,e*log(n) <= n\n";

        // Escribir los datos en el archivo
        for (double n = params.inicio; n <= params.fin; n += params.paso)
        {
            double eLogN = Matematicas::calcularELogN(n);
            bool cumpleRelacion = eLogN <= n;

            archivo << std::fixed << std::setprecision(4)
                    << n << ","
                    << eLogN << ","
                    << n << ","
                    << (cumpleRelacion ? "Si" : "No") << "\n";
        }

        archivo.close(); // Cerrar el archivo
        std::cout << "Datos guardados en " << nombreArchivo << std::endl;
    }

public:
    void demostrar()
    {
        ParametrosDemo params = obtenerParametros();

        std::cout << "\nDemostracion numerica de e*log(n) ∈ O(n):" << std::endl;
        std::cout << "Verifica que e*log(n) ≤ n para n ≥ n0" << std::endl;
        std::cout << std::string(85, '-') << std::endl;

        // Encabezado de tabla
        std::cout << std::setw(10) << "n"
                  << std::setw(20) << "e*log(n)"
                  << std::setw(20) << "n"
                  << std::setw(25) << "e*log(n) <= n" << std::endl;
        std::cout << std::string(85, '-') << std::endl;

        // Calcular y mostrar resultados
        for (double n = params.inicio; n <= params.fin; n += params.paso)
        {
            double eLogN = Matematicas::calcularELogN(n);
            bool cumpleRelacion = eLogN <= n;

            std::cout << std::fixed << std::setprecision(4)
                      << std::setw(10) << n
                      << std::setw(20) << eLogN
                      << std::setw(20) << n
                      << std::setw(25) << (cumpleRelacion ? "Si" : "No") << std::endl;
        }

        // Guardar datos en un archivo .txt
        guardarDatos(params, "datos_demostracion.txt");

        // Conclusión
        std::cout << std::string(85, '-') << std::endl;
        std::cout << "Conclusion: Se verifica que e*log(n) pertenece a O(n)\n";
        std::cout << "ya que e*log(n) <= n para todo n >= n0.\n";
    }
};