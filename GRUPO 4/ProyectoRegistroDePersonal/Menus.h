#ifndef MENUS_H
#define MENUS_H

class Menus {
private:
    int opcionActual;
    int totalOpciones;

public:
    Menus(int totalOpciones);
    void regresarMenu();
    void mostrarMenu();
    int operarMenu();
};

#endif