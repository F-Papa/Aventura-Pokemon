#include "datos.h"

size_t partir_linea(char *linea_leida, char *tokens[]){

	size_t i=0;
	if(linea_leida && tokens){
		tokens[0] = strtok(linea_leida, ";");
		
		while(tokens[i++] != NULL)
			tokens[i] = strtok(NULL, ";");
	}
	return i;
}
int agregar_pokemon_pj(personaje_t *personaje, char *tokens[]){
	int retorno = ERROR;

	if(personaje && tokens){
		if(validar_info_pokemon(tokens) == EXITO){
			pokemon_t *pokemon = pokemon_crear(tokens[1], (size_t)atoi(tokens[2]), (size_t)atoi(tokens[3]),(size_t)atoi(tokens[4]));
			
			if(pokemon){
				if (personaje->nro_pkm_combate < 6){
					personaje->pokemon_para_combatir[personaje->nro_pkm_combate++] = pokemon;
					retorno = EXITO;
				}
	
				else{
				 	if (lista_insertar(personaje->pokemon_obtenidos, pokemon) == 0)
					retorno = EXITO;
				}
			}
		}
	}
	if (retorno == ERROR)
		mi_log("No se pudo agregar el pokemon", LOG_ERROR);

	return retorno;
}
void cargar_personaje_aux(personaje_t **personaje, char *tokens[], size_t *pokemon_insertados, bool *personaje_creado){
	if(!personaje || !tokens || !pokemon_insertados || !personaje_creado){
		mi_log("En cargar_personaje_aux", LOG_ERROR);
		return;
	}

	switch (*tokens[0]){
				case 'E':
					if(*personaje)
						mi_log("Se encontro mas de un jugador en el archivo, se usara el primero", LOG_AVISO);
					else{
						if(validar_info_entrenador(tokens) == EXITO)
							*personaje = personaje_crear(strtok(tokens[1],"\n"));					
					}
						break;

				case 'P':
						if(agregar_pokemon_pj(*personaje, tokens) == EXITO)
							*pokemon_insertados +=1;
					break;

				default:
					printf("%c ", *tokens[0]);
					mi_log("Linea Invalida en el archivo", LOG_AVISO);
					break;
			}
}
size_t cargar_personaje(FILE *archivo_personaje, personaje_t **personaje){
	
	size_t pokemon_insertados = 0;

	if (archivo_personaje != NULL){
		if(personaje != NULL){
			bool personaje_creado = false;
			char buffer[MAX_LINEA], *tokens[10], *linea_leida;
	
			do{
				linea_leida = fgets(buffer, MAX_LINEA, archivo_personaje);
				
				if(linea_leida != NULL){
					partir_linea(linea_leida, tokens);
					cargar_personaje_aux(personaje, tokens, &pokemon_insertados, &personaje_creado);
				}
			
			} while (linea_leida != NULL);
		}
	fclose(archivo_personaje);
	}

	return pokemon_insertados;
}
int agregar_pokemon_gym(gimnasio_t *ultimo_gimnasio, char *tokens[]){
	int retorno = ERROR;

	if(ultimo_gimnasio){
		entrenador_t *entrenador = lista_tope(ultimo_gimnasio->entrenadores); 
		if(entrenador->nro_pkm < 6 && validar_info_pokemon(tokens) == EXITO){
		
			if (lista_tope(ultimo_gimnasio->entrenadores)){
				pokemon_t *nuevo_pokemon = pokemon_crear(tokens[1], (size_t)atoi(tokens[2]), 
										(size_t)atoi(tokens[3]), (size_t)atoi(tokens[4]));

				if (nuevo_pokemon){
					entrenador->pokemon[entrenador->nro_pkm++] = nuevo_pokemon;
					retorno = EXITO;	
				}
			}
		}
	}

	if (retorno == ERROR)
		mi_log("No se pudo agregar el pokemon", LOG_ERROR);
	return retorno;
}
int agregar_gimnasio(heap_t *heap_gimnasios, char *tokens[], size_t *gimnasios_insertados, gimnasio_t **ultimo_gimnasio){
	int retorno = ERROR;

	if (heap_gimnasios && gimnasios_insertados && ultimo_gimnasio && validar_info_gimnasio(tokens) == EXITO){
		*ultimo_gimnasio = gimnasio_crear(tokens[1], (size_t)atoi(tokens[2]), (size_t)atoi(tokens[3]));
		if (*ultimo_gimnasio)
			if(!heap_insertar(heap_gimnasios, (void*)*ultimo_gimnasio)){
				retorno = EXITO;
				*gimnasios_insertados+=1;
			}
	}
	if (retorno == ERROR)
		mi_log("No se pudo agregar el gimnasio", LOG_ERROR);

	return retorno;	
}
int agregar_entrenador(gimnasio_t *gimnasio, char *tokens[]){
	int retorno = ERROR;

	if (gimnasio && validar_info_entrenador(tokens) == EXITO){
		bool es_lider = (*tokens[0] == 'L') ? true:false;
		
		if(!es_lider || !gimnasio->tiene_lider){
			entrenador_t *nuevo_entrenador = entrenador_crear(es_lider, strtok(tokens[1],"\n"));				
			
			if (nuevo_entrenador)
				retorno = lista_apilar(gimnasio->entrenadores, nuevo_entrenador);
		}				

	}

	if (retorno == ERROR)
		mi_log("No se pudo agregar el entrenador", LOG_ERROR);

	return retorno;
}
void cargar_gimnasios_aux(heap_t *heap_gimnasios, gimnasio_t **ultimo_gimnasio, char *tokens[], size_t *gimnasios_insertados){
	
	if(!heap_gimnasios || !ultimo_gimnasio || !gimnasios_insertados || !tokens)
		return;

	switch (*tokens[0]) {
				case 'G': 
					agregar_gimnasio(heap_gimnasios, tokens, gimnasios_insertados, ultimo_gimnasio);
					break;

				case 'L': 
					if (*ultimo_gimnasio)
						if((*ultimo_gimnasio)->tiene_lider)
							mi_log("Multiples lideres encontrados para el mismo gimnasio", LOG_AVISO);		
				case 'E': 
					agregar_entrenador(*ultimo_gimnasio, tokens);
					break;

				case 'P': 
					agregar_pokemon_gym(*ultimo_gimnasio, tokens);	
					break;

				case '\n':
					break;

				default:
					mi_log("Linea Invalida en el archivo", LOG_AVISO);
					break;
			}
}
size_t cargar_gimnasios(FILE *archivo_gimnasios, heap_t *heap_gimnasios, size_t cantidad_actual){
	size_t gimnasios_insertados = 0;

	if (archivo_gimnasios != NULL){
		if(heap_gimnasios){
			
			char buffer[MAX_LINEA], *tokens[10], *linea_leida;	
			gimnasio_t *ultimo_gimnasio = NULL;
			
			do {
				linea_leida = fgets(buffer, MAX_LINEA, archivo_gimnasios);
				
				if(linea_leida != NULL){
					partir_linea(linea_leida, tokens);
					cargar_gimnasios_aux(heap_gimnasios, &ultimo_gimnasio, tokens, &gimnasios_insertados);
				}

			} while (linea_leida != NULL);
		}
		fclose(archivo_gimnasios);
	}

	return gimnasios_insertados;
}

