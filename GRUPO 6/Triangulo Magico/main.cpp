#include <graphics.h>
#include <iostream>
#include <vector>
using namespace std;

/* -------------------------------------------------------------------
 * Estructura para almacenar la solución completa de un triángulo:
 *  - corners: las 3 esquinas
 *  - side1, side2, side3: los nodos intermedios de cada lado
 *  - found: indica si se logró encontrar una solución
 * ------------------------------------------------------------------- */
struct TrianguloSolution {
    vector<int> corners; // tamaño = 3
    vector<int> side1;   // tamaño = (orden - 2)
    vector<int> side2;   // tamaño = (orden - 2)
    vector<int> side3;   // tamaño = (orden - 2)
    bool found;
};

/* -------------------------------------------------------------------
 * Calcula la "suma de esquinas" (sumaEsquinas) para un orden dado.
 * La fórmula se basa en la suma total de los dígitos disponibles.
 * Para:
 *   - Orden 3: se usan dígitos 1..6 (suma total = 21)
 *   - Orden 4: se usan dígitos 1..9 (suma total = 45)
 *   - Orden 5: se usan dígitos 1..12 (suma total = 78)
 * ------------------------------------------------------------------- */
int calcularSumaEsquinas(int orden, int sumaObjetivo) {
    // Fórmulas derivadas: sumaEsquinas = 3 * sumaObjetivo - (suma total de dígitos)
    switch (orden) {
        case 3: return 3 * sumaObjetivo - 21;
        case 4: return 3 * sumaObjetivo - 45;
        case 5: return 3 * sumaObjetivo - 78;
        // Puedes extender para otros órdenes si amplías el rango de dígitos
        default: return -1; // Orden no soportado en esta versión
    }
}

/* -------------------------------------------------------------------
 * Backtracking para elegir 'count' dígitos (sin repetir) de [1..maxDigit]
 * que sumen 'needed'. Se usa un vector<bool> 'used' para marcar los dígitos ya ocupados.
 *
 * Devuelve true si encuentra una combinación válida (y la deja en 'resultado'),
 * o false si no la hay.
 * ------------------------------------------------------------------- */
bool backtrackSide(int needed, int count, int start, vector<bool>& used,
                   vector<int>& resultado, int maxDigit) {
    if (count == 0)
        return (needed == 0);
    if (start > maxDigit)
        return false;
    for (int dig = start; dig <= maxDigit; dig++) {
        if (!used[dig] && dig <= needed) {
            used[dig] = true;
            resultado.push_back(dig);
            if (backtrackSide(needed - dig, count - 1, dig + 1, used, resultado, maxDigit))
                return true;
            used[dig] = false;
            resultado.pop_back();
        }
    }
    return false;
}

/* -------------------------------------------------------------------
 * Intenta resolver el triángulo completo sin repetir dígitos.
 *  - orden, sumaObjetivo
 *  - Retorna un TrianguloSolution con found=true si hay solución.
 *
 * Lógica:
 *  1) Calcula la suma de esquinas.
 *  2) Recorre todas las combinaciones (a,b,c) de [1..maxDigit] (con a<b<c)
 *     cuya suma sea 'sumaEsquinas'.
 *  3) Con esos dígitos marcados como usados, busca para cada lado la combinación
 *     de nodos intermedios que complete la sumaObjetivo.
 * ------------------------------------------------------------------- */
