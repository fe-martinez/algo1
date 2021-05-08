#include <stdio.h>
#include <stdbool.h>

const char SUMA = 'S';
const char RESTA = 'R';
const char MULTIPLICACION = 'M';
const char DIVISION = 'D';

bool es_operacion(char operacion) {
	return (operacion == SUMA || operacion == RESTA || operacion == MULTIPLICACION || operacion == DIVISION);
}

int suma(int primer_numero, int segundo_numero){
	int total = primer_numero + segundo_numero;
	return total;
}

int resta(int primer_numero, int segundo_numero) {
	int total = primer_numero - segundo_numero;
	return total;
}

int multiplicacion(int primer_numero, int segundo_numero) {
	int total = primer_numero * segundo_numero;
	return total;
}

int division(int primer_numero, int segundo_numero) {
	int total = primer_numero / segundo_numero;
	return total;
}

int main(){

	int primer_numero;
	int segundo_numero;
	char tipo_operacion;

	printf("Dame el primer numero: ");
	scanf("%i", &primer_numero);

	printf("Dame el segundo numero: ");
	scanf("%i", &segundo_numero);

	printf("Seleccione la operacion (%c, %c, %c o %c): ", SUMA, RESTA, MULTIPLICACION, DIVISION);
	scanf(" %c", &tipo_operacion);

	while(!es_operacion(tipo_operacion)){
		printf("No se que operacion es esa, solo admito %c, %c, %c o %c: ", SUMA, RESTA, MULTIPLICACION, DIVISION);
		scanf(" %c", &tipo_operacion);
	}

	switch(tipo_operacion) {
		case 'S':
			printf("%i\n", (suma(primer_numero, segundo_numero)));
			break;
		case 'R':
			printf("%i\n", (resta(primer_numero, segundo_numero)));
			break;
		case 'M':
			printf("%i\n", (multiplicacion(primer_numero, segundo_numero)));
			break;
		case 'D':
			if(segundo_numero == 0) {
				printf("No se puede dividir por 0 vas a romper el espacio tiempo!!!!\n");
			} else {
				printf("%i\n", (division(primer_numero, segundo_numero)));
			}
			break;
		}
}