#include <iostream>
#include "DigraphGenerator.h"
#include "../Algoritmos/FloydWarshall.h"

//Para ejecutar correr en terminal
//g++ graphtest.cpp ../Algoritmos/FloydWarshall.cpp DigraphGenerator.cpp -o dgraphgen
//Luego ejecutar ./dgraphgen
using namespace std;

void probarGrafo(const vector<vector<int>>& grafo, string nombrePrueba) {
    cout << "--- " << nombrePrueba << " ---" << endl;
    FloydWarshall fw(grafo);
    
    if (fw.run()) {
        cout << ">>> RESULTADO: Se detecto un ciclo negativo.\n\n";
    } else {
        cout << ">>> RESULTADO: NO hay ciclos negativos. Rutas calculadas.\n\n";
    }
}

int main() {
    int V = 5;       // 5 vértices
    int minW = -10;  // Peso mínimo
    int maxW = 10;   // Peso máximo
    
    // Instanciamos el generador con una semilla fija para que sea reproducible
    DigraphGenerator generador(V, minW, maxW, 42);

    // 1. Grafo positivo (NO debe detectar ciclo negativo)
    auto grafoPositivo = generador.generatePositiveDigraph();
    probarGrafo(grafoPositivo, "Prueba 1: Grafo Positivo");

    // 2. Grafo con ciclo negativo (SI debe detectar ciclo negativo)
    auto grafoCicloNegativo = generador.generateNegativeCycleDigraph();
    probarGrafo(grafoCicloNegativo, "Prueba 2: Grafo con Ciclo Negativo Garantizado");

    // 3. Grafo sin ciclos, pero con pesos negativos (NO debe detectar ciclo negativo)
    auto grafoSinCiclos = generador.generateMixedNoNegativeCycleDigraph();
    probarGrafo(grafoSinCiclos, "Prueba 3: Grafo Mixto sin Ciclos");

    auto grafoBosque = generador.generateForest();
    probarGrafo(grafoBosque, "Prueba 4: Bosque Dirigido con Pesos Positivos y Negativos");

    return 0;
}