#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "osos_contra_reloj.h"

#define MAX_OBSTACULOS 600
#define MAX_HERRAMIENTAS 600
const char POLAR = 'I', PARDO = 'G', PANDA = 'P', CHLOE = 'C';
const char LINTERNA = 'L', VELA = 'V', BENGALA = 'E', PILA = 'B';
const char ARRIBA = 'W', ABAJO = 'S', IZQUIERDA = 'A', DERECHA = 'D';
const int COLUMNA_INICIO = 0;
const int FILAS = 20, COLUMNAS = 30;
const int DURACION_LINTERNA = 10, DURACION_VELA = 5, DURACION_BENGALA = 3;
const int DURACION_LINTERNA_PARDO = 15;
const int CANTIDAD_INICIAL_VELAS = 4, CANTIDAD_INICIAL_VELAS_POLAR = 6;
const int CANTIDAD_INICIAL_BENGALAS = 0, CANTIDAD_INICIAL_BENGALAS_PANDA = 2;
const char ARBOL = 'A', PIEDRA = 'P', KOALA = 'K', OSCURO = '-', VACIO = '_';
const int CANTIDAD_ARBOLES = 350, CANTIDAD_PIEDRAS = 80;
const int PILAS_MAPA = 30, VELAS_MAPA = 30, BENGALAS_MAPA = 10;

void imprimir(juego_t juego){
    char mapa[FILAS][COLUMNAS];

    int k = 0;
    int l = 0;

    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            mapa[i][j] = OSCURO;
        }
    }

    while(k < juego.cantidad_obstaculos){

        if(juego.obstaculos[k].visible == true){
            int i = juego.obstaculos[k].posicion.fil;
            int j = juego.obstaculos[k].posicion.col;
            mapa[i][j] = juego.obstaculos[k].tipo;
        }
        k++;
    }

    while(l < juego.cantidad_herramientas){

        if(juego.herramientas[l].visible == true){
            int i = juego.herramientas[l].posicion.fil;
            int j = juego.herramientas[l].posicion.col;
            mapa[i][j] = juego.herramientas[l].tipo;
        }
        l++;
    }

    int fila_oso = juego.personaje.posicion.fil;
    int columna_oso = juego.personaje.posicion.col;
    mapa[fila_oso][columna_oso] = juego.personaje.tipo;

    int fila_chloe = juego.amiga_chloe.fil;
    int columna_chloe = juego.amiga_chloe.col;
    if(juego.chloe_visible == true){
        mapa[fila_chloe][columna_chloe] = CHLOE;
    }

    int counter_koalas = 0;
    int counter_arboles = 0;
    int counter_piedras = 0;
    int counter_pilas = 0;
    int counter_velas = 0;


    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            if(mapa[i][j] == KOALA){
                counter_koalas++;
            } else if(mapa[i][j] == ARBOL){
                counter_arboles++;
            } else if(mapa[i][j] == PIEDRA){
                counter_piedras++;
            } else if(mapa[i][j] == PILA){
                counter_pilas++;
            } else if(mapa[i][j] == VELA){
                counter_velas++;
            }
        }
    }

    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }
    printf("%i, %i, %i, %i, %i\n", counter_arboles, counter_piedras, counter_koalas, counter_pilas, counter_velas);

}

void randomizar_fila_oso(int* fila){
    (*fila) = rand() % FILAS;
}

void randomizar_fila_chloe(int* fila){
    (*fila) = rand() % FILAS;
}

void randomizar_columna_chloe(int* columna){
    (*columna) = rand() % COLUMNAS;
}

int distancia_manhattan(coordenada_t posicion, coordenada_t objeto){
    int x = abs(posicion.fil - objeto.fil);
    int y = abs(posicion.col - objeto.col);
    int distancia = x + y;
    return distancia;
}

bool hay_objeto(juego_t* juego, int fila, int columna, int lugar){
    if(((fila == juego->obstaculos[lugar].posicion.fil) && (columna == juego->obstaculos[lugar].posicion.col)) || ((fila == juego->personaje.posicion.fil) && (columna == juego->personaje.posicion.col)) || ((fila == juego->amiga_chloe.fil) && (columna == juego->amiga_chloe.col))){
        return true;
    }else if(((fila == juego->herramientas[lugar].posicion.fil) && (columna == juego->herramientas[lugar].posicion.col)) || ((fila == juego->personaje.posicion.fil) && (columna == juego->personaje.posicion.col)) || ((fila == juego->amiga_chloe.fil) && (columna == juego->amiga_chloe.col))){
        return true;
    } else{
        return false;
    }
}

