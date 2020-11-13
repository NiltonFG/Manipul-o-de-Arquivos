//
// Created by gavaz on 09/11/2020.
//
#ifndef UNTITLED_INSERCAOATUALIZACAO_H
#define UNTITLED_INSERCAOATUALIZACAO_H
#include <stdio.h>
#include "funcoesArq.h"


void insereAtualiza(FILE* binFile,Pessoa* pessoa);
void compactaBin(FILE* binFile, int count,char* arqIndexaPessoa);
Pessoa auxilirCompacta(FILE* binFile);
void pre_insere();
void atualizaCampo();


#endif //UNTITLED_INSERCAOATUALIZACAO_H
