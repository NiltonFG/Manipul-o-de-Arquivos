//
// Created by gavaz on 08/11/2020.
//

#ifndef UNTITLED_LISTADINENCAD_H
#define UNTITLED_LISTADINENCAD_H

#include <stdio.h>
typedef struct pessoa{
    int idPessoa;
    char nomePessoa[100];
    int idade;
    char twitterPessoa[100];
    int RRN;
} Pessoa;

//Arquivo ListaDinEncad.h
struct index{
    int idPessoa;
    int RRN;
};

typedef struct elemento* Lista;
typedef struct pessoa1* Lista1;

Lista1* cria_lista1();
Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_final(Lista1* li, Pessoa pessoa);
int remove_lista(Lista* li, int id);
int tamanho_lista(Lista* li);
void imprime_lista(Lista* li);
int insere_lista_ordenada(Lista* li, struct index al);
int consulta_lista_id(Lista* li, int id, struct index *al);
void salva_arq(Lista* li, FILE *indexFile);
void pre_insere_bin(Lista1* li,FILE* binFile);
void libera_lista1(Lista1* li);
#endif //UNTITLED_LISTADINENCAD_H
