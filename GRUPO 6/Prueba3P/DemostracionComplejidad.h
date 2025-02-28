#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include "Matematicas.h"

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
        std::cout << mensaje;
        if (!(std::cin >> valor))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada no valida. Intentalo de nuevo.\n";
            return false;
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
            std::cout << "\nIngrese los parametros para la demostracion:\n";

            // Valor inicial
            if (!validarEntrada(params.inicio, "Valor inicial (n > 0): ") ||
                params.inicio <= 0)
            {
                std::cout << "Error: El valor inicial debe ser mayor que 0.\n";
                continue;
            }

            // Valor final
            if (!validarEntrada(params.fin, "Valor final: ") ||
                params.fin <= params.inicio)
            {
                std::cout << "Error: El valor final debe ser mayor que el inicial.\n";
                continue;
            }

            // Paso
            if (!validarEntrada(params.paso, "Paso: ") ||
                params.paso <= 0 || params.paso > (params.fin - params.inicio))
            {
                std::cout << "Error: El paso debe ser positivo y menor que el rango.\n";
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

        std::cout << "\nDemostracion numerica de e*log(n) E O(n):" << std::endl;
        std::cout << "Verifica que e*log(n) <= n para n >= n0" << std::endl;
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

        // Conclusión
        std::cout << std::string(85, '-') << std::endl;
        // Guardar datos en un archivo .txt
        guardarDatos(params, "datos.txt");
        std::cout << "Conclusion: Se verifica que e*log(n) pertenece a O(n)\n";
        std::cout << "ya que e*log(n) <= n para todo n >= n0.\n";
    }
};