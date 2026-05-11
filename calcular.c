//FUNC CALCULADORA

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calcular(char *ts[]){
    char *pilha[20];
    int i, e=0;
    for(i=0; ts[i]!=NULL; i++){
        switch(*ts[i]){
            case '+':
                pilha[e++]= ts[i-1]+ts[i+1];
            case '-':
                pilha[e++]= *ts[i-1]-*ts[i+1];
            case '*':
                pilha[e++]= ts[i-1]*ts[i+1];
            case '/':
                pilha[e++]= ts[i-1]/ts[i+1];
            case '^':
                pilha[e++]= pow(ts[i-1], ts[i+1]);
        }
        printf("pilha: %s ", pilha[e-1]);
    }
}