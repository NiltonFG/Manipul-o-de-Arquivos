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

    fseek(binFile,0,SEEK_SET);
    fread(&auxVerifIntegridade, sizeof(char), 1, binFile);

    if (auxVerifIntegridade == '0') {
        printf("Falha no processamento do arquivo.");
        return;
    } else {
        fread(&quantRegistros, sizeof(int), 1, binFile);

        fseek(binFile, 64, SEEK_SET);
        int flag2 = 0;
        int count = 0;
        long tamanho = ftell(binFile);
        while(fread(&auxVerifReg, sizeof(char), 1, binFile) != 0) {
            if(auxVerifReg == '0') {
                if( flag2 == 0 && count != 0){
                    printf("Registro inexistente.");
                    return;
                }
                count++;
                fseek(binFile,64,SEEK_SET);
                fseek(binFile,64*count,SEEK_CUR);

            }else {

                fread(&pessoa.idPessoa, sizeof(int), 1, binFile);

                fread(&pessoa.nomePessoa, sizeof(char), 40, binFile);

                fread(&pessoa.idade, sizeof(int), 1, binFile);

                fread(&pessoa.twitterPessoa, sizeof(char), 15, binFile);

                printPessoa(pessoa);
                count++;
                flag2++;
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
        printf("Idade: -\n");
    }else {
        printf("Idade: %d anos\n", pessoa.idade);
    }
    printf("Twitter: %s\n",pessoa.twitterPessoa);
    printf("\n");
}