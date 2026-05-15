//FUNC CALCULADORA

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double calcular(NO *raiz){

    if(raiz == NULL)
        return 0;

    //se for operação ou func 
    if(strcmp(raiz->info, "+") == 0)
        return calcular(raiz->esq) + calcular(raiz->dir);

    if(strcmp(raiz->info, "-") == 0)
        return calcular(raiz->esq) - calcular(raiz->dir);

    if(strcmp(raiz->info, "*") == 0)
        return calcular(raiz->esq) * calcular(raiz->dir);

    if(strcmp(raiz->info, "/") == 0)
        return calcular(raiz->esq) / calcular(raiz->dir);

    if(strcmp(raiz->info, "^") == 0)
        return pow(calcular(raiz->esq), calcular(raiz->dir));

    if(strcmp(raiz->info, "sqrt") == 0)
        return sqrt(calcular(raiz->dir));

    if(strcmp(raiz->info, "neg") == 0)
        return -calcular(raiz->dir);

    if(strcmp(raiz->info, "log") == 0)
        return log(calcular(raiz->dir));

    //se for um numero só retorna ele msm
    return atof(raiz->info);
}