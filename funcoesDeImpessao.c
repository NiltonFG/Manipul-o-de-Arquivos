//
// Created by gavaz on 09/11/2020.
//

#include "funcoesDeImpessao.h"
#include <stdlib.h>
#include <stdio.h>


void imprimeArqBin(char *arqPessoa){

    FILE* binFile = fopen(arqPessoa, "rb");
    if (binFile == NULL) {
        printf("Falha no processamento do arquivo.");
        fclose(binFile);
        return;
    }

    Pessoa pessoa;
    int quantRegistros;
    char auxVerifIntegridade;
    char auxVerifReg;
    long tamanho;

    auxVerifIntegridade = fread(&auxVerifIntegridade, sizeof(char), 1, binFile);
    tamanho = ftell(binFile);

    if (auxVerifIntegridade == '0') {
        return;
    } else {
        quantRegistros = fread(&quantRegistros, sizeof(int), 1, binFile);
        tamanho = ftell(binFile);

        fseek(binFile, 0, SEEK_SET);
        tamanho = ftell(binFile);

        fseek(binFile, 64, SEEK_SET);
        tamanho = ftell(binFile);

        int count = 0;
        while(fread(&auxVerifReg, sizeof(char), 1, binFile)!= EOF) {
            tamanho = ftell(binFile);
            count++;
            if(auxVerifReg == 0) {
                printf("Registro inexistente.");
                tamanho = ftell(binFile);
                fseek(binFile,64,SEEK_SET);
                tamanho = ftell(binFile);
                fseek(binFile,count*64,SEEK_CUR);
                tamanho = ftell(binFile);
            }
            tamanho = ftell(binFile);
            fread(&pessoa.idPessoa, sizeof(int), 1, binFile);
            tamanho = ftell(binFile);
            fread(&pessoa.nomePessoa, sizeof(char), 40, binFile);
            tamanho = ftell(binFile);
            fread(&pessoa.idade, sizeof(int), 1, binFile);
            tamanho = ftell(binFile);
            fread(&pessoa.twitterPessoa, sizeof(char), 15, binFile);
            tamanho = ftell(binFile);
            printPessoa(pessoa);
        }
    }
    fclose(binFile);
}

void printPessoa(Pessoa pessoa){
    printf("Dados da pessoa de código %d\n",pessoa.idPessoa);
    if(pessoa.nomePessoa[0] == '\0'){
        printf("Nome: -\n");
    }else {
        printf("Nome: %s\n", pessoa.nomePessoa);
    }
    if(pessoa.idade == -1){
        printf("Idade: - anos\n");
    }else {
        printf("Idade: %d anos\n", pessoa.idade);
    }
    printf("Twitter: %s\n",pessoa.twitterPessoa);
    printf("\n");
}