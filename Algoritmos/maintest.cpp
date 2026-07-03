#include <iostream>
#include <vector>
#include "FloydWarshall.h"
#include "BellmanFord.h"

using namespace std;

// Para compilar se debe usar
// g++ -std=c++20 maintest.cpp BellmanFord.cpp FloydWarshall.cpp -o test

int main() {
    int V = 5;
    const int INF = 1e8;

    // Inicializamos el grafo con INF
    vector<vector<int>> graph(V, vector<int>(V, INF));
    
    // Rellenamos la diagonal principal con 0 (muy importante para Floyd-Warshall)
    for(int i = 0; i < V; i++) {
        graph[i][i] = 0;
    }

    // Agregamos las aristas
    graph[3][1] = 2;
    graph[4][3] = 1;
    graph[2][4] = 1;
    graph[1][2] = 1;
    graph[0][1] = 5;
    graph[4][0] = 3;

    cout << "Selecciona el algoritmo descomentando el bloque deseado en el codigo." << endl << endl;

    // ==========================================
    // OPCIÓN 1: Usar Bellman-Ford
    // ==========================================
    /*
    cout << "--- Ejecutando Bellman-Ford ---" << endl;
    BellmanFord bf(graph);
    if (bf.runAllSources()) {
        cout << "Negative cycle detected!" << endl;
    } else {
        cout << "Shortest distances:" << endl;
        bf.printResult();
    }
    */
    

    // ==========================================
    // OPCIÓN 2: Usar Floyd-Warshall
    // ==========================================
    
    cout << "--- Ejecutando Floyd-Warshall ---" << endl;
    FloydWarshall fw(graph);
    if (fw.run()) {
        cout << "Negative cycle detected!" << endl;
    } else {
        cout << "Shortest distances:" << endl;
        fw.printResult();
    }
    

    return 0;
}