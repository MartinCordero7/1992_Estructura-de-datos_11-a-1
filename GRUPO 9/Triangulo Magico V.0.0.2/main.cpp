/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Triangulo Magico                                         *
 * Autor:                          Erika Guayanay, Maycol Celi, Jerson Llumiquinga          *
 * Fecha de creacion:              26/02/2025                                               *
 * Fecha de modificacion:          26/02/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include <graphics.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Validaciones.h"
using namespace std;


struct TrianguloSolution {
    vector<int> corners; 
    vector<int> side1;   
    vector<int> side2;  
    vector<int> side3;  
    bool found;
};

bool backtrackCombination(int needed, int count, int start, vector<bool>& used,
                   vector<int>& resultado, int maxDigit) {
    if (count == 0)
        return (needed == 0);
    if (start > maxDigit)
        return false;
    for (int dig = start; dig <= maxDigit; dig++) {
        if (!used[dig] && dig <= needed) {
            used[dig] = true;
            resultado.push_back(dig);
            if (backtrackCombination(needed - dig, count - 1, dig + 1, used, resultado, maxDigit))
                return true;
            used[dig] = false;
            resultado.pop_back();
        }
    }
    return false;
}

TrianguloSolution NumerosNoRepetidos(int orden, int sumaObjetivo) {
    TrianguloSolution sol;
    sol.found = false;

    if(orden < 3 || orden > 10) {
        cout << "Orden no soportado. Debe estar entre 3 y 10." << endl;
        return sol;
    }

    // Determinamos el rango de dígitos:
    int maxDigit = 3 * (orden - 1);
    // Suma total de los dígitos del 1 a maxDigit:
    int T = maxDigit * (maxDigit + 1) / 2;
    // La suma de las 3 esquinas debe ser:
    int sumaEsquinas = 3 * sumaObjetivo - T;
    
    // Verificamos que la suma de esquinas esté en el rango posible:
    int minEsquinas = 1 + 2 + 3;  // 6
    int maxEsquinas = (maxDigit) + (maxDigit - 1) + (maxDigit - 2); // los 3 mayores
    if (sumaEsquinas < minEsquinas || sumaEsquinas > maxEsquinas) {
        return sol;
    }
    
    // Recorrer combinaciones para las esquinas (a, b, c) de 1 a maxDigit:
    for (int a = 1; a <= maxDigit; a++) {
        for (int b = a + 1; b <= maxDigit; b++) {
            for (int c = b + 1; c <= maxDigit; c++) {
                if (a + b + c == sumaEsquinas) {
                    // Usamos un vector<bool> para llevar el control de los dígitos ya usados.
                    vector<bool> used(maxDigit + 1, false);
                    used[a] = used[b] = used[c] = true;
                    
                    // Para cada lado, se deben llenar (orden - 2) nodos intermedios.
                    int cant = orden - 2;
                    // Lado 1: entre esquinas a y b
                    int resto1 = sumaObjetivo - (a + b);
                    // Lado 2: entre esquinas b y c
                    int resto2 = sumaObjetivo - (b + c);
                    // Lado 3: entre esquinas c y a
                    int resto3 = sumaObjetivo - (c + a);
                    
                    vector<int> lado1, lado2, lado3;
                    
                    // Se busca una combinación para cada lado sin reutilizar dígitos.
                    if (!backtrackCombination(resto1, cant, 1, used, lado1, maxDigit))
                        continue;
                    if (!backtrackCombination(resto2, cant, 1, used, lado2, maxDigit))
                        continue;
                    if (!backtrackCombination(resto3, cant, 1, used, lado3, maxDigit))
                        continue;
                    
                    sol.corners = {a, b, c};
                    sol.side1 = lado1;
                    sol.side2 = lado2;
                    sol.side3 = lado3;
                    sol.found = true;
                    return sol;
                }
            }
        }
    }
    return sol;
}

void dibujarNodo(int x, int y, int radio, int numero) {
    setcolor(LIGHTCYAN); // Color celeste para el círculo
    circle(x, y, radio);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    floodfill(x, y, LIGHTCYAN);
    setcolor(WHITE); // Color blanco para el número
    char buffer[10];
    sprintf(buffer, "%d", numero);
    outtextxy(x - (radio / 2), y - (radio / 2), buffer);
}


