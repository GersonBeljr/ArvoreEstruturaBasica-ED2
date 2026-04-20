/*
    Arvore Gerson:
*/

#include <stdio.h>
#include <stdlib.h>

//Define a estrutura
struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

//Define o tipo da estrutura e coloca nela o nome ArvBin
typedef struct NO* ArvBin;

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

//Percorre a arvore e libera NO a NO
void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
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
    
    if(alt_esq>alt_dir)
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
        printf("%d\n", (*raiz)->info);
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
        printf("%d\n", (*raiz)->info);
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
        printf("%d\n", (*raiz)->info);
    }
};

//Inserçao, Remoçao e consulta em Arvore Binaria
//Inserçao:
int insere_ArvBin(ArvBin* raiz, int valor){
    //Verifica se a raiz existe
    if(raiz == NULL)
        return 0;
        
    struct NO* new;
    new = (struct NO*) malloc(sizeof(struct NO));
    
    //Verifica se o novo nó foi criado corretamente
    if(new == NULL)
        return 0;
    
    new->info = valor;
    new->dir = NULL;
    new->esq = NULL;
    
    if(*raiz == NULL)
        *raiz = new;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL){
            ant = atual;
            
            //Se o elemento ja existir na arvore cancela
            if(valor == atual->info){
                free(new);
                return 0;
            }
            
            //Percorre verificando se o valor é maior ou menor que a esq ou dir;
            if(valor> atual->info){
                atual = atual->dir;
            } else {
                atual = atual->esq;
            }
        };
        
        if(valor > ant->info)
            ant->dir = new;
        else
            ant->esq = new;
        
        return 1;
    };
};

//Remoção (Remover folha, remover no com 1 ou 2 filhos);

struct NO* remove_atual(struct NO* atual){
    struct NO *no1, *no2;
    
    //Sem filho a esq
    if(atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    
    //Procura o filho mais a direira da sub-arv da esq;
    no1 = atual;
    no2 - atual->esq;
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }
    
    //Procura o filho mais a direita e coloca no lugar
    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    
    free(atual);
    return no2;
}

int remove_ArvBin(ArvBin *raiz, int valor){
    //Verifica se a arvore já não existe
    if(raiz == NULL) return 0;
    
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while(atual != NULL){
        // caso tenha achado o no a ser removido
        if(valor == atual->info){
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            };
            return 1;
        }
        
        //Anda para o proximo nó, esq ou dir
        ant = atual;
        if(valor > atual->info)
            atual = atual->dir;
        else 
            atual = atual->esq;
    }
    
}

//consulta: retorna 1 se achou e 0 se não;
int consulta_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}


int main()
{
   ArvBin* raiz = cria_ArvBin();

    return 0;
}