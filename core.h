 //106249 Franco Papa - Utilidades

#ifndef __CORE_H__
#define __CORE_H__

#include "batallas.h"

void victoria(personaje_t *personaje);
//pre- Recibe un puntero a un personaje.
//post- Felicita al personaje por haberse convertido en Maestro y le muestra su progreso.

void derrota(personaje_t *personaje, heap_t *gimnasios);
//pre- Recibe un puntero a un personaje y otro a un heap
//post- Le muestra a personaje el progreso que logro.

void comenzar_partida(heap_t *heap_gimnasios, personaje_t *personaje);
//pre- recibe un heap con gimnasios y un personaje
//post- Comienza la partida y si el jugador vencio al juego, le otorga el titulo de Maestro Pokemon.

void simular_partida(heap_t *heap_gimnasios, personaje_t *personaje);
//pre- recibe un heap con gimnasios y un personaje
//post- Simula todos los combates y si el jugador salio victorioso, lo convierte en Maestro Pokemon.

#endif /* __CORE_H__ */