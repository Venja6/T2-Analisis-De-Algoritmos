# T2-Analisis-De-Algoritmos

## Ejecucion y recolección de datos
Para conseguir un resultado en los tiempos de ejecucion de ambos algoritmos, usamos el código de testeo "uhr" el que ofrece un ambiente donde podemos evaluar la eficiencia de cada algoritmo al tratar con distintos tipos de problemas.
Todas las pruebas se hicieron con un minW de -10 y un maxW de 30, cuando el grafo es positivo todos los pesos negativos se convierten en 1

Compilando con -O3 para una mejor optimizacion:
g++ -std=c++17 -O3 uhr.cpp ../Grafos/DigraphGenerator.cpp ../Algoritmos/BellmanFord.cpp ../Algoritmos/FloydWarshall.cpp -o test

*Dentro del código se determina que algoritmo a usar y el tipo de grafo sobre el que queremos trabajar

Como argumentos, se dieron:
./test [algoritmo_instancia.csv] [32 Iteraciones] [4 Nodos mínimos] [512 Nodos máximos] [2 Como factor de multiplicacion en los pasos]

Que es lo mismo a:
./test nombre.csv 32 4 512 2 

Como resultado de uhr.cpp, terminamos con varios .csv de los tiempos de ejecución.