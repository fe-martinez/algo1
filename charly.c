#include <stdio.h>

int main(){

	char letra_charly;
	int numero_charly;
	char letra_persona;
	int numero_persona;

		printf("Charly dame una letra: ");
		scanf("%c", &letra_charly);
	while(letra_charly < 'A' || letra_charly > 'Z'){
		printf("Error, una letra (entre A y Z): ");
		scanf("%c", &letra_charly);
	}
		printf("Charly dame un numero: ");
		scanf("%i", &numero_charly);
		printf("Persona dame una letra: ");
		scanf(" %c", &letra_persona);
		printf("Persona dame un numero: ");
		scanf("%i", &numero_persona);

	if (letra_charly == letra_persona && numero_charly == numero_persona){
		printf("Ganaste 500dls");
	} else {
		printf("Perdiste 1 peso");
	}

	//printf("La letra que eligio Charly es %c y el numero que eligio Charly es %i.", letra_charly, numero_charly);
	//printf(" La letra que eligio la persona es %c y el numero %i.", letra_persona, numero_persona);
	//printf("La letra que eligio charly es: %c ", letra_charly);

	return 0;
}

