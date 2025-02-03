#ifndef LIST_H
#define LIST_H

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class List {
private:
    Node<T>* head;
    int size;

public:
    List() : head(nullptr), size(0) {}
    
    void push_back(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }
    
    T& operator[](int index) {
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    int getSize() const { return size; }
    
    bool empty() const { return size == 0; }
    
    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }
    
    class Iterator {
    private:
        Node<T>* current;
    public:
        Iterator(Node<T>* node) : current(node) {}
        T& operator*() { return current->data; }
        Iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const Iterator& other) { return current != other.current; }
    };
    
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

#endif