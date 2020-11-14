//
// Created by gavaz on 09/11/2020.
//
#ifndef UNTITLED_INSERCAOATUALIZACAO_H
#define UNTITLED_INSERCAOATUALIZACAO_H
#include <stdio.h>
#include "funcoesArq.h"

typedef struct nomeCampo{
    char nomeCampoBusca[50];
    char nomeCampo1[50];
} nomeCampo;

void insereAtualiza(FILE* binFile,Pessoa* pessoa);
void compactaBin(FILE* binFile, int count);
Pessoa auxilirCompacta(FILE* binFile);
void pre_insere();
void pre_atualizaCampo();
void atualizaCampos(FILE* binFile,FILE* indexFile,Pessoa* pessoa,int aux_int);
int comparaCampo(char* nomeCampo);
void verfica_nulo(Pessoa* pessoa);


#endif //UNTITLED_INSERCAOATUALIZACAO_H