TrianguloSolution resolverTrianguloMagicoNoRepetir(int orden, int sumaObjetivo) {
    TrianguloSolution sol;
    sol.found = false;
    
    // Determinamos el rango de dígitos según el orden:
    // Orden 3: se usan dígitos 1..6, Orden 4: 1..9, Orden 5: 1..12.
    int maxDigit;
    if (orden == 3)
        maxDigit = 6;
    else if (orden == 4)
        maxDigit = 9;
    else if (orden == 5)
        maxDigit = 12;
    else {
        cout << "Orden no soportado en esta versión." << endl;
        return sol;
    }
    
    int totalNumeros = 3 * (orden - 1); // Debe coincidir con maxDigit
    if (maxDigit != totalNumeros) {
        // Verificamos consistencia; si no coinciden, abortamos.
        return sol;
    }
    
    // Calcular la suma que deben tener las 3 esquinas
    int sumaEsquinas = calcularSumaEsquinas(orden, sumaObjetivo);
    if (sumaEsquinas == -1)
        return sol; // Orden no soportado

    // Probar todas las combinaciones de esquinas (a, b, c) con 1 <= a < b < c <= maxDigit
    for (int a = 1; a <= maxDigit; a++) {
        for (int b = a + 1; b <= maxDigit; b++) {
            for (int c = b + 1; c <= maxDigit; c++) {
                if (a + b + c == sumaEsquinas) {
                    // Preparar vector<bool> para controlar dígitos usados
                    vector<bool> used(maxDigit + 1, false);
                    used[a] = used[b] = used[c] = true;
                    
                    // Calcular el "resto" que deben sumar los nodos intermedios en cada lado:
                    // Lado 1: a + (side1) + b = sumaObjetivo  => side1 = sumaObjetivo - a - b
                    // Lado 2: b + (side2) + c = sumaObjetivo  => side2 = sumaObjetivo - b - c
                    // Lado 3: c + (side3) + a = sumaObjetivo  => side3 = sumaObjetivo - c - a
                    int resto1 = sumaObjetivo - (a + b);
                    int resto2 = sumaObjetivo - (b + c);
                    int resto3 = sumaObjetivo - (c + a);
                    
                    // Cada lado tiene (orden - 2) nodos intermedios
                    int cant = orden - 2;
                    vector<int> lado1, lado2, lado3;
                    
                    if (!backtrackSide(resto1, cant, 1, used, lado1, maxDigit))
                        continue;
                    if (!backtrackSide(resto2, cant, 1, used, lado2, maxDigit))
                        continue;
                    if (!backtrackSide(resto3, cant, 1, used, lado3, maxDigit))
                        continue;
                    
                    // Solución encontrada
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
    // Si se recorrieron todas las opciones sin éxito, no hay solución.
    return sol;
}

/* -------------------------------------------------------------------
 * Función auxiliar para dibujar un nodo (círculo con número).
 * ------------------------------------------------------------------- */
void dibujarNodo(int x, int y, int radio, int numero) {
    setcolor(WHITE);
    circle(x, y, radio);
    char buffer[10];
    sprintf(buffer, "%d", numero);
    outtextxy(x - (radio / 2), y - (radio / 2), buffer);
}

/* -------------------------------------------------------------------
 * Dibuja el triángulo mágico en la pantalla.
 * ------------------------------------------------------------------- */
void dibujarTrianguloMagico(const TrianguloSolution &sol, int orden, int sumaObjetivo) {
    int gd = DETECT, gm;
    char initPath[] = "";
    initgraph(&gd, &gm, initPath);
    setbkcolor(BLACK);
    cleardevice();
    
    // Coordenadas de los vértices (ajústalas a tu gusto)
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
    
    setcolor(WHITE);
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
    char titulo[] = "Triangulo Magico";
    outtextxy(200, 20, titulo);
    
    getch();
    closegraph();
}

/* -------------------------------------------------------------------
 * main()
 * ------------------------------------------------------------------- */
int main() {
    int orden, sumaObjetivo;
    cout << "Ingrese el orden del triangulo magico (3, 4 o 5): ";
    cin >> orden;
    cout << "Ingrese la suma objetivo para cada lado del triangulo magico: ";
    cin >> sumaObjetivo;
    
    TrianguloSolution sol = resolverTrianguloMagicoNoRepetir(orden, sumaObjetivo);
    if (!sol.found) {
        cout << "No se encontro una solucion sin repetir numeros para esos datos." << endl;
    } else {
        dibujarTrianguloMagico(sol, orden, sumaObjetivo);
    }
    return 0;
}
