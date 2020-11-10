//
// Created by gavaz on 08/11/2020.
//
#include "funcoesArq.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void leArqBin(char* arqvEntrada ,char* arqPessoa,char* arqIndexaPessoa){
    Lista* li = cria_lista();
    Pessoa* pessoa = (Pessoa*)malloc(sizeof(Pessoa));

    char c = '0';
    char c2 = '$';

    FILE* binFile = fopen(arqPessoa, "wb");
    if(binFile == NULL){
        printf("Falha no carregamento do arquivo.");
        fclose(binFile);
        return;
    }
    fwrite(&c, sizeof(char), 1, binFile);
    for(int i = 0; i < 63; i++) {
        fwrite(&c2, sizeof(char), 1, binFile);
    }

    FILE *csvFile = fopen(arqvEntrada, "r");
    if(csvFile == NULL){
        printf("Falha no carregamento do arquivo.");
        fclose(csvFile);
        return;
    }

    FILE* indexFile = fopen(arqIndexaPessoa,"wb");
    if(indexFile == NULL){
        printf("Falha no carregamento do arquivo.");
        fclose(binFile);
        return;
    }

    char cabec[256];
    fseek(csvFile, 0, SEEK_SET);
    fgets(cabec,256,csvFile);

    int quantRegistros = 0; //indica a quantidade de registros para o cabeçalho

    while(fscanf(csvFile, "%d%*c", &(pessoa->idPessoa)) != EOF){

        pessoa->RRN = quantRegistros;
        fscanf(csvFile, "%50[^,]", pessoa->nomePessoa);
        fscanf(csvFile, "%*c%d[^,]", &(pessoa->idade) );
        fscanf(csvFile, "%*c%s", pessoa->twitterPessoa);
        pessoa->nomePessoa[39] = '\0';
        pessoa->twitterPessoa[14] = '\0';

        insereBinario(pessoa, binFile);
        insereIndex(li,pessoa);

        quantRegistros++;
        fflush(csvFile);
        pessoa = (Pessoa*)malloc(sizeof(Pessoa));
    }

    char c3 = '1';
    setCabecalho(binFile, quantRegistros);
    fclose(binFile);
    fclose(csvFile);
    salva_arq(li,indexFile);
    fseek(indexFile,0,SEEK_SET);
    fwrite(&c3,sizeof(char),1,indexFile);
    fclose(indexFile);
    libera_lista(li);
    free(pessoa);
    return;
}

void insereIndex(Lista* li, Pessoa* pessoa){
    struct index index1;
    index1.idPessoa = pessoa->idPessoa;
    index1.RRN = pessoa->RRN;
    insere_lista_ordenada(li,index1);
}

void insereBinario(Pessoa* pessoa, FILE* binFile){
    char c = '1';
    char c2 = '$';
    char c3 = '\0';

    long tamanho = ftell(binFile);

    fwrite(&c, sizeof(char), 1, binFile);
    tamanho = ftell(binFile);

    fwrite(&(pessoa->idPessoa), sizeof(int), 1, binFile);
    tamanho = ftell(binFile);

    int y = strlen(pessoa->nomePessoa);
    printf("%s\n",pessoa->twitterPessoa);
    if(strlen(pessoa->nomePessoa) == 0){
        fwrite(&c3, sizeof(char), 1, binFile);
        tamanho = ftell(binFile);
        for(int i = 0; i < 39 ; i++) {
            fwrite(&c2, sizeof(char), 1, binFile);
        }
    }else {
        fwrite(&(pessoa->nomePessoa), 40 * sizeof(char), 1, binFile);
        fseek(binFile,-(40-strlen(pessoa->nomePessoa)-1),SEEK_CUR);
        tamanho = ftell(binFile);
        for(int i = 0; i < (39 - strlen(pessoa->nomePessoa)); i++) {
            fwrite(&c2, sizeof(char), 1, binFile);
        }
    }
    tamanho = ftell(binFile);

    fwrite(pessoa->idade, sizeof(int), 1, binFile);
    tamanho = ftell(binFile);

    fwrite(pessoa->twitterPessoa, 15*sizeof(char), 1, binFile);
    tamanho = ftell(binFile);
    fseek(binFile,-(15-strlen(pessoa->twitterPessoa)-1),SEEK_CUR);
    tamanho = ftell(binFile);

    for(int i = 0; i < (14-strlen(pessoa->twitterPessoa)); i++) {
        fwrite(&c2, sizeof(char), 1, binFile);
    }
    tamanho = ftell(binFile);
}


void setCabecalho(FILE* binFile, int quantRegistros){
    char c = '1';
    char c2 = '$';
    fseek(binFile,0,SEEK_SET);
    fwrite(&c, sizeof(char), 1, binFile);
    fwrite(&quantRegistros, sizeof(int), 1, binFile);
    for(int i =0 ; i < 59; i++) {
        fwrite(&c2, sizeof(char), 1, binFile);
    }
}