#ifndef PROJEKTAIZO_GRAPHSTRUCTURES_H
#define PROJEKTAIZO_GRAPHSTRUCTURES_H

#include <iostream>

// Węzeł listy sąsiedztwa
struct Node {
    int vertex;
    int weight;
    Node* next;
};

// Lista sąsiedztwa grafu
struct Graph {
    int V;
    Node** adjList;

    Graph(int vertices) {
        V = vertices;
        adjList = new Node*[V];
        for (int i = 0; i < V; ++i)
            adjList[i] = nullptr;
    }

    void addEdge(int u, int v, int w) {
        Node* nodeU = new Node{v, w, adjList[u]};
        adjList[u] = nodeU;

        Node* nodeV = new Node{u, w, adjList[v]};
        adjList[v] = nodeV;
    }

    void print() {
        for (int i = 0; i < V; ++i) {
            std::cout << i << " -> ";
            Node* curr = adjList[i];
            while (curr) {
                std::cout << "(" << curr->vertex << ", " << curr->weight << ") ";
                curr = curr->next;
            }
            std::cout << "\n";
        }
    }

    ~Graph() {
        for (int i = 0; i < V; ++i) {
            Node* curr = adjList[i];
            while (curr) {
                Node* tmp = curr;
                curr = curr->next;
                delete tmp;
            }
        }
        delete[] adjList;
    }
};

#endif // PROJEKTAIZO_GRAPHSTRUCTURES_H
