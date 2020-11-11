//
// Created by gavaz on 08/11/2020.
//
#include <stdio.h>
#include <string.h>
#include "funcoesBusca.h"
#include <stdbool.h>
#include <stdlib.h>


void buscaArquivo_String(char* arqPessoa,char* nomeCampo,char* conteudo){
    FILE *binFile = fopen(arqPessoa, "rb");
    if (binFile == NULL) {
        printf("Falha no processamento do arquivo.");
        return;
    }

    Pessoa *pessoa = (Pessoa*) malloc(sizeof(Pessoa));

    if (verificaCabecalhoArqDados(binFile) == false) {
        return;
    } else {
        int c, a;
        c = a = 0;
        char aux_campo1[] = "nomePessoa";
        if (strcmp(nomeCampo, aux_campo1) == 0) {
            while (a < 11 && c == 0) {
                if (nomeCampo[a] == aux_campo1[a]) {
                    c = 0;
                } else {
                    c = 1;
                }
                a++;
            }
            if (c == 0) {
                bool flag = false;
                fseek(binFile, 64, SEEK_SET);
                int verifica = 0;
                while (fread(&verifica, sizeof(char), 1, binFile) != 0) {
                    fseek(binFile, -1, SEEK_CUR);
                    pessoa = pesquisa_nome(binFile, conteudo, 1);
                    if (pessoa->idade == -2) {
                        if (flag == false)
                            printf("Registro inexistente.");
                        fclose(binFile);
                        return;
                    } else
                        printPessoa(*pessoa);
                    flag = true;
                }
                fclose(binFile);
                return;
            }
        }

        a = c = 0;
        char aux_campo[] = "twitterPessoa";
        if (strcmp(nomeCampo, aux_campo) == 0) {
            while (a < 14 && c == 0) {
                if (nomeCampo[a] == aux_campo[a]) {
                    c = 0;
                } else {
                    c = 1;
                }
                a++;
            }
            if (c == 0) {
                pessoa = pesquisa_twitter(binFile, conteudo);
            }
            if(pessoa->idade == -2){
                printf("Registro inexistente.");
            }
            else printPessoa(*pessoa);
        }
    fclose(binFile);
    }
}


void buscaArquivo_int(char* arqPessoa,char* arqIndexaPessoa,char* nomeCampo,int valor) {

    FILE *binFile = fopen(arqPessoa, "rb");
    if (binFile == NULL) {
        printf("Falha no processamento do arquivo.");
        return;
    }

    FILE *indexFile = fopen(arqIndexaPessoa, "rb");
    if (indexFile == NULL) {
        printf("Falha no processamento do arquivo.");
        return;
    }

    char verifCabecArq;
    Pessoa *pessoa = (Pessoa*) malloc(sizeof(Pessoa));

    if (verificaCabecalhoArqDados(binFile) == false) {
        return;
    } else {
        int a = 0, c = 0;
        char aux_campo[] = "idPessoa";
        if (strcmp(nomeCampo, aux_campo) == 0) {
            while (a < 9 && c == 0) {
                if (nomeCampo[a] == aux_campo[a]) {
                    c = 0;
                } else {
                    c = 1;
                }
                a++;
            }
            if (c == 0) {
                if (verificaCabecalhoArqIndex(indexFile) == false)
                    return;
                pessoa = pesquisa_id(binFile, indexFile, valor);
            }
        }
        c = a = 0;
        char aux_campo1[] = "idadePessoa";
        if (strcmp(nomeCampo, aux_campo1) == 0) {
            while (a < 12 && c == 0) {
                if (nomeCampo[a] == aux_campo1[a]) {
                    c = 0;
                } else {
                    c = 1;
                }
                a++;
            }
            if (c == 0) {
                bool flag = false;
                fseek(binFile,64,SEEK_SET);
                int verifica = 0;
                while(fread(&verifica,sizeof(char),1,binFile) != 0){
                    fseek(binFile,-1,SEEK_CUR);
                    pessoa = pesquisa_idade(binFile, valor,1);
                    if(pessoa->idade == -2 ){
                        if(flag == false)
                            printf("Registro inexistente.");
                        return;
                    }else
                        printPessoa(*pessoa);
                        flag = true;
                }
                return;
            }
        }

        if (pessoa == NULL){
            printf("Registro inexistente.");
            free(pessoa);
            fclose(indexFile);
            fclose(binFile);
            return;
        }
        else
            printPessoa(*pessoa);
            free(pessoa);
            fclose(indexFile);
            fclose(binFile);
    }
}

Pessoa* pesquisa_id(FILE *binFile, FILE *indexFile, int valor) {

    Pessoa *pessoa = (Pessoa *) malloc(sizeof(Pessoa));
    fseek(indexFile, 8, SEEK_SET);
    fseek(binFile, 64, SEEK_SET);

    int id_aux;
    int RRN = -1;
    int flag = 0;

    while (!feof(indexFile)) {

        fread(&id_aux, sizeof(int), 1, indexFile);
        if (id_aux == valor) {
            fread(&RRN, sizeof(int), 1, indexFile);
            flag = 1;
            break;
        }else{
            fseek(indexFile,4,SEEK_CUR);

        }
    }
    if (flag == 0) {
        free(pessoa);
        return NULL;
    }else{
        char  aux;
        fseek(binFile, 64*RRN, SEEK_CUR);
        fread(&aux,sizeof(char),1,binFile);

        if(aux == '0'){
            free(pessoa);
            return NULL;
        }

        fread(&pessoa->idPessoa, sizeof(int), 1, binFile);

        fread(&pessoa->nomePessoa, sizeof(char) * 40, 1, binFile);

        fread(&pessoa->idade, sizeof(int), 1, binFile);

        fread(&pessoa->twitterPessoa, sizeof(char) * 15, 1, binFile);

        return pessoa;
    }
}


