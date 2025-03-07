#ifndef MENUSEMPLEADO_H
#define MENUSEMPLEADO_H

class MenuEmpleado {
private:
    int opcionActualEmpleado;
    int totalOpcionesEmpleado;

public:
    MenuEmpleado(int totalOpcionesEmpleado);
    void regresarMenuEmpleado();
    void mostrarMenuEmpleado();
    int operarMenuEmpleado();
};

#endif
