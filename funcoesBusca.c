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
        fclose(binFile);
        return;
    }
    if (verificaCabecalhoArqDados(binFile) == false) {
        return;
    } else {
        Pessoa pessoa;
        fseek(binFile, 64, SEEK_SET);
        if (strcmp(nomeCampo, "nomePessoa")){
         //   pessoa = pesquisa_nome(binFile,nomeCampo);
        }
        if (strcmp(nomeCampo, "twitterPessoa")){
           // pessoa = pesquisa_twitter(binFile,nomeCampo);
        }
        if(pessoa.idPessoa == -1)
            return;
        printPessoa(pessoa);
    }
}

void buscaArquivo_int(char* arqPessoa,char* arqIndexaPessoa,char* nomeCampo,int valor) {

    FILE *binFile = fopen(arqPessoa, "rb");
    if (binFile == NULL) {
        printf("Falha no processamento do arquivo.");
        fclose(binFile);
        return;
    }

    FILE *indexFile = fopen(arqIndexaPessoa, "rb");
    if (binFile == NULL) {
        printf("Falha no processamento do arquivo.");
        fclose(binFile);
        return;
    }
    char verifCabecArq;
    Pessoa *pessoa = (Pessoa *) malloc(sizeof(Pessoa));

    if (verificaCabecalhoArqDados(binFile) == false) {
        return;
    } else {
        fseek(binFile, 64, SEEK_SET);
        int a = 0, c = 0;
        char aux_campo[] = "idPessoa";
        if (strcmp(nomeCampo, aux_campo) == 0) {
            while (a != strlen(nomeCampo) || c == 0) {
                if (nomeCampo[a] == aux_campo[a]) {
                    c = 0;
                } else {
                    c = 1;
                }
                a++;
            }
            if (c == 0) {
                //   if (verificaCabecalhoArqIndex(indexFile) == false) {
                return;
                //  }
                //pessoa = pesquisa_id(binFile, indexFile, valor);
            }
            c = a = 0;
            char aux_campo1[] = "idadePessoa";
            if (strcmp(nomeCampo, aux_campo1) == 0) {
                while (a != strlen(nomeCampo) || c == 0) {
                    if (nomeCampo[a] == aux_campo[a]) {
                        c = 0;
                    } else {
                        c = 1;
                    }
                    a++;
                }
                if (c == 0) {
                    //    *pessoa = pesquisa_idade(binFile, valor);
                }
                if (pessoa->idPessoa == NULL)
                    return;
                printPessoa(*pessoa);
            }
        }
    }
}

