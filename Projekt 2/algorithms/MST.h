#ifndef PROJEKTAIZO_MST_H
#define PROJEKTAIZO_MST_H

#include "../../Timer.h"
#include "../utils/GraphStructure.h"
#include <climits>
#include <vector>
#include <algorithm>

class MST {
private:
    int** incidenceMatrix = nullptr;
    Graph* graph = nullptr;
    int representation; // 0 - macierz, 1 - lista

public:
    MST(int** _matrix, int _representation)
            : incidenceMatrix(_matrix), graph(nullptr), representation(_representation) {}

    MST(Graph* g, int _representation)
            : incidenceMatrix(nullptr), graph(g), representation(_representation) {}

    int prim(Timer& timer) {
        timer.reset();
        timer.start();

        if (representation == 0) {
            // === PRIM: MACIERZ INCYDENCJI ===
            int V = 0, E = 0;
            while (incidenceMatrix[V]) ++V;
            while (incidenceMatrix[0][E] != -9999) ++E;

            int* key = new int[V];
            bool* inMST = new bool[V];
            for (int i = 0; i < V; ++i) {
                key[i] = INT_MAX;
                inMST[i] = false;
            }

            key[0] = 0;
            int totalWeight = 0;

            for (int count = 0; count < V; ++count) {
                int u = -1, minKey = INT_MAX;
                for (int v = 0; v < V; ++v)
                    if (!inMST[v] && key[v] < minKey) {
                        minKey = key[v];
                        u = v;
                    }

                inMST[u] = true;
                totalWeight += key[u];

                for (int e = 0; e < E; ++e) {
                    if (incidenceMatrix[u][e]) {
                        for (int v = 0; v < V; ++v) {
                            if (v != u && incidenceMatrix[v][e] && !inMST[v] && key[v] > 1) {
                                key[v] = 1;
                            }
                        }
                    }
                }
            }

            delete[] key;
            delete[] inMST;

            timer.stop();
            return timer.result();

        } else {
            // === PRIM: LISTA SĄSIEDZTWA ===
            int V = graph->V;
            int* key = new int[V];
            bool* inMST = new bool[V];
            for (int i = 0; i < V; ++i) {
                key[i] = INT_MAX;
                inMST[i] = false;
            }

            key[0] = 0;
            int totalWeight = 0;

            for (int count = 0; count < V; ++count) {
                int u = -1, minKey = INT_MAX;
                for (int v = 0; v < V; ++v)
                    if (!inMST[v] && key[v] < minKey) {
                        minKey = key[v];
                        u = v;
                    }

                inMST[u] = true;
                totalWeight += key[u];

                Node* current = graph->adjList[u];
                while (current) {
                    int v = current->vertex;
                    int w = current->weight;
                    if (!inMST[v] && key[v] > w)
                        key[v] = w;
                    current = current->next;
                }
            }

            delete[] key;
            delete[] inMST;

            timer.stop();
            return timer.result();
        }
    }

    int kruskal(Timer& timer) {
        timer.reset();
        timer.start();

        struct Edge {
            int u, v, w;
        };

        struct DisjointSet {
            int* parent;
            int* rank;

            DisjointSet(int n) {
                parent = new int[n];
                rank = new int[n]();
                for (int i = 0; i < n; ++i)
                    parent[i] = i;
            }

            int find(int u) {
                if (parent[u] != u)
                    parent[u] = find(parent[u]);
                return parent[u];
            }

            bool unite(int u, int v) {
                int pu = find(u);
                int pv = find(v);
                if (pu == pv) return false;
                if (rank[pu] < rank[pv]) {
                    parent[pu] = pv;
                } else if (rank[pu] > rank[pv]) {
                    parent[pv] = pu;
                } else {
                    parent[pv] = pu;
                    rank[pu]++;
                }
                return true;
            }

            ~DisjointSet() {
                delete[] parent;
                delete[] rank;
            }
        };

        std::vector<Edge> edges;
        int V = 0;

        if (representation == 0) {
            while (incidenceMatrix[V]) ++V;
            int E = 0;
            while (incidenceMatrix[0][E] != -9999) ++E;

            for (int e = 0; e < E; ++e) {
                int u = -1, v = -1;
                for (int i = 0; i < V; ++i) {
                    if (incidenceMatrix[i][e]) {
                        if (u == -1) u = i;
                        else v = i;
                    }
                }
                if (u != -1 && v != -1)
                    edges.push_back({u, v, 1});
            }

        } else {
            V = graph->V;
            bool** visited = new bool*[V];
            for (int i = 0; i < V; ++i)
                visited[i] = new bool[V]();

            for (int u = 0; u < V; ++u) {
                Node* node = graph->adjList[u];
                while (node) {
                    int v = node->vertex;
                    if (!visited[u][v]) {
                        edges.push_back({u, v, node->weight});
                        visited[u][v] = visited[v][u] = true;
                    }
                    node = node->next;
                }
            }

            for (int i = 0; i < V; ++i)
                delete[] visited[i];
            delete[] visited;
        }

        std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.w < b.w;
        });

        DisjointSet dsu(V);
        int totalWeight = 0;
        for (const auto& e : edges) {
            if (dsu.unite(e.u, e.v)) {
                totalWeight += e.w;
            }
        }

        timer.stop();
        return timer.result();
    }
};

#endif // PROJEKTAIZO_MST_H
