#include <iostream>
#include <string>
#include <graphics.h>

using namespace std;

const int TABLE_SIZE = 10;
const int WINDOW_WIDTH = 1600;  // Aumentamos el ancho para mejor visualización
const int WINDOW_HEIGHT = 800;

class HashTable {
protected:
    int hashFunction(const string &key) const {
        if (key.size() == 1 && isalpha(key[0]))
            return (toupper(key[0]) - 'A') % TABLE_SIZE;
        
        unsigned int hash = 5381;
        for (char c : key)
            hash = (hash << 5) + hash + c;
        return hash % TABLE_SIZE;
    }
};

class OpenHashTable : public HashTable {
private:
    struct Node {
        string data;
        Node* next;
        Node(const string &val) : data(val), next(nullptr) {}
    };

    Node* table[TABLE_SIZE] = {nullptr};

public:
    void insert(const string &key) {
        int index = hashFunction(key);
        Node* newNode = new Node(key);
        
        if (!table[index]) {
            table[index] = newNode;
        } else {
            Node* temp = table[index];
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    void draw(int startX, int startY) const {
        const int BOX_WIDTH = 80;
        const int BOX_HEIGHT = 40;
        const int HORIZONTAL_SPACING = 90;  // Espaciado ajustado

        setcolor(WHITE);
        outtextxy(startX, startY - 30, (char*)"Hash Abierto (Separate Chaining)");

        for (int i = 0; i < TABLE_SIZE; i++) {
            int xPos = startX + i * HORIZONTAL_SPACING;
            int yPos = startY;
            
            // Dibujar índice
            rectangle(xPos, yPos, xPos + BOX_WIDTH, yPos + BOX_HEIGHT);
            char index[3];
            sprintf(index, "%d", i);
            outtextxy(xPos + 10, yPos + 10, index);

            // Dibujar elementos
            Node* current = table[i];
            yPos += BOX_HEIGHT + 20;
            while (current) {
                setcolor(LIGHTCYAN);
                rectangle(xPos, yPos, xPos + BOX_WIDTH, yPos + BOX_HEIGHT);
                outtextxy(xPos + 10, yPos + 10, (char*)current->data.c_str());
                
                if (current->next) {
                    setcolor(YELLOW);
                    line(xPos + BOX_WIDTH/2, yPos + BOX_HEIGHT, 
                        xPos + BOX_WIDTH/2, yPos + BOX_HEIGHT + 20);
                }
                
                yPos += BOX_HEIGHT + 20;
                current = current->next;
            }
        }
    }

    ~OpenHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
};

class ClosedHashTable : public HashTable {
private:
    struct Entry {
        string key;
        int originalHash;
        bool occupied;
        Entry() : key(""), originalHash(-1), occupied(false) {}
    };
    
    Entry table[TABLE_SIZE];

public:
    void insert(const string &key) {
        int originalHash = hashFunction(key);
        int index = originalHash;
        int probes = 0;

        while (table[index].occupied && probes < TABLE_SIZE) {
            index = (index + 1) % TABLE_SIZE;
            probes++;
        }

        if (probes == TABLE_SIZE) {
            cout << "Tabla llena!" << endl;
            return;
        }

        table[index].key = key;
        table[index].originalHash = originalHash;
        table[index].occupied = true;
    }

    void draw(int startX, int startY) const {
        const int BOX_WIDTH = 150;
        const int BOX_HEIGHT = 40;
        const int COLUMNS = 2;
        const int VERTICAL_SPACING = 60;
        const int HORIZONTAL_SPACING = 250;  // Aumentamos el espaciado horizontal

        setcolor(WHITE);
        outtextxy(startX, startY - 30, (char*)"Hash Cerrado (Linear Probing)");

        for (int i = 0; i < TABLE_SIZE; i++) {
            int col = i % COLUMNS;
            int row = i / COLUMNS;
            
            int xPos = startX + col * HORIZONTAL_SPACING;
            int yPos = startY + row * VERTICAL_SPACING;
            
            if (table[i].occupied) {
                setcolor(table[i].originalHash == i ? GREEN : RED);
                rectangle(xPos, yPos, xPos + BOX_WIDTH, yPos + BOX_HEIGHT);
                
                char text[50];
                sprintf(text, "%s (%d)", table[i].key.c_str(), table[i].originalHash);
                outtextxy(xPos + 10, yPos + 10, (char*)text);
            }
            else {
                setcolor(WHITE);
                rectangle(xPos, yPos, xPos + BOX_WIDTH, yPos + BOX_HEIGHT);
            }
            
            char index[3];
            sprintf(index, "%d", i);
            outtextxy(xPos + BOX_WIDTH + 10, yPos + 10, index);
        }
    }
};

int main() {
    OpenHashTable openTable;
    ClosedHashTable closedTable;

    cout << "Ingrese elementos (numeros o letras), escriba 'fin' para terminar:\n";
    string input;
    
    while (true) {
        cin >> input;
        if (input == "fin") break;
        openTable.insert(input);
        closedTable.insert(input);
    }

    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, (char*)"Tablas Hash");
    cleardevice();
    
    // Posiciones definitivas sin solapamiento
    openTable.draw(50, 100);          // Tabla abierta (ancho total ≈ 900px)
    closedTable.draw(1000, 100);      // Tabla cerrada (inicia en 1000px)
    
    getch();
    closegraph();

    return 0;
}