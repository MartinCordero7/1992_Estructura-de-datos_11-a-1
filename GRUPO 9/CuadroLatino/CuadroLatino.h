#ifndef CUADROLATINO_H
#define CUADROLATINO_H

#include <vector>

class CuadroLatino {
private:
    int n;
    std::vector<std::vector<int>> matriz;

public:
    CuadroLatino(int size);
    void generar();
    std::vector<std::vector<int>> getMatriz() const;
};

#endif
