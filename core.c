#include "core.h"

void victoria(personaje_t *personaje){
	limpiar_pantalla();
	fuente_titulo("\t\tF E L I C I T A C I O N E S\n");
	mostrar_personaje(personaje);
}
void derrota(personaje_t *personaje, heap_t *gimnasios){
	limpiar_pantalla();
	fuente_titulo("\t\tBUEN INTENTO\n");
	separador(60);
	printf("Has logrado vencer %ld gimnasios.\nTe faltaron %ld para convertirte en un Maestro Pokemon\n\n",
		lista_elementos(personaje->medallas), heap_cantidad(gimnasios));
	
	mostrar_personaje(personaje);
}
void comenzar_partida(heap_t *heap_gimnasios, personaje_t *personaje){
	bool se_rinde = false;

	while (!heap_esta_vacia(heap_gimnasios) && !se_rinde){
		int resultado = GANO_PRIMERO;

		gimnasio_t *gimnasio = (gimnasio_t*)heap_raiz(heap_gimnasios);
		menu_gimnasio(gimnasio, personaje);
		
		limpiar_pantalla();
				
		resultado = enfrentar_entrenadores(gimnasio, personaje);
		
		if(resultado == GANO_PRIMERO)
			heap_quitar_raiz(heap_gimnasios);
		else{
			if(menu_derrota(personaje))
				se_rinde = true;
		}
	}

	if (heap_esta_vacia(heap_gimnasios))
		personaje->maestro_pokemon = true;
}
void simular_partida(heap_t *heap_gimnasios, personaje_t *personaje){
	int resultado = true;

	while(!heap_esta_vacia(heap_gimnasios) && resultado == GANO_PRIMERO){
		gimnasio_t *gimnasio_actual = heap_raiz(heap_gimnasios);
		resultado = simular_gimnasio(gimnasio_actual, personaje);

		if (resultado == GANO_PRIMERO){ 
			otorgar_medalla(personaje, gimnasio_actual);
			heap_quitar_raiz(heap_gimnasios);
		}
	}		
	limpiar_pantalla();
	if (heap_esta_vacia(heap_gimnasios))
		personaje->maestro_pokemon = true;
}
int main(){
	heap_t *heap_gimnasios = heap_crear(comparar_gimnasios, gimnasio_destruir);
	personaje_t *personaje = NULL;

	char modo = menu_inicio(heap_gimnasios, &personaje);

	switch (toupper(modo)){

		case 'E':
		mi_log("Error en el menu de inicio", LOG_ERROR);
			break;

		case 'I':
			comenzar_partida(heap_gimnasios, personaje);
			break;

		case 'S':
			simular_partida(heap_gimnasios, personaje);
			break;

	}

	if(personaje->maestro_pokemon){
		victoria(personaje);
	}
	else{
		derrota(personaje, heap_gimnasios);
	}

	heap_destruir(heap_gimnasios);
	personaje_destruir(personaje);
	return 0;
}