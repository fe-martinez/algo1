#include <stdio.h>
#include <stdbool.h>

const char PEON = 'P';
const char TORRE = 'T';
const char ALFIL = 'A';
const char CABALLO = 'C';
const char REINA = 'Q';
const char REY = 'R';
const int MAXIMO_TABLERO = 8;
const int MINIMO_TABLERO = 1;

bool es_pieza_valida(char pieza) {
	return(pieza == PEON || pieza == TORRE || pieza == ALFIL || pieza == CABALLO || pieza == REINA || pieza == REY);
}

bool es_numero_valido(int numero) {
	return(numero >= MINIMO_TABLERO && numero <= MAXIMO_TABLERO);
}

bool movimiento_peon(int fila_inicial, int columna_inicial, int fila_llegada, int columna_llegada) {
	if (fila_llegada == (fila_inicial + 1) && (columna_inicial == columna_llegada)) {
		return true;
	} else {
		return false;
	}
}

/* Puede variar solo la fila o solo la columna */
bool movimiento_torre(int fila_inicial, int columna_inicial, int fila_llegada, int columna_llegada) {
	if (((fila_inicial != fila_llegada) && (columna_inicial == columna_llegada)) || ((fila_inicial == fila_llegada) && (columna_inicial != columna_llegada))) {
		return true;
	} else {
		return false;
	}
}

/* Para que el movimiento del alfil sea valido, el modulo de (fila de llegada - fila de salida) tiene que ser igual al de (columna llegada - columna salida).*/
bool movimiento_alfil(int fila_inicial, int columna_inicial, int fila_llegada, int columna_llegada) {
	int division_filas;
	int division_columnas;

	if(fila_inicial > fila_llegada) {
		division_filas = fila_inicial-fila_llegada;
	} else {
		division_filas = fila_llegada-fila_inicial;
	}

	if(columna_inicial > columna_llegada) {
		division_columnas = columna_inicial-columna_llegada;
	} else {
		division_columnas = columna_llegada-columna_inicial;
	}

	if(division_filas != division_columnas) {
		return false;
	} else if (division_filas == 0 || division_columnas == 0) {
		return false;
	} else {
		return true;
	}
}

int main(){
	char pieza;
	int fila_inicial;
	int columna_inicial;
	int fila_llegada;
	int columna_llegada;

	printf("Piezas: Peon(P), Torre(T), Alfil(A), Caballo(C), Reina(Q), Rey(R).\n");
	printf("Decime la inicial de la pieza a mover: ");
	scanf(" %c", &pieza);
	while(!es_pieza_valida(pieza)) {
		printf("Esa pieza no existe, elegi entre %c, %c, %c, %c, %c o %c: ", PEON, TORRE, ALFIL, CABALLO, REINA, REY);
		scanf(" %c", &pieza);
	}

	printf("¿En que fila esta tu pieza?: ");
	scanf("%i", &fila_inicial);
	while(!es_numero_valido(fila_inicial)) {
		printf("Eso significaria que tu pieza esta fuera del tablero (numero entre %i y %i): ", MINIMO_TABLERO, MAXIMO_TABLERO);
		scanf("%i", &fila_inicial);
	}

	printf("¿En que columna esta tu pieza?: ");
	scanf("%i", &columna_inicial);
	while(!es_numero_valido(columna_inicial)) {
		printf("Eso significaria que tu pieza esta fuera del tablero (numero entre %i y %i): ", MINIMO_TABLERO, MAXIMO_TABLERO);
		scanf("%i", &columna_inicial);
	}

	printf("¿A que fila queres llevar tu pieza?: ");
	scanf("%i", &fila_llegada);
	while(!es_numero_valido(fila_llegada)) {
		printf("Eso significaria que tu pieza caeria fuera del tablero (numero entre %i y %i): ", MINIMO_TABLERO, MAXIMO_TABLERO);
		scanf("%i", &fila_llegada);
	}

	printf("¿A que columna queres llevar tu pieza?: ");
	scanf("%i", &columna_llegada);
	while(!es_numero_valido(columna_llegada)) {
		printf("Eso significaria que tu pieza caeria fuera del tablero (numero entre %i y %i): ", MINIMO_TABLERO, MAXIMO_TABLERO);
		scanf("%i", &columna_llegada);
	}

	switch(pieza) {
		case 'P':
			if (movimiento_peon(fila_inicial, columna_inicial, fila_llegada, columna_llegada) == true) {
			 	printf("El movimiento que elegiste es valido!\n");
			} else {
			 	printf("Volve a leer el manual por favor, ese movimiento no vale.\n");
			}
			break;
		case 'T':
			if (movimiento_torre(fila_inicial, columna_inicial, fila_llegada, columna_llegada) == true) {
				printf("El movimiento que elegiste es valido!\n");
			} else {
				printf("Volve a leer el manual por favor, ese movimiento no vale.\n");
			}
		case 'A':
			if (movimiento_alfil(fila_inicial, columna_inicial, fila_llegada, columna_llegada) == true) {
				printf("El movimiento que elegiste es valido!\n");
			} else {
				printf("Volve a leer el manual por favor, ese movimiento no vale.\n");
			}


	}

}