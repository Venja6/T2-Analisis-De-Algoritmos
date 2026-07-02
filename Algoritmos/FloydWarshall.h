#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include <vector>

class FloydWarshall {
private:
    std::vector<std::vector<int>> dist;
    int V;
    const int INF = 1e8;

public:
    // Constructor que recibe la matriz de adyacencia
    FloydWarshall(const std::vector<std::vector<int>>& graph);

    // Método principal para ejecutar el algoritmo
    bool run();

    // Método para imprimir la matriz resultante
    void printResult() const;
};

#endif // FLOYD_WARSHALL_H