/*
    ÁRVORE CALCULADORA
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NUMERO,
    OPERADOR,
    FUNCAO,
} Tipo;

typedef struct NO{
    Tipo tipo;
    char info[10]; //a info deve ser char para aceitar os símbolos e letras (e para os numeros, 10 digitos max)
    struct NO *esq;
    struct NO *dir;
}NO;

//Define o tipo da estrutura e coloca nela o nome ArvBin
typedef struct NO* ArvBin;

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

//Percorre a arvore e libera NO a NO
void libera_NO(NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
}

//Libera a arvore toda
void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);
    free(raiz);
}

//Verifica se a arvore existe
int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
} 

//Retorna a altura da arvore
int altura_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
        
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    
    if(alt_esq<alt_dir)
        return (alt_dir + 1);
    else
        return(alt_esq + 1);
        
    
};

//Retorna o numero total de NOs na arvore
int totalNo_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    
    int alt_esq = totalNo_ArvBin(&((*raiz)->esq));
    int alt_dir = totalNo_ArvBin(&((*raiz)->dir));
    
    return(alt_esq + alt_dir + 1);
};

//PERCORRENDO A ARVORE
//Pre Ordem
void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%s ", (*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
};

//In Ordem
void inOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        inOrdem_ArvBin(&((*raiz)->esq));
        printf("%s ", (*raiz)->info);
        inOrdem_ArvBin(&((*raiz)->dir));
    }
};

//Pos Ordem
void posOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%s ", (*raiz)->info);
    }
};

NO* construir(char *tokens[], int *pos){ //passa a lista de tokens inteira de uma vez e insere tds recursivamente
    if(tokens[*pos] == NULL)
        return NULL;
    //CRIAR NO E ATRIBUIR VALOR
        NO *novo = (NO*) malloc(sizeof(NO));

        strcpy(novo->info, tokens[*pos]);
        novo->esq = NULL;
        novo->dir = NULL;

        if(strcmp(novo->info, "+") == 0 ||
        strcmp(novo->info, "-") == 0 ||
        strcmp(novo->info, "*") == 0 ||
        strcmp(novo->info, "/") == 0 ||
        strcmp(novo->info, "^") == 0){
            novo->tipo = OPERADOR;
        }
        else if(strcmp(novo->info, "sqrt") == 0 ||
                strcmp(novo->info, "log") == 0 ||
                strcmp(novo->info, "neg") == 0){
            novo->tipo = FUNCAO;
        }
        else{
            novo->tipo = NUMERO;
        }
    //att o índice atravéz de um ptr pq vai usar passar para tds as funções o msm valor (conteúdo tem q ficar fora)
    (*pos)++;

    //SE TIVER CRIADO UMA OPERACAO OU FUNCAO, CONSTRÓI O Q TEM ATRÁS. SE FOR UM NUMERO SÓ COLOCA
    if(novo->tipo == OPERADOR){
        novo->esq = construir(tokens, pos);
        novo->dir = construir(tokens, pos);
    }
    else if(novo->tipo == FUNCAO){
        novo->dir = construir(tokens, pos);
    }
    return novo;
}

int main()
{   
    ListaExp* lista = criaLista();
    char expressao[60];

    while(1){
        printf("insira a expressão de até 30 caracteres (0 para terminar): ");
        fgets(expressao, sizeof(expressao), stdin); //scaneia espacos, só para qndo quebra linha
        expressao[strcspn(expressao, "\n")] = '\0'; //troca o \n do enter por \0
        if(strcmp(expressao, "0") == 0) break;//o fgets deixa o \n no final

        //cria novo nó
        NoLista *new = (NoLista*) malloc(sizeof(NoLista));
        if(new == NULL){
            printf("Erro ao inserir expressão (desinstala o cod ae pq n tem espaço nessa bagaça)");
            break;
        }
        strcpy(new->exp, expressao); 
        new->next=NULL;

        //insere no fim
        if(*lista == NULL){
            *lista = new;
        } else {
            NoLista *aux = *lista;
            while(aux->next != NULL)
                aux = aux->next;
            aux->next = new;
        }
    }

    //lógica de atravessar a lista de exps traduzindo td pra preOrdem
    int e=1;
    printf("\n-----CONVERTENDO EXPRESSÕES PARA ORDEM PREFIXA-----\n");
    NoLista *carro = *lista;
    while(carro!=NULL){
        printf("\n%dª EXPRESSÃO: \n", e);
        strcpy(carro->exp, toPreFix(carro->exp)); 
        printf("%s\n", carro->exp);
        carro = carro->next;
        e++;
    } 
    printf("\n\n");

    //LÓGICA DA INSERÇÃO NA ÁRVORE
    carro = *lista;
    int i=0;
    e=1;

    printf("-----ÁRVORES DE CADA EXPRESSÃO ESCRITAS EM INORDEM-----\n");
    while(carro!=NULL){
        ArvBin* raiz = cria_ArvBin();
        char copia[60];
        strcpy(copia, carro->exp);

        char *t = strtok(copia, " ");
        //30 tokens ~= 60 chars
        char *tokens[30];
        int i =0;

        while(t != NULL){
            tokens[i++] = t;
            t = strtok(NULL, " ");
        }
        
        int pos = 0;
        NO *r = construir(tokens, &pos);
        *raiz = r; //raiz aponta pra pro primeiro no

        printf("\n%dª EXPRESSÃO: \n", e);
        inOrdem_ArvBin(raiz);
        printf("\n");
        carro = carro->next;

        //LIBERA TD
        libera_ArvBin(raiz);  
        e++;
    } 

    return 0;
}