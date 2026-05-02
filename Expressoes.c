/*
FUNÇÕES DE TRADUÇÃO DAS EXPRESSÕES PARA PRÉ E PÓS ORDEM
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoLista{
    char exp[30]; //a info deve ser char para aceitar os símbolos e letras (e para os numeros, 10 digitos max)
    struct NoLista *next;
}NoLista;

typedef struct NoLista* ListaExp;

ListaExp* criaLista(){
    ListaExp *raizL = (ListaExp*) malloc(sizeof(ListaExp));
    if(raizL != NULL)
        *raizL = NULL;
    return raizL;
}


char* toPreOrdem(char exp[]){
    return exp;
}