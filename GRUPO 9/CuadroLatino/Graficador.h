#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <graphics.h>
#include <vector>

class Graficador {
public:
    static void dibujarCuadroLatino(const std::vector<std::vector<int>>& matriz);
};

#endif
