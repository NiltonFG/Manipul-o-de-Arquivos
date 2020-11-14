//
// Created by gavaz on 08/11/2020.
//

#ifndef UNTITLED_FUNCOESARQ_H
#define UNTITLED_FUNCOESARQ_H

#include <wchar.h>
#include <stdio.h>
#include "ListaDinEncad.h"

//arquivo funções lista.h


int leArqBin(char* arqvEntrada ,char* arqPessoa,char* arqIndexaPessoa);
void insereBinario(Pessoa* pessoa, FILE* binFile);
void setCabecalho(FILE* binFile, int quantRegistros);
void insereIndex(Lista* li, Pessoa* pessoa);


#endif //UNTITLED_FUNCOESARQ_H
