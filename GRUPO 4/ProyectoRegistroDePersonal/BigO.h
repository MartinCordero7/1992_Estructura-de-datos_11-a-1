#ifndef BIGO_H
#define BIGO_H

class BigO {
private:
    int opcionActualBigO;
    int totalOpcionesBigO;

public:
    BigO(int totalOpcionesBigO);
    void regresarMenuBigO();
    void mostrarMenuBigO();
    int operarMenuBigO();
};

#endif