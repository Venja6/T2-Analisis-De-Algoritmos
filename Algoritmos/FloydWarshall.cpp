#include "FloydWarshall.h"
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

// Constructor: copia el grafo inicial y define el número de vértices
FloydWarshall::FloydWarshall(const vector<vector<double>>& graph) {
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


void FloydWarshall::makeCSV() const {
    std::string nombreCSV = "resultado_distancias2.csv";
    std::ofstream archivoCSV(nombreCSV);

    if (!archivoCSV.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo CSV." << std::endl;
        return;
    }

    archivoCSV << "Nodo_Origen;Nodo_Destino;Peso_Del_Camino\n";

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            
            if (dist[i][j] == INF) {
                continue; 
            }
            
            int nodo_origen = i + 1;
            int nodo_destino = j + 1;
            archivoCSV << nodo_origen << ";" << nodo_destino << ";" << dist[i][j] << "\n";
        }
    }
    archivoCSV.close();
}