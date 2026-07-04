#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include <vector>
#include <limits>


class FloydWarshall {
private:
    std::vector<std::vector<double>> dist;
    int V;
    const double INF = std::numeric_limits<double>::infinity();

public:
    // Constructor que recibe la matriz de adyacencia
    FloydWarshall(const std::vector<std::vector<double>>& graph);

    // Método principal para ejecutar el algoritmo
    bool run();

    // Método para imprimir la matriz resultante
    void printResult() const;

    // Método para exportar la matriz resultante a un archivo CSV
    void makeCSV() const;
};

#endif // FLOYD_WARSHALL_H