#include "heap.h"

heap_t *heap_crear(heap_Comparador comparador, heap_Destructor destructor){
	heap_t *retorno = NULL;

	if (comparador){
		heap_t *miHeap = calloc(1, sizeof(heap_t));
		
		if (miHeap){
			miHeap->comparador = comparador;
			
			if(destructor)
				miHeap->destructor = destructor;

			miHeap->cantidad = 0;
			retorno = miHeap;
		}
	}
	return retorno;
}

void swap(void **a, void **b){
	void *aux = *a;
	*a = *b;
	*b = aux;
}

size_t heap_cantidad(heap_t *heap){
	size_t retorno = 0;
	if (heap)
		retorno = heap->cantidad;

	return retorno;
}

void *heap_raiz(heap_t *heap){
	void *retorno = NULL;

	if (heap){
		if (heap->elementos)
			retorno = heap->elementos[0];
	}
	return retorno;
}

void heap_sift_down(heap_t *heap, int n){
	bool izq_es_menor = false;
	bool der_es_menor = false;

	if (n*2 + 1 < heap_cantidad(heap)){ 		//Tiene Hijo Izquierdo
		if (heap->comparador(heap->elementos[n], heap->elementos[2*n +1]) == -1)
			izq_es_menor = true;

		if (n*2 + 2 < heap_cantidad(heap)){		//Tiene Hijo Derecho
			if (heap->comparador(heap->elementos[n], heap->elementos[2*n +2]) == -1)
				der_es_menor = true;
		}
		
		if (izq_es_menor && der_es_menor){		//Buscamos al menor de los 2
			if (heap->comparador(heap->elementos[2*n + 1], heap->elementos[2*n + 2]) == -1)
				izq_es_menor = false;
			else
				der_es_menor = false;
		}
				

		if (izq_es_menor){
			swap(&heap->elementos[n], &heap->elementos[2*n + 1]);
			heap_sift_down(heap, 2*n + 1);
		}

		else if (der_es_menor){
			swap(&heap->elementos[n], &heap->elementos[2*n + 2]);
			heap_sift_down(heap, 2*n + 2 );
		}
	}
	//endif - Si no tiene hijos no hacer nada
}

void heap_heapify(heap_t *heap){

	if (heap_cantidad(heap) > 1) {

		int index = (heap_cantidad(heap) % 2) ? (int)(heap_cantidad(heap) - 1)/2 : (int)(heap_cantidad(heap))/2 -1;

		while (index >= 0) {
			heap_sift_down(heap, index);
			index--;
		}
	}
}

int heap_insertar(heap_t *heap, void *elemento){
	int retorno = -1;

	if (heap) {
		heap->elementos = realloc(heap->elementos, sizeof(void*)*(heap_cantidad(heap) + 1));

		if (heap->elementos){
			heap->elementos[heap_cantidad(heap)] = elemento;
			heap->cantidad +=1;
			retorno = 0;
		}
	}

	heap_heapify(heap);

	return retorno;
}

void heap_vaciar(heap_t *heap){
	if(heap){
		while(!heap_esta_vacia(heap))
			heap_quitar_raiz(heap);
	}
}

void heap_destruir(heap_t *heap){
	if (heap){
		heap_vaciar(heap);
		free(heap);
	}
}

bool heap_esta_vacia(heap_t *heap){
	bool retorno = true;
	if (heap){
		if(heap_cantidad(heap) > 0)
			retorno = false;
		}

	return retorno;
}

void heap_quitar_raiz(heap_t *heap){
	if (heap) {
		if (!heap_esta_vacia(heap)){
			if (heap_cantidad(heap) > 1)
				swap(&heap->elementos[0], &heap->elementos[heap_cantidad(heap)-1]);

			if (heap->destructor)
				heap->destructor(heap->elementos[heap_cantidad(heap)-1]);

			heap->elementos = realloc(heap->elementos, sizeof(void*)*(heap_cantidad(heap)-1));//CHECKMEM?
			heap->cantidad -= 1;

			heap_sift_down(heap, 0);
		}			
	}
}

