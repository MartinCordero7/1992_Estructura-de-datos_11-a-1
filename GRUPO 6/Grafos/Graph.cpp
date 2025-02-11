#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <graphics.h>
#include <math.h>
#include <queue>
#include <algorithm>
using namespace std;

const int ARROW_SIZE = 10;
const int NODE_RADIUS = 20;

class Graph {
private:
    int V;
    vector<vector<int>> adjList;
    vector<vector<int>> adjMatrix;
    bool directed;
    vector<int> x, y;
    bool positionsGenerated;

    void drawArrow(int x1, int y1, int x2, int y2) {
        line(x1, y1, x2, y2);
        if (!directed) return;

        double angle = atan2(y2 - y1, x2 - x1);
        int x3 = x2 - ARROW_SIZE * cos(angle - M_PI/6);
        int y3 = y2 - ARROW_SIZE * sin(angle - M_PI/6);
        int x4 = x2 - ARROW_SIZE * cos(angle + M_PI/6);
        int y4 = y2 - ARROW_SIZE * sin(angle + M_PI/6);
        
        line(x2, y2, x3, y3);
        line(x2, y2, x4, y4);
    }

    void generatePositionsIfNeeded() {
        if (!positionsGenerated) {
            int gd = DETECT, gm;
            initgraph(&gd, &gm, "");
            for (int i = 0; i < V; ++i) {
                x[i] = rand() % (getmaxx() - 2 * NODE_RADIUS) + NODE_RADIUS;
                y[i] = rand() % (getmaxy() - 2 * NODE_RADIUS) + NODE_RADIUS;
            }
            closegraph();
            positionsGenerated = true;
        }
    }

    vector<pair<int, int>> bfsTraversal(int startVertex, vector<int>& parent, vector<bool>& visited) {
        vector<pair<int, int>> edges;
        queue<int> q;
        fill(parent.begin(), parent.end(), -1);
        fill(visited.begin(), visited.end(), false);

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adjList[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    edges.push_back({u, v});
                    q.push(v);
                }
            }
        }
        return edges;
    }

public:
    Graph(int vertices, bool isDirected) : V(vertices), directed(isDirected) {
        adjList.resize(V);
        adjMatrix.resize(V, vector<int>(V, 0));
        x.resize(V);
        y.resize(V);
        positionsGenerated = false;
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

    void drawGraph() {
        generatePositionsIfNeeded();
        int gd = DETECT, gm;
        initgraph(&gd, &gm, "");
        
        // Draw edges with arrows for directed graphs
        for (int u = 0; u < V; ++u) {
            for (int v : adjList[u]) {
                setcolor(WHITE);
                drawArrow(x[u], y[u], x[v], y[v]);
            }
        }

        // Draw nodes as circles
        for (int i = 0; i < V; ++i) {
            circle(x[i], y[i], NODE_RADIUS);
            char label[10];
            sprintf(label, "%d", i);
            outtextxy(x[i] - 5, y[i] - 8, label);
        }

        getch();
        closegraph();
    }

    void drawStarVertex(int startVertex) {
        generatePositionsIfNeeded();
        int gd = DETECT, gm;
        initgraph(&gd, &gm, "");
        
        vector<int> parent(V);
        vector<bool> visited(V);
        auto traversalEdges = bfsTraversal(startVertex, parent, visited);

        // Draw original graph in gray
        setcolor(DARKGRAY);
        for (int u = 0; u < V; ++u) {
            for (int v : adjList[u]) {
                drawArrow(x[u], y[u], x[v], y[v]);
            }
        }

        // Draw BFS traversal in green
        setcolor(GREEN);
        setlinestyle(SOLID_LINE, 0, 3);
        for (auto& edge : traversalEdges) {
            drawArrow(x[edge.first], y[edge.first], x[edge.second], y[edge.second]);
        }
        setlinestyle(SOLID_LINE, 0, 1);

        // Draw nodes
        for (int i = 0; i < V; ++i) {
            circle(x[i], y[i], NODE_RADIUS);
            char label[10];
            sprintf(label, "%d", i);
            outtextxy(x[i] - 5, y[i] - 8, label);
        }

        // Draw BFS table
        int tableX = getmaxx() - 150;
        int tableY = 50;
        setcolor(WHITE);
        outtextxy(tableX, tableY, "Parent  Visited");
        for (int i = 0; i < V; ++i) {
            char row[20];
            sprintf(row, "%d\t%s", parent[i], visited[i] ? "T" : "F");
            outtextxy(tableX, tableY + 30 + i*20, row);
        }

        getch();
        closegraph();
    }

    void drawAdjacencyList() {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, "");
        int startX = 50, startY = 50;
        
        for (int u = 0; u < V; ++u) {
            // Draw node box
            rectangle(startX - 10, startY + u*30 - 10, 
                     startX + 30, startY + u*30 + 20);
            
            char label[10];
            sprintf(label, "%d", u);
            outtextxy(startX, startY + u*30, label);
            
            // Draw arrow
            outtextxy(startX + 25, startY + u*30, "->");
            
            int xOffset = 80;
            for (int v : adjList[u]) {
                // Draw adjacent nodes in boxes
                rectangle(startX + xOffset - 10, startY + u*30 - 10,
                         startX + xOffset + 20, startY + u*30 + 20);
                sprintf(label, "%d", v);
                outtextxy(startX + xOffset, startY + u*30, label);
                xOffset += 40;
            }
        }
        getch();
        closegraph();
    }

    void drawAdjacencyMatrix() {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, "");
        int cellSize = 30;
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                char value[2];
                sprintf(value, "%d", adjMatrix[i][j]);
                rectangle(50 + j * cellSize, 50 + i * cellSize, 
                        80 + j * cellSize, 80 + i * cellSize);
                outtextxy(60 + j * cellSize, 60 + i * cellSize, value);
            }
        }
        getch();
        closegraph();
    }
};

int main() {
    int choice, sizeChoice, repChoice;
    bool directed;
    int vertices;

    cout << "1. Directed Graph\n2. Undirected Graph\nEnter your choice: ";
    cin >> choice;
    directed = (choice == 1);

    cout << "1. Small Graph (5 vertices)\n2. Large Graph (10 vertices)\nEnter your choice: ";
    cin >> sizeChoice;
    vertices = (sizeChoice == 1) ? 5 : 10;

    Graph g(vertices, directed);
    g.generateRandomEdges();

    do {
        cout << "Select Representation:\n1. Graph\n2. Adjacency List\n3. Adjacency Matrix\n4. Star Vertex\n5. Exit\nEnter your choice: ";
        cin >> repChoice;

        switch (repChoice) {
            case 1: g.drawGraph(); break;
            case 2: g.drawAdjacencyList(); break;
            case 3: g.drawAdjacencyMatrix(); break;
            case 4: {
                int startVertex;
                cout << "Enter starting vertex (0-" << vertices-1 << "): ";
                cin >> startVertex;
                if (startVertex >= 0 && startVertex < vertices) g.drawStarVertex(startVertex);
                else cout << "Invalid vertex!\n";
                break;
            }
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (repChoice != 5);

    return 0;
}