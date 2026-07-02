#ifndef DIGRAPH_GENERATOR_H
#define DIGRAPH_GENERATOR_H

#include <vector>
#include <random>

// ============================================================
//  DigraphGenerator
//
//  Genera digrafos con peso representados como matriz de
//  adyacencia (vector<vector<int>>).
//
//  Convencion:
//    - graph[i][j] = peso de la arista i -> j
//    - graph[i][i] = 0     (diagonal, no se usa como arista)
//    - graph[i][j] = INF   (no existe arista i -> j)
// ============================================================

class DigraphGenerator {
private:
    int V;
    int minW;
    int maxW;
    const int INF = 1e8;
    const double EDGE_PROBABILITY = 0.3; // densidad fija de aristas
    std::mt19937 rng;

    // Metodo privado: matriz VxV llena de INF, con 0 en la diagonal
    std::vector<std::vector<int>> emptyMatrix() const;

public:
    // Constructor
    DigraphGenerator(int V, int minW, int maxW,
                      unsigned seed = std::random_device{}());

    // 1) Digrafo simple con ciclos y pesos POSITIVOS
    std::vector<std::vector<int>> generatePositiveDigraph();

    // 2) Digrafo con al menos un CICLO NEGATIVO garantizado
    std::vector<std::vector<int>> generateNegativeCycleDigraph();

    // 3) Digrafo con pesos positivos y negativos pero SIN ciclos
    //    negativos (construido como DAG, asi que no tiene ciclos
    //    de ningun tipo)
    std::vector<std::vector<int>> generateMixedNoNegativeCycleDigraph();

    // 4) Bosque dirigido con pesos positivos y negativos.
    //    No es necesariamente conexo: puede haber vertices a los
    //    que no se puede llegar desde otros (raices sueltas).
    std::vector<std::vector<int>> generateForest(double newRootProbability = 0.3);
};

#endif // DIGRAPH_GENERATOR_H