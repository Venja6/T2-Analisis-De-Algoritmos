#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <vector>

class BellmanFord {
private:
    std::vector<std::vector<int>> graph;
    int V;
    const int INF = 1e8;
    std::vector<std::vector<int>> allDistances; // Guarda el resultado final

    // Método privado para ejecutar el algoritmo desde un solo nodo origen
    std::vector<int> runSingleSource(int src, bool &hasNegativeCycle);

public:
    // Constructor
    BellmanFord(const std::vector<std::vector<int>>& g);

    // Ejecuta Bellman-Ford para todos los vértices
    bool runAllSources();

    // Imprime la matriz resultante
    void printResult() const;
};

#endif // BELLMAN_FORD_H