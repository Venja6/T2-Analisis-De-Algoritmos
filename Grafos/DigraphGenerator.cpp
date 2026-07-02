#include "DigraphGenerator.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>

using namespace std;

DigraphGenerator::DigraphGenerator(int V, int minW, int maxW, unsigned seed)
    : V(V), minW(minW), maxW(maxW), rng(seed) {

    if (V <= 0)
        throw invalid_argument("V debe ser mayor a 0");
    if (minW > maxW)
        throw invalid_argument("minW no puede ser mayor a maxW");
}

vector<vector<int>> DigraphGenerator::emptyMatrix() const {
    vector<vector<int>> graph(V, vector<int>(V, INF));
    for (int i = 0; i < V; i++) graph[i][i] = 0;
    return graph;
}

// ============================================================
// 1) Digrafo simple con ciclos y pesos POSITIVOS
// ============================================================
vector<vector<int>> DigraphGenerator::generatePositiveDigraph() {
    // Forzamos que el rango de pesos sea positivo (minimo 1)
    int lo = max(1, minW);
    int hi = max(lo, maxW);

    uniform_real_distribution<double> prob(0.0, 1.0);
    uniform_int_distribution<int> weight(lo, hi);

    auto graph = emptyMatrix();

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) continue;
            if (prob(rng) < EDGE_PROBABILITY) {
                graph[i][j] = weight(rng);
            }
        }
    }

    // Nos aseguramos de que el grafo tenga al menos un ciclo
    bool hasCycle = false;
    for (int i = 0; i < V && !hasCycle; i++)
        for (int j = 0; j < V && !hasCycle; j++)
            if (i != j && graph[i][j] != INF && graph[j][i] != INF)
                hasCycle = true;

    if (!hasCycle && V >= 2) {
        graph[0][1] = weight(rng);
        graph[1][0] = weight(rng);
    }

    return graph;
}

// ============================================================
// 2) Digrafo con al menos un CICLO NEGATIVO garantizado
// ============================================================
vector<vector<int>> DigraphGenerator::generateNegativeCycleDigraph() {
    if (V < 2)
        throw invalid_argument("Se necesitan al menos 2 vertices para un ciclo negativo");

    uniform_real_distribution<double> prob(0.0, 1.0);
    uniform_int_distribution<int> weight(minW, maxW);
    uniform_int_distribution<int> cycleLenDist(2, V);

    auto graph = emptyMatrix();

    // Grafo base con pesos mixtos, densidad EDGE_PROBABILITY
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) continue;
            if (prob(rng) < EDGE_PROBABILITY) {
                graph[i][j] = weight(rng);
            }
        }
    }

    // Elegimos un subconjunto aleatorio de vertices para formar el ciclo
    vector<int> order(V);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end(), rng);

    int cycleLen = cycleLenDist(rng);
    vector<int> cycle(order.begin(), order.begin() + cycleLen);

    long long sum = 0;
    vector<int> cycleWeights(cycleLen);
    for (int k = 0; k < cycleLen; k++) {
        cycleWeights[k] = weight(rng);
        sum += cycleWeights[k];
    }

    // Si la suma no quedo negativa, ajustamos la ultima arista del
    // ciclo para forzar que la suma total quede en -1
    if (sum >= 0) {
        long long oldLast = cycleWeights[cycleLen - 1];
        long long newLast = oldLast - sum - 1;
        cycleWeights[cycleLen - 1] = (int)newLast;
    }

    for (int k = 0; k < cycleLen; k++) {
        int u = cycle[k];
        int v = cycle[(k + 1) % cycleLen];
        graph[u][v] = cycleWeights[k];
    }

    return graph;
}

// ============================================================
// 3) Digrafo mixto SIN ciclos negativos (implementado como DAG)
// ============================================================
vector<vector<int>> DigraphGenerator::generateMixedNoNegativeCycleDigraph() {
    uniform_real_distribution<double> prob(0.0, 1.0);
    uniform_int_distribution<int> weight(minW, maxW);

    auto graph = emptyMatrix();

    // Orden aleatorio de vertices: solo se permiten aristas
    // order[a] -> order[b] si a < b (garantiza DAG, sin ciclos)
    vector<int> order(V);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end(), rng);

    for (int a = 0; a < V; a++) {
        for (int b = a + 1; b < V; b++) {
            if (prob(rng) < EDGE_PROBABILITY) {
                int u = order[a];
                int v = order[b];
                graph[u][v] = weight(rng);
            }
        }
    }

    return graph;
}

// ============================================================
// 4) Bosque dirigido con pesos positivos y negativos
// ============================================================
vector<vector<int>> DigraphGenerator::generateForest(double newRootProbability) {
    uniform_real_distribution<double> prob(0.0, 1.0);
    uniform_int_distribution<int> weight(minW, maxW);

    auto graph = emptyMatrix();

    vector<int> order(V);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end(), rng);

    vector<int> placed; // vertices ya insertados en el bosque

    for (int idx = 0; idx < V; idx++) {
        int v = order[idx];

        // El primer vertice siempre es raiz. Los demas se vuelven
        // raiz nueva con probabilidad newRootProbability, o se
        // cuelgan de un padre ya existente elegido al azar.
        if (placed.empty() || prob(rng) < newRootProbability) {
            placed.push_back(v);
            continue;
        }

        uniform_int_distribution<int> parentPick(0, (int)placed.size() - 1);
        int parent = placed[parentPick(rng)];
        graph[parent][v] = weight(rng);
        placed.push_back(v);
    }

    return graph;
}