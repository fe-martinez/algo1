#include <stdio.h>
#include <stdbool.h>

const int MINIMAS_VECES = 1;
const int MAXIMAS_VECES = 100;

bool es_cantidad_bolsas_valida(int bolsas){

	if (bolsas >= MINIMAS_VECES || bolsas <= MAXIMAS_VECES){
		return true;
	} else{
		return false;
	}
}

int cantidad_de_rollos(int bolsas_por_dia, int dias, int bolsas_por_rollo) {

	int rollitos = ((bolsas_por_dia * dias) / bolsas_por_rollo);

	if ((bolsas_por_dia * dias) % bolsas_por_rollo != 0) {
		rollitos++;
	}

	return rollitos;
}

int main(){

	int bolsas_diarias;
	int dias;
	int bolsas_por_rollo;

	printf("Charly, ¿cuantas veces hace caca Alma por dia?:");
	scanf("%i", &bolsas_diarias);

	while(!es_cantidad_bolsas_valida(bolsas_diarias)){
		printf("Charly, ¿cuantas veces hace caca Alma por dia? (entre %i y %i):", MINIMAS_VECES, MAXIMAS_VECES);
		scanf("%i", &bolsas_diarias);
		}

	printf("¿Cuantos dias pensas quedarte?:");
	scanf("%i", &dias);

	printf("¿Cuantas bolsas vienen en los rollitos que queres comprar?:");
	scanf("%i", &bolsas_por_rollo);

	printf("Charly, vas a tener que llevar %i rollitos.\n", cantidad_de_rollos(bolsas_diarias, dias, bolsas_por_rollo));


	return 0;
}