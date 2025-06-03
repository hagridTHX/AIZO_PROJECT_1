#ifndef PROJEKTAIZO_MAXFLOW_H
#define PROJEKTAIZO_MAXFLOW_H

#include "../../Timer.h"
#include "../utils/GraphStructure.h"
#include <climits>

class MaxFlow {
private:
    int representation; // 0 - macierz, 1 - lista
    int** incidenceMatrix = nullptr;
    Graph* graph = nullptr;

public:
    MaxFlow(int** matrix, int representation)
            : incidenceMatrix(matrix), representation(representation) {}

    MaxFlow(Graph* g, int representation)
            : graph(g), representation(representation) {}

    int fordFulkerson(Timer& timer, int source, int sink) {
        timer.reset();
        timer.start();

        int V = 0;
        int** capacity;

        if (representation == 0) {
            // MACIERZ INCYDENCJI
            while (incidenceMatrix[V]) ++V;
            int E = 0;
            while (incidenceMatrix[0][E] != -9999) ++E;

            capacity = new int*[V];
            for (int i = 0; i < V; ++i) {
                capacity[i] = new int[V];
                for (int j = 0; j < V; ++j)
                    capacity[i][j] = 0;
            }

            for (int e = 0; e < E; ++e) {
                int u = -1, v = -1;
                for (int i = 0; i < V; ++i) {
                    if (incidenceMatrix[i][e] == 1) {
                        if (u == -1) u = i;
                        else v = i;
                    }
                }
                if (u != -1 && v != -1)
                    capacity[u][v] = 1; // lub inna wartość
            }

        } else {
            // LISTA SĄSIEDZTWA
            V = graph->V;
            capacity = new int*[V];
            for (int i = 0; i < V; ++i) {
                capacity[i] = new int[V];
                for (int j = 0; j < V; ++j)
                    capacity[i][j] = 0;
            }
            for (int u = 0; u < V; ++u) {
                Node* node = graph->adjList[u];
                while (node) {
                    int v = node->vertex;
                    capacity[u][v] = node->weight;
                    node = node->next;
                }
            }
        }

        int** rGraph = new int*[V];
        for (int i = 0; i < V; ++i) {
            rGraph[i] = new int[V];
            for (int j = 0; j < V; ++j)
                rGraph[i][j] = capacity[i][j];
        }

        int* parent = new int[V];
        bool* visited = new bool[V];
        int* queue = new int[V];

        auto bfs = [&](int src, int tgt) -> bool {
            for (int i = 0; i < V; ++i) {
                visited[i] = false;
                parent[i] = -1;
            }
            int front = 0, rear = 0;
            queue[rear++] = src;
            visited[src] = true;
            parent[src] = -1;

            while (front < rear) {
                int u = queue[front++];
                for (int v = 0; v < V; ++v) {
                    if (!visited[v] && rGraph[u][v] > 0) {
                        queue[rear++] = v;
                        parent[v] = u;
                        visited[v] = true;
                        if (v == tgt) return true;
                    }
                }
            }
            return false;
        };

        int maxFlow = 0;
        while (bfs(source, sink)) {
            int pathFlow = INT_MAX;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                if (rGraph[u][v] < pathFlow) pathFlow = rGraph[u][v];
            }
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                rGraph[u][v] -= pathFlow;
                rGraph[v][u] += pathFlow;
            }
            maxFlow += pathFlow;
        }

        for (int i = 0; i < V; ++i) {
            delete[] capacity[i];
            delete[] rGraph[i];
        }
        delete[] capacity;
        delete[] rGraph;
        delete[] parent;
        delete[] visited;
        delete[] queue;

        timer.stop();
        return timer.result();
    }
};

#endif //PROJEKTAIZO_MAXFLOW_H
