#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>


std::vector<std::vector<double>> leerMatriz(std::string nombreArchivo) {
    std::ifstream file(nombreArchivo);  //Chebyshev2.mtx es el archivo de la actividad 1
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
        return {};
    }

    std::string linea;

    //Ignora las lineas iniciales
    while (std::getline(file, linea)) {
        if (linea.empty()) continue;
        if (linea[0] != '%') {
            break;
        }
    }

    int filas = 0, columnas = 0, aristas = 0;
    std::stringstream ss_dimensiones(linea);
    ss_dimensiones >> filas >> columnas >> aristas;
    std::vector<std::vector<double>> matriz(filas, std::vector<double>(columnas, 0.0));

    std::cout << "INFORMACION" << std::endl;
    std::cout << "Nodos:" << filas << std::endl;
    std::cout << "Aristas: " << aristas << std::endl;

    int origen, destino;
    double peso;
    while (file >> origen >> destino >> peso) {
        matriz[origen][destino] = peso; 
    }

    file.close();
    return matriz;
}

int main(){
    std::string nombreArchivo = "Chebyshev2.mtx";
    auto matriz = leerMatriz(nombreArchivo);
    //Algoritmos
    return 0;
}