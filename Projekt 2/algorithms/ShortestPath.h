#ifndef PROJEKTAIZO_SHORTESTPATH_H
#define PROJEKTAIZO_SHORTESTPATH_H

#include "../../Timer.h"
#include "../utils/GraphStructure.h"
#include <climits>
#include "../utils/Edge.h"

class ShortestPath {
private:
    int representation; // 0 - macierz, 1 - lista
    int** incidenceMatrix = nullptr;
    Graph* graph = nullptr;

public:
    ShortestPath(int** matrix, int representation)
            : incidenceMatrix(matrix), representation(representation) {}

    ShortestPath(Graph* g, int representation)
            : graph(g), representation(representation) {}

    int dijkstra(Timer& timer, int source, int target) {
        timer.reset();
        timer.start();

        int V;
        if (representation == 0) {
            V = 0;
            while (incidenceMatrix[V]) ++V;
        } else {
            V = graph->V;
        }

        int* dist = new int[V];
        bool* visited = new bool[V];
        for (int i = 0; i < V; ++i) {
            dist[i] = INT_MAX;
            visited[i] = false;
        }
        dist[source] = 0;

        for (int count = 0; count < V - 1; ++count) {
            int u = -1, minDist = INT_MAX;
            for (int i = 0; i < V; ++i)
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            if (u == -1) break;
            visited[u] = true;

            if (representation == 0) {
                int E = 0;
                while (incidenceMatrix[0][E] != -9999) ++E;
                for (int e = 0; e < E; ++e) {
                    if (incidenceMatrix[u][e]) {
                        for (int v = 0; v < V; ++v) {
                            if (v != u && incidenceMatrix[v][e]) {
                                if (dist[u] + 1 < dist[v])
                                    dist[v] = dist[u] + 1;
                            }
                        }
                    }
                }
            } else {
                Node* node = graph->adjList[u];
                while (node) {
                    int v = node->vertex;
                    if (!visited[v] && dist[u] + node->weight < dist[v])
                        dist[v] = dist[u] + node->weight;
                    node = node->next;
                }
            }
        }

        timer.stop();
        int result = timer.result();
        delete[] dist;
        delete[] visited;
        return result;
    }

    int bellmanFord(Timer& timer, int source, int target) {
        timer.reset();
        timer.start();

        int V, E;
        Edge* edgeList;

        if (representation == 0) {
            V = 0;
            while (incidenceMatrix[V]) ++V;
            E = 0;
            while (incidenceMatrix[0][E] != -9999) ++E;

            edgeList = new Edge[E];
            int count = 0;
            for (int e = 0; e < E; ++e) {
                int u = -1, v = -1;
                for (int i = 0; i < V; ++i) {
                    if (incidenceMatrix[i][e] == 1) {
                        if (u == -1) u = i;
                        else v = i;
                    }
                }
                edgeList[count++] = { u, v, 1 };
            }
        } else {
            V = graph->V;
            E = 0;
            for (int u = 0; u < V; ++u) {
                Node* node = graph->adjList[u];
                while (node) {
                    ++E;
                    node = node->next;
                }
            }

            edgeList = new Edge[E];
            int count = 0;
            for (int u = 0; u < V; ++u) {
                Node* node = graph->adjList[u];
                while (node) {
                    edgeList[count++] = { u, node->vertex, node->weight };
                    node = node->next;
                }
            }
        }

        int* dist = new int[V];
        for (int i = 0; i < V; ++i)
            dist[i] = INT_MAX;
        dist[source] = 0;

        for (int i = 1; i <= V - 1; ++i) {
            for (int j = 0; j < E; ++j) {
                int u = edgeList[j].u;
                int v = edgeList[j].v;
                int w = edgeList[j].weight;
                if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                    dist[v] = dist[u] + w;
            }
        }

        timer.stop();
        int result = timer.result();

        delete[] dist;
        delete[] edgeList;
        return result;
    }
};

#endif //PROJEKTAIZO_SHORTESTPATH_H
