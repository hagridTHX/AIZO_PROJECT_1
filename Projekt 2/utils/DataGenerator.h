#ifndef PROJEKTAIZO_DATAGENERATOR_H
#define PROJEKTAIZO_DATAGENERATOR_H

#include <iostream>
#include <algorithm>
#include <random>
#include "Edge.h"

// === Węzeł listy sąsiedztwa ===
struct Node {
    int vertex;
    int weight;
    Node* next;
};

// === Reprezentacja grafu (lista sąsiedztwa) ===
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

// === Generator grafu ===
class DataGenerator {
private:
    int vertices;
    int density;
    int edgesCount;
    Edge* edgeList;
    std::mt19937 rng;

    static bool edgeExists(const Edge* edges, int edge_count, int a, int b) {
        if (a > b) std::swap(a, b);
        for (int i = 0; i < edge_count; ++i) {
            int u = edges[i].u;
            int v = edges[i].v;
            if (u > v) std::swap(u, v);
            if (u == a && v == b) return true;
        }
        return false;
    }

    void computeEdgesCount() {
        long long maxEdges = 1LL * vertices * (vertices - 1) / 2;
        long long calc = (1LL * density * maxEdges) / 100;
        if (calc < vertices - 1)
            calc = vertices - 1;
        edgesCount = static_cast<int>(calc);
    }

    void generateEdgeList() {
        edgeList = new Edge[edgesCount];
        int edge_count = 0;

        int* connected = new int[vertices];
        int* unconnected = new int[vertices];
        int c_size = 1, u_size = 0;

        connected[0] = 0;
        for (int i = 1; i < vertices; ++i)
            unconnected[u_size++] = i;

        auto pick = [&](int N) {
            std::uniform_int_distribution<int> dist(0, N - 1);
            return dist(rng);
        };

        while (u_size > 0) {
            int a = connected[pick(c_size)];
            int b_index = pick(u_size);
            int b = unconnected[b_index];

            edgeList[edge_count++] = { a, b, 1 };

            connected[c_size++] = b;
            for (int i = b_index; i < u_size - 1; ++i)
                unconnected[i] = unconnected[i + 1];
            --u_size;
        }

        while (edge_count < edgesCount) {
            int a = pick(vertices);
            int b = pick(vertices);
            if (a == b || edgeExists(edgeList, edge_count, a, b)) continue;
            edgeList[edge_count++] = { a, b, 1 };
        }

        delete[] connected;
        delete[] unconnected;
    }

public:
    DataGenerator(int V, int densityPercent)
            : vertices(V), density(densityPercent), edgeList(nullptr), rng(std::random_device{}()) {
        computeEdgesCount();
        generateEdgeList();
    }

    ~DataGenerator() {
        delete[] edgeList;
    }

    int getNumVertices() const { return vertices; }
    int getNumEdges() const { return edgesCount; }

    int** getIncidenceMatrix() const {
        int** matrix = new int*[vertices];
        for (int i = 0; i < vertices; ++i)
            matrix[i] = new int[edgesCount]();

        for (int j = 0; j < edgesCount; ++j) {
            int u = edgeList[j].u;
            int v = edgeList[j].v;
            matrix[u][j] = 1;
            matrix[v][j] = 1;
        }

        return matrix;
    }

    Graph* getAdjacencyList() const {
        Graph* g = new Graph(vertices);
        for (int i = 0; i < edgesCount; ++i) {
            g->addEdge(edgeList[i].u, edgeList[i].v, edgeList[i].weight);
        }
        return g;
    }

    void freeIncidenceMatrix(int** matrix) const {
        for (int i = 0; i < vertices; ++i)
            delete[] matrix[i];
        delete[] matrix;
    }
};

#endif // PROJEKTAIZO_DATAGENERATOR_H
