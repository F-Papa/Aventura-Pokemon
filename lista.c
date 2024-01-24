#include "lista.h"

lista_t* lista_crear(){

	lista_t* nuevaLista = malloc(sizeof(lista_t));
	
	if (nuevaLista){

		nuevaLista->cantidad = 0;
		nuevaLista->nodo_inicio = NULL;
		nuevaLista->nodo_fin = NULL;
		return nuevaLista;
	}		
	
	else
		return NULL;
}

int lista_insertar(lista_t* lista, void* elemento){

	if (!lista)
		return -1;

	nodo_t* nuevoNodo = malloc(sizeof(nodo_t));

	if (!nuevoNodo)
		return -1;
	
	nuevoNodo->elemento = elemento;
	nuevoNodo->siguiente = NULL;

	if (lista->cantidad == 0){
		lista->nodo_inicio = nuevoNodo;
	}
		
	else {
		lista->nodo_fin->siguiente = nuevoNodo;
	}		
		
	lista->nodo_fin = nuevoNodo;
	(lista->cantidad)++;
	return 0;

}

int lista_apilar(lista_t* lista, void* elemento){
	
	return lista_insertar(lista, elemento);
}

int lista_encolar(lista_t* lista, void* elemento){
	
	return lista_insertar(lista, elemento);
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	
	if(!lista)
		return -1;

	if (posicion >= lista->cantidad){
		return lista_insertar(lista, elemento);
	}
		
	
	nodo_t* nuevoNodo = malloc(sizeof(nodo_t));
		
	if (!nuevoNodo)
		return -1;

	nuevoNodo->elemento = elemento;

	if (posicion == 0){

		nuevoNodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevoNodo;
	}

	else{	

		nodo_t* aux = lista->nodo_inicio;

		for(unsigned int i=0; i<posicion-1; i++)
			aux = aux->siguiente;

		nuevoNodo->siguiente = aux->siguiente;
		aux->siguiente = nuevoNodo;
	}

	lista->cantidad++;
	return 0;	
}

int lista_borrar(lista_t* lista){
	
	if(!lista)
		return -1;

	if (lista_vacia(lista))
		return -1;
		
	
	if(lista->cantidad>1){
		nodo_t* aux = lista->nodo_inicio;

		for(unsigned int i=0; i<(lista->cantidad)-2; i++)			
			aux = aux->siguiente;
	
		free(lista->nodo_fin);
		aux->siguiente = NULL;
		lista->nodo_fin = aux;
	}

	else {
		free(lista->nodo_inicio);
		lista->nodo_fin = NULL;
		lista->nodo_inicio = NULL;
	}

	lista->cantidad--;
	return 0;	
}

int lista_desapilar(lista_t* lista){
	
	return lista_borrar(lista);
}

int lista_desencolar(lista_t* lista){

	if (lista){

		if (lista_vacia(lista))
			return -1;

		nodo_t* aux = lista->nodo_inicio;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;

		free(aux);

		if (lista->cantidad == 1)
			lista->nodo_fin = NULL;

		(lista->cantidad)--;

		return 0;
	}

	return -1;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	
	if (!lista)
		return -1;

	
	if (lista_vacia(lista))
		return -1;
		

	if (posicion >= lista->cantidad-1)
		return lista_borrar(lista);
		

	if (posicion == 0)
		return lista_desencolar(lista);

					
	nodo_t* indice = lista->nodo_inicio;

	for(unsigned int i=0; i<posicion-1; i++)
		indice = indice->siguiente;

	nodo_t* aux = indice->siguiente;
	indice->siguiente = aux->siguiente;
	free(aux);

	lista->cantidad--;

	return 0;
}

bool lista_vacia(lista_t* lista){
	
	if (lista){

		if (lista->cantidad)
			return false;
	}

	return true;
}

void* lista_primero(lista_t* lista){
	
	if(!lista_vacia(lista)){
		return lista->nodo_inicio->elemento;
	}

	return NULL;
}

void* lista_ultimo(lista_t* lista){
	
	if(!lista_vacia(lista)){
		return lista->nodo_fin->elemento;
	}

	return NULL;
}

void* lista_tope(lista_t* lista){
	
	return lista_ultimo(lista);
}

size_t lista_elementos(lista_t* lista){
	if (lista_vacia(lista))
		return 0;

	return lista->cantidad;
}

void lista_destruir(lista_t* lista){
	
	if (lista){
		while(!lista_vacia(lista))
			lista_borrar(lista);

		free(lista);
		lista = NULL;
	}
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){

	if(lista){
		
		if(!lista_vacia(lista)){

			if (lista->cantidad == 1 || posicion == lista->cantidad-1){
				return lista_ultimo(lista);
			}

			if (posicion == 0){
				return lista_primero(lista);
			}

			if (posicion<lista->cantidad-1){
				nodo_t* indice = lista->nodo_inicio;
				for (unsigned int i = 0; i < posicion; ++i)
					indice = indice->siguiente;
				
				return indice->elemento;
			}
		}
	}
	
	return NULL;		
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){

		if(!lista)
			return NULL;

		lista_iterador_t* nuevoIterador = malloc(sizeof(lista_iterador_t));
		if(!nuevoIterador)
			return NULL;

		nuevoIterador->lista = lista;
		nuevoIterador->corriente = NULL;
		
		if(!lista_vacia(lista))
			nuevoIterador->corriente = lista->nodo_inicio;

		return nuevoIterador;	
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	
	if(iterador)
		return (iterador->corriente);

	return false;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){

	if(!iterador)
		return false;

	if(lista_iterador_tiene_siguiente(iterador)){ //Si ya no nos pasamos del ultimo elemento
		iterador->corriente = iterador->corriente->siguiente; //Avanzar
		if(iterador->corriente)	//Si no venimos del ultimo elemento
			return true;
	}

	return false;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
	
	return (iterador->corriente != NULL) ? iterador->corriente->elemento :  NULL; 
}

void lista_iterador_destruir(lista_iterador_t* iterador){

	if (iterador)
		free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){

	if (lista && funcion && contexto){

		size_t cantidad_a_devolver = 0;
		nodo_t* indice = lista->nodo_inicio;

		while(indice){

			if (funcion(indice->elemento, contexto)){
				indice = indice->siguiente;
				cantidad_a_devolver++;
			}

			else {

				break;
			}

		}
	return cantidad_a_devolver;
	}
	
	return (size_t)0;
}
