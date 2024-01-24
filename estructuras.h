//106249 Franco Papa - Estructuras

#ifndef __ESTRUCTURAS_H__
#define __ESTRUCTURAS_H__

#include "lista.h"
#include "heap.h"
#include "utils.h"

#include <string.h>

#define MAX_CAMPO 50
#define MAX_LINEA 300
#define EXITO 0
#define ERROR -1

typedef int (*funcion_batalla)(void*, void *);

typedef struct medalla {
	size_t dificultad;
	char nombre[MAX_CAMPO];
} medalla_t;
typedef struct pokemon {
	char nombre[MAX_CAMPO];
	char tipo[MAX_CAMPO];
	size_t velocidad, ataque, defensa;
	struct entrenador *amo;
	int vida;
	size_t bonificaciones;
} pokemon_t;
typedef struct personaje {
	size_t nro_pkm_combate;
	char nombre[MAX_CAMPO];
	bool maestro_pokemon;
	pokemon_t *pokemon_para_combatir[6];
	lista_t *pokemon_obtenidos; 			//lista
	lista_t *medallas;						//lista
} personaje_t;
typedef struct entrenador {
	size_t nro_pkm;
	char nombre[MAX_CAMPO];
	bool es_lider;
	pokemon_t *pokemon[6];
} entrenador_t;
typedef struct gimnasio {
	char nombre[MAX_CAMPO];
	bool tiene_lider;
	size_t dificultad;
	size_t id_funcion;
	lista_t *entrenadores; 			//pila
} gimnasio_t;

int validar_info_entrenador(char* tokens[]);
//pre- Recibe un array de strings.
//post- Devuelve EXITO si los strings del array son validos para crear un entrenador o un personaje o ERROR en caso contrario.

int validar_info_gimnasio(char* tokens[]);
//pre- Recibe un array de strings.
//post- Devuelve EXITO si los strings del array son validos para crear un gimnasio o ERROR en caso contrario.

int validar_info_pokemon(char* tokens[]);
//pre- Recibe un array de strings.
//post- Devuelve EXITO si los strings del array son validos para crear un pokemon o ERROR en caso contrario.

void mejorar_pokemon(pokemon_t *pokemon);
//pre- Recibe un puntero a un pokemon.
//post- Aumenta en 1 todos sus atributos si la cantidad de bonificaciones es menor a 63.

medalla_t *medalla_crear(gimnasio_t *gimnasio_vencido);
//pre- Recibe un puntero a un gimnasio.
//post- Devuelve un puntero a una nueva medalla de ese gimnasio (con sus datos) o NULL si falla.

personaje_t *personaje_crear(const char *nombre);
//pre- Recibe un nombre.
//post- Devuelve un puntero a un nuevo personaje o NULL si falla.

gimnasio_t *gimnasio_crear(const char *nombre, size_t dificultad, size_t id_funcion);
//pre- Recibe un nombre, una dificultad, un id de funcion y un id.
//post-  Devuelve un puntero a un nuevo gimnasio o NULL si falla.

pokemon_t *pokemon_crear(const char *nombre, size_t velocidad, size_t ataque, size_t defensa);
//pre- Recibe un nombre, velocidad, ataque y defensa.
//post- Devuelve un puntero a un nuevo pokemon o NULL si falla.

entrenador_t *entrenador_crear(bool es_lider, const char *nombre);
//pre- Recibe un bool y un nombre.
//post- Devuelve un puntero a un nuevo entrenador o NULL si falla.

int comparar_gimnasios(void *gimnasio_a, void *gimnasio_b);
//pre- Recibe dos punteros a gimnasios.
//post- Devuelve -1 si el primero es mas dificil, 1 si el segundo es mas dificil o 0 si son de igual dificultad.

void mostrar_pokemon(void *pokemon);
//pre- Recibe un puntero a un pokemon.
//post- Imprime en pantalla la informacion del pokemon.

void mostrar_entrenador(void *entrenador);
//pre- Recibe un puntero a un entrenador.
//post- Imprime en pantalla la informacion del entrenador y de sus pokemones.

void mostrar_gimnasio(void *gimnasio);
//pre- Recibe un puntero a un gimnasio.
//post- Imprime en pantalla la informacion del gimnasio, de sus entrenadores y sus pokemones.

void mostrar_personaje(void *personaje);
//pre- Recibe un puntero a un personaje.
//post- Imprime en pantalla la informacion del pokemon, de sus pokemones y de sus medallas.

void mostrar_medalla(void *medalla);
//pre- Recibe un puntero a una medalla.
//post- Lmprime en pantalla la informacion de la medalla .

void gimnasio_destruir(void *gimnasio);
//pre- Recibe un puntero a un gimnasio.
//post- Libera la memoria reservada para el gimnasio y sus miembros.

void entrenador_destruir(void *entrenador);
//pre- Recibe un puntero a un entrenador.
//post- Libera la memoria reservada para el entrenador y sus miembros.

void pokemon_destruir(void *pokemon);
//pre- Recibe un puntero a un pokemon.
//post- Libera la memoria reservada para el pokemon.

void personaje_destruir(void *personaje);
//pre- Recibe un puntero a un personaje.
//post- Libera la memoria reservada para el personaje y sus miembros.

void medalla_destruir(void *medalla);
//pre- Recibe un ptr a una medalla.
//post- Libera la memoria reservada para la medalla.

#endif /* __ESTRUCTURAS_H__ */