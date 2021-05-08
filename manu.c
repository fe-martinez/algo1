#include <stdio.h>

int main () {

	int numeromanu;
	int numeropart;
	const int VALOR_MAX = 100;
	const int VALOR_MIN = 1;
	
	//Numero de Manu
	printf("Numero de manu: ");
	scanf("%i", &numeromanu);
	while(numeromanu < VALOR_MIN || numeromanu > VALOR_MAX){
		printf("Error (numeros del 1 al 100): ");
		scanf("%i", &numeromanu);
	}

	//Numero del participante
	printf("Numero del participante: ");
	scanf("%i", &numeropart);
	while(numeropart < VALOR_MIN || numeropart > VALOR_MAX){
		printf("Error (numeros del 1 al 100): ");
		scanf("%i", &numeropart);
	}

	while(numeromanu != numeropart) {
		if (numeromanu > numeropart) {
			printf("Pista: mi numero es mas grande\n");
			printf("Otra chance: ");
			scanf("%i", &numeropart);
			while(numeropart < VALOR_MIN || numeropart > VALOR_MAX) {
				printf("Error (numeros del 1 al 100): ");
				scanf("%i", &numeropart);
			}
		} else {
			printf("Pista: mi numero es mas chico\n");
			printf("Otra chance: ");
			scanf("%i", &numeropart);
			while(numeropart < VALOR_MIN || numeropart > VALOR_MAX) {
				printf("Error (numeros del 1 al 100): ");
				scanf("%i", &numeropart);
			}
		}
	}
	
	printf("Ganaste!!\n");	

	return 0;
}