//106249 Franco Papa - Heap Minimal

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef int (*heap_Comparador)(void*, void*);
typedef void (*heap_Destructor)(void*);

typedef struct heap {
	heap_Comparador comparador;
	heap_Destructor destructor;

	size_t cantidad;
	void **elementos;
} heap_t;


heap_t *heap_crear(heap_Comparador comparador, heap_Destructor destructor);
//pre- Recibe un puntero a una funcion de comparacion y una de destruccion, la segunda puede ser NULL
//post- Crea el heap. Devuelve un puntero al mismo o NULL en caso de error.

void heap_heapify(heap_t *heap);
//pre- Recibe un ptr a un heap
//post- Ordena el vector del heap de forma que quede un heap minimal.

void *heap_raiz(heap_t *heap);
//pre- Recibe un puntero a un heap
//post- Devuelve un puntero al elemento ubicado en la raiz del heap.

void heap_quitar_raiz(heap_t *heap);
//pre- Recibe un puntero a un heap
//post- Quita la raiz del heap y luego lo ordena.

void heap_vaciar(heap_t *heap);
//pre- Recibe un puntero a un heap
//post- Destruye a todos los elementos del heap usando el destructor del mismo. Si no hay destructor simplemente libera los 'nodos'.

void heap_destruir(heap_t *heap);
//pre- Recibe un puntero a un heap
//post- Vacia al heap en caso de que no este vacio y luego libera la memoria que habia reservada para este.

int heap_insertar(heap_t *heap, void *elemento);
//pre- Recibe un puntero a un heap y a un elemento cualquiera
//post- Inserta un elemento en el heap. Devuelve -1 en caso de error o 0 si fue exitoso.

bool heap_esta_vacia(heap_t *heap);
//pre- Recibe un puntero a un heap
//post- Devuelve 1 si el heap esta vacio o 0 si no lo esta.

size_t heap_cantidad(heap_t *heap);
//pre- Recibe un puntero a un heap
//post- Devuelve la cantidad de elementos almacenados en el heap.

#endif /*__HEAP_H__*/