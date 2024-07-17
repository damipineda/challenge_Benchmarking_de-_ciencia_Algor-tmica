//El programa genera distintos conjuntos de datos (aleatorios, casi ordenados, inversamente ordenados y con muchos duplicados) 
//en tres tamaños (100, 300 y 500 elementos) y los ordena utilizando un algoritmo QuickSort optimizado con la técnica de "mediana de tres" 
//y std::sort para subarrays pequeños. Para medir la eficiencia, el tiempo de ejecución se evalúa varias veces para cada conjunto de datos 
//y se calcula un promedio, proporcionando una medida precisa de la eficiencia del algoritmo en diferentes escenarios.

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <numeric>  // Para std::accumulate

void quicksort(std::vector<int>& arreglo, int izquierda, int derecha);
void medirTiempoDeOrdenamiento(std::vector<int>& arreglo, int repeticiones);

int medianaDeTres(std::vector<int>& arreglo, int izquierda, int derecha) {
    int centro = (izquierda + derecha) / 2;
    if (arreglo[izquierda] > arreglo[centro]) std::swap(arreglo[izquierda], arreglo[centro]);
    if (arreglo[izquierda] > arreglo[derecha]) std::swap(arreglo[izquierda], arreglo[derecha]);
    if (arreglo[centro] > arreglo[derecha]) std::swap(arreglo[centro], arreglo[derecha]);
    std::swap(arreglo[centro], arreglo[derecha - 1]);
    return arreglo[derecha - 1];
}

void ordenarQuicksort(std::vector<int>& arreglo, int izquierda, int derecha) {
    if (izquierda + 10 <= derecha) {
        int pivote = medianaDeTres(arreglo, izquierda, derecha);

        int indiceIzquierda = izquierda;
        int indiceDerecha = derecha - 1;
        while (true) {
            while (arreglo[++indiceIzquierda] < pivote) {}
            while (arreglo[--indiceDerecha] > pivote) {}
            if (indiceIzquierda < indiceDerecha) {
                std::swap(arreglo[indiceIzquierda], arreglo[indiceDerecha]);
            } else {
                break;
            }
        }
        std::swap(arreglo[indiceIzquierda], arreglo[derecha - 1]);

        ordenarQuicksort(arreglo, izquierda, indiceIzquierda - 1);
        ordenarQuicksort(arreglo, indiceIzquierda + 1, derecha);
    } else {
        std::sort(arreglo.begin() + izquierda, arreglo.begin() + derecha + 1);
    }
}

void medirTiempoDeOrdenamiento(std::vector<int>& arreglo, int repeticiones) {
    std::vector<double> tiempos(repeticiones);
    for (int i = 0; i < repeticiones; ++i) {
        std::vector<int> copiaArreglo = arreglo;  // Crear una copia del arreglo original
        auto inicio = std::chrono::high_resolution_clock::now();
        ordenarQuicksort(copiaArreglo, 0, copiaArreglo.size() - 1);
        auto fin = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duracion = fin - inicio;
        tiempos[i] = duracion.count();
    }
    double tiempoPromedio = std::accumulate(tiempos.begin(), tiempos.end(), 0.0) / repeticiones;
    std::cout << "Tiempo de ejecución promedio: " << tiempoPromedio << " segundos\n";
}

std::vector<int> generarDatosAleatorios(int tamano, int rango) {
    std::vector<int> datos(tamano);
    std::generate(datos.begin(), datos.end(), [rango]() { return rand() % rango; });
    return datos;
}

std::vector<int> generarDatosCasiOrdenados(int tamano) {
    std::vector<int> datos(tamano);
    std::iota(datos.begin(), datos.end(), 0); // Genera 0, 1, 2, ...
    // Intercambia algunos elementos para desordenar ligeramente
    for (int i = 0; i < tamano / 10; ++i) {
        std::swap(datos[rand() % tamano], datos[rand() % tamano]);
    }
    return datos;
}

std::vector<int> generarDatosInversamenteOrdenados(int tamano) {
    std::vector<int> datos(tamano);
    std::iota(datos.rbegin(), datos.rend(), 0); // Genera tamano-1, tamano-2, ...
    return datos;
}

std::vector<int> generarDatosConDuplicados(int tamano, int rango) {
    std::vector<int> datos(tamano);
    std::generate(datos.begin(), datos.end(), [rango]() { return rand() % (rango / 10); }); // Muchos duplicados
    return datos;
}

int main() {
    int tamanos[] = {100, 300, 500};
    int repeticiones = 5;  // Número de repeticiones para cada conjunto de datos

    for (int tamano : tamanos) {
        std::cout << "Conjunto de datos aleatorios (" << tamano << " elementos):\n";
        std::vector<int> datosAleatorios = generarDatosAleatorios(tamano, 1000);
        medirTiempoDeOrdenamiento(datosAleatorios, repeticiones);

        std::cout << "Conjunto de datos casi ordenados (" << tamano << " elementos):\n";
        std::vector<int> datosCasiOrdenados = generarDatosCasiOrdenados(tamano);
        medirTiempoDeOrdenamiento(datosCasiOrdenados, repeticiones);

        std::cout << "Conjunto de datos inversamente ordenados (" << tamano << " elementos):\n";
        std::vector<int> datosInversamenteOrdenados = generarDatosInversamenteOrdenados(tamano);
        medirTiempoDeOrdenamiento(datosInversamenteOrdenados, repeticiones);

        std::cout << "Conjunto de datos con muchos duplicados (" << tamano << " elementos):\n";
        std::vector<int> datosConDuplicados = generarDatosConDuplicados(tamano, 1000);
        medirTiempoDeOrdenamiento(datosConDuplicados, repeticiones);

        std::cout << "-----------------------------------\n";
    }

    return 0;
}
