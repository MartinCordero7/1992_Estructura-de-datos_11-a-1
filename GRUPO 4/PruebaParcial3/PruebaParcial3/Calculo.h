// **********************************************************
// * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
// * ALUMNO:  Steven Egas,Pablo Dominguez, Esteban Santos
// * FECHA CREACION: Viernes,  28 de febrero de 2025
// * FECHA MODIFICACION: Viernes,  28 de febrero de 2025
// * Nivel: TERCERO     NRC: 1992
// **********************************************************


#pragma once
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath> // Para usar log (logaritmo natural)

class Matematicas
{
private:
    static const double E; // e ≈ 2.71828...

public:
    static double obtenerE()
    {
        return E;
    }

    // Función para calcular e * log(n)
    static double calcularELogN(double n)
{
    if (n <= 0)
        throw std::invalid_argument("n debe ser mayor que 0.");
    return E * log(n); // e * log(n)
}
};

// Definición de la constante E
const double Matematicas::E = 2.71828182845904523536;