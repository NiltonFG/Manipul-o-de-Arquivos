//
// Created by gavaz on 08/11/2020.
//

#include "ListaDinEncad.h"
#include "funcoesArq.h"
#include <stdio.h>
#include <stdlib.h>

//Definição do tipo lista
struct elemento{
    struct index dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

struct pessoa1{
    Pessoa pessoa;
    struct pessoa1 *prox;
};
typedef struct pessoa1 Elem1;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

Lista1* cria_lista1(){
    Lista1* li = (Lista1*) malloc(sizeof(Lista1));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

void libera_lista1(Lista1* li){
    if(li != NULL){
        Elem1* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_id(Lista* li, int id, struct index *al){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.RRN != id){
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int insere_lista_final(Lista1* li, Pessoa pessoa){
    if(li == NULL)
        return 0;
    Elem1* no;
    no = (Elem1*)malloc(sizeof(Elem1));
    if(no == NULL)
        return 0;

    no->pessoa = pessoa;
    no->prox = NULL;

    if((*li) == NULL){
        *li = no;
    }else {
        Elem1 *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct index al){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    if((*li) == NULL){//lista vazia: insere início
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        Elem *ant, *atual = *li;
        while(atual != NULL && atual->dados.idPessoa < al.idPessoa){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere início
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_lista(Lista* li, int id){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem *ant, *no = *li;
    while(no != NULL && no->dados.idPessoa != id){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//não encontrado
        return 0;

    if(no == *li)//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}


int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}


void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL){
        printf("%d %d\n",no->dados.RRN,no->dados.idPessoa);
        no = no->prox;
    }
}

void pre_insere_bin(Lista1* li,FILE* binFile){
    if(li == NULL)
        return;
    Elem1* no;
    no = *li;
    char c;
    while(fread(&c, sizeof(char), 1, binFile) != 0 && no != NULL) {
        fseek(binFile,-1,SEEK_CUR);
        insereBinario(&no->pessoa,binFile);
        no = no->prox;
    }
}


void salva_arq(Lista* li, FILE *indexFile){
    char c = '0';
    char c2 = '$';
    if(li == NULL)
        return;
    fseek(indexFile,0,SEEK_SET);
    fwrite(&c, sizeof(char), 1, indexFile);
    for(int i =0; i < 7; i++){
    fwrite(&c2, sizeof(char), 1, indexFile);
    }
    Elem* no = *li;
    while(no != NULL){
        fwrite(&(no->dados.idPessoa), sizeof(int), 1, indexFile);
        fwrite(&(no->dados.RRN), sizeof(int), 1, indexFile);
        no = no->prox;
    }
}