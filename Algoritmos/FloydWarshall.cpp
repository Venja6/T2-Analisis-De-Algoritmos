#include "FloydWarshall.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Constructor: copia el grafo inicial y define el número de vértices
FloydWarshall::FloydWarshall(const vector<vector<int>>& graph) {
    dist = graph;
    V = graph.size();
}

// Ejecuta el algoritmo y retorna 'true' si hay ciclos negativos
bool FloydWarshall::run() {
    // Algoritmo clásico
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Comprobar ciclos negativos en la diagonal principal
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            return true;
        }
    }
    
    return false;
}

// Imprime la matriz formateada
void FloydWarshall::printResult() const {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                cout << "INF\t";
            } else {
                cout << dist[i][j] << "\t";
            }
        }
        cout << endl;
    }
}