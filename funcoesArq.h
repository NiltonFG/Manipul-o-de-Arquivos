//
// Created by gavaz on 08/11/2020.
//

#ifndef UNTITLED_FUNCOESARQ_H
#define UNTITLED_FUNCOESARQ_H

#include <wchar.h>
#include <stdio.h>
#include "ListaDinEncad.h"

//arquivo funções lista.h
typedef struct pessoa{
    int idPessoa;
    char nomePessoa[100];
    int idade;
    char twitterPessoa[100];
    int RRN;
} Pessoa;

Pessoa *pesquisa_idade(FILE *binFile, int valor,int verificao);
        void leArqBin(char* arqvEntrada ,char* arqPessoa,char* arqIndexaPessoa);
void insereBinario(Pessoa* pessoa, FILE* binFile);
void setCabecalho(FILE* binFile, int quantRegistros);
void insereIndex(Lista* li, Pessoa* pessoa);


#endif //UNTITLED_FUNCOESARQ_H
