//106249 Franco Papa - Utilidades

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#ifndef __UTILS_H__
#define __UTILS_H__

#define LOG_ERROR 			1 //Notifica Eventos perjudiciales para el programa.
#define LOG_AVISO 			2 //Notifica Eventos inesperados que que podrian alterar el comportamiento esperado y errores.
#define LOG_INFO 			3 //Notifica Todo lo anterior y algunos eventos relevantes.

//Macros
#define LOG_LEVEL 			0 //Nivel deseado (Dejar en 0 cuando este 'productivo').
#define SIMULACION_RAPIDA 	0 //Ponga esta valor en 1 si desea saltear todas las pausas y que el programa se corra en 'camara rapida'.
#define CARGA_RAPIDA 		0 //Carga automaticamente el personaje de 'pokemon.txt' y los gimnasios de 'gimnasios.txt'.

void limpiar_pantalla();
//post- Limpia la pantalla de la consola si el logeo esta desactivado.

void mi_log(const char * texto, size_t nivel);
//pre- Recibe un string y un nivel.
//post- Si el nivel de logeo de la aplicacion es mayor o igual al del mensaje, lo imprime.

void fuente_titulo(char texto[]);
//pre- Recibe un string.
//post- Imprime el string con una fuente llamativa.

void texto_separador(const char *separador, char texto[], size_t largo);
//pre- Recibe un separador (string), un mensaje (string) y un largo (int).
//post- Imprime el mensaje entre dos separadores y luego imprime guines (-) hasta que se la linea llegue al largo deseado y un * al final

void separador(size_t N);
//pre- Recibe un N (int).
//post- Imprime un separador de largo N

void mi_sleep(size_t N);
//post- Espera N segundos antes de continuar si simulacion rapida esta en 0.

#endif /* __UTILS_H__ */