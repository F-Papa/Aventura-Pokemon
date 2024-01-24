//106249 Franco Papa - Batallas

#ifndef __BATALLAS_H__
#define __BATALLAS_H__

#include <math.h>
#include <time.h>

#include "menu.h"


#define ATACA_EL_PRIMERO 1
#define ATACA_EL_SEGUNDO 0


#define GANO_PRIMERO 1
#define GANO_SEGUNDO -1

int funcion_batalla_1(void* pkm_1, void* pkm_2);
//pre- Recibe 2 punteros a pokemones.
//post- Devuelve GANO_PRIMERO o GANO_SEGUNDO segun que pokemon gano la simulacion de combate.

int funcion_batalla_2(void* pkm_1, void* pkm_2);
//pre- Recibe 2 punteros a pokemones.
//post- devuelve GANO_PRIMERO o GANO_SEGUNDO segun que pokemon que gane la pista de obstaculos.

int funcion_batalla_3(void* pkm_1, void* pkm_2);
//pre- Recibe 2 punteros a pokemones.
//post- devuelve GANO_PRIMERO o GANO_SEGUNDO segun que pokemon sea mas inteligente.

int funcion_batalla_4(void* pkm_1, void* pkm_2);
//pre- Recibe 2 punteros a pokemones.
//post- devuelve GANO_PRIMERO o GANO_SEGUNDO segun que pokemon canalice mas energia.

int funcion_batalla_5(void* pkm_1, void* pkm_2);
//pre- Recibe 2 punteros a pokemones.
//post- devuelve GANO_PRIMERO o GANO_SEGUNDO segun que pokemon tenga mayor poder destructivo.

void curar_pokemones(personaje_t *personaje, entrenador_t *entrenador);
//pre- Recibe un puntero a un personaje y otro a un entrenador.
//post- Asigna 100 al valor de vida de todos los pokemones de combate de ambos entrenadores pokemon.

int enfrentar_entrenador(personaje_t *personaje, entrenador_t *entrenador, size_t id_funcion);
//pre- Recibe un puntero a un personaje personaje, otro a un entrenador y un id de funcion.
//post- Muestra al usuario los pokemones que se enfrentaran y brinda informacion de los resultados de los enfrentamientos. Devuelve GANO_PRIMERO o GANO_SEGUNDO dependiendo del resultado.

int enfrentar_entrenadores(gimnasio_t *gimnasio, personaje_t *personaje);
//pre- Recibe un puntero a un gimnasio y otro a un personaje.
//post- Devuelve GANO_PRIMERO si el usuario logro vencer a todos los entrenadores del gimnasio o GANO_SEGUNDO en caso contrario.

int simular_entrentamiento(personaje_t *jugador, entrenador_t *oponente, size_t id_funcion);
//pre- Recibe un puntero a un jugador, otro a un entrenador y el id de una de las funciones de batalla.
//post- Devuelve GANO_PRIMERO o GANO_SEGUNDO segun quien gano el enfrentamiento.

bool simular_gimnasio(gimnasio_t *gimnasio, personaje_t *jugador);
//pre- Recibe un puntero a un jugador, otro a un entrenador y el id de una de las funciones de batalla.
//post - Devuelve true si el gimnasio esta vacio cuando terminan los combates o false si todavia quedan entrenadores.

#endif /* __BATALLAS_H__ */