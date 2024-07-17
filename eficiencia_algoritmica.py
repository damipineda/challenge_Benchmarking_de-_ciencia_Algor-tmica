import random
import time
import psutil
import os

def particionar(arreglo, bajo, alto):
    """
    Función para particionar el arreglo en el algoritmo QuickSort.
    Elige el último elemento como pivote y lo coloca en su posición correcta.
    """
    pivote = arreglo[alto]
    i = bajo - 1
    for j in range(bajo, alto):
        if arreglo[j] <= pivote:
            i += 1
            arreglo[i], arreglo[j] = arreglo[j], arreglo[i]
    arreglo[i + 1], arreglo[alto] = arreglo[alto], arreglo[i + 1]
    return i + 1

def ordenar_quicksort(arreglo, bajo, alto):
    #Implementación recursiva del algoritmo QuickSort.

    if bajo < alto:
        indice_particion = particionar(arreglo, bajo, alto)
        ordenar_quicksort(arreglo, bajo, indice_particion - 1)
        ordenar_quicksort(arreglo, indice_particion + 1, alto)

def obtener_uso_memoria():

    #Función para obtener el uso actual de memoria en MB.

    proceso = psutil.Process(os.getpid())
    return proceso.memory_info().rss / (1024 * 1024)  # Convertir a MB

def medir_rendimiento(arreglo):

    #Mide el tiempo de ejecución y uso de memoria del algoritmo QuickSort.

    copia_arreglo = arreglo.copy()
    
    tiempo_inicio = time.time()
    memoria_inicio = obtener_uso_memoria()
    
    ordenar_quicksort(copia_arreglo, 0, len(copia_arreglo) - 1)
    
    tiempo_fin = time.time()
    memoria_fin = obtener_uso_memoria()
    
    tiempo_ejecucion = tiempo_fin - tiempo_inicio  # Tiempo en segundos
    uso_memoria = memoria_fin - memoria_inicio
    
    return tiempo_ejecucion, uso_memoria, copia_arreglo

def generar_arreglo_aleatorio(tamano):

    #Genera un arreglo de números enteros aleatorios.

    return [random.randint(1, 1000) for _ in range(tamano)]

def verificar_ordenamiento(arreglo):

    #Verifica si el arreglo esta correctamente ordenado.

    return all(arreglo[i] <= arreglo[i+1] for i in range(len(arreglo)-1))

def main():
    tamanos = [100, 300, 500]
    
    for tamano in tamanos:
        print(f"\nConjunto de {tamano} elementos:")
        arreglo_original = generar_arreglo_aleatorio(tamano)
        
        tiempo_ejecucion, uso_memoria, arreglo_ordenado = medir_rendimiento(arreglo_original)
        
        print(f"Tiempo de Ejecucion: {tiempo_ejecucion:.6f} sgs")
        print(f"Uso de Memoria: {uso_memoria:.6f} MB")
        
        if verificar_ordenamiento(arreglo_ordenado):
            print("El arreglo esta correctamente ordenado.")
        else:
            print("Error: El arreglo no esta correctamente ordenado.")

if __name__ == "__main__":
    main()