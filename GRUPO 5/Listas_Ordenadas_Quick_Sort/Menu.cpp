#include <conio.h>
#include <iostream>
#include <conio.h>
#include "Ayuda.cpp"
#include "Menu.h"

Menu::Menu()
{
    numero_datos = 0;
}

int Menu::get_numero_datos()
{
    return numero_datos;
}

Lista<string> Menu::get_menu()
{
    return menu;
}

void Menu::set_menu(string dato)
{
    menu.insertarPorCabeza(dato);
    numero_datos++;
}

void Menu::print_menu_option(string op, string titulo)
{

    Nodo<string> *actual = menu.get_cola();
    int cont = 1;
    system("cls");
    cout << titulo << endl
         << endl;
    do
    {
        if (op == actual->data)
        {
            cout << ">> " << actual->data << " <<" << endl;
        }
        else
        {
            cout << actual->data << endl;
        }
        actual = actual->anterior;
        cont++;
    } while (actual != menu.get_cola());
}

int Menu::coursor(string titulo)
{
    char c;
    Nodo<string> *actual = menu.get_cola();
    print_menu_option(actual->data, titulo);
    while (((c = getch()) != 13))
    {
        if ((c == 80))
        { // flecha hacia abajo
            actual = actual->anterior;
            print_menu_option(actual->data, titulo);
        }
        else if (c == 72)
        { // Flecha hacia arriba
            actual = actual->siguiente;
            print_menu_option(actual->data, titulo);
        }
        else if (GetAsyncKeyState(VK_F1) & 0x8000)
        {
            Ayuda::mostrarAyuda();

            return -1;
        }
    }

    return search_data(actual->data);
}

string Menu::coursor_string(string titulo){
    char c;
    Nodo<string> *actual = menu.get_cola();
    print_menu_option(actual->data, titulo);
    while (((c = getch()) != 13))
    {
        if ((c == 80))
        { // flecha hacia abajo
            actual = actual->anterior;
            print_menu_option(actual->data, titulo);
        }
        else if (c == 72)
        { // Flecha hacia arriba
            actual = actual->siguiente;
            print_menu_option(actual->data, titulo);
        }
    }

    return actual->data;
}


int Menu::search_data(string option)
{
    Nodo<string> *actual = menu.get_cola();
    int i = 1;

    do
    {
        if (actual->data == option)
        {
            return i;
        }
        i++;
        actual = actual->anterior;
    } while (actual != menu.get_cola());
}