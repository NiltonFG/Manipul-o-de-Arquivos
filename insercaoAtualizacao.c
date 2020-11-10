//
// Created by gavaz on 09/11/2020.
//

#include "insercaoAtualizacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesArq.h"

void pre_insere(){
    Pessoa* pessoa;
    int n;
    char c = '0';
    char c1 = '1';
    char arqPessoa[256];
    char arqIndexaPessoa[256];
    scanf("%s %s %d",arqPessoa, arqIndexaPessoa,&n);
    FILE* binFile = fopen(arqPessoa, "wb+");
    fwrite(&c,sizeof(char),1,binFile);
    if(binFile == NULL){
        printf("Falha no carregamento do arquivo.");
        fclose(binFile);
        return;
    }
    for(int i =0 ; i <n ; i++){
        scanf("%d %s %d %s",&pessoa->idPessoa,pessoa->nomePessoa,&pessoa->idade,pessoa->twitterPessoa);
        insereAtualiza(binFile,pessoa);
    }
    fseek(binFile,0,SEEK_SET);
    fwrite(&c1,sizeof(char),1,binFile);
    fclose(binFile);
}


void insereAtualiza(FILE* binFile,Pessoa* pessoa){
    fseek(binFile, 0, SEEK_END);
    insereBinario(pessoa ,binFile);
    fseek(binFile, 0, SEEK_SET);
    compactaBin(binFile);
}

void compactaBin(FILE *binFile){
    fseek(binFile, 64, SEEK_SET);
    Pessoa* pessoa;
    char c;
    int count;
    while(fread(&c, sizeof(char), 1, binFile)){
        if(c ==  '0'){
            pessoa = auxilirCompacta(binFile, count);
            if(pessoa != NULL){
                fseek(binFile,64,SEEK_SET);
                fseek(binFile,count*64,SEEK_CUR);
                insereBinario(pessoa, binFile);
            }else{
                return;
            }
        }
        count++;
        fseek(binFile,64,SEEK_SET);
        fseek(binFile,count*64,SEEK_CUR);
    }
}

Pessoa* auxilirCompacta(FILE *binFile, int count){
    fseek(binFile,64,SEEK_SET);
    fseek(binFile,count*64,SEEK_CUR);
    Pessoa* pessoa;
    char c;
    while(fread(&c, sizeof(char), 1, binFile) != EOF){
        if(c == '1'){
            char c = '0';
            fread(&pessoa->idPessoa,sizeof(int),1,binFile);
            fread(&pessoa->nomePessoa,sizeof(char)*40,1,binFile);
            fread(&pessoa->idade,sizeof(int),1,binFile);
            fread(&pessoa->twitterPessoa,sizeof(char)*15,1,binFile);
            fseek(binFile, -64, SEEK_CUR);
            fwrite(&c, sizeof(char), 1, binFile);
            return pessoa;
        }
    }
    pessoa = NULL;
    return pessoa;
}
