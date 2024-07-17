//El programa genera distintos conjuntos de datos (aleatorios, casi ordenados, inversamente ordenados y con muchos duplicados) 
//en tres tamaños (100, 300 y 500 elementos) y los ordena utilizando un algoritmo QuickSort optimizado con la técnica de "mediana de tres" 
//y std::sort para subarrays pequeños. Para medir la eficiencia, el tiempo de ejecución se evalúa varias veces para cada conjunto de datos 
//y se calcula un promedio, proporcionando una medida precisa de la eficiencia del algoritmo en diferentes escenarios.
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <numeric> 

// Función para calcular la mediana de tres elementos y colocarla en la posición correcta
int medianaDeTres(std::vector<int>& arreglo, int izquierda, int derecha) {
    int centro = (izquierda + derecha) / 2;

    // Ordenar los tres elementos (izquierda, centro, derecha)
    if (arreglo[izquierda] > arreglo[centro]) std::swap(arreglo[izquierda], arreglo[centro]);
    if (arreglo[izquierda] > arreglo[derecha]) std::swap(arreglo[izquierda], arreglo[derecha]);
    if (arreglo[centro] > arreglo[derecha]) std::swap(arreglo[centro], arreglo[derecha]);

    // Colocar la mediana (centro) en la penúltima posición (derecha - 1) para usarla como pivote
    std::swap(arreglo[centro], arreglo[derecha - 1]);
    return arreglo[derecha - 1]; // Devolver el valor del pivote
}

// Función principal de QuickSort (recursiva)
void ordenarQuicksort(std::vector<int>& arreglo, int izquierda, int derecha) {
    // Caso base: si el subarreglo tiene menos de 10 elementos, usar std::sort (más eficiente para subarreglos pequeños)
    if (izquierda + 10 <= derecha) {
        int pivote = medianaDeTres(arreglo, izquierda, derecha); // Seleccionar el pivote

        // Particionar el arreglo alrededor del pivote
        int indiceIzquierda = izquierda;
        int indiceDerecha = derecha - 1;
        while (true) {
            while (arreglo[++indiceIzquierda] < pivote) {} // Mover indiceIzquierda hasta encontrar un elemento mayor o igual al pivote
            while (arreglo[--indiceDerecha] > pivote) {}  // Mover indiceDerecha hasta encontrar un elemento menor o igual al pivote
            if (indiceIzquierda < indiceDerecha) {
                std::swap(arreglo[indiceIzquierda], arreglo[indiceDerecha]); // Intercambiar elementos si están en el lado incorrecto del pivote
            } else {
                break; // Salir del bucle cuando los índices se cruzan
            }
        }
        std::swap(arreglo[indiceIzquierda], arreglo[derecha - 1]); // Colocar el pivote en su posición final

        // Ordenar recursivamente las dos particiones
        ordenarQuicksort(arreglo, izquierda, indiceIzquierda - 1);
        ordenarQuicksort(arreglo, indiceIzquierda + 1, derecha);
    } else {
        std::sort(arreglo.begin() + izquierda, arreglo.begin() + derecha + 1); // Ordenar subarreglo pequeño con std::sort
    }
}

// Función para medir el tiempo de ejecución promedio de QuickSort sobre varias repeticiones
void medirTiempoDeOrdenamiento(std::vector<int>& arreglo, int repeticiones) {
    std::vector<double> tiempos(repeticiones); // Vector para almacenar los tiempos de cada repetición

    for (int i = 0; i < repeticiones; ++i) {
        std::vector<int> copiaArreglo = arreglo; // Crear una copia del arreglo para no modificar el original
        auto inicio = std::chrono::high_resolution_clock::now(); // Registrar el tiempo de inicio
        ordenarQuicksort(copiaArreglo, 0, copiaArreglo.size() - 1); // Ordenar la copia
        auto fin = std::chrono::high_resolution_clock::now(); // Registrar el tiempo de fin
        std::chrono::duration<double> duracion = fin - inicio; // Calcular la duración
        tiempos[i] = duracion.count(); // Almacenar el tiempo en segundos
    }

    // Calcular el tiempo promedio
    double tiempoPromedio = std::accumulate(tiempos.begin(), tiempos.end(), 0.0) / repeticiones;
    std::cout << "Tiempo de ejecución promedio: " << tiempoPromedio << " segundos\n";
}

// Función para generar datos aleatorios
std::vector<int> generarDatosAleatorios(int tamano, int rango) {
    std::vector<int> datos(tamano);
    std::generate(datos.begin(), datos.end(), [rango]() { return rand() % rango; }); // Generar números aleatorios en el rango [0, rango)
    return datos;
}

// Función para generar datos casi ordenados
std::vector<int> generarDatosCasiOrdenados(int tamano) {
    std::vector<int> datos(tamano);
    std::iota(datos.begin(), datos.end(), 0); // Generar una secuencia ordenada de 0 a tamano-1
    // Intercambiar algunos elementos para desordenar ligeramente
    for (int i = 0; i < tamano / 10; ++i) {
        std::swap(datos[rand() % tamano], datos[rand() % tamano]); 
    }
    return datos;
}

// Función para generar datos inversamente ordenados
std::vector<int> generarDatosInversamenteOrdenados(int tamano) {
    std::vector<int> datos(tamano);
    std::iota(datos.rbegin(), datos.rend(), 0); // Generar una secuencia inversa de tamano-1 a 0
    return datos;
}

// Función para generar datos con muchos duplicados
std::vector<int> generarDatosConDuplicados(int tamano, int rango) {
    std::vector<int> datos(tamano);
    std::generate(datos.begin(), datos.end(), [rango]() { return rand() % (rango / 10); }); // Generar números aleatorios con muchos duplicados
    return datos;
}

int main() {
    int tamanos[] = {100, 300, 500}; // Tamaños de los conjuntos de datos
    int repeticiones = 5; // Número de repeticiones para cada conjunto de datos

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
