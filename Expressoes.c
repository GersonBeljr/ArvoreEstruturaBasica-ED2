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


int precedencia(char op){
    if(op == '^') return 3;
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
    return 0;
}

void inverter(char *str){
    int i, j;
    char temp;
    int n = strlen(str);

    for(i = 0, j = n-1; i < j; i++, j--){
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

char* toPreFix(char exp[]){
    static char resultado[100];
    resultado[0] = '\0';

    char copia[100];
    strcpy(copia, exp);

    char *tokens[30];
    int n = 0;

    //tokeniza
    char *t = strtok(copia, " ");
    while(t != NULL){
        tokens[n++] = t;
        t = strtok(NULL, " ");
    }

    //inverter tokens
    for(int i = 0; i < n/2; i++){
        char *tmp = tokens[i];
        tokens[i] = tokens[n-1-i];
        tokens[n-1-i] = tmp;
    }

    char *pilhaOp[30];
    int topoOp = -1;

    char *saida[30];
    int k = 0;

    for(int i = 0; i < n; i++){
        char *tok = tokens[i];

        if(strcmp(tok, "+") != 0 &&
           strcmp(tok, "-") != 0 &&
           strcmp(tok, "*") != 0 &&
           strcmp(tok, "/") != 0 &&
           strcmp(tok, "^") != 0){

            saida[k++] = tok;
        }
        else{
            while(topoOp != -1 &&
                  precedencia(pilhaOp[topoOp][0]) > precedencia(tok[0])){
                saida[k++] = pilhaOp[topoOp--];
            }
            pilhaOp[++topoOp] = tok;
        }
    }

    while(topoOp != -1){
        saida[k++] = pilhaOp[topoOp--];
    }

    //inverter pra prefixa
    for(int i = 0; i < k/2; i++){
        char *tmp = saida[i];
        saida[i] = saida[k-1-i];
        saida[k-1-i] = tmp;
    }

    //MONTA NO FINAL
    for(int i = 0; i < k; i++){
        strcat(resultado, saida[i]);
        if(i != k-1) strcat(resultado, " ");
    }

    return resultado;
}