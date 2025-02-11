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

    void drawGraph(int startVertex = -1, bool highlightBFS = false) {
        int gd = DETECT, gm;
        char driver[] = "";
        initgraph(&gd, &gm, driver);
        int radius = 20;

        // Generar posiciones de los vértices solo si no están definidas
        if (x[0] == 0 && y[0] == 0) { 
            for (int i = 0; i < V; ++i) {
                x[i] = rand() % (getmaxx() - 2 * radius) + radius;
                y[i] = rand() % (getmaxy() - 2 * radius) + radius;
            }
        }

        // Dibujar las conexiones
        for (int u = 0; u < V; ++u) {
            for (int v : adjList[u]) {
                line(x[u], y[u], x[v], y[v]);
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
        setcolor(RED);

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
                }
            }
        }
    }

    void printLogicalRepresentation() {
        cout << "\nLogical Representation (Edges List):\n";
        for (int u = 0; u < V; ++u) {
            for (int v : adjList[u]) {
                cout << "(" << u << " -> " << v << ")\n";
            }
        }
    }

    void printAdjacencyList() {
        cout << "\nAdjacency List Representation:\n";
        for (int u = 0; u < V; ++u) {
            cout << u << " -> ";
            for (int v : adjList[u]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    void printAdjacencyMatrix() {
        cout << "\nAdjacency Matrix Representation:\n";
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
        cout << "1. Directed Graph\n2. Undirected Graph\n3. Exit\nEnter your choice: ";
        cin >> choice;
        if (choice == 3) break;
        directed = (choice == 1);

        cout << "1. Small Graph (5 vertices)\n2. Large Graph (10 vertices)\n3. Back\nEnter your choice: ";
        cin >> sizeChoice;
        if (sizeChoice == 3) continue;
        vertices = (sizeChoice == 1) ? 5 : 10;

        Graph g(vertices, directed);
        g.generateRandomEdges();

        cout << "Select Representation:\n1. Logical Representation\n2. Adjacency List\n3. Adjacency Matrix\nEnter your choice: ";
        cin >> repChoice;

        // Imprimir la representación en la consola
        switch (repChoice) {
            case 1:
                g.printLogicalRepresentation();
                break;
            case 2:
                g.printAdjacencyList();
                break;
            case 3:
                g.printAdjacencyMatrix();
                break;
            default:
                cout << "Invalid choice!" << endl;
        }

        // Dibujar el grafo
        g.drawGraph();

        // Pedir el vértice de inicio para BFS
        cout << "Enter Start Vertex for BFS: ";
        cin >> startVertex;
        if (startVertex >= 0 && startVertex < vertices) {
            g.drawGraph(startVertex, true);
        } else {
            cout << "Invalid Start Vertex!" << endl;
        }
    }

    return 0;
}
