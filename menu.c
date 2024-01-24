#include "menu.h"

#define MAX_INPUT 20

FILE *abrir_archivo(){
	FILE *archivo = NULL;
	bool archivo_encontrado = false;

	while (!archivo_encontrado){
		char nombre[MAX_NOMBRE_ARCHIVO];
		printf("Ingrese el nombre del archivo o * para volver atras: ");
		scanf("%s", nombre);

		if (strcmp(nombre, "*") == 0)
			break;

		archivo = fopen(nombre, "r");
		if (!archivo)
			printf("Archivo no encontrado. ");	
		else 
			archivo_encontrado = true;
		
	}

	return archivo;
}
void print_anuncio(const char *mensaje){
	if(mensaje){
		for(size_t i=0; i<strlen(mensaje); ++i)
			printf("/");

		printf("\n%s\n", mensaje);
		
		for(size_t i=0; i<strlen(mensaje); ++i)
			printf("/");
		printf("\n\n");
	}
}
char menu_inicio_opciones(bool personaje_valido, size_t gimnasios_cargados){
	char eleccion;

	limpiar_pantalla();

	texto_separador("◒", "MENU DE INICIO", 60);
	printf("%sIngresar el archivo del entrenador principal  %s\n", (personaje_valido)? "": "[E]: ",
																	 (personaje_valido)? "✔" : "✘");

	printf("[A]: Agregar un gimnasio al arbol de gimnasios (%ld) %s\n", gimnasios_cargados, (gimnasios_cargados)? "✔" : "✘");
	if(personaje_valido && gimnasios_cargados>0){
		printf("[I]: Comenzar partida\n");
		printf("[S]: Simular partida\n");
	}
	separador(60);

	scanf("%c", &eleccion);

	return (char)toupper(eleccion);
}
void transferir_a_obtenidos(personaje_t *personaje){
	if (!personaje){
		mi_log("En transferir_a_obtenidos", LOG_ERROR);
		return;
	}
	for(int i = (int)personaje->nro_pkm_combate - 1; i>=0; --i){
		lista_insertar(personaje->pokemon_obtenidos, personaje->pokemon_para_combatir[i]);
		personaje->nro_pkm_combate -=1;
	}
}
bool es_numero(char s[]){
	bool valido = false;
	if(s){
		valido = true;
		for(size_t i=0;i<strlen(s); ++i){
			if isalpha(s[i])
				valido = false;
		}
	}

	return valido;
}
void rearmar_equipo_aux(size_t *i, personaje_t *personaje, size_t cantidad_esperada){
	size_t posicion;
	char input[MAX_INPUT];

	printf("\n-Ingrese el numero del pokemon que desea transferir: (%ld/%ld)", *i, cantidad_esperada);
	scanf("%s", input);

	if (es_numero(input)){
		posicion = (size_t)atoi(input);

		pokemon_t *pokemon_transferido = (pokemon_t*)lista_elemento_en_posicion(personaje->pokemon_obtenidos, posicion);
		
		if(pokemon_transferido){
			personaje->pokemon_para_combatir[*i] = pokemon_transferido;
			personaje->nro_pkm_combate +=1;
			lista_borrar_de_posicion(personaje->pokemon_obtenidos, posicion);//obtenidos
			*i +=1;
		}
	}
}
void rearmar_equipo(personaje_t *personaje){
 	if (!personaje){
 		mi_log("En rearmar_equipo", LOG_ERROR);
 		return;
 	}

 	transferir_a_obtenidos(personaje);

	size_t cantidad_esperada = (6 > lista_elementos(personaje->pokemon_obtenidos)) ? 
					lista_elementos(personaje->pokemon_obtenidos) : 6;

 	size_t i=0;
	while (i<cantidad_esperada){
		
		limpiar_pantalla();
		
		printf("◒ 𝙰𝚁𝙼𝙴 𝚂𝚄 𝙴𝚀𝚄𝙸𝙿𝙾! ◒ -------------------------*\n\n");
		fuente_titulo("     TODOS ESTOS POKEMONES ESTAN DISPONIBLES!\n\n");

		for(size_t j=0; j<lista_elementos(personaje->pokemon_obtenidos); j++){
			printf("%3ld. ", j);
			mostrar_pokemon((pokemon_t*)lista_elemento_en_posicion(personaje->pokemon_obtenidos, j));
		}

		rearmar_equipo_aux(&i, personaje, cantidad_esperada);
	}
}
char menu_inicio(heap_t *heap_gimnasios, personaje_t **nuevo_personaje){
	if (!heap_gimnasios || !nuevo_personaje){
		mi_log("En menu_inicio", LOG_ERROR);
		return 'E';
	}

	size_t gimnasios_cargados = 0;
	bool personaje_valido = false;
	bool desea_empezar = false;
	FILE *archivo_gimnasios = NULL;
	FILE *archivo_personaje = NULL;
	char eleccion;

	if(CARGA_RAPIDA){
		archivo_personaje = fopen("pokemon.txt", "r");
		personaje_valido = cargar_personaje(archivo_personaje, nuevo_personaje);

		archivo_gimnasios = fopen("gimnasios.txt", "r");
		gimnasios_cargados += cargar_gimnasios(archivo_gimnasios, heap_gimnasios, gimnasios_cargados);
	}	

	while (!desea_empezar){

		eleccion = menu_inicio_opciones(personaje_valido, gimnasios_cargados);

		switch (eleccion) {
			case 'E':
				if (!personaje_valido){
					archivo_personaje = abrir_archivo();
					personaje_valido = cargar_personaje(archivo_personaje, nuevo_personaje);	
				}
				break;

			case 'A':
				archivo_gimnasios = abrir_archivo();
				gimnasios_cargados += cargar_gimnasios(archivo_gimnasios,heap_gimnasios, gimnasios_cargados);
				break;

			case 'I':
			case 'S':
				if (gimnasios_cargados > 0 && personaje_valido)
					desea_empezar = true;
				break;

			default :
				break;
		}
	}

	return eleccion;
}
void quitar_pokemon_prestado(entrenador_t *entrenador, size_t posicion){

	for(size_t i=posicion; i<entrenador->nro_pkm-1; i++){
		entrenador->pokemon[i] = entrenador->pokemon[i+1];
	}
	entrenador->nro_pkm -=1;
}
void pedir_pokemon(personaje_t *personaje, entrenador_t *entrenador){
	size_t eleccion = 0;
	bool selecciono = false;

	if(personaje && entrenador){
		for(size_t j=0; j< entrenador->nro_pkm; j++){
				printf("%3ld. ", j);
				mostrar_pokemon((pokemon_t*)entrenador->pokemon[j]);
			}

			printf("Ingrese el numero del pokemon que desea pedir prestado: ");
			while(eleccion >= entrenador->nro_pkm || !selecciono){
				selecciono = true;
				scanf("%lu", &eleccion);
			}

		lista_insertar(personaje->pokemon_obtenidos, entrenador->pokemon[eleccion]);		
		quitar_pokemon_prestado(entrenador, eleccion);

		limpiar_pantalla();
		print_anuncio("El pokemon elegido se encuentra ahora entre sus pokemones obtenidos!");
		// printf("El pokemon elegido se encuentra ahora entre sus pokemones obtenidos!\n");
		mi_sleep(2);
		limpiar_pantalla();
	}
}
void menu_gimnasio(gimnasio_t *gimnasio, personaje_t *personaje){
	if(!gimnasio || !personaje){
		mi_log("En menu_gimnasio", LOG_ERROR);
		return;
	}

	char eleccion[MAX_INPUT];
	bool desea_pelear = false;

	limpiar_pantalla();

	while (!desea_pelear){
		texto_separador("◒", "MENU DEL GIMNASIO", 60);
		printf("[E]: Informacion del personaje\n");
		printf("[G]: Informacion del gimnasio\n");
		printf("[C]: Cambiar Pokemon de batalla\n");
		printf("[B]: Combatir!\n");
		separador(60);

		scanf("%s", eleccion);

		switch(toupper(eleccion[0])){
			case 'E':
				limpiar_pantalla();
				mostrar_personaje(personaje);

				break;

			case 'G':
				limpiar_pantalla();
				mostrar_gimnasio(gimnasio);
				break;

			case 'C':
				rearmar_equipo(personaje);
				limpiar_pantalla();
				break;

			case 'B':
				desea_pelear = true;

			default:
				printf("\n");
				break;
		}		
	}
}
void otorgar_medalla(personaje_t *personaje, gimnasio_t *gimnasio_vencido){
	if (!personaje || !gimnasio_vencido){
		mi_log("En otorgar_medalla", LOG_ERROR);
		return;
	}

	medalla_t *nueva_medalla = medalla_crear(gimnasio_vencido);
	if(nueva_medalla)
		lista_apilar(personaje->medallas, nueva_medalla);
	else
		mi_log("No se pudo crear la medalla", LOG_ERROR);

	if (LOG_LEVEL < LOG_ERROR)
		limpiar_pantalla();
}
void menu_victoria(personaje_t *personaje, entrenador_t *lider, gimnasio_t *gimnasio_vencido){
	if(!personaje || !lider || !gimnasio_vencido){
		mi_log("En menu_victoria", LOG_ERROR);
		return;
	}

	char eleccion[MAX_INPUT];
	bool desea_continuar = false;
	bool pidio_prestado = false;
	
	otorgar_medalla(personaje, gimnasio_vencido);

	while(!desea_continuar){

		texto_separador("✪", "LIDER DEL GIMNASIO VENCIDO", 60);
		fuente_titulo("\tMEDALLA OBTENIDA\n\t\t");
		mostrar_medalla(lista_tope(personaje->medallas));
		printf("\n");

		if(!pidio_prestado)
			printf("[T]: Tomar prestado un Pokemon\n");
		
		printf("[C]: Cambiar Pokemon de batalla\n");
		printf("[N]: Continuar\n");
		separador(60);

		scanf("%s", eleccion);

		switch(toupper(eleccion[0])){
			case 'N':
				desea_continuar = true;
				break;
			case 'C':
				rearmar_equipo(personaje);
				break;				
			case 'T':
				if(!pidio_prestado){
					pedir_pokemon(personaje, lider);				
					pidio_prestado = true;
				}
				break;
			default:
				break;
		}

	}
}
void menu_batalla(personaje_t *personaje, entrenador_t *entrenador, pokemon_t *pkm_personaje, pokemon_t *pkm_entrenador){
	if (!personaje || !entrenador || !pkm_entrenador || !pkm_personaje){
		mi_log("En menu_batalla", LOG_ERROR);
		return;
	}

	texto_separador("◒", "MENU DE BATALLA", 60);
	fuente_titulo("ENTRENADOR\t  POKEMON\t\tESTADISTICAS\n");
	fuente_titulo(personaje->nombre);
	printf("\t\t");
	mostrar_pokemon(pkm_personaje);
	
	printf("\t\t\tvs.\n");
	
	if(entrenador->es_lider)
		printf("✪ ");

	fuente_titulo(entrenador->nombre);
	printf("\t\t");
	mostrar_pokemon(pkm_entrenador);

	printf("\n[N] Pelear!");
	
	char eleccion = 'X';
	while(toupper(eleccion) != 'N'){
		scanf("%c", &eleccion);
	}
}
bool menu_derrota(personaje_t *personaje){
	if (!personaje){
		mi_log("En menu_derrota", LOG_ERROR);
		return true;
	}


	char eleccion[MAX_INPUT];
	bool desea_reintentar = false;
	bool desea_salir = false;

	while(!desea_reintentar && !desea_salir){
		if(LOG_LEVEL<LOG_ERROR)
			limpiar_pantalla();

		texto_separador("⨂", "DERROTA", 60);
		fuente_titulo("\tTODOS TUS POKEMONES FUERON VENCIDOS\n\t\t\n\n");
	
		printf("[C]: Cambiar Pokemon de batalla\n");
		printf("[R]: Reintentar\n");
		printf("[F]: Finalizar partida\n");
		separador(60);
		scanf("%s", eleccion);

		switch(toupper(eleccion[0])){
			case 'C':
				rearmar_equipo(personaje);
				break;
			case 'R':
				desea_reintentar = true;
				break;
			
			case 'F':
				desea_salir = true;
				break;
		}
	}

	return desea_salir;
}