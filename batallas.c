#include "batallas.h"

void mostrar_resultado_batalla(pokemon_t *pkm_personaje, pokemon_t *pkm_entrenador, int resultado){
	printf("\n");
	texto_separador("❂", "RESULTADO", 60);

		if(resultado == GANO_PRIMERO){
			mejorar_pokemon(pkm_personaje);
			printf("VICTORIA! %s vence a %s\n", pkm_personaje->nombre, pkm_entrenador->nombre);
		} else{
			printf("DERROTA! %s vence a %s\n",  pkm_entrenador->nombre, pkm_personaje->nombre);
		}

		separador(60);
}
void curar_pokemones(personaje_t *personaje, entrenador_t *entrenador){
	if(personaje){
		for(size_t i=0; i<personaje->nro_pkm_combate; ++i)
			(personaje->pokemon_para_combatir[i])->vida = 100;
	}
	if(entrenador){
		for(size_t i=0; i<entrenador->nro_pkm; ++i)
			(entrenador->pokemon[i])->vida = 100;
	}
}
int enfrentar_entrenador(personaje_t *personaje, entrenador_t *entrenador, size_t id_funcion){
	funcion_batalla funciones_de_batalla[] = 	{funcion_batalla_1, funcion_batalla_2,
												funcion_batalla_3, funcion_batalla_4,
												funcion_batalla_5};
	size_t i=0, j=0;
	int resultado;

	while(i<personaje->nro_pkm_combate && j<entrenador->nro_pkm){
		pokemon_t *pkm_personaje = personaje->pokemon_para_combatir[i];
		pokemon_t *pkm_entrenador = entrenador->pokemon[j];

		menu_batalla(personaje, entrenador, pkm_personaje, pkm_entrenador);
		resultado = funciones_de_batalla[id_funcion-1](pkm_personaje, pkm_entrenador);
	
		mostrar_resultado_batalla(pkm_personaje, pkm_entrenador, resultado);
		(resultado == GANO_PRIMERO) ? j++ : i++;
	}

	curar_pokemones(personaje, entrenador);

	return resultado;
}
int enfrentar_entrenadores(gimnasio_t *gimnasio, personaje_t *personaje){
	int resultado = GANO_PRIMERO;

	while(!lista_vacia(gimnasio->entrenadores) && resultado == GANO_PRIMERO){ 
			entrenador_t *entrenador = (entrenador_t*)lista_tope(gimnasio->entrenadores);	
			resultado = enfrentar_entrenador(personaje, entrenador, gimnasio->id_funcion);		
					
			if (resultado == GANO_PRIMERO){									
				if(entrenador->es_lider)									
					menu_victoria(personaje, entrenador, gimnasio);					
																			
				entrenador_destruir(lista_tope(gimnasio->entrenadores));	
				lista_desapilar(gimnasio->entrenadores);					
			}
		}

	return resultado;
}
int simular_enfrentamiento(personaje_t *jugador, entrenador_t *oponente, size_t id_funcion){
	funcion_batalla funciones_de_batalla[] = 	{funcion_batalla_1, funcion_batalla_2,
												funcion_batalla_3, funcion_batalla_4,
												funcion_batalla_5};
	size_t i=0, j=0;
	
	while (i < jugador->nro_pkm_combate && j < oponente->nro_pkm){
		
		pokemon_t *pkm_jugador = jugador->pokemon_para_combatir[i];
		pokemon_t *pkm_oponente = oponente->pokemon[j];

		if (funciones_de_batalla[id_funcion-1](pkm_jugador, pkm_oponente) == GANO_PRIMERO){	
			printf("Victoria! %s fue vencido por %s\n", pkm_oponente->nombre, pkm_jugador->nombre);
			j++;
		} else{
			printf("Derrota! %s fue vencido por %s\n", pkm_jugador->nombre, pkm_oponente->nombre);
			i++;
		}	
	}
	int resultado = (i < jugador->nro_pkm_combate) ? GANO_PRIMERO : GANO_SEGUNDO;

	curar_pokemones(jugador, oponente);

	return resultado;
}
bool simular_gimnasio(gimnasio_t *gimnasio, personaje_t *jugador){
	int resultado_entrentamiento = GANO_PRIMERO;
	entrenador_t *entrenador_actual = NULL;

	limpiar_pantalla();
	mostrar_gimnasio(gimnasio);
	mi_sleep(4);

	while (resultado_entrentamiento == GANO_PRIMERO && !lista_vacia(gimnasio->entrenadores)) {
		entrenador_actual = lista_tope(gimnasio->entrenadores);
		resultado_entrentamiento = simular_enfrentamiento(jugador, entrenador_actual, gimnasio->id_funcion);
		
		if (resultado_entrentamiento == GANO_PRIMERO){
			printf("Entrenador Vencido!\n\n");
			mi_sleep(1);
			entrenador_destruir(lista_tope(gimnasio->entrenadores));
			lista_desapilar(gimnasio->entrenadores);
		}
	}

	return lista_vacia(gimnasio->entrenadores) ? true : false;
}
bool chance_de_golpe(size_t v_atacante, size_t v_defensor){
	bool golpea = false;
	double chance = 60 + ((double)v_atacante - (double)v_defensor)/8;
	
	if (chance >= 100){
		golpea = true;
	
	} else {
		srand((unsigned int)time(NULL));
		if (rand()%100 <= chance)
			golpea = true;
	}

	return golpea;
}
int calcular_dmg(size_t a_atacante, size_t d_defensor){
	srand((unsigned int)time(NULL));
	return (int)(1 + (rand()%10) + 19 * pow((double)(a_atacante/d_defensor), 0.5));
}
void print_vida_pokemon(pokemon_t *pokemon, bool invertido){
	printf("[");
	
	if (pokemon->vida > 0){
		if(!invertido){
			for(size_t i=0; i<(pokemon->vida)/5; ++i)
				printf("\033[0;32m|");
		}

		for(size_t i=0; i<(100/5-pokemon->vida/5); ++i)
			printf("\033[0;31m|");

		if(invertido){
			for(size_t i=0; i<(pokemon->vida)/5; ++i)
				printf("\033[0;32m|");
		}

	} else {
		for(size_t i=0; i<20; ++i)
			printf("\033[0;31m|");
	}
	printf("\033[0;37m]");
}
void log_batalla(pokemon_t *pokemon1, pokemon_t *pokemon2, int dmg, bool ataca_el_primero){
	char *atacante, *defensor;
	char tabulador[100] = "\t\t\t\t";

	if (ataca_el_primero){
		atacante = pokemon1->nombre;
		defensor = pokemon2->nombre;
	} else {
		atacante = strcat(tabulador, pokemon2->nombre);
		defensor = pokemon1->nombre;
	}

	if (dmg>0){
		printf("%s golpea a %s! -%d\n", atacante, defensor, dmg);
	} else {
		printf("%s falla!\n", atacante);
	}
}
void visualizar_batalla(pokemon_t *pokemon1, pokemon_t *pokemon2, int dmg, bool ataca_el_primero){
	limpiar_pantalla();

	texto_separador("⨁", "BATALLA POKEMON", 60);
	// fuente_titulo("SUPERMEGADINASAUR");
	printf("%-15s", pokemon1->nombre);
	printf("\t\t  vs\t");
	// fuente_titulo(pokemon2->nombre);
	printf("%15s", pokemon2->nombre);
	printf("\n");
	print_vida_pokemon(pokemon1, 0);
	printf("\t\t");
	print_vida_pokemon(pokemon2, 1);
	printf("\n\n");

	log_batalla(pokemon1, pokemon2, dmg, ataca_el_primero);
}
void turno_ataque(pokemon_t *pokemon1, pokemon_t *pokemon2, bool ataca_el_primero){
	int danio_recibido = 0;
	pokemon_t *atacante, *defensor;

	if(ataca_el_primero){
		atacante = pokemon1;
		defensor = pokemon2;
	} else {
		atacante = pokemon2;
		defensor = pokemon1;
	}

	bool golpea = chance_de_golpe(atacante->velocidad, defensor->velocidad);
	
	if (golpea){
		danio_recibido = calcular_dmg(atacante->ataque, defensor->defensa);
		defensor->vida -= danio_recibido;
	} 
			
	visualizar_batalla(pokemon1, pokemon2, danio_recibido, ataca_el_primero);
	mi_sleep(1);
}
bool pkm_esta_vivo(pokemon_t *pokemon){
	
	return (pokemon->vida > 0);
}
int funcion_batalla_1(void* pkm_1, void* pkm_2){
	int retorno;

	if(pkm_1 && pkm_2){
		while(pkm_esta_vivo((pokemon_t*)pkm_1) > 0 && pkm_esta_vivo((pokemon_t*)pkm_2)){
			turno_ataque((pokemon_t*)pkm_1, (pokemon_t*)pkm_2, ATACA_EL_PRIMERO);

			if(pkm_esta_vivo((pokemon_t*)pkm_2)){
				turno_ataque((pokemon_t*)pkm_1, (pokemon_t*)pkm_2, ATACA_EL_SEGUNDO);
			}		 
		}

		retorno = (((pokemon_t*)pkm_1)->vida > 0) ? GANO_PRIMERO : GANO_SEGUNDO;

	} else {

		mi_log("Pokemon Invalido", LOG_ERROR);
		retorno = GANO_PRIMERO;
	}

	return retorno;
}
int funcion_batalla_2_aux(pokemon_t *atacante, pokemon_t *defensor){
	size_t x = (size_t)atacante->ataque * strlen(atacante->nombre)/defensor->defensa;
	double poder = pow((double) x, 0.3) * (double)atacante->velocidad;
	mi_sleep(1);
	printf("%s consiguio %f puntos!\n", atacante->nombre, poder);
	return (int)poder;
}
int funcion_batalla_2(void* pkm_1, void* pkm_2){
	int retorno;

	limpiar_pantalla();

	if(pkm_1 && pkm_2){
		pokemon_t *pokemon1 = (pokemon_t*)pkm_1;
		pokemon_t *pokemon2 = (pokemon_t*)pkm_2;

		texto_separador("⬖", "PISTA DE OBSTACULOS", 60);
		
		int poder_1 = funcion_batalla_2_aux(pokemon1, pokemon2);	
		int poder_2 = funcion_batalla_2_aux(pokemon2, pokemon1);

		retorno = (poder_1>poder_2)? GANO_PRIMERO : GANO_SEGUNDO;
	
	} else {
		mi_log("Pokemon Invalido", LOG_ERROR);
		retorno = GANO_PRIMERO;
	}
		mi_sleep(1);
		return retorno;
}
int funcion_batalla_3(void* pkm_1, void* pkm_2){
	int retorno;

	limpiar_pantalla();
	if (pkm_1 && pkm_2){
		pokemon_t *pokemon1 = (pokemon_t*)pkm_1;
		pokemon_t *pokemon2 = (pokemon_t*)pkm_2;

		size_t x1=0, x2=0;
		size_t n = (strlen(pokemon1->nombre) < strlen(pokemon2->nombre)) ? strlen(pokemon1->nombre) : strlen(pokemon2->nombre);

		for(size_t i=0; i<n; ++i){
			x1 += (size_t)pokemon1->nombre[i]*(size_t)pokemon1->ataque;
			x2 += (size_t)pokemon2->nombre[i]*(size_t)pokemon2->ataque;
		}
		
		texto_separador("⥦", "CALCULANDO INTELIGENCIA", 60);
		mi_sleep(1);
		printf("%s alcanzo un IQ de: %ld\n\n",pokemon1->nombre,  x1);
		mi_sleep(1);
		printf("%s alcanzo un IQ de: %ld\n\n",pokemon2->nombre,  x2);
		mi_sleep(1);

		if (x1 > x2)
			retorno = GANO_PRIMERO;
		else if (x1 < x2)
			retorno = GANO_SEGUNDO;
		else{
			retorno = (rand() % 2)? GANO_PRIMERO : GANO_SEGUNDO;
			printf("Empataron pero la suerte estuvo del lado de: %s\n", 
				(retorno == GANO_PRIMERO) ? pokemon1->nombre : pokemon2->nombre);
		}
	} else {
		mi_log("Pokemon Invalido", LOG_ERROR);
		retorno = GANO_PRIMERO;
	}

	return retorno;
}
int funcion_batalla_4_aux(pokemon_t *pokemon){
	double poder = pow((double)(pokemon->ataque*pokemon->velocidad), 0.5);
	mi_sleep(1);
	printf("%s alcanzo un poder de %i!\n\n", pokemon->nombre, (int)poder);
	return (int)poder;
}
int funcion_batalla_4(void* pkm_1, void* pkm_2){
	int retorno;

	limpiar_pantalla();
	if (pkm_1 && pkm_2){
		pokemon_t *pokemon1 = (pokemon_t*)pkm_1;
		pokemon_t *pokemon2 = (pokemon_t*)pkm_2;

		texto_separador("ϟ", "POKEMONES CANALIZANDO", 60);
		int poder1 = funcion_batalla_4_aux(pokemon1);
		int poder2 = funcion_batalla_4_aux(pokemon2);
		mi_sleep(1);

		if(poder1>poder2)
			retorno = GANO_PRIMERO;
		else if(poder1<poder2)
			retorno = GANO_SEGUNDO;
		else{
			retorno = (rand() %2) ? GANO_PRIMERO : GANO_SEGUNDO;
			printf("Empataron pero la suerte estuvo del lado de: %s\n", 
				(retorno == GANO_PRIMERO) ? pokemon1->nombre : pokemon2->nombre);
		}
	} else {
		mi_log("Pokemon Invalido", LOG_ERROR);
		retorno = GANO_PRIMERO;

	}
	return retorno;
}
int funcion_batalla_5(void* pkm_1, void* pkm_2){
	int retorno;

	limpiar_pantalla();
	if (pkm_1 && pkm_2){
		texto_separador("☠ ", "Competencia de Destruccion", 60);

		mi_sleep(1);
		printf("\t\t\t✷    ✷    ✷\n");
		mi_sleep(1);
	
		if (((pokemon_t *)pkm_1)->ataque > ((pokemon_t *)pkm_2)->ataque)
			retorno = GANO_PRIMERO;
		else if (((pokemon_t *)pkm_1)->ataque < ((pokemon_t *)pkm_2)->ataque)
			retorno = GANO_SEGUNDO;
		else
			retorno = (rand()%2)? GANO_PRIMERO : GANO_SEGUNDO;

	} else {
		mi_log("Pokemon Invalido", LOG_ERROR);
		retorno = GANO_PRIMERO;
	}

	return retorno;
}


