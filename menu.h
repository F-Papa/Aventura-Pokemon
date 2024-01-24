//106249 Franco Papa - Menu

#ifndef __MENU_H__
#define __MENU_H__

#include "datos.h"

char menu_inicio();
//post- Muestra al usuario una pantalla principal donde le permite cargar los archivos necesarios para comenzar la partida.

void menu_gimnasio(gimnasio_t *gimnasio, personaje_t *personaje);
//pre- Recibe un puntero a un gimnasio y otro a un personaje.
//post- Le permite al usuario ver la informacion de su personaje o del gimnasio, rearmar su conjunto de pokemones y proceder a la batalla cuando este asi lo desee.

void menu_batalla(personaje_t *personaje, entrenador_t *entrenador, pokemon_t *pkm_personaje, pokemon_t *pkm_entrenador);
//pre- Recibe un puntero a un personaje, uno a un entrenador, uno a un pokemon del personaje y otro a un pokemon del entrenador.
//post- Muestra la informacion de los pokemones que se enfrentaran y a para quien pelean hasta que el usuario ingrese 'N'. 

void menu_victoria(personaje_t *personaje, entrenador_t *lider, gimnasio_t *gimnasio_vencido);
//pre- Recibe un puntero a un personaje, uno a un entrenador y otro a un gimnasio.
//post- Le permite al usuario tomar prestado uno de los pokemones del lider si ya no lo hizo, rearmar su equipo y proceder a la batalla cuando este asi lo desee.
	
bool menu_derrota(personaje_t *personaje);
//pre- Recibe un puntero a un personaje.
//post- Le permite al usuario rearmar su equipo y reintentar o terminar la partida. Devuelve true si desea salir o false si desea reintentar.

void pedir_pokemon(personaje_t *personaje, entrenador_t *entrenador);
//pre- Recibe un puntero a un personaje y otro a un entrenador.
//post- Le muestra al usuario los pokemones del entrenador y le permite elegir uno para tomar prestado. Agrega este pokemon al conjunto de pokemones obtenidos del jugador.

void rearmar_equipo(personaje_t *personaje);
//pre- Recibe un puntero a un personaje.
//post- Presenta al jugador la oportunidad de volver a elegir su conjunto de pokemones de combate.

void otorgar_medalla(personaje_t *personaje, gimnasio_t *gimnasio_vencido);
//pre- Recibe un puntero aun personaje y otro a un gimnasio.
//post- Agrega una medalla con los datos del gimnasio a la lista de medallas del jugador.

#endif /* __MENU_H__ */