import random
import time
import psutil
import os

def mediana_de_tres(arreglo, bajo, alto):

    #Selecciona el pivote usando la técnica de la mediana de tres.
  
    medio = (bajo + alto) // 2
    if arreglo[bajo] > arreglo[medio]:
        arreglo[bajo], arreglo[medio] = arreglo[medio], arreglo[bajo]
    if arreglo[bajo] > arreglo[alto]:
        arreglo[bajo], arreglo[alto] = arreglo[alto], arreglo[bajo]
    if arreglo[medio] > arreglo[alto]:
        arreglo[medio], arreglo[alto] = arreglo[alto], arreglo[medio]
    return medio

def particionar(arreglo, bajo, alto):
    """
    Función para particionar el arreglo en el algoritmo QuickSort.
    Utiliza la mediana de tres para seleccionar el pivote.
    """
    pivote_indice = mediana_de_tres(arreglo, bajo, alto)
    pivote = arreglo[pivote_indice]
    arreglo[pivote_indice], arreglo[alto] = arreglo[alto], arreglo[pivote_indice]
    
    i = bajo - 1
    for j in range(bajo, alto):
        if arreglo[j] <= pivote:
            i += 1
            arreglo[i], arreglo[j] = arreglo[j], arreglo[i]
    arreglo[i + 1], arreglo[alto] = arreglo[alto], arreglo[i + 1]
    return i + 1

def insercion_directa(arreglo, bajo, alto):

    #Implementación del algoritmo de ordenamiento por inserción directa.

    for i in range(bajo + 1, alto + 1):
        clave = arreglo[i]
        j = i - 1
        while j >= bajo and arreglo[j] > clave:
            arreglo[j + 1] = arreglo[j]
            j -= 1
        arreglo[j + 1] = clave

def ordenar_quicksort(arreglo, bajo, alto):
    """
    Implementación optimizada del algoritmo QuickSort.
    Utiliza inserción directa para subarreglos pequeños y evita la recursión excesiva.
    """
    while bajo < alto:
        if alto - bajo + 1 < 10:
            insercion_directa(arreglo, bajo, alto)
            break
        else:
            indice_particion = particionar(arreglo, bajo, alto)
            if indice_particion - bajo < alto - indice_particion:
                ordenar_quicksort(arreglo, bajo, indice_particion - 1)
                bajo = indice_particion + 1
            else:
                ordenar_quicksort(arreglo, indice_particion + 1, alto)
                alto = indice_particion - 1

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
    
    tiempo_ejecucion = tiempo_fin - tiempo_inicio
    uso_memoria = memoria_fin - memoria_inicio
    
    return tiempo_ejecucion, uso_memoria, copia_arreglo

def generar_arreglo_aleatorio(tamano):

    #Genera un arreglo de números enteros aleatorios.

    return [random.randint(1, 1000) for _ in range(tamano)]

def verificar_ordenamiento(arreglo):

    #Verifica si el arreglo está correctamente ordenado.

    return all(arreglo[i] <= arreglo[i+1] for i in range(len(arreglo)-1))

def main():
    tamanos = [100, 300, 500]
    
    for tamano in tamanos:
        print(f"\nConjunto de {tamano} elementos:")
        arreglo_original = generar_arreglo_aleatorio(tamano)
        
        tiempo_ejecucion, uso_memoria, arreglo_ordenado = medir_rendimiento(arreglo_original)
        
        print(f"Tiempo de Ejecución: {tiempo_ejecucion:.6f} segundos")
        print(f"Uso de Memoria: {uso_memoria:.6f} MB")
        
        if verificar_ordenamiento(arreglo_ordenado):
            print("El arreglo está correctamente ordenado.")
        else:
            print("Error: El arreglo no está correctamente ordenado.")

if __name__ == "__main__":
    main()