Pessoa *pesquisa_idade(FILE *binFile, int valor,int verificao) {
    if(verificao == 0)
        fseek(binFile, 64, SEEK_SET);
    Pessoa *pessoa = (Pessoa *) malloc(sizeof(Pessoa));

    int flag = 0;
    char verifica;
    int idade_aux;

    while (fread(&verifica, sizeof(char), 1, binFile) != 0) {
        if (verifica == '1') {
            fseek(binFile, 44, SEEK_CUR);
            fread(&idade_aux, sizeof(int), 1, binFile);
            if (idade_aux == valor){
                flag = 1;
                fseek(binFile, -48, SEEK_CUR);
                fread(&pessoa->idPessoa, sizeof(int), 1, binFile);
                fread(&pessoa->nomePessoa, sizeof(char) * 40, 1, binFile);
                fread(&pessoa->idade, sizeof(int), 1, binFile);
                fread(&pessoa->twitterPessoa, sizeof(char) * 15, 1, binFile);
                return pessoa;
            }
        }
        fseek(binFile, 15, SEEK_CUR);
    }
    if (flag == 0) {
        pessoa->idade = -2;
        return pessoa;
    }

}

Pessoa* pesquisa_nome(FILE *binFile, char *conteudo,int verificao) {
    if (verificao == 0)
        fseek(binFile, 64, SEEK_SET);

    Pessoa *pessoa = (Pessoa *) malloc(sizeof(Pessoa));

    int flag = 0;
    char verifica;
    char nome_aux[60];

    while (fread(&verifica, sizeof(char), 1, binFile) != 0) {
        if (verifica == '1') {
            fseek(binFile, 4, SEEK_CUR);
            fread(nome_aux, sizeof(char) * 40, 1, binFile);

            int c, a;
            c = 0;
            a = 0;
            while (a < strlen(conteudo) && c == 0) {
                if (nome_aux[a] == conteudo[a]) {
                    c = 0;
                } else {
                    c = 1;
                }
                a++;
            }
            if (c == 0) {
                fseek(binFile, -44, SEEK_CUR);
                fread(&pessoa->idPessoa, sizeof(int), 1, binFile);
                fread(&pessoa->nomePessoa, sizeof(char) * 40, 1, binFile);
                fread(&pessoa->idade, sizeof(int), 1, binFile);
                fread(&pessoa->twitterPessoa, sizeof(char) * 15, 1, binFile);
                return pessoa;
            }
            fseek(binFile, 19, SEEK_CUR);
        }
    }
        if (flag == 0) {
            pessoa->idade = -2;
            return pessoa;
        }
}


Pessoa* pesquisa_twitter(FILE *binFile, char *conteudo){
    fseek(binFile, 64, SEEK_SET);
    Pessoa* pessoa = (Pessoa *) malloc(sizeof(Pessoa));

    int flag = 0;
    char verifica;
    char nome_aux[60];

    while (fread(&verifica, sizeof(char), 1, binFile) != 0) {
        if (verifica == '1') {
            fseek(binFile, 48, SEEK_CUR);
            fread(nome_aux, sizeof(char) * 15, 1, binFile);
            int c, a;
            c = 0;
            a = 0;
            if (strcmp(nome_aux, conteudo) == 0) {
                while (a < strlen(conteudo) && c == 0) {
                    if (nome_aux[a] == conteudo[a]) {
                        c = 0;
                    } else {
                        c = 1;
                    }
                    a++;
                }
                if (c == 0) {
                    flag = 1;
                    fseek(binFile, -63, SEEK_CUR);
                    fread(&pessoa->idPessoa, sizeof(int), 1, binFile);
                    fread(&pessoa->nomePessoa, sizeof(char) * 40, 1, binFile);
                    fread(&pessoa->idade, sizeof(int), 1, binFile);
                    fread(&pessoa->twitterPessoa, sizeof(char) * 15, 1, binFile);
                    return pessoa;
                }
            }
        }
    }
    if (flag == 0) {
        pessoa->idade = -2;
        return pessoa;
    }
}

bool verificaCabecalhoArqDados(FILE *binFile) {
    char verifCabecArq;
    fseek(binFile,0,SEEK_SET);
    if (fread(&verifCabecArq, sizeof(char), 1, binFile) == '0') {
        printf("Falha no processamento do arquivo.");
        return false;
    } else {
        fseek(binFile, -1, SEEK_CUR);
        return true;
    }
}

bool verificaCabecalhoArqIndex(FILE *indexFile) {
    char verifCabecArq;
    fseek(indexFile,0,SEEK_SET);
    if (fread(&verifCabecArq, sizeof(char), 1, indexFile) == '0') {
        printf("Falha no processamento do arquivo.");
        return false;
    } else {
        fseek(indexFile, -1, SEEK_CUR);
        return true;
    }
}