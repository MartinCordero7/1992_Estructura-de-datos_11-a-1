#include "ArbolRadix.h"
#include "validaciones.h"
#include <iostream>
#include <conio.h>
#include <graphics.h>

ArbolRadix::ArbolRadix() : raiz(new Nodo()) {}

ArbolRadix::~ArbolRadix()
{
    destruirRecursivo(raiz);
}

void ArbolRadix::destruirRecursivo(Nodo *nodo)
{
    if (nodo != nullptr)
    {
        for (auto &hijo : nodo->hijos)
        {
            destruirRecursivo(hijo.second);
        }
        delete nodo->empleado;
        delete nodo;
    }
}

void ArbolRadix::insertarEmpleado(Empleado *empleado)
{
    Nodo *actual = raiz;
    std::string cedula = empleado->getCedula();
    for (char c : cedula)
    {
        if (actual->hijos.find(c) == actual->hijos.end())
        {
            actual->hijos[c] = new Nodo();
        }
        actual = actual->hijos[c];
    }
    actual->empleado = empleado;
}

Empleado *ArbolRadix::buscarPorCedula(const std::string &cedula)
{
    Nodo *actual = raiz;
    for (char c : cedula)
    {
        if (actual->hijos.find(c) == actual->hijos.end())
        {
            return nullptr;
        }
        actual = actual->hijos[c];
    }
    return actual->empleado;
}

void ArbolRadix::imprimirArbol() const
{
    imprimirArbolRecursivo(raiz, "");
}

void ArbolRadix::imprimirArbolRecursivo(Nodo *nodo, std::string prefijo) const
{
    if (nodo != nullptr)
    {
        if (nodo->empleado != nullptr)
        {
            std::cout << "\nCedula: " << nodo->empleado->getCedula()
                      << ", Nombre: " << nodo->empleado->getNombre()
                      << ", Apellido: " << nodo->empleado->getApellido()
                      << ", Cargo: " << nodo->empleado->getCargo()
                      << ", Sueldo: " << nodo->empleado->getSalario()
                      << ", Fecha de nacimiento: " << nodo->empleado->getFechaNacimiento().toString() << std::endl;
        }
        for (auto &hijo : nodo->hijos)
        {
            imprimirArbolRecursivo(hijo.second, prefijo + hijo.first);
        }
    }
}

void ArbolRadix::buscarYMostrarEmpleadoPorCedula()
{
    Validacion miValidador;
    std::string cedulaBuscada = miValidador.ingresoCedula();
    Empleado *empleadoEncontrado = buscarPorCedula(cedulaBuscada);

    if (empleadoEncontrado)
    {
        std::cout << "||||||||||||||||||||||||||||||||||||" << std::endl;
        std::cout << "Empleado encontrado:" << std::endl;
        std::cout << "Cedula: " << empleadoEncontrado->getCedula() << std::endl;
        std::cout << "Nombre: " << empleadoEncontrado->getNombre() << std::endl;
        std::cout << "Apellido: " << empleadoEncontrado->getApellido() << std::endl;
        Fecha fechaNacimiento = empleadoEncontrado->getFechaNacimiento();
        std::cout << "Fecha de nacimiento: " << fechaNacimiento.getDia() << "/" << fechaNacimiento.getMes() << "/" << fechaNacimiento.getAnio() << std::endl;
        std::cout << "Cargo: " << empleadoEncontrado->getCargo() << std::endl;
        std::cout << "Salario: " << empleadoEncontrado->getSalario() << std::endl;
        std::cout << "||||||||||||||||||||||||||||||||||||" << std::endl;
    }
    else
    {
        std::cout << "Empleado no encontrado." << std::endl;
    }
}

std::string ArbolRadix::validarExistenciaCedula(const std::string &cedula)
{
    Empleado *empleadoEncontrado = buscarPorCedula(cedula);
    if (empleadoEncontrado)
    {
        std::cout << "La cedula ya existe en el arbol. Ingrese una nueva cedula: ";
        std::string nuevaCedula;
        std::cin >> nuevaCedula;
        return validarExistenciaCedula(nuevaCedula);
    }
    return cedula;
}

ArbolRadix::Nodo *ArbolRadix::getRaiz() const
{
    return raiz;
}

void ArbolRadix::graficarArbol(const std::string &filename) const
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int contador = 0;
    int x = getmaxx() / 2;
    int y = 50;
    graficarArbolRecursivo(raiz, x, y, contador);

    getch();
    closegraph();
}

void ArbolRadix::graficarArbolRecursivo(Nodo *nodo, int x, int y, int &contador) const
{
    if (nodo != nullptr)
    {
        if (nodo->empleado != nullptr)
        {
            circle(x, y, 20);
            outtextxy(x - 10, y - 10, const_cast<char*>(nodo->empleado->getNombre().c_str()));
        }

        int desplazamiento = 50 / (contador + 1);
        int childX = x - desplazamiento * 20;
        int childY = y + 50;

        for (auto &hijo : nodo->hijos)
        {
            int nuevoContador = contador + 1;
            line(x, y, childX, childY);
            graficarArbolRecursivo(hijo.second, childX, childY, nuevoContador);
            childX += desplazamiento * 40;
        }
    }
}