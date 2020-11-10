//
// Created by gavaz on 08/11/2020.
//

#ifndef UNTITLED_LISTADINENCAD_H
#define UNTITLED_LISTADINENCAD_H

#include <stdio.h>

//Arquivo ListaDinEncad.h
struct index{
    int idPessoa;
    int RRN;
};

typedef struct elemento* Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int remove_lista(Lista* li, int id);
int tamanho_lista(Lista* li);
void imprime_lista(Lista* li);
int insere_lista_ordenada(Lista* li, struct index al);
int consulta_lista_id(Lista* li, int id, struct index *al);
void salva_arq(Lista* li, FILE *indexFile);
#endif //UNTITLED_LISTADINENCAD_H