void colocar_arboles(juego_t* juego){
    int i = 0;
    
    while(i < CANTIDAD_ARBOLES){

        int fila = rand() % FILAS;
        int columna = rand() % COLUMNAS;
        
        bool coincidencia = false;

        for(int largo = 0; largo < i; largo++){
            if(hay_objeto(juego, fila, columna, largo)){
                coincidencia = true;
            }
        }

        if(coincidencia != true){
            juego->obstaculos[i].tipo = ARBOL;
            juego->obstaculos[i].posicion.fil = fila;
            juego->obstaculos[i].posicion.col = columna;
            juego->obstaculos[i].visible = false;
            i++;
            juego->cantidad_obstaculos++;
        }
    }

}

void colocar_piedras(juego_t* juego){
    int i = juego->cantidad_obstaculos;
    int l = 0;

    while(l < CANTIDAD_PIEDRAS){
        int fila = rand() % FILAS;
        int columna = rand() % COLUMNAS;
        bool coincidencia = false;
        for(int largo = 0; largo < i; largo++){
            if(hay_objeto(juego, fila, columna, largo)){
                coincidencia = true;
            }
        }
        if(coincidencia != true){
            juego->obstaculos[i].tipo = PIEDRA;
            juego->obstaculos[i].posicion.fil = fila;
            juego->obstaculos[i].posicion.col = columna;
            juego->obstaculos[i].visible = false;
            l++;
            i++;
            juego->cantidad_obstaculos++;
        }
    }
}

void colocar_pilas(juego_t* juego){

    int i = 0;
    while(i < PILAS_MAPA){
        int fila = rand() % FILAS;
        int columna = rand() % COLUMNAS;

        bool coincidencia = false;

        for(int j = 0; j < juego->cantidad_obstaculos; j++){
            if(hay_objeto(juego, fila, columna, j)){
                coincidencia = true;
            }
        }
        if(coincidencia == false){
            juego->herramientas[i].tipo = PILA;
            juego->herramientas[i].posicion.fil = fila;
            juego->herramientas[i].posicion.col = columna;
            juego->herramientas[i].visible = false;
            i++;
            juego->cantidad_herramientas++;
        }
    }
}

void colocar_velas(juego_t* juego){
    
    int largo = juego->cantidad_herramientas;
    int i = 0;

    while(i < VELAS_MAPA){
        int fila = rand() % FILAS;
        int columna = rand() % COLUMNAS;

        bool coincidencia = false;

        for(int j = 0; j < juego->cantidad_obstaculos; j++){
            if(hay_objeto(juego, fila, columna, j)){
                coincidencia = true;
            }
        }
        for(int k = 0; k < juego->cantidad_herramientas; k++){
            if(hay_objeto(juego, fila, columna, k)){
                coincidencia = true;
            }
        }
        if(coincidencia == false){
            juego->herramientas[largo].tipo = VELA;
            juego->herramientas[largo].posicion.fil = fila;
            juego->herramientas[largo].posicion.col = columna;
            juego->herramientas[largo].visible = false;
            i++;
            largo++;
            juego->cantidad_herramientas++;
        }
    }
}

void colocar_bengalas(juego_t* juego){
    
    int largo = juego->cantidad_herramientas;
    int i = 0;

    while(i < BENGALAS_MAPA){
        int fila = rand() % FILAS;
        int columna = rand() % COLUMNAS;

        bool coincidencia = false;

        for(int j = 0; j < juego->cantidad_obstaculos; j++){
            if(hay_objeto(juego, fila, columna, j)){
                coincidencia = true;
            }
        }
        for(int k = 0; k < juego->cantidad_herramientas; k++){
            if(hay_objeto(juego, fila, columna, k)){
                coincidencia = true;
            }
        }
        if(coincidencia == false){
            juego->herramientas[largo].tipo = BENGALA;
            juego->herramientas[largo].posicion.fil = fila;
            juego->herramientas[largo].posicion.col = columna;
            juego->herramientas[largo].visible = false;
            i++;
            largo++;
            juego->cantidad_herramientas++;
        }
    }
}

