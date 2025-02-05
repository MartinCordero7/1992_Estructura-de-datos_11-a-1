#include "funciones.h"
#include "Validaciones.h"
#include <iostream>
#include <fstream>
#include <graphics.h>

using namespace std;

void ingresarNumeros(BTree *&arbol)
{
    try
    {
        int grado = 2; // Hardcoded degree
        string input;
        bool numeroIngresado = false; // Flag to check if at least one number is entered

        cout << "Arbol B - Grado Maximo 4" << endl; // New message

        if (arbol != nullptr)
        {
            delete arbol;
        }
        arbol = new BTree(grado);

        cout << "Ingrese un numero (n para finalizar): ";

        while (true)
        {
            input = Validaciones::leerSoloNumerosONLimitado(4);
            if (input == "n" || input == "N")
            {
                if (!numeroIngresado)
                {
                    Validaciones::mostrarMensajeError("Debe ingresar al menos un numero.");
                    cout << "Ingrese un numero (n para finalizar): ";
                    continue;
                }
                break;
            }

            try
            {
                int numero = stoi(input);
                if (numero >= 0 && numero <= 9999)
                {
                    arbol->insert(numero);
                    graficarArbol(arbol);   // Update the tree graphically after each insertion
                    numeroIngresado = true; // Set flag to true when a number is entered
                }
                else
                {
                    Validaciones::mostrarMensajeError("Numero invalido. Intente de nuevo.");
                }
            }
            catch (const std::invalid_argument &)
            {
                Validaciones::mostrarMensajeError("Entrada no valida. Intente de nuevo.");
            }
            cout << "Ingrese un numero (n para finalizar): ";
        }

        cout << "Recorrido del arbol B:\n";
        arbol->traverse();
        arbol->saveToFile("datos.txt");

        cout << "\nNumeros ordenados guardados en datos.txt, presione enter para finalizar.";
        cin.ignore();
        cin.get();
    }
    catch (const std::exception &e)
    {
        Validaciones::mostrarMensajeError("Exception: " + string(e.what()));
    }
}

void buscarNumero(BTree *arbol)
{
    try
    {
        if (arbol == nullptr)
        {
            cout << "Primero ingrese numeros en el arbol.\n";
            cin.ignore();
            cin.get();
            return;
        }

        cout << "Ingrese el numero a buscar: ";
        string input = Validaciones::leerSoloNumerosONLimitado(4);

        if (!input.empty() && input != "n" && input != "N")
        {
            try
            {
                int numero = stoi(input);
                if (arbol->search(numero))
                {
                    cout << "El numero " << numero << " fue encontrado en el arbol.\n";
                }
                else
                {
                    cout << "El numero " << numero << " no se encuentra en el arbol.\n";
                }
            }
            catch (const std::invalid_argument &)
            {
                Validaciones::mostrarMensajeError("Entrada no valida. Intente de nuevo.");
            }
        }
    }
    catch (const std::exception &e)
    {
        Validaciones::mostrarMensajeError("Exception: " + string(e.what()));
    }
}

void eliminarNumero(BTree *&arbol)
{
    try
    {
        if (arbol == nullptr)
        {
            cout << "Primero ingrese numeros en el arbol.\n";
            cin.ignore();
            cin.get();
            return;
        }

        cout << "Ingrese el numero a eliminar: ";
        string input = Validaciones::leerSoloNumerosONLimitado(4);

        if (!input.empty() && input != "n" && input != "N")
        {
            try
            {
                int numero = stoi(input);
                arbol->remove(numero);
                cout << "Si el numero existia, ha sido eliminado.\n";
                actualizarArbol(arbol); // Update the tree graphically after deletion
            }
            catch (const std::invalid_argument &)
            {
                Validaciones::mostrarMensajeError("Entrada no valida. Intente de nuevo.");
            }
        }
    }
    catch (const std::exception &e)
    {
        Validaciones::mostrarMensajeError("Exception: " + string(e.what()));
    }
}

void mostrarNumerosOrdenados(BTree *arbol)
{
    try
    {
        if (arbol == nullptr)
        {
            cout << "Primero ingrese numeros en el arbol.\n";
        }
        else
        {
            cout << "Numeros ordenados:\n";
            arbol->traverse();
        }
        cout << "\nPresione enter para regresar al menu.";
        cin.ignore();
        cin.get();
    }
    catch (const std::exception &e)
    {
        cout << "Exception: " << e.what() << endl;
    }
}

void mostrarArbolConsola(BTree *arbol)
{
    try
    {
        if (arbol == nullptr)
        {
            cout << "Primero ingrese numeros en el arbol.\n";
        }
        else
        {
            cout << "\nArbol B en consola:\n";
            arbol->imprimirArbol();
        }
    }
    catch (const std::exception &e)
    {
        cout << "Exception: " << e.what() << endl;
    }
}

