#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <graphics.h>
using namespace std;

// Clase Cliente (Nodo del BST)
class Cliente {
public:
    int cedula;
    string nombre;
    string zonaEntrega;
    int prioridad;
    Cliente* izquierda;
    Cliente* derecha;
    Cliente(int _cedula, string _nombre, string _zonaEntrega, int _prioridad) 
        : cedula(_cedula), nombre(_nombre), zonaEntrega(_zonaEntrega), prioridad(_prioridad), izquierda(nullptr), derecha(nullptr) {}
};

// Clase para gestionar el BST de clientes
class ClienteBST {
public:
    Cliente* raiz;
    ClienteBST() : raiz(nullptr) {}
    void insertar(int cedula, string nombre, string zonaEntrega, int prioridad) { 
        raiz = insertarRec(raiz, cedula, nombre, zonaEntrega, prioridad); 
    }
    void inOrden() { inOrdenRec(raiz); }

private:
    Cliente* insertarRec(Cliente* nodo, int cedula, string nombre, string zonaEntrega, int prioridad) {
        if (!nodo) return new Cliente(cedula, nombre, zonaEntrega, prioridad);
        if (cedula < nodo->cedula) nodo->izquierda = insertarRec(nodo->izquierda, cedula, nombre, zonaEntrega, prioridad);
        else nodo->derecha = insertarRec(nodo->derecha, cedula, nombre, zonaEntrega, prioridad);
        return nodo;
    }
    void inOrdenRec(Cliente* nodo) {
        if (!nodo) return;
        inOrdenRec(nodo->izquierda);
        cout << "Cliente: " << nodo->cedula << " - " << nodo->nombre << " - Zona: " << nodo->zonaEntrega << " - Prioridad: " << nodo->prioridad << endl;
        inOrdenRec(nodo->derecha);
    }
};

// Clase para gestionar rutas con Backtracking
typedef pair<int, int> Pos;
class Ruta {
public:
    vector<vector<int>> mapa;
    vector<vector<bool>> visitado;
    int filas, columnas;
    Ruta(vector<vector<int>> m) : mapa(m), filas(m.size()), columnas(m[0].size()), visitado(m.size(), vector<bool>(m[0].size(), false)) {}
    bool encontrarRuta(int x, int y) {
        if (x < 0 || y < 0 || x >= filas || y >= columnas || mapa[x][y] == 0 || visitado[x][y])
            return false;
        visitado[x][y] = true;
        if (mapa[x][y] == 9) return true;
        if (encontrarRuta(x + 1, y) || encontrarRuta(x - 1, y) || encontrarRuta(x, y + 1) || encontrarRuta(x, y - 1))
            return true;
        visitado[x][y] = false;
        return false;
    }

    void mostrarMapa() {
        initwindow(800, 600);
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                int x = j * 40, y = i * 40;
                if (mapa[i][j] == 9) setfillstyle(SOLID_FILL, RED);
                else if (mapa[i][j] == 0) setfillstyle(SOLID_FILL, BLACK);
                else setfillstyle(SOLID_FILL, WHITE);
                bar(x, y, x + 40, y + 40);
            }
        }
        delay(5000);
        closegraph();
    }
};

void menu() {
    ClienteBST clientes;
    vector<vector<int>> mapa = {
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 1, 9},
        {1, 0, 0, 0, 0, 0, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 1}
    };
    Ruta ruta(mapa);
    
    int opcion;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Agregar Cliente\n";
        cout << "2. Mostrar Clientes\n";
        cout << "3. Buscar Ruta y Mostrar\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        if (opcion == 1) {
            int cedula, prioridad;
            string nombre, zonaEntrega;
            cout << "Ingrese cedula del cliente: ";
            cin >> cedula;
            cout << "Ingrese nombre del cliente: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Ingrese zona de entrega: ";
            getline(cin, zonaEntrega);
            cout << "Ingrese prioridad (1 = Alta, 3 = Baja): ";
            cin >> prioridad;
            clientes.insertar(cedula, nombre, zonaEntrega, prioridad);
        } else if (opcion == 2) {
            cout << "Lista de clientes:" << endl;
            clientes.inOrden();
        } else if (opcion == 3) {
            if (ruta.encontrarRuta(0, 0)) {
                cout << "Ruta encontrada exitosamente." << endl;
                ruta.mostrarMapa();
            } else {
                cout << "No se encontró una ruta." << endl;
            }
        }
    } while (opcion != 4);
}

int main() {
    menu();
    return 0;
}