void colocar_koalas(juego_t* juego){
    if(juego->personaje.elemento_en_uso == 0){
        bool coincidencia = false;
        int fila = 0;
        int columna = 0;

        do{
            int i = 0;
            fila = rand() % FILAS;
            columna = rand() % COLUMNAS;
            coincidencia = false;
            while(i < juego->cantidad_obstaculos){
                if(hay_objeto(juego, fila, columna, i)){
                    coincidencia = true;
                }
                i++;
            }
        }while(coincidencia == true);



        if(coincidencia == false){
            juego->obstaculos[juego->cantidad_obstaculos].tipo = KOALA;
            juego->obstaculos[juego->cantidad_obstaculos].posicion.fil = fila;
            juego->obstaculos[juego->cantidad_obstaculos].posicion.col = columna;
            juego->obstaculos[juego->cantidad_obstaculos].visible = false;
            juego->cantidad_obstaculos++;
        }
    }
}

void llenar_mochila(personaje_t* personaje){
    
    personaje->mochila[0].tipo = LINTERNA;
    personaje->mochila[0].movimientos_restantes = DURACION_LINTERNA;
    personaje->cantidad_elementos++;

    personaje->mochila[1].tipo = VELA;
    personaje->mochila[1].movimientos_restantes = CANTIDAD_INICIAL_VELAS;
    personaje->cantidad_elementos++;

    personaje->mochila[2].tipo = BENGALA;
    personaje->mochila[2].movimientos_restantes = CANTIDAD_INICIAL_BENGALAS;
    personaje->cantidad_elementos++;
}

void inicializar_juego(juego_t* juego, char tipo_personaje){

    juego->personaje.tipo = tipo_personaje;
    juego->personaje.posicion.col = COLUMNA_INICIO;
    int fila_oso = 0;
    randomizar_fila_oso(&fila_oso);
    juego->personaje.posicion.fil = fila_oso;    
    
    int fila_chloe = 0;
    int columna_chloe = 0;
    randomizar_columna_chloe(&columna_chloe);
    randomizar_fila_chloe(&fila_chloe);
    juego->amiga_chloe.col = columna_chloe;
    juego->amiga_chloe.fil = fila_chloe;
    juego->chloe_visible = false;

    juego->personaje.elemento_en_uso = -1;
}

void actualizar_linterna(juego_t* juego){
    int contador = 0;

    if(juego->personaje.ultimo_movimiento == IZQUIERDA){
        while(contador < juego->cantidad_obstaculos){
            if(juego->obstaculos[contador].posicion.fil != juego->personaje.posicion.fil){
                juego->obstaculos[contador].visible = false;
            }
            if(juego->obstaculos[contador].posicion.col > juego->personaje.posicion.col){
                juego->obstaculos[contador].visible = false;
            }
            contador++;
        }
        if(juego->amiga_chloe.fil != juego->personaje.posicion.fil){
            juego->chloe_visible = false;
        }
        if(juego->amiga_chloe.col > juego->personaje.posicion.col){
            juego->chloe_visible = false;
        }
    }
    if(juego->personaje.ultimo_movimiento == DERECHA){
        while(contador < juego->cantidad_obstaculos){
            if(juego->obstaculos[contador].posicion.fil != juego->personaje.posicion.fil){
                juego->obstaculos[contador].visible = false;
            }
            if(juego->obstaculos[contador].posicion.col < juego->personaje.posicion.col){
                juego->obstaculos[contador].visible = false;
            }
            contador++;
        }
        if(juego->amiga_chloe.fil != juego->personaje.posicion.fil){
            juego->chloe_visible = false;
        }
        if(juego->amiga_chloe.col < juego->personaje.posicion.col){
            juego->chloe_visible = false;
        }
    }
    if(juego->personaje.ultimo_movimiento == ARRIBA){
        while(contador < juego->cantidad_obstaculos){
            if(juego->obstaculos[contador].posicion.col != juego->personaje.posicion.col){
                juego->obstaculos[contador].visible = false;
            }
            if(juego->obstaculos[contador].posicion.fil > juego->personaje.posicion.fil){
                juego->obstaculos[contador].visible = false;
            }
            contador++;
        }
        if(juego->amiga_chloe.col != juego->personaje.posicion.col){
            juego->chloe_visible = false;
        }
        if(juego->amiga_chloe.fil > juego->personaje.posicion.fil){
            juego->chloe_visible = false;
        }
    }
    if(juego->personaje.ultimo_movimiento == ABAJO){
        while(contador < juego->cantidad_obstaculos){
            if(juego->obstaculos[contador].posicion.col != juego->personaje.posicion.col){
                juego->obstaculos[contador].visible = false;
            }
            if(juego->obstaculos[contador].posicion.fil < juego->personaje.posicion.fil){
                juego->obstaculos[contador].visible = false;
            }
            contador++;
        }
        if(juego->amiga_chloe.col != juego->personaje.posicion.col){
            juego->chloe_visible = false;
        }
        if(juego->amiga_chloe.fil < juego->personaje.posicion.fil){
            juego->chloe_visible = false;
        }
    }
}

