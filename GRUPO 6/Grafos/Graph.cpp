#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <graphics.h>
#include <math.h>
#include <queue>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjList;
    vector<vector<int>> adjMatrix;
    bool directed;
    vector<int> x; // Posiciones X de los vértices
    vector<int> y; // Posiciones Y de los vértices

public:
    Graph(int vertices, bool isDirected) {
        V = vertices;
        directed = isDirected;
        adjList.resize(V);
        adjMatrix.resize(V, vector<int>(V, 0));
        x.resize(V);
        y.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjMatrix[u][v] = 1;
        if (!directed) {
            adjList[v].push_back(u);
            adjMatrix[v][u] = 1;
        }
    }

    void generateRandomEdges() {
        srand(time(0));
        for (int i = 0; i < V; ++i) {
            int edges = rand() % V;
            for (int j = 0; j < edges; ++j) {
                int neighbor = rand() % V;
                if (neighbor != i) {
                    addEdge(i, neighbor);
                }
            }
        }
    }

    void drawGraph(int startVertex = -1, int repChoice = 1, bool highlightBFS = false) {
        int gd = DETECT, gm;
        char driver[] = "";
        initgraph(&gd, &gm, driver);
        int radius = 20;

        // Generar posiciones de los vértices solo si no están definidas
        if (x[0] == 0 && y[0] == 0) { // Verificar si las posiciones ya fueron generadas
            for (int i = 0; i < V; ++i) {
                x[i] = rand() % (getmaxx() - 2 * radius) + radius;
                y[i] = rand() % (getmaxy() - 2 * radius) + radius;
            }
        }

        // Dibujar las conexiones
        for (int u = 0; u < V; ++u) {
            for (int v : adjList[u]) {
                line(x[u], y[u], x[v], y[v]); // Fix the error by providing the correct number of arguments
                if (directed) {
                    drawArrow(x[u], y[u], x[v], y[v]);
                }
            }
        }

        // Dibujar los nodos
        for (int i = 0; i < V; ++i) {
            circle(x[i], y[i], radius);
            char label[10];
            sprintf(label, "%d", i);
            outtextxy(x[i] - 5, y[i] - 5, label);
        }

        // Si se seleccionó BFS, resaltarlo
        if (highlightBFS) {
            bfs(startVertex, radius);
        }

        // Crear una nueva ventana para la representación
        int gd2 = DETECT, gm2;
        initgraph(&gd2, &gm2, driver);

        // Mostrar representación elegida
        if (repChoice == 2) {
            setcolor(GREEN);
            drawAdjacencyList();
        } else if (repChoice == 3) {
            setcolor(YELLOW);
            drawAdjacencyMatrix();
        }

        getch();
        closegraph();
    }

    void drawArrow(int x1, int y1, int x2, int y2) {
        int arrowSize = 10;
        double angle = atan2(y2 - y1, x2 - x1);
        int arrowX1 = x2 - arrowSize * cos(angle - M_PI / 6);
        int arrowY1 = y2 - arrowSize * sin(angle - M_PI / 6);
        int arrowX2 = x2 - arrowSize * cos(angle + M_PI / 6);
        int arrowY2 = y2 - arrowSize * sin(angle + M_PI / 6);
        line(x2, y2, arrowX1, arrowY1);
        line(x2, y2, arrowX2, arrowY2);
    }

    void bfs(int start, int radius) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        setcolor(RED); // Color para resaltar el recorrido

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                    line(x[node], y[node], x[neighbor], y[neighbor]);
                    if (directed) {
                        drawArrow(x[node], y[node], x[neighbor], y[neighbor]);
                    }
                    circle(x[neighbor], y[neighbor], radius);
                    char label[10];
                    sprintf(label, "%d", neighbor);
                    outtextxy(x[neighbor] - 5, y[neighbor] - 5, label);
                    delay(500); // Delay to visualize the traversal step-by-step
                }
            }
        }
    }

    void drawAdjacencyList() {
        int xOffset = 50;
        int yOffset = 50;
        int lineHeight = 20;

        for (int i = 0; i < V; ++i) {
            char label[100];
            sprintf(label, "%d -> ", i);
            outtextxy(xOffset, yOffset + i * lineHeight, label);

            int xPos = xOffset + 40;
            for (int j : adjList[i]) {
                sprintf(label, "%d ", j);
                outtextxy(xPos, yOffset + i * lineHeight, label);
                xPos += 20;
            }
        }
    }

    void drawAdjacencyMatrix() {
        int xOffset = 50;
        int yOffset = 50;
        int cellSize = 20;

        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                char label[2];
                sprintf(label, "%d", adjMatrix[i][j]);
                outtextxy(xOffset + j * cellSize, yOffset + i * cellSize, label);
            }
        }
    }

    // Método para imprimir la lista de adyacencia
    void printAdjacencyList() {
        cout << "Adjacency List Representation:" << endl;
        for (int i = 0; i < V; ++i) {
            cout << i << " -> ";
            for (int j : adjList[i]) {
                cout << j << " ";
            }
            cout << endl;
        }
    }

    // Método para imprimir la matriz de adyacencia
    void printAdjacencyMatrix() {
        cout << "Adjacency Matrix Representation:" << endl;
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int choice, sizeChoice, repChoice, startVertex;
    bool directed = false;
    int vertices;

    while (true) {
        cout << "1. Grafo Dirigido" << endl;
        cout << "2. Grafo No Dirigido" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese su eleccion: ";
        cin >> choice;

        if (choice == 3) break;
        directed = (choice == 1);

        cout << "1. Grafo Pequeno (5 vertices)" << endl;
        cout << "2. Grafo Grande (10 vertices)" << endl;
        cout << "3. Atras" << endl;
        cout << "Ingrese su eleccion: ";
        cin >> sizeChoice;

        if (sizeChoice == 3) continue;
        vertices = (sizeChoice == 1) ? 5 : 10;

        Graph g(vertices, directed);
        g.generateRandomEdges();

        cout << "Seleccione Representacion:" << endl;
        cout << "1. Representacion Logica" << endl;
        cout << "2. Lista de Adyacencia" << endl;
        cout << "3. Matriz de Adyacencia" << endl;
        cout << "Ingrese su eleccion: ";
        cin >> repChoice;

        // Mostrar el grafo antes de ingresar el Start Vertex
        g.drawGraph(-1, repChoice, false);

        // Mostrar la representacion seleccionada
        if (repChoice == 2) {
            g.printAdjacencyList();
        } else if (repChoice == 3) {
            g.printAdjacencyMatrix();
        }

        // Pedir el vertice de inicio
        cout << "Ingrese el Vertice de Inicio para BFS: ";
        cin >> startVertex;
        if (startVertex >= 0 && startVertex < vertices) {
            // Mostrar el grafo con BFS resaltado
            g.drawGraph(startVertex, repChoice, true);
        } else {
            cout << "Vertice de Inicio Invalido!" << endl;
        }
    }

    return 0;
}