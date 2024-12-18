#include "lista.cpp"

class Menu{
private:
    Lista<string> menu;
    int numero_datos;
public:
    Menu();
    
    Lista<string> get_menu();
    void set_menu(string);

    int get_numero_datos();
    void set_numero_datos();
    
    void print_menu_option(string, string);
    int search_data(string);
    int coursor(string);
    string coursor_string(string titulo);
};
