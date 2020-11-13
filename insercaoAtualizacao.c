#include "insercaoAtualizacao.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoesArq.h"

void pre_insere(){

    Lista * li = cria_lista();
    Pessoa* pessoa = (Pessoa*)malloc(sizeof(Pessoa));
    int n;
    char c = '0';
    char arqPessoa[256];
    char arqIndexaPessoa[256];
    scanf("%s %s %d",arqPessoa, arqIndexaPessoa,&n);

    FILE* binFile = fopen(arqPessoa, "r+b");
    if(binFile == NULL){
        printf("Falha no carregamento do arquivo.");
        return;
    }

    long tamanho = ftell(binFile);

    int qntRRN;
    fseek(binFile,1,SEEK_SET);
    fread(&qntRRN,sizeof(int),1,binFile);

    tamanho = ftell(binFile);

    tamanho = ftell(binFile);
    fwrite(&c,sizeof(char),1,binFile);
    tamanho = ftell(binFile);

    struct index index1;
    for(int i =0 ; i <n ; i++){
        qntRRN++;
        scanf("%d %s %d %s", &pessoa->idPessoa, pessoa->nomePessoa, &pessoa->idade, pessoa->twitterPessoa);
        index1.idPessoa = pessoa->idPessoa;
        index1.RRN = qntRRN;
        insereAtualiza(binFile, pessoa);
        insere_lista_ordenada(li,index1);
    }
    char c1;
    fseek(binFile,1,SEEK_SET);
    fwrite(&qntRRN,sizeof(int),1,binFile);
    fseek(binFile,64,SEEK_SET);

    tamanho = ftell(binFile);
    while (fread(&c1,sizeof(char),1,binFile)!= 0 ){
        if(c1 == '0'){
            fclose(binFile);
            compactaBin(arqPessoa);
            break;
        }
        tamanho = ftell(binFile);
        fseek(binFile,63,SEEK_CUR);
    }
    fclose(binFile);

    FILE* indexFile = fopen(arqIndexaPessoa, "r+b");
    if(indexFile == NULL){
        printf("Falha no carregamento do arquivo.");
        return;
    }
    fwrite(&c,sizeof(char),1,indexFile);
    fseek(indexFile,7,SEEK_CUR);
    int aux_id;
    while(fread(&aux_id,sizeof(int),1,indexFile) != 0){
        fread(&index1.RRN,sizeof(int),1,indexFile);
        index1.idPessoa = aux_id;
        insere_lista_ordenada(li,index1);
    }
    salva_arq(li,indexFile);
    imprime_lista(li);
    libera_lista(li);
    fclose(indexFile);
}


void insereAtualiza(FILE* binFile,Pessoa* pessoa){
    int aux =  fseek(binFile, 0, SEEK_END);
    long tamanho = ftell(binFile);
    insereBinario(pessoa ,binFile);
    tamanho = ftell(binFile);
}

void compactaBin(char* arqPessoa){
    Lista1* li = cria_lista1();
    Pessoa pessoa;
    int flag = 0;
    char c;
    char c1 = '1';
    int RRN;
    int count;

    FILE* binFile = fopen(arqPessoa,"r+b");
    if(binFile == NULL){
        printf("Falha no carregamento do arquivo.");
        return;
    }

    fseek(binFile, 64, SEEK_SET);

    while(fread(&c, sizeof(char), 1, binFile) != 0){
        if(c == '0'){
            flag = 1;
            RRN = count;
        }
        if(flag = 1 && c != '0'){
            pessoa = auxilirCompacta(binFile,count);
            insere_lista_final(li,pessoa);
        }
        count++;
        fseek(binFile,64,SEEK_SET);
        fseek(binFile,count*64,SEEK_CUR);
    }
    fseek(binFile,64,SEEK_SET);
    fseek(binFile,RRN*64,SEEK_CUR);
    pre_insere_bin(li,binFile);
    fseek(binFile,0,SEEK_SET);
    fwrite(&c1,sizeof(char),1,binFile);
    fclose(binFile);
    libera_lista1(li);
}


Pessoa auxilirCompacta(FILE* binFile, int count){
    fseek(binFile,64,SEEK_SET);
    fseek(binFile,count*64,SEEK_CUR);
    Pessoa* pessoa = (Pessoa*)malloc(sizeof(Pessoa));
    char c;

    fread(&c, sizeof(char), 1, binFile);
    fread(&pessoa->idPessoa,sizeof(int),1,binFile);
    fread(&pessoa->nomePessoa,sizeof(char)*40,1,binFile);
    fread(&pessoa->idade,sizeof(int),1,binFile);
    fread(&pessoa->twitterPessoa,sizeof(char)*15,1,binFile);
    fseek(binFile, -64, SEEK_CUR);

    fwrite(&c, sizeof(char), 1, binFile);
    return *pessoa;
}