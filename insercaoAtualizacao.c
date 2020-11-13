#include "insercaoAtualizacao.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoesArq.h"
#include "fornecido.h"

void pre_insere(){

    Lista * li = cria_lista();
    Pessoa* pessoa = (Pessoa*)malloc(sizeof(Pessoa));
    int n;
    char c = '0';
    char c2 = '1';
    char arqPessoa[256];
    char arqIndexaPessoa[256];
    scanf("%s %s %d",arqPessoa, arqIndexaPessoa,&n);

    FILE* binFile = fopen(arqPessoa, "r+b");
    if(binFile == NULL){
        printf("Falha no carregamento do arquivo.");
        return;
    }

    int qntRRN;
    fseek(binFile,1,SEEK_SET);
    fread(&qntRRN,sizeof(int),1,binFile);

    fwrite(&c,sizeof(char),1,binFile);

    struct index index1;
    for(int i =0 ; i <n ; i++){
        qntRRN++;
        char aux_idade[5];
        scanf("%d", &pessoa->idPessoa);
        scan_quote_string(&pessoa->nomePessoa);
        if(scanf("%d",&pessoa->idade) != 1){
            scanf("%s", aux_idade);
            pessoa->idPessoa = -1;
        }

        int a = 0, d = 0;
        char aux_campo[] = "NULO";
        if (strcmp(pessoa->nomePessoa, aux_campo) == 0) {
            while (a < strlen(pessoa->nomePessoa) && d == 0) {
                if (pessoa->nomePessoa[a] == aux_campo[a]) {
                    d = 0;
                } else {
                    d = 1;
                }
                a++;
            }
            if (d == 0){
                pessoa->nomePessoa[0]= '\0';
            }
        }

        scan_quote_string(&pessoa->twitterPessoa);

        index1.idPessoa = pessoa->idPessoa;
        index1.RRN = qntRRN;
        insereAtualiza(binFile, pessoa);
        insere_lista_ordenada(li,index1);
    }
    char c1;
    fseek(binFile,1,SEEK_SET);
    fwrite(&qntRRN,sizeof(int),1,binFile);
    fseek(binFile,64,SEEK_SET);
    int count = 0;
    fflush(binFile);
    while (fread(&c1,sizeof(char),1,binFile)!= 0 ){
        if(c1 == '0'){
            compactaBin(binFile,count,arqIndexaPessoa);
            fclose(binFile);
            return;
        }
        fseek(binFile,63,SEEK_CUR);
        count++;
    }
    fseek(binFile,0,SEEK_SET);
    fwrite(&c1,sizeof(char),1,binFile);
    fclose(binFile);

    FILE* indexFile = fopen(arqIndexaPessoa, "r+b");
    if(indexFile == NULL){
        printf("Falha no carregamento do arquivo.");
        return;
    }
    fwrite(&c2,sizeof(char),1,indexFile);
    fseek(indexFile,7,SEEK_CUR);
    int aux_id;
    while(fread(&aux_id,sizeof(int),1,indexFile) != 0){
        fread(&index1.RRN,sizeof(int),1,indexFile);
        index1.idPessoa = aux_id;
        insere_lista_ordenada(li,index1);
    }
    salva_arq(li,indexFile);
    libera_lista(li);
    fseek(indexFile,0,SEEK_SET);
    fwrite(&c2,sizeof(char),1,indexFile);
    fclose(indexFile);
}


void insereAtualiza(FILE* binFile,Pessoa* pessoa){
    int aux =  fseek(binFile, 0, SEEK_END);
    insereBinario(pessoa ,binFile);
}

void compactaBin(FILE* binFile, int count,char* arqIndexaPessoa){
    Lista * li = cria_lista();
    Lista1* li1 = cria_lista1();

    Pessoa pessoa;
    struct index index1;
    char c2 = '0';

    FILE* indexFile = fopen(arqIndexaPessoa, "r+b");
    if(indexFile == NULL){
        printf("Falha no carregamento do arquivo.");
        return;
    }

    fwrite(&c2,sizeof(char),1,indexFile);
    fseek(indexFile,7,SEEK_CUR);
    int aux_id;
    while(fread(&aux_id,sizeof(int),1,indexFile) != 0){
        fread(&index1.RRN,sizeof(int),1,indexFile);
        index1.idPessoa = aux_id;
        insere_lista_ordenada(li,index1);
    }

    char c;
    char c1 = '1';
    long tamanho;
    int RRN = count;

    fseek(binFile,64,SEEK_SET);
    fseek(binFile,RRN*64,SEEK_CUR);
    tamanho = ftell(binFile);

    while (fread(&c,sizeof(char),1,binFile) != 0){
        if( c != '0'){
            RRN++;
            tamanho = ftell(binFile);
            pessoa = auxilirCompacta(binFile);
            remove_lista(li,pessoa.idPessoa);
            insere_lista_final(li1,pessoa);
            index1.RRN = RRN;
            index1.idPessoa = pessoa.idPessoa;
            insere_lista_ordenada(li,index1);
        }else {
            fseek(binFile, 63, SEEK_CUR);
        }
    }
    fseek(binFile,64,SEEK_SET);
    fseek(binFile,count*64,SEEK_CUR);
    pre_insere_bin(li1,binFile);
    fseek(binFile,64,SEEK_SET);
    fseek(binFile,(RRN)*64,SEEK_CUR);
    while(fread(&c,sizeof(char),1,binFile) != 0){
        fseek(binFile,-1,SEEK_CUR);
        fwrite(&c2,sizeof(char),1,binFile);
        fseek(binFile,63,SEEK_CUR);
    }
    salva_arq(li,indexFile);
    fseek(binFile,0,SEEK_SET);
    fwrite(&c1,sizeof(char),1,binFile);
    fseek(indexFile,0,SEEK_SET);
    fwrite(&c1,sizeof(char),1,indexFile);
    fclose(indexFile);
}


Pessoa auxilirCompacta(FILE* binFile){
    Pessoa* pessoa = (Pessoa*)malloc(sizeof(Pessoa));

    fread(&pessoa->idPessoa,sizeof(int),1,binFile);
    fread(&pessoa->nomePessoa,sizeof(char)*40,1,binFile);
    fread(&pessoa->idade,sizeof(int),1,binFile);
    fread(&pessoa->twitterPessoa,sizeof(char)*15,1,binFile);

    return *pessoa;
}

void atualizaCampo(){
    int n;
    char c = '0';
    char c2 = '1';
    char arqPessoa[256];
    char arqIndexaPessoa[256];
    scanf("%s %s %d",arqPessoa, arqIndexaPessoa,&n);

    FILE* binFile = fopen(arqPessoa, "r+b");
    if(binFile == NULL){
        printf("Falha no carregamento do arquivo.");
        return;
    }
}