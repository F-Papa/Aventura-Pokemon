#include "estructuras.h"

int validar_info_entrenador(char* tokens[]){
	int retorno = ERROR;

	if(tokens){
		if(tokens[1]){
			if(strlen(tokens[1]))
				retorno = EXITO;
		}
	}
	
	else
		mi_log("Formato incorrecto en un entrenador/personaje", LOG_AVISO);


	return retorno;
}
int validar_info_gimnasio(char* tokens[]){
	int retorno = ERROR;
	if(tokens){
		if (strlen(tokens[1]) && tokens[2] && tokens[3]){
			if (atoi(tokens[2]) > 0 && atoi(tokens[3]) > 0)
				retorno = EXITO;
		}
	}

	if (retorno == ERROR)
		mi_log("Formato incorrecto en un gimnasio", LOG_AVISO);

	return retorno;
}
int validar_info_pokemon(char* tokens[]){
	int retorno = ERROR;
	if(tokens){
		if (strlen(tokens[1]) && tokens[2] && tokens[3] && tokens[4]){
			if (atoi(tokens[2]) > 0 && atoi(tokens[3]) > 0 && atoi(tokens[4]) > 0)
				retorno = EXITO;
		}
	}

	if (retorno == ERROR)
		mi_log("Formato incorrecto en un pokemon", LOG_AVISO);
	
	return retorno;
}
void mejorar_pokemon(pokemon_t *pokemon){
	if(pokemon){
		if(pokemon->bonificaciones < 63){
			pokemon->velocidad +=1;
			pokemon->ataque +=1;
			pokemon->defensa +=1;
			pokemon->bonificaciones +=1;
		}
	}
}
personaje_t *personaje_crear(const char *nombre){
	personaje_t *mi_personaje = NULL;
	
	if(nombre){
		mi_personaje = calloc(1, sizeof(personaje_t));

		if(mi_personaje){
			strcpy(mi_personaje->nombre, nombre);

			mi_personaje->nro_pkm_combate = 0;
			mi_personaje->medallas = lista_crear();
			mi_personaje->pokemon_obtenidos = lista_crear();
			mi_personaje->maestro_pokemon = false;

			if(!mi_personaje->pokemon_obtenidos || !mi_personaje->pokemon_para_combatir){
				lista_destruir(mi_personaje->medallas);
				lista_destruir(mi_personaje->pokemon_obtenidos);
				free(mi_personaje);
			}
		}
	}

	(mi_personaje == NULL) ? mi_log("Error creando el personaje", LOG_ERROR) : mi_log("Personaje Creado", LOG_INFO);
	return mi_personaje;
}
medalla_t *medalla_crear(gimnasio_t *gimnasio_vencido){
	medalla_t *nueva_medalla = NULL;

	if(gimnasio_vencido){
		nueva_medalla = calloc(1, sizeof(medalla_t));
	
		if(nueva_medalla){
			strcpy(nueva_medalla->nombre, gimnasio_vencido->nombre);
			nueva_medalla->dificultad = gimnasio_vencido->dificultad;
		}
	}

	(nueva_medalla == NULL) ? mi_log("Error creando la medalla", LOG_ERROR) : mi_log("Medalla Creada", LOG_INFO);

	return nueva_medalla;	
}
gimnasio_t *gimnasio_crear(const char *nombre, size_t dificultad, size_t id_funcion){
	gimnasio_t *mi_gimnasio = NULL;
	
	if (nombre && dificultad){
		mi_gimnasio =  calloc(1, sizeof(gimnasio_t));

		if (mi_gimnasio) {
			strcpy(mi_gimnasio->nombre,nombre);
			mi_gimnasio->dificultad = dificultad;
			mi_gimnasio->id_funcion = id_funcion;
			mi_gimnasio->entrenadores = lista_crear();
			mi_gimnasio->tiene_lider = false;

			if (mi_gimnasio->entrenadores == NULL)
				free(mi_gimnasio);
		}
	}
	(mi_gimnasio == NULL) ? mi_log("Error creando el gimnasio", LOG_ERROR) : mi_log("Gimnasio Creado", LOG_INFO);
	return mi_gimnasio;
}
pokemon_t *pokemon_crear(const char *nombre, size_t velocidad, size_t ataque, size_t defensa){
	pokemon_t *mi_pokemon = NULL;

	if(nombre){
		mi_pokemon = calloc(1, sizeof(pokemon_t));

		if (mi_pokemon) {
			strcpy(mi_pokemon->nombre, nombre);
			mi_pokemon->velocidad = velocidad;
			mi_pokemon->ataque = ataque;
			mi_pokemon->defensa = defensa;
			mi_pokemon->bonificaciones = 0;
			mi_pokemon->vida = 100;
		}
	}
	

	(mi_pokemon == NULL) ? mi_log("Error creando el pokemon", LOG_ERROR) : mi_log("Pokemon Creado", LOG_INFO);
	return mi_pokemon;
}
entrenador_t *entrenador_crear(bool es_lider, const char *nombre){
	entrenador_t *mi_entrenador = NULL;

	if(nombre){
		mi_entrenador = calloc(1, sizeof(entrenador_t));
		
		if (mi_entrenador) {
			strcpy(mi_entrenador->nombre, nombre);
			mi_entrenador->es_lider = es_lider;
		}
			
	}
	(mi_entrenador == NULL) ? mi_log("Error creando el entrenador", LOG_ERROR) : mi_log("Entrenador Creado", LOG_INFO);
	return mi_entrenador;
}
int comparar_gimnasios(void *gimnasio_a, void *gimnasio_b){
	int retorno = 0;


	if (gimnasio_a && gimnasio_b){
		size_t dificultad_a = ((gimnasio_t*)gimnasio_a)->dificultad;
		size_t dificultad_b = ((gimnasio_t*)gimnasio_b)->dificultad;

		if (dificultad_a > dificultad_b){
			retorno = -1;
		} else if (dificultad_a < dificultad_b){ 
			retorno = 1;
		}
		
	} else
		mi_log("Uno de los gimnasios a comparar es NULL", LOG_AVISO);

	return retorno;
}
void mostrar_pokemon(void *void_pkm){
	if(void_pkm){
		pokemon_t *pokemon = (pokemon_t*)void_pkm;
		printf("%-15s V:%3ld A:%3ld D:%3ld\n",	pokemon->nombre, pokemon->velocidad,
													 pokemon->ataque, pokemon->defensa);
	}
}
void mostrar_medalla(void *void_medalla){
	if(void_medalla){
		medalla_t *medalla = (medalla_t*)void_medalla;
		printf("|~ ✪ %-20s / Dif. %ld\n", medalla->nombre, medalla->dificultad);
	}
}
void mostrar_personaje(void *void_personaje){
	if(void_personaje){
		personaje_t *personaje = (personaje_t*)void_personaje;
	
		texto_separador("◒", "PERSONAJE", 60);
		printf("\t\t");
		fuente_titulo(personaje->nombre);
		printf("  (%s )\n\n", (personaje->maestro_pokemon) ? "𝙼𝙰𝙴𝚂𝚃𝚁𝙾 𝙿𝙾𝙺𝙴𝙼𝙾𝙽":"𝙴𝙽𝚃𝚁𝙴𝙽𝙰𝙳𝙾𝚁");
		texto_separador("◒", "POKEMON DE BATALLA", 60);
		
		for(size_t i=0; i<personaje->nro_pkm_combate; ++i){
			mostrar_pokemon(personaje->pokemon_para_combatir[i]);
		}
	
		printf("\n(+%ld Pokemon Obtenidos)\n\n", lista_elementos(personaje->pokemon_obtenidos));
	
		texto_separador("◒", "MEDALLAS", 60);
		for(size_t i=0; i<lista_elementos(personaje->medallas); ++i){
			medalla_t *medalla = (medalla_t*)lista_elemento_en_posicion(personaje->medallas, i);
			mostrar_medalla(medalla);
		}
	
		separador(60);
	}
}
void mostrar_entrenador(void *void_entrenador){
	if(void_entrenador){
		entrenador_t *entrenador = (entrenador_t*)void_entrenador;
		if(entrenador->es_lider)
			printf("✪ ");
		
		fuente_titulo(entrenador->nombre);
		printf(" (%s )\n", (entrenador->es_lider) ? "𝙻𝙸𝙳𝙴𝚁" : "𝙴𝙽𝚃𝚁𝙴𝙽𝙰𝙳𝙾𝚁");
	
		for(size_t i=0; i<entrenador->nro_pkm; i++){
			mostrar_pokemon(entrenador->pokemon[i]);
		}
	}
}
void mostrar_gimnasio(void *void_gimnasio){
	if(void_gimnasio){
		gimnasio_t* gimnasio = (gimnasio_t*)void_gimnasio;
		texto_separador("◒", "GIMNASIO", 60);

		printf("\t\t");
		fuente_titulo(gimnasio->nombre);
		fuente_titulo("\n\t\t\tDIFICULTAD:");
		printf(" %ld\n\n", gimnasio->dificultad);
		texto_separador("◒", "ENTRENADORES", 60);

		for(size_t i=0; i<lista_elementos(gimnasio->entrenadores); ++i){
			mostrar_entrenador(lista_elemento_en_posicion(gimnasio->entrenadores, i));
			separador(60);

		}
	}
}
void gimnasio_destruir(void *void_gimnasio){

	if(void_gimnasio){
		gimnasio_t *gimnasio = (gimnasio_t*)void_gimnasio;
		while(!lista_vacia(gimnasio->entrenadores)){
			entrenador_destruir(lista_tope(gimnasio->entrenadores));
			lista_desapilar(gimnasio->entrenadores);
		}

		lista_destruir(gimnasio->entrenadores);
		
		free(gimnasio);
		mi_log("Gimnasio Liberado", LOG_INFO);
	}
}
void pokemon_destruir(void *void_pokemon){
	
	if(void_pokemon){
		free((pokemon_t*)void_pokemon);
		mi_log("Pokemon Liberado", LOG_INFO);
	}
}
void entrenador_destruir(void *void_entrenador){

	if(void_entrenador){
		entrenador_t* entrenador = (entrenador_t*)void_entrenador;
		for(int i= (int)entrenador->nro_pkm -1; i>=0; i--){
			pokemon_destruir(entrenador->pokemon[i]);
			entrenador->nro_pkm--;
		}
		free(entrenador);
		mi_log("Entrenador Liberado", LOG_INFO);
	}
}

void personaje_destruir(void *void_personaje){

	if(void_personaje){
		personaje_t* personaje = (personaje_t*)void_personaje;

		while(!lista_vacia(personaje->pokemon_obtenidos)){
			pokemon_destruir(lista_elemento_en_posicion(personaje->pokemon_obtenidos, 0));
			lista_borrar_de_posicion(personaje->pokemon_obtenidos, 0);
		}

		lista_destruir(personaje->pokemon_obtenidos);

		for(int i= (int)personaje->nro_pkm_combate-1; i>=0; i--){
			pokemon_destruir(personaje->pokemon_para_combatir[i]);
			personaje->nro_pkm_combate --;
		}


		while(!lista_vacia(personaje->medallas)){
			medalla_destruir((lista_elemento_en_posicion(personaje->medallas, 0)));
			lista_borrar_de_posicion(personaje->medallas, 0);
		}

		lista_destruir(personaje->medallas);
		
		free(personaje);
		mi_log("Personaje Liberado", LOG_INFO);
	}
}
void medalla_destruir(void *void_medalla){
	if(void_medalla){
		free((medalla_t*)void_medalla);
		mi_log("Medalla Liberada", LOG_INFO);
	}
}