void prender_linterna(juego_t* juego){
    int fila_pj = juego->personaje.posicion.fil;
    int columna_pj = juego->personaje.posicion.col;

    if(juego->personaje.ultimo_movimiento == ARRIBA){
        for(int k = 0; k < juego->cantidad_obstaculos; k++){
            if(juego->obstaculos[k].posicion.col == columna_pj){
                if(juego->obstaculos[k].posicion.fil < fila_pj){
                    juego->obstaculos[k].visible = true;
                }
            }
        }
        if(juego->amiga_chloe.col == columna_pj){
                if(juego->amiga_chloe.fil < fila_pj){
                    juego->chloe_visible = true;
                }
            }
    }
    if(juego->personaje.ultimo_movimiento == ABAJO){
        for(int k = 0; k < juego->cantidad_obstaculos; k++){
            if(juego->obstaculos[k].posicion.col == columna_pj){
                if(juego->obstaculos[k].posicion.fil > fila_pj){
                    juego->obstaculos[k].visible = true;
                }
            }
        }
        if(juego->amiga_chloe.col == columna_pj){
                if(juego->amiga_chloe.fil > fila_pj){
                    juego->chloe_visible = true;
                }
            }
    }
    if(juego->personaje.ultimo_movimiento == IZQUIERDA){
        for(int k = 0; k < juego->cantidad_obstaculos; k++){
            if(juego->obstaculos[k].posicion.fil == fila_pj){
                if(juego->obstaculos[k].posicion.col < columna_pj){
                    juego->obstaculos[k].visible = true;
                }
            }
        }
        if(juego->amiga_chloe.fil == fila_pj){
                if(juego->amiga_chloe.col < columna_pj){
                    juego->chloe_visible = true;
                }
            }
    }
    if(juego->personaje.ultimo_movimiento == DERECHA){
        for(int k = 0; k < juego->cantidad_obstaculos; k++){
            if(juego->obstaculos[k].posicion.fil == fila_pj){
                if(juego->obstaculos[k].posicion.col > columna_pj){
                    juego->obstaculos[k].visible = true;
                }
            }
        }
        if(juego->amiga_chloe.fil == fila_pj){
                if(juego->amiga_chloe.col > columna_pj){
                    juego->chloe_visible = true;
                }
            }
    }
    actualizar_linterna(juego);
}

void prender_vela(juego_t* juego){
    int fila_pj = juego->personaje.posicion.fil;
    int columna_pj = juego->personaje.posicion.col;
    
    for(int k = 0; k < juego->cantidad_obstaculos; k++){
        if(juego->obstaculos[k].posicion.fil == fila_pj || juego->obstaculos[k].posicion.fil == fila_pj - 1 || juego->obstaculos[k].posicion.fil == fila_pj + 1){
                if(juego->obstaculos[k].posicion.col == columna_pj || juego->obstaculos[k].posicion.col == columna_pj - 1 || juego->obstaculos[k].posicion.col == columna_pj + 1){
                    juego->obstaculos[k].visible = true;
            }
        } 
    }
    if(juego->amiga_chloe.fil == fila_pj || juego->amiga_chloe.fil == fila_pj - 1 || juego->amiga_chloe.fil == fila_pj + 1){
                if(juego->amiga_chloe.col == columna_pj || juego->amiga_chloe.col == columna_pj - 1 || juego->amiga_chloe.col == columna_pj + 1){
                    juego->chloe_visible = true;
            }
        }

    for(int k = 0; k < juego->cantidad_obstaculos; k++){
        if(juego->obstaculos[k].posicion.fil < fila_pj - 1 || juego->obstaculos[k].posicion.fil > fila_pj + 1){
            juego->obstaculos[k].visible = false;
        }
        if(juego->obstaculos[k].posicion.col < columna_pj - 1 || juego->obstaculos[k].posicion.col > columna_pj + 1){
            juego->obstaculos[k].visible = false;
        }
    }
    if(juego->amiga_chloe.fil < fila_pj - 1 || juego->amiga_chloe.fil > fila_pj + 1){
                    juego->chloe_visible = false;
        }
        if(juego->amiga_chloe.col < columna_pj - 1 || juego->amiga_chloe.col > columna_pj + 1){
                    juego->chloe_visible = false;
        }
}

