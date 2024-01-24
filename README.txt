//Aventura Pokemon - Franco Papa 106249

-----------------------------

- Qué Es:

Este es un juego de Pokémon en el que el usuario carga desde un archivo .txt su personaje con su conjunto de Pokémones. El usuario carga también desde otro archivo de texto una serie de gimnasios Pokémon el numero de la funcion de batalla a utilizar y entrenadores, cada uno con sus Pokémon. 
El juego recrea la experiencia de convertirse en un maestro Pokémon, dominando gimnasios, venciendo entrenadores y mejorando e intercambiando sus pokemones de batalla. Una vez se hayan vencido todos los gimnasios el jugador recibe el titulo de Maestro Pokémon y la partida se acaba. 

Se incluyen 2 archivos:
pokemon.txt 	- Archivo con la información de un personaje.
gimnasios.txt 	- Archivo con la información de los gimnasios, fiel a uno de los juegos de la saga.

Las funciones de batalla son:

1) BATALLA POKÉMON:
Simula un combate por turnos como el de los juegos, mostrando las barras de vida e informando si los ataques golpean o no y cuanto daño hacen. La velocidad de los Pokémon determina si el golpe erra o no, y luego se calcula el daño recibido en funcion de los atributos de los Pokémon combatientes en combinación con un poco de aleatoriedad.

2) PISTA DE OBSTÁCULOS:
Simula una pista de obstáculos en la que ambos Pokémon compiten por la victoria. En función de los atributos de los mismos se calcula cuál gana la carrera, si ambos resultados coincide, se sortea el ganador (50% de chances para cada uno).

3) TEST DE INTELIGENCIA:
Ambos Pokémon reciben un número de IQ relativo dependiendo de las letras en sus nombres. El Pokémon con mayor inteligencia gana y si ambos resultados coinciden, se sortea el ganador (50% de chances para cada uno).

4) CANALIZCIÓN DE ENERGÍA MÁXIMA:
Ambos Pokémon canalizan energía, cuyo valor depende de su Ataque y su Velocidad. El Pokémon que hay canalizado mayor energía gana y si ambos resultados coinciden, se sortea el ganador (50% de chances para cada uno).

5) COMPETENCIA DE DESTRUCCIÓN:
Los Pokémon desatan todo su poder destructivo. El Pokémon con mayor Ataque vencerá y si ambos resultados coinciden, se sortea el ganador (50% de chances para cada uno).

-----------------------------

- Cómo Compilarlo:

gcc *.c -o aventura_pokemon -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -lm

-----------------------------

- Cómo Ejecutarlo:

./aventura_pokemon


-----------------------------

- ENTRENADORES DE UN GIMNASIO -

✧ Estructura Utilizada: Heap Minimal
✧ Motivo: Usar un heap minimal permite conseguir sin mucha complejidad el siguiente elemento en cuanto a dificultad, así el personaje se enfrentara a los gimnasios en orden de dificultad creciente.


- POKÉMON EN LOS ENTRENADORES DE UN GIMNASIO Y POKÉMON DE COMBATE DEL PERSONAJE-

✧ Estructura Utilizada: Vector Estatico
✧ Motivo: Resulta conveniente usar un vector ya que podemos acceder a sus elementos directamente. Si bien un vector dinámico también presenta estos pros más la posibilidad de agregar cuantos elementos queramos, como la cantidad máxima de elementos es conocida, no suma nada.
La unica desventaja de haber empleado un vector es que a la hora de quitarle al lider del gimnasio el Pokémon a prestar, es más complicado que reapuntar punteros como sería en el caso de una lista. Sin embargo al ser solo 6 elementos como máximo, se vuelve irrelevante.
Si bien en versiones anteriores se empleó una lista, fuera de lo mencionado anteriormente el uso de esta solo resultaría beneficioso en un caso particular.Este caso limite sería en el cual no hubiera suficiente memoria continua como para almacenar 6 Pokémon aunque dicho caso no parece factible.


- CONJUNTO DE POKÉMON OBTENIDOS -

✧ Estructura Utilizada: LISTA
✧ Motivo: Una lista permite almacenar cuantos elementos se desee mientras haya memoria suficiente. Eso es útil porque no sabemos cuantos pokémon tendrá el usuario entonces no se reservará memoria insuficiente ni de sobra. Un vector estático es otra buena opción, pero es innecesario tenerlos todos seguidos en memoria, más desconociendo la cantidad máxima. En cuanto a un ABB, sería util si quisieramos tenerlos ordenados con algun criterio pero no es el caso.


- CONJUNTO DE MEDALLAS -

✧ Estructura Utilizada: LISTA
✧ Motivo: Una lista permite almacenar cuantos elementos se desee mientras haya memoria suficiente. Eso es útil porque no sabemos cuántas medallas recibirá el jugador entonces no se reservará memoria insuficiente ni de sobra. Un vector estático es otra buena opción, pero es innecesario tenerlos todos seguidos en memoria, más desconociendo la cantidad máxima. En cuanto a un ABB, sería util si quisieramos tenerlos ordenados con algun criterio pero no es el caso. Una Cola suena interesante ya que las medallas se muestran en el orden en que se obtuvieron. Sin embargo se necesitaría desapilarlas, mostrarlas, almacenarlas en una estructura auxiliar y volver a insertarlas cada vez que se quisiera mostrar el conjunto, volviendolo menos efectivo.

-----------------------------

Comentario: En ultis.h hay algunos macros que facilitan las pruebas del programa. Estas son SIMULACION_RAPIDA, LOG_LEVEL y CARGA_RAPIDA