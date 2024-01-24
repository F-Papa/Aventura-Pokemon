//106249 Franco Papa - Carga de datos

#ifndef __DATOS_H__
#define __DATOS_H__

#include "estructuras.h"
#include <stdbool.h>

#define MAX_NOMBRE_ARCHIVO 100

size_t cargar_personaje(FILE *archivo_personaje, personaje_t **personaje);
//pre- Recibe un puntero a un archivo y la direccion de un puntero a un personaje.
//post- Carga los datos que se encuentren en el archivo y los almacena en el personaje. Devuelve la 
// cantidad de pokemones que se insertaron.

size_t cargar_gimnasios(FILE *archivo_gimnasios, heap_t *heap_gimnasios, size_t cantidad_actual);
//pre- Recibe un puntero a un archivo, un puntero a un heap y un size_t.
//post- Carga los datos almacenados en el archivo, creando las estructuras necesarias y almacenandolas 
// en el heap. Devuelve la cantidad de gimnasios insertados.

#endif /* __DATOS_H__ */