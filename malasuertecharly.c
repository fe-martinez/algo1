#include <stdio.h>

const char PRIMERA_ALFABETO = 'A';
const char ULTIMA_ALFABETO = 'Z';

const int MINIMO_VALOR_PERMITIDO = 1;
const int MAXIMO_VALOR_PERMITIDO = 50;

const int INTENTOS_PERMITIDOS = 10;

int main() {

	char letra_charly;
	int numero_charly;

	char letra_participante;
	int numero_participante;
	int intentos = 1;

	printf("Charly tirate esa letra pa (entre %c y %c): ", PRIMERA_ALFABETO, ULTIMA_ALFABETO);
	scanf(" %c", &letra_charly);
	while (letra_charly < PRIMERA_ALFABETO || letra_charly > ULTIMA_ALFABETO){
		printf("Charly, te equivocastesssss, te dije entre %c y %c: ", PRIMERA_ALFABETO, ULTIMA_ALFABETO);	
		scanf(" %c", &letra_charly);
	}

	printf("Charly tirate ese numero pa (%i y %i): ", MINIMO_VALOR_PERMITIDO, MAXIMO_VALOR_PERMITIDO);
	scanf("%i", &numero_charly);
	while (numero_charly < MINIMO_VALOR_PERMITIDO || numero_charly > MAXIMO_VALOR_PERMITIDO){
		printf("Charly, te equivocastesssss, te dije entre %i y %i: ", MINIMO_VALOR_PERMITIDO, MAXIMO_VALOR_PERMITIDO);
		scanf("%i", &numero_charly);
	}



	printf("Intento: %i\n", intentos);
	printf("Participante, elegi una letra: ");
	scanf(" %c", &letra_participante);
	printf("Participante, elegi un numero: ");
	scanf("%i", &numero_participante);

	while (!(letra_charly == letra_participante && numero_charly == numero_participante) 
		&& intentos <= INTENTOS_PERMITIDOS){

		intentos++;

		printf("Intento: %i\n", intentos);

		printf("Participante, elegi una letra: ");
		scanf(" %c", &letra_participante);
		
		printf("Participante, elegi un numero: ");
		scanf("%i", &numero_participante);

	}


	if (intentos <= INTENTOS_PERMITIDOS) {
		printf("Charly largá los dolarucos!");
	} else {
		printf("Dame ese pesito bb.");
	}

	return 0;
}

