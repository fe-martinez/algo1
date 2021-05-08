#include <stdio.h>
#include <stdbool.h>

/*
*PRE: recibe un caracter
*POST: devuelve true si es minuscula
*/

bool es_minuscula(char letra){
    return(letra >= 'a' && letra <= 'z');
}

void recibir_letra(char *letra){
    printf("Letra a convertir: ");
    scanf(" %c", letra);
    while(es_minuscula(*letra) != true){
        printf("Tiene que ser minuscula: ");
        scanf(" %c", letra);
    }
}

void capitalizar(char *letra){
    *letra = *letra-32;
}
int main(){

    char letra;
    recibir_letra(&letra);
    capitalizar(&letra);
    printf(" %c\n", letra);

    return 0;
}