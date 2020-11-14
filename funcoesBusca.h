//
// Created by gavaz on 08/11/2020.
//
#ifndef UNTITLED_FUNCOESBUSCA_H
#define UNTITLED_FUNCOESBUSCA_H
#include "funcoesDeImpessao.h"
#include <stdbool.h>


Pessoa* pesquisa_id(FILE *binFile, FILE *indexFile, int valor);
Pessoa* pesquisa_idade(FILE *binFile, int valor,int verificao);
Pessoa* pesquisa_nome(FILE *binFile, char *conteudo,int verificao);
Pessoa* pesquisa_twitter(FILE *binFile, char *conteudo);

void buscaArquivo_int(char* arqPessoa,char* arqIndexaPessoa,char* nomeCampo,int valor);
void buscaArquivo_String(char* arqPessoa,char* nomeCampo,char* conteudo);

bool verificaCabecalhoArqDados(FILE *binFile);
bool verificaCabecalhoArqIndex(FILE *indexFile);

#endif //UNTITLED_FUNCOESBUSCA_H

