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
    static char resultado[30];
    char temp[30];
    char pilha[30];
    int topo = -1;

    strcpy(temp, exp);

    // 1. inverter expressão
    inverter(temp);

    // 2. trocar parênteses
    for(int i = 0; temp[i]; i++){
        if(temp[i] == '(') temp[i] = ')';
        else if(temp[i] == ')') temp[i] = '(';
    }

    int k = 0;

    // 3. infixa → pós-fixa
    for(int i = 0; temp[i]; i++){
        char c = temp[i];

        // operando
        if((c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9')){
            resultado[k++] = c;
        }
        // abre parêntese
        else if(c == '('){
            pilha[++topo] = c;
        }
        // fecha parêntese
        else if(c == ')'){
            while(topo != -1 && pilha[topo] != '('){
                resultado[k++] = pilha[topo--];
            }
            topo--; // remove '('
        }
        // operador
        else{
            while(topo != -1 && precedencia(pilha[topo]) >= precedencia(c)){
                resultado[k++] = pilha[topo--];
            }
            pilha[++topo] = c;
        }
    }

    // esvaziar pilha
    while(topo != -1){
        resultado[k++] = pilha[topo--];
    }

    resultado[k] = '\0';

    // 4. inverter resultado → prefixa
    inverter(resultado);

    return resultado;
}