void dibujarTrianguloMagico(const TrianguloSolution &sol, int orden, int sumaObjetivo) {
    int gd = DETECT, gm;
    char initPath[] = "";
    initgraph(&gd, &gm, initPath);
    setbkcolor(BLACK);
    cleardevice();
    
    // Coordenadas de los vértices (puedes ajustarlas según tu preferencia)
    int x1 = 300, y1 = 100; // Vértice superior
    int x2 = 100, y2 = 400; // Vértice inferior izquierdo
    int x3 = 500, y3 = 400; // Vértice inferior derecho
    int radio = 20;
    
    // Esquinas
    int A = sol.corners[0];
    int B = sol.corners[1];
    int C = sol.corners[2];
    
    dibujarNodo(x1, y1, radio, A);
    dibujarNodo(x2, y2, radio, B);
    dibujarNodo(x3, y3, radio, C);
    
    setcolor(MAGENTA); // Color morado para las líneas del triángulo
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
    
    int numIntermedios = orden - 2;
    auto dibujarLado = [&](int xIni, int yIni, int xFin, int yFin, const vector<int> &valores) {
        for (int i = 0; i < (int)valores.size(); i++) {
            float t = (float)(i + 1) / (numIntermedios + 1);
            int x = xIni + t * (xFin - xIni);
            int y = yIni + t * (yFin - yIni);
            dibujarNodo(x, y, radio, valores[i]);
        }
    };
    
    dibujarLado(x1, y1, x2, y2, sol.side1);
    dibujarLado(x2, y2, x3, y3, sol.side2);
    dibujarLado(x3, y3, x1, y1, sol.side3);
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    char titulo[] = "GRAFICA-TRIANGULO MAGICO";
    outtextxy(150, 20, titulo);
    
    char mensaje[50];
    sprintf(mensaje, "La suma de los lados es: %d", sumaObjetivo);
    outtextxy(150, 50, mensaje);
    
    getch();
    closegraph();
}


int main() {
    srand(time(0)); // Inicializar la semilla para números aleatorios
    
    while (true) {
        int orden;
        cout << "Nivel triangulo magico (3 a 10): ";
        string entrada = capturarEntrada();
        try {
            orden = stoi(entrada);
        } catch (invalid_argument&) {
            cout << "Entrada no valida. Debe ser un numero entre 3 y 10." << endl;
            continue;
        }
        
        if (orden < 3 || orden > 10) {
            cout << "Nivel no soportado. Debe ser entre 3 y 10." << endl;
            continue;
        }
        
        // Determinamos el rango de dígitos y la suma total de esos dígitos:
        int maxDigit = 3 * (orden - 1);
        int T = maxDigit * (maxDigit + 1) / 2;
        
        // La suma mínima de esquinas es 6 (1+2+3), y la suma de esquinas es: 3*S - T.
        // Por ello, el valor mínimo de S es:
        int minS = (T + 6) / 3;
        // La suma máxima de las 3 esquinas es: (maxDigit) + (maxDigit-1) + (maxDigit-2)
        int maxEsquinas = maxDigit + (maxDigit - 1) + (maxDigit - 2);
        int maxS = (T + maxEsquinas) / 3;
        
        // Seleccionar aleatoriamente la suma objetivo dentro del rango permitido
        int sumaObjetivo = rand() % (maxS - minS + 1) + minS;
        
        cout << "La suma objetivo seleccionada aleatoriamente para cada lado del triangulo magico es: " << sumaObjetivo << endl;
        
        TrianguloSolution sol = NumerosNoRepetidos(orden, sumaObjetivo);
        if (!sol.found) {
            cout << "No se encontro una solucion sin repetir numeros para esos datos." << endl;
        } else {
            dibujarTrianguloMagico(sol, orden, sumaObjetivo);
        }
        
        cout << "Presione 'x' para salir o enter continuar..." << endl;
        char opcion = obtenerEntradaValidada();
        if (opcion == 'x' || opcion == 'X') {
            break;
        }
    }
    return 0;
}