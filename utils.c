#include "utils.h"

void mi_sleep(size_t N){
	if (!SIMULACION_RAPIDA)
		sleep(1);
}

void mi_log(const char *texto, size_t nivel){
	if(texto){
		char *niveles[] = {"\033[0;31mERROR\033[0m","\033[0;33mAVISO\033[0m", "\033[0;36mINFO\033[0m"};
	
		if (LOG_LEVEL >= nivel)
			printf("[%s]: %s\n", niveles[nivel-1], texto);
	}
}

void limpiar_pantalla(){
	if(LOG_LEVEL == 0)
		system("clear");
}

void fuente_titulo(char texto[]){
	char *letras[] = {"𝙰","𝙱","𝙲","𝙳","𝙴","𝙵","𝙶","𝙷","𝙸","𝙹",
					"𝙺","𝙻","𝙼","𝙽","𝙾","𝙿","𝚀","𝚁","𝚂","𝚃",
					"𝚄","𝚅","𝚆","𝚇","𝚈","𝚉"};
	char *numeros[] = {"𝟶","𝟷","𝟸","𝟹","𝟺","𝟻","𝟼","𝟽","𝟾","𝟿"};

	for(size_t i=0; i<strlen(texto); i++){
		int posicion = (int)(toupper(texto[i]) - 'A');

		if (toupper(texto[i]) >= 'A' && toupper(texto[i]) <= 'Z'){
			printf("%s", letras[posicion]);

		} else if (texto[i] >= '0' && texto[i] <= '9')
			printf("%s", numeros[i]);

		else 
			printf("%c", texto[i]);
	}
}

void texto_separador(const char *separador, char texto[], size_t largo){

	if(separador && texto){
	
		printf("%s ", separador);
		fuente_titulo(texto);
		printf(" %s ", separador);
	
		for(size_t i=0; i<(largo-strlen(texto)); ++i)
			printf("-");
		printf("*\n\n");
	}
}

void separador(size_t N){
	
	printf("\n*");
	for(size_t i=0; i<N+4; ++i)
		printf("-");

	printf("*\n\n");
}
