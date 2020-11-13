//
// Created by gavaz on 09/11/2020.
//
#ifndef UNTITLED_INSERCAOATUALIZACAO_H
#define UNTITLED_INSERCAOATUALIZACAO_H
#include <stdio.h>
#include "funcoesArq.h"


void insereAtualiza(FILE* binFile,Pessoa* pessoa);
void compactaBin(char* arqPessoa);
Pessoa auxilirCompacta(FILE* binFile, int count);
void pre_insere();



#endif //UNTITLED_INSERCAOATUALIZACAO_H
