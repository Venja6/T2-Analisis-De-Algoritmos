#include "BellmanFord.h"
#include <iostream>

using namespace std;

BellmanFord::BellmanFord(const vector<vector<int>>& g) {
    graph = g;
    V = g.size();
    allDistances.resize(V);
}

vector<int> BellmanFord::runSingleSource(int src, bool &hasNegativeCycle) {
    vector<int> dist(V, INF);
    dist[src] = 0;
    hasNegativeCycle = false;

    for (int i = 0; i < V; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (u == v || graph[u][v] == INF)
                    continue;

                int wt = graph[u][v];

                if (dist[u] != INF && dist[u] + wt < dist[v]) {
                    // Si es la V-ésima relajación, hay un ciclo negativo
                    if (i == V - 1) {
                        hasNegativeCycle = true;
                        return {};
                    }
                    dist[v] = dist[u] + wt;
                }
            }
        }
    }
    return dist;
}

bool BellmanFord::runAllSources() {
    for (int src = 0; src < V; src++) {
        bool negativeCycle = false;
        vector<int> ans = runSingleSource(src, negativeCycle);
        
        if (negativeCycle) {
            return true; // Se encontró ciclo negativo
        }
        allDistances[src] = ans; // Guardar resultados si todo está bien
    }
    return false; // No hay ciclos negativos
}

void BellmanFord::printResult() const {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (allDistances[i][j] == INF)
                cout << "INF\t";
            else
                cout << allDistances[i][j] << "\t";
        }
        cout << endl;
    }
}