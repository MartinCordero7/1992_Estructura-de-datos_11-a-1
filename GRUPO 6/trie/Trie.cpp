#include "trie.h"
#include <iostream>
#include <algorithm>

Trie::Trie() : isLeaf(false) {}

void Trie::insert(std::string key) {
    if (key.empty()) {
        isLeaf = true;
        return;
    }
    char c = key[0];
    if (!children[c]) children[c] = new Trie();
    children[c]->insert(key.substr(1));
}

bool Trie::search(std::string key) {
    if (key.empty()) return isLeaf;
    char c = key[0];
    if (children.find(c) == children.end()) return false;
    return children[c]->search(key.substr(1));
}

bool Trie::deletion(std::string key) {
    if (key.empty()) {
        if (!isLeaf) return false;
        isLeaf = false;
        return children.empty();
    }
    char c = key[0];
    if (children.find(c) == children.end()) return false;
    bool shouldDelete = children[c]->deletion(key.substr(1));
    if (shouldDelete) {
        delete children[c];
        children.erase(c);
        return !isLeaf && children.empty();
    }
    return false;
}

void Trie::printInOrder(std::string prefix) {
    if (isLeaf) {
        std::cout << prefix << std::endl;
    }
    for (auto& pair : children) {
        pair.second->printInOrder(prefix + pair.first);
    }
}

int Trie::getHeight() {
    int maxHeight = 0;
    for (auto& pair : children) {
        maxHeight = std::max(maxHeight, pair.second->getHeight());
    }
    return 1 + maxHeight;
}

int Trie::getDepth() {
    return getHeight();
}

int Trie::getLevel() {
    return getHeight() - 1;
}

void Trie::drawNode(int x, int y, char c, bool isLastLetter) {
    // Si es la última letra de una palabra, usar color verde
    if (isLastLetter) {
        setcolor(GREEN);
    } else {
        setcolor(WHITE);
    }
    
    circle(x, y, 20);
    setcolor(WHITE); // Reset color
    
    // Si es nodo hoja, dibujar círculo exterior en rojo
    if (isLeaf) {
        setcolor(RED);
        circle(x, y, 23);
        setcolor(WHITE);
    }

    // Dibujar carácter
    char str[2] = {c, '\0'};
    outtextxy(x - 6, y - 7, str);
}

void Trie::drawConnection(int x1, int y1, int x2, int y2) {
    line(x1, y1 + 20, x2, y2 - 20);
}

void Trie::drawSubtree(Trie* node, int x, int y, int level, int spacing) {
    if (!node) return;

    const int LEVEL_SPACING = getmaxy() / (getHeight() + 1);
    const int MIN_NODE_SPACING = 80;

    int childCount = static_cast<int>(node->children.size());
    int childSpacing = std::max(spacing / (childCount + 1), MIN_NODE_SPACING);
    int totalWidth = childSpacing * (childCount - 1);
    int startX = x - totalWidth / 2;
    int childY = y + LEVEL_SPACING;
    
    int i = 0;
    for (auto& pair : node->children) {
        int childX = startX + childSpacing * i;
        
        drawConnection(x, y, childX, childY);
        
        // Determinar si es la última letra de una palabra
        bool isLastLetter = pair.second->isLeaf;
        
        drawNode(childX, childY, pair.first, isLastLetter);
        
        drawSubtree(pair.second, childX, childY, level + 1, childSpacing * 0.9);
        
        i++;
    }
}

void Trie::printTree() {
    int gd = DETECT, gm;
    
    initwindow(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), "");
    
    int maxX = getmaxx();
    int maxY = getmaxy();
    
    setbkcolor(BLACK);
    cleardevice();
    
    setcolor(WHITE);
    
    int treeHeight = getHeight();
    
    int initialSpacing = maxX * 0.9;
    
    int rootX = maxX / 2;
    int rootY = maxY * 0.1;
    
    circle(rootX, rootY, 20);
    outtextxy(rootX - 15, rootY - 7, (char*)"root");
    
    if (!children.empty()) {
        drawSubtree(this, rootX, rootY, 1, initialSpacing);
    }
    
    getch();
    closegraph();
}
