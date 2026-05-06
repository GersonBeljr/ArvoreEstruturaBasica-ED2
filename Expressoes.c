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

    //Tokenizar por espaço
    char *t = strtok(copia, " ");
    while(t != NULL){
        tokens[n++] = t;
        t = strtok(NULL, " ");
    }

    //Pilha de strings
    char *pilha[30];
    int topo = -1;

    //Percorrer de trás pra frente (prefixa)
    for(int i = n-1; i >= 0; i--){
        char *tok = tokens[i];

        // operando (número, variável, função)
        if(strcmp(tok, "+") != 0 &&
           strcmp(tok, "-") != 0 &&
           strcmp(tok, "*") != 0 &&
           strcmp(tok, "/") != 0 &&
           strcmp(tok, "^") != 0){

            pilha[++topo] = tok;
        }
        else{
            // operador → pega dois operandos
            if(topo < 1) return exp; // erro

            char *op1 = pilha[topo--];
            char *op2 = pilha[topo--];

            static char temp[100];
            temp[0] = '\0';

            strcat(temp, tok);
            strcat(temp, " ");
            strcat(temp, op1);
            strcat(temp, " ");
            strcat(temp, op2);

            pilha[++topo] = temp;
        }
    }

    // resultado final
    strcpy(resultado, pilha[topo]);
    return resultado;
}