void prender_bengala(juego_t* juego){
    coordenada_t centro;

    centro.fil = rand() % FILAS;
    centro.col = rand() % COLUMNAS;

    for(int i = 0; i < juego->cantidad_obstaculos; i++){
        if(distancia_manhattan(centro, juego->obstaculos[i].posicion) <= 3){
            juego->obstaculos[i].visible = true;
        }
    }
    if(distancia_manhattan(centro, juego->amiga_chloe) <= 3){
            juego->chloe_visible = true;
        }

    for(int i = 0; i < juego->cantidad_obstaculos; i++){
        if(distancia_manhattan(centro, juego->obstaculos[i].posicion) > 3){
            juego->obstaculos[i].visible = false;
        }
    }
    if(distancia_manhattan(centro, juego->amiga_chloe) > 3){
            juego->chloe_visible = false;
        }
}

void apagar_item(juego_t* juego){
    int i = 0;

    while(i < juego->cantidad_obstaculos){
        juego->obstaculos[i].visible = false;
        i++;
    }

    if(juego->chloe_visible == true){
        juego->chloe_visible = false;
    }
}

void usar_item(juego_t* juego, char jugada){

    if(((juego->personaje.elemento_en_uso == -1)) && (jugada == LINTERNA)){
        juego->personaje.elemento_en_uso = 0;
    } else if((juego->personaje.elemento_en_uso == 0) && (jugada == LINTERNA)){
        juego->personaje.elemento_en_uso = -1;
        apagar_item(juego);
    }

    if(((juego->personaje.elemento_en_uso == -1)) && (jugada == VELA)){
        juego->personaje.elemento_en_uso = 1;
    } else if((juego->personaje.elemento_en_uso == 1) && (jugada == VELA)){
        juego->personaje.elemento_en_uso = -1;
        apagar_item(juego);
    }

    if(((juego->personaje.elemento_en_uso == -1)) && (jugada == BENGALA)){
        juego->personaje.elemento_en_uso = 2;
    } else if((juego->personaje.elemento_en_uso == 2) && (jugada == BENGALA)){
        juego->personaje.elemento_en_uso = -1;
        apagar_item(juego);
    }
}

void realizar_jugada(juego_t* juego, char jugada){

    if((jugada == ARRIBA) && (juego->personaje.posicion.fil > 0)){
        (juego->personaje.posicion.fil)--;
        juego->personaje.ultimo_movimiento = jugada;
    } else if((jugada == IZQUIERDA) && (juego->personaje.posicion.col > 0)){
        (juego->personaje.posicion.col)--;
        juego->personaje.ultimo_movimiento = jugada;
    } else if((jugada == ABAJO) && (juego->personaje.posicion.fil < FILAS)){
        (juego->personaje.posicion.fil)++;
        juego->personaje.ultimo_movimiento = jugada;
    } else if((jugada == DERECHA) && (juego->personaje.posicion.col < COLUMNAS)){
        (juego->personaje.posicion.col)++;
        juego->personaje.ultimo_movimiento = jugada;
    }

    if(jugada == LINTERNA){
        usar_item(juego, jugada);
    } else if(jugada == VELA){
        usar_item(juego, jugada);
    } else if(jugada == BENGALA){
        usar_item(juego, jugada);
    }
}

int estado_juego(juego_t juego){
    int estado_juego = 0;

    coordenada_t coordenada_personaje = juego.personaje.posicion;

    if((coordenada_personaje.fil == juego.amiga_chloe.fil) && (coordenada_personaje.col == juego.amiga_chloe.col)){
        estado_juego = -1;
    }

    return estado_juego;
}

int main(){
    juego_t juego;
    srand (( unsigned)time(NULL));
    char tipo_personaje = POLAR;
    inicializar_juego(&juego, tipo_personaje);
    llenar_mochila(&juego.personaje);
    colocar_arboles(&juego);
    colocar_piedras(&juego);
    colocar_pilas(&juego);
    colocar_velas(&juego);
    colocar_bengalas(&juego);

    char jugada;
    while(estado_juego(juego) == 0){
    imprimir(juego);
    scanf(" %c", &jugada);
    realizar_jugada(&juego, jugada);
    if(juego.personaje.elemento_en_uso != -1){
        if(juego.personaje.elemento_en_uso == 0){
            prender_linterna(&juego);
        } else if(juego.personaje.elemento_en_uso == 1){
            prender_vela(&juego);
        } else if(juego.personaje.elemento_en_uso == 2){
            prender_bengala(&juego);
        }
    }
    colocar_koalas(&juego);
    printf("\n\n\n");
    }

    return 0;
}