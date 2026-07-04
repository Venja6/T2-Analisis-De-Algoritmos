#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
#include <limits>

#include "../Algoritmos/FloydWarshall.h"

const double INF = std::numeric_limits<double>::infinity();

std::vector<std::vector<double>> leerMatriz(std::string nombreArchivo) {
    std::ifstream file(nombreArchivo);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return {};
    }

    std::string linea;

    while (std::getline(file, linea)) {
        if (linea.empty()) continue;
        if (linea[0] != '%') {
            break; 
        }
    }
    
    int filas = 0, columnas = 0, aristas = 0;
    std::stringstream ss_dimensiones(linea);
    ss_dimensiones >> filas >> columnas >> aristas;    
    
    std::vector<std::vector<double>> matriz(filas, std::vector<double>(columnas, INF));
    
    for (int i = 0; i < filas; i++) {
        matriz[i][i] = 0.0;
    }
    
    //std::cout << "INFORMACION DEL GRAFO" << std::endl;
    //std::cout << "Nodos: " << filas << std::endl;
    std::cout << "Aristas: " << aristas << std::endl;

    int origen, destino;
    double peso;
    int aristasLeidas = 0;

    while (std::getline(file, linea)) {
        if (linea.empty()) continue; 

        std::stringstream ss_linea(linea);
        if (!(ss_linea >> origen >> destino >> peso)) {
            continue; 
        }

        if (origen == destino) {
            continue; 
        }
        
        if (origen >= 0 && origen < filas && destino >= 0 && destino < columnas) {
            matriz[origen][destino] = peso;
            aristasLeidas++;
        }
    }

    file.close();
    std::cout << "Lectura completada. Aristas válidas cargadas: " << aristasLeidas << std::endl;
    return matriz;
}

int main() {
    std::string nombreArchivo = "bio-SC-TS.edges"; 
    
    auto matriz = leerMatriz(nombreArchivo);
    if (matriz.empty()) {
        std::cerr << "Error: Matriz vacía. Abortando." << std::endl;
        return 1;
    }

    
    std::cout << "Iniciando algoritmo de Floyd-Warshall..." << std::endl;
    
    FloydWarshall fw(matriz);
    auto t_start = std::chrono::high_resolution_clock::now();
    bool tieneCicloNegativo = fw.run();
    auto t_end = std::chrono::high_resolution_clock::now();
    fw.makeCSV();
    std::chrono::duration<double, std::nano> duration = t_end - t_start;

    std::cout << "Tiempo de ejecución: " << duration.count() << " ns" << std::endl;
    
    return 0;
}