Pessoa pesquisa_id(FILE *binFile, FILE *indexFile, int valor) {
    Pessoa *pessoa = (Pessoa *) malloc(sizeof(Pessoa));
    fseek(indexFile, 8, SEEK_SET);
    int id_aux;
    int RRN = -1;
    int flag = 0;
    while (fread(&id_aux, sizeof(int), 1, indexFile) != EOF) {
        if (id_aux == valor) {
            fread(&RRN, sizeof(int), 1, indexFile);
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        printf("Registro inexistente.");
        pessoa.idPessoa = -1;
        return pessoa;
    }
    char verifica;
    fseek(binFile, RRN * 64, SEEK_SET);
    fread(&verifica, sizeof(char), 1, binFile);
    if (verifica == '0') {
        printf("Registro inexistente.");
        return pessoa;
    } else {
        fread(&pessoa->idPessoa, sizeof(int), 1, binFile);
        fread(&pessoa->nomePessoa, sizeof(char) * 40, 1, binFile);
        fread(&pessoa->idade, sizeof(int), 1, binFile);
        fread(&pessoa->twitterPessoa, sizeof(char) * 15, 1, binFile);
        return pessoa;
    }
}

/*
        Pessoa *pesquisa_idade(FILE *binFile, int valor) {
            Pessoa *pessoa = (Pessoa *) malloc(sizeof(Pessoa));
            int flag = 0;
            int count = 0;
            char verifica;
            int idade_aux;
            while (fread(&verifica, sizeof(char), 1, binFile) != EOF) {
                count++;
                if (verifica == '1') {
                    fseek(binFile, 44, SEEK_CUR);
                    fread(&idade_aux, sizeof(int), 1, binFile);
                    if (idade_aux == valor) {
                        flag = 1;
                        fseek(binFile, -48, SEEK_CUR);
                        fread(&pessoa->idPessoa, sizeof(int), 1, binFile);
                        fread(&pessoa->nomePessoa, sizeof(char) * 40, 1, binFile);
                        fread(&pessoa->idade, sizeof(int), 1, binFile);
                        fread(&pessoa->twitterPessoa, sizeof(char) * 15, 1, binFile);
                        return pessoa;
                    }
                }
                fseek(binFile, 64, SEEK_SET);
                fseek(binFile, count * 64, SEEK_CUR);
            }
            if (flag == 0) {
                printf("Registro inexistente.");
                pessoa = NULL;
                return pessoa;
            }
        }

        Pessoa pesquisa_nome(FILE *binFile, char *conteudo) {
            Pessoa pessoa;
            int flag = 0;
            int count = 0;
            char verifica;
            char nome_aux[256];
            while (fread(&verifica, sizeof(char), 1, binFile) != EOF) {
                count++;
                if (verifica == '1') {
                    fseek(binFile, 4, SEEK_CUR);
                    fread(nome_aux, sizeof(char) * 40, 1, binFile);
                    if (strcmp(nome_aux, conteudo)) {
                        flag = 1;
                        fseek(binFile, -44, SEEK_CUR);
                        fread(&pessoa.idPessoa, sizeof(int), 1, binFile);
                        fread(&pessoa.nomePessoa, sizeof(char) * 40, 1, binFile);
                        fread(&pessoa.idade, sizeof(int), 1, binFile);
                        fread(&pessoa.twitterPessoa, sizeof(char) * 15, 1, binFile);
                        return pessoa;
                    }
                }
                fseek(binFile, 64, SEEK_SET);
                fseek(binFile, count * 64, SEEK_CUR);
            }
            if (flag == 0) {
                printf("Registro inexistente.");
                pessoa.idPessoa = -1;
                return pessoa;
            }
        }

        Pessoa pesquisa_twitter(FILE *binFile, char *conteudo) {
            Pessoa pessoa;
            int flag = 0;
            int count = 0;
            char verifica;
            char twitter_aux[256];
            while (fread(&verifica, sizeof(char), 1, binFile) != EOF) {
                count++;
                if (verifica == '1') {
                    fseek(binFile, 48, SEEK_CUR);
                    fread(twitter_aux, sizeof(char) * 15, 1, binFile);
                    if (strcmp(twitter_aux, conteudo)) {
                        flag = 1;
                        fseek(binFile, -63, SEEK_CUR);
                        fread(&pessoa.idPessoa, sizeof(int), 1, binFile);
                        fread(&pessoa.nomePessoa, sizeof(char) * 40, 1, binFile);
                        fread(&pessoa.idade, sizeof(int), 1, binFile);
                        fread(&pessoa.twitterPessoa, sizeof(char) * 15, 1, binFile);
                        return pessoa;
                    }
                }
                fseek(binFile, 64, SEEK_SET);
                fseek(binFile, count * 64, SEEK_CUR);
            }
            if (flag == 0) {
                printf("Registro inexistente.");
                pessoa.idPessoa = -1;
                return pessoa;
            }
        }
*/
bool verificaCabecalhoArqDados(FILE *binFile) {
    char verifCabecArq;
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
    if (fread(&verifCabecArq, sizeof(char), 1, indexFile) == '0') {
        printf("Falha no processamento do arquivo.");
        return false;
    } else {
        fseek(indexFile, -1, SEEK_CUR);
        return true;
    }
}