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
        return;
    }

    Pessoa pessoa;
    int quantRegistros;
    char auxVerifIntegridade;
    char auxVerifReg;

    auxVerifIntegridade = fread(&auxVerifIntegridade, sizeof(char), 1, binFile);

    if (auxVerifIntegridade == '0') {
        return;
    } else {
        fread(&quantRegistros, sizeof(int), 1, binFile);

        fseek(binFile, 0, SEEK_SET);

        fseek(binFile, 64, SEEK_SET);

        int count = 0;
        while(count < quantRegistros) {

            count++;
            fread(&auxVerifReg, sizeof(char), 1, binFile);
            if(auxVerifReg == '0') {
                printf("Registro inexistente.");

                fseek(binFile,64,SEEK_SET);

                fseek(binFile,count*64,SEEK_CUR);

            }else {

                fread(&pessoa.idPessoa, sizeof(int), 1, binFile);

                fread(&pessoa.nomePessoa, sizeof(char), 40, binFile);

                fread(&pessoa.idade, sizeof(int), 1, binFile);

                fread(&pessoa.twitterPessoa, sizeof(char), 15, binFile);

                printPessoa(pessoa);
            }
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