void mostrarArbolDetallado(BTree *arbol)
{
    try
    {
        if (arbol == nullptr)
        {
            cout << "Primero ingrese numeros en el arbol.\n";
        }
        else
        {
            cout << "\nArbol B detallado en consola:\n";
            arbol->imprimirArbolDetallado();
        }
    }
    catch (const std::exception &e)
    {
        cout << "Exception: " << e.what() << endl;
    }
}

void mostrarNumerosEnOrdenInfijo(BTree *arbol)
{
    try
    {
        if (arbol == nullptr)
        {
            cout << "Primero ingrese numeros en el arbol.\n";
        }
        else
        {
            cout << "Numeros en orden infijo:\n";
            inOrderTraversal(arbol->getRoot());
        }
    }
    catch (const std::exception &e)
    {
        cout << "Exception: " << e.what() << endl;
    }
}

void inOrderTraversal(BTreeNode *node)
{
    try
    {
        if (node == nullptr)
            return;

        int i;
        for (i = 0; i < node->keys.size(); i++)
        {
            if (!node->leaf)
            {
                inOrderTraversal(node->children[i]);
            }
            cout << node->keys[i] << " ";
        }
        if (!node->leaf)
        {
            inOrderTraversal(node->children[i]);
        }
    }
    catch (const std::exception &e)
    {
        cout << "Exception: " << e.what() << endl;
    }
}

void probarGraphics()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");
    circle(200, 200, 150);
    getch();
    closegraph();
}

void graficarArbol(BTree* arbol) {
    static bool isGraphInitialized = false;
    static int gd = DETECT, gm;

    if (!isGraphInitialized) {
        initgraph(&gd, &gm, (char*)"");
        isGraphInitialized = true;
    }

    if (arbol == nullptr || arbol->getRoot() == nullptr) {
        std::cout << "El arbol esta vacio.\n";
        return;
    }

    int screenWidth = getmaxx();
    int screenHeight = getmaxy();

    cleardevice();
    setcolor(WHITE);
    setbkcolor(BLACK);

    std::function<void(BTreeNode*, int, int, int, float)> drawNode = [&](BTreeNode* node, int x, int y, int offset, float scaleFactor) {
        if (!node) return;

        int nodeHeight = 20 * scaleFactor;
        int padding = 5 * scaleFactor;
        int keyWidth = 20 * scaleFactor;
        int nodeWidth = node->keys.size() * keyWidth + (node->keys.size() - 1) * padding;
        int childOffset = offset / 2;

        // Adjust offset to ensure nodes do not overlap and fit within the screen
        if (childOffset < keyWidth + padding) {
            childOffset = keyWidth + padding;
        }

        // Ensure nodes do not overlap by adjusting the offset based on the screen width
        if (childOffset * node->children.size() > screenWidth) {
            childOffset = screenWidth / (node->children.size() + 1);
        }

        // Dibujar el rectángulo del nodo
        rectangle(x - nodeWidth / 2, y - nodeHeight / 2, x + nodeWidth / 2, y + nodeHeight / 2);
        
        // Dibujar separaciones internas
        for (int i = 1; i < node->keys.size(); ++i) {
            int sepX = x - nodeWidth / 2 + i * (keyWidth + padding) - padding / 2;
            line(sepX, y - nodeHeight / 2, sepX, y + nodeHeight / 2);
        }

        // Dibujar las claves dentro del nodo
        int textX = x - nodeWidth / 2 + padding / 2;
        for (int key : node->keys) {
            char buffer[10];
            sprintf(buffer, "%d", key);
            outtextxy(textX + keyWidth / 4, y - nodeHeight / 4, buffer);
            textX += keyWidth + padding;
        }

        // Dibujar conexiones con los hijos
        int childX = x - (offset * (node->children.size() - 1)) / 2;
        for (BTreeNode* child : node->children) {
            if (child) {
                line(x, y + nodeHeight / 2, childX, y + nodeHeight + 30 * scaleFactor - nodeHeight / 2);
                drawNode(child, childX, y + nodeHeight + 30 * scaleFactor, childOffset, scaleFactor * 0.9f);
                childX += offset;
            }
        }
    };

    int initialOffset = screenWidth / 3;
    drawNode(arbol->getRoot(), screenWidth / 2, 50, initialOffset, 1.0f);
    delay(500); // Pequeño retraso para actualizar la gráfica
}

void actualizarArbol(BTree *arbol)
{
    graficarArbol(arbol);
}