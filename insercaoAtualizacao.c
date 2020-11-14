#include "insercaoAtualizacao.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoesArq.h"
#include "fornecido.h"
#include "funcoesBusca.h"

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
        printf("Falha no processamento do arquivo.");
        return;
    }

    int qntRRN ;
    fseek(binFile,1,SEEK_SET);
    fread(&qntRRN,sizeof(int),1,binFile);
    fseek(binFile,0,SEEK_SET);
    fwrite(&c,sizeof(char),1,binFile);
    qntRRN;

    for(int i =0 ; i <n ; i++){
        qntRRN++;
        char aux_idade[5];
        scanf("%d", &pessoa->idPessoa);
        scan_quote_string(pessoa->nomePessoa);
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

        scan_quote_string(pessoa->twitterPessoa);
        pessoa->nomePessoa[39] = '\0';
        pessoa->twitterPessoa[14] = '\0';
        insereAtualiza(binFile, pessoa);
    }

    char c1;

    fseek(binFile,1,SEEK_SET);
    fwrite(&qntRRN,sizeof(int),1,binFile);
    fseek(binFile,64,SEEK_SET);

    int count = 0;
    fflush(binFile);
    while (fread(&c1,sizeof(char),1,binFile)!= 0 ){
        if(c1 == '0'){
           compactaBin(binFile,count);
            fclose(binFile);
            return;
        }
        fseek(binFile,63,SEEK_CUR);
        count++;
    }
    fseek(binFile,0,SEEK_SET);
    fwrite(&c1,sizeof(char),1,binFile);


    FILE* indexFile = fopen(arqIndexaPessoa, "r+b");
    if(indexFile == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    struct index index1;
    fseek(indexFile,7,SEEK_CUR);
    int aux_id;
    int RRN = 0;
    fseek(binFile,64,SEEK_SET);
    while (fread(&c,sizeof(char),1,binFile) != 0 && c!= '0'){
        fread(&aux_id,sizeof(int),1,binFile);
        fseek(binFile,59,SEEK_CUR);
        index1.idPessoa = aux_id;
        index1.RRN = RRN;
        insere_lista_ordenada(li,index1);
        RRN++;
    }

    salva_arq(li,indexFile);
    libera_lista(li);
    fseek(indexFile,0,SEEK_SET);
    fwrite(&c2,sizeof(char),1,indexFile);
    fclose(indexFile);

    fclose(binFile);
    binarioNaTela1(arqPessoa,arqIndexaPessoa);
}


void insereAtualiza(FILE* binFile,Pessoa* pessoa){
    int aux =  fseek(binFile, 0, SEEK_END);
    insereBinario(pessoa ,binFile);
}

void compactaBin(FILE* binFile, int count){
    Lista1* li1 = cria_lista1();

    Pessoa pessoa;

    char c2 = '0';

    char c;
    char c1 = '1';
    int RRN;

    fseek(binFile,64,SEEK_SET);
    fseek(binFile,RRN*64,SEEK_CUR);

    while (fread(&c,sizeof(char),1,binFile) != 0){
        if( c != '0'){
            pessoa = auxilirCompacta(binFile);
            insere_lista_final(li1,pessoa);
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

    fseek(binFile,0,SEEK_SET);
    fwrite(&c1,sizeof(char),1,binFile);
}


Pessoa auxilirCompacta(FILE* binFile){
    Pessoa* pessoa = (Pessoa*)malloc(sizeof(Pessoa));
    fread(&pessoa->idPessoa,sizeof(int),1,binFile);
    fread(&pessoa->nomePessoa,sizeof(char)*40,1,binFile);
    fread(&pessoa->idade,sizeof(int),1,binFile);
    fread(&pessoa->twitterPessoa,sizeof(char)*15,1,binFile);

    return *pessoa;
}

void pre_atualizaCampo(){
    Lista* li = cria_lista();
    Pessoa* pessoa;
    int n;
    char c = '0';
    char c2 = '1';
    char arqPessoa[256];
    char arqIndexaPessoa[256];
    nomeCampo nomeCampos;
    char charAux;
    int id_aux;
    int RRN;

    scanf("%s %s %d",arqPessoa, arqIndexaPessoa,&n);

    FILE* binFile = fopen(arqPessoa, "r+b");
    if(binFile == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    FILE* indexFile = fopen(arqIndexaPessoa, "r+b");
    if(indexFile == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    fwrite(&c,sizeof(char),1,binFile);
    fwrite(&c,sizeof(char),1,indexFile);

    char buffer[100];
    int numMudancas;
    Pessoa* pessoaAux;
    int flag[4];

    struct index index1;
    fseek(indexFile,8,SEEK_SET);
    while(fread(&index1.idPessoa,sizeof(int),1,indexFile)){
        fread(&index1.RRN,sizeof(int),1,indexFile);
        insere_lista_ordenada(li,index1);
    }

    for(int i = 0; i < n ; i++) {

        pessoa = (Pessoa*)malloc(sizeof(Pessoa));
        scanf("%s", nomeCampos.nomeCampoBusca);
        int aux_selecao = comparaCampo(nomeCampos.nomeCampoBusca);

        switch (aux_selecao) {
            case 0:
                return;
            case 1:
                fseek(binFile,64,SEEK_SET);
                scanf("%d",&pessoa->idPessoa);
                pessoa = pesquisa_id(binFile,indexFile,pessoa->idPessoa);
                if(pessoa == NULL){
                    fgets(buffer,100,stdin);
                    break;
                }
                scanf("%d",&numMudancas);
                for (int j = 0; j < numMudancas ; ++j) {
                    scanf("%s",nomeCampos.nomeCampo1);
                    aux_selecao = comparaCampo(nomeCampos.nomeCampo1);
                    int id_aux3;
                    switch (aux_selecao) {
                        case 1:
                            scanf("%d",&id_aux3);
                            remove_lista(li, pessoa->idPessoa);
                            pessoa->idPessoa = id_aux3;
                            index1.idPessoa = pessoa->idPessoa;
                            index1.RRN = pessoa->RRN;
                            insere_lista_ordenada(li,index1);
                            break;
                        case 2:
                            scan_quote_string(pessoa->nomePessoa);
                            pessoa->nomePessoa[39] = '\0';
                            verfica_nulo(pessoa);
                            break;
                        case 3:
                            scanf("%d",&pessoa->idade);
                            break;
                        case 4:
                            scan_quote_string(pessoa->twitterPessoa);
                            pessoa->twitterPessoa[14] ='\0';
                            break;
                    }
                }
                fseek(binFile,64,SEEK_SET);
                fseek(binFile,64 * pessoa->RRN,SEEK_CUR);
                insereBinario(pessoa,binFile);
                break;


            case 2:
                for (int t = 0;t <4;t++){
                    flag[t] = 0;
                }
                char nome_aux[60];
                pessoaAux = (Pessoa*)malloc(sizeof(Pessoa));
                fseek(binFile,64,SEEK_SET);
                scanf("%s",pessoa->nomePessoa);
                verfica_nulo(pessoa);
                strcpy(nome_aux,pessoa->nomePessoa);

                scanf("%d",&numMudancas);
                for (int j = 0; j < numMudancas ; ++j) {
                    scanf("%s",nomeCampos.nomeCampo1);
                    aux_selecao = comparaCampo(nomeCampos.nomeCampo1);
                    switch (aux_selecao) {
                        case 1:
                            scanf("%d",&pessoaAux->idPessoa);
                            flag[0] =1;
                            break;
                        case 2:
                            scan_quote_string(pessoaAux->nomePessoa);
                            verfica_nulo(pessoaAux);
                            pessoaAux->nomePessoa[39] = '\0';
                            flag[1] =1;
                            break;
                        case 3:
                            scanf("%d",&pessoaAux->idade);
                            flag[2] =1;
                            break;
                        case 4:
                            scan_quote_string(pessoaAux->twitterPessoa);
                            pessoaAux->twitterPessoa[14] ='\0';
                            flag[3] =1;
                            break;
                    }
                }

                int flag_primeiroRRN_nome = 0;
                while (fread(&charAux,sizeof(char),1,binFile) != 0) {
                    fseek(binFile,-1,SEEK_CUR);
                    pessoa = pesquisa_nome(binFile, nome_aux,1);

                    if(pessoaAux->RRN == 0 && flag_primeiroRRN_nome != 1) {
                        flag_primeiroRRN_nome++;
                        pessoaAux->RRN += pessoa->RRN;
                    }else {
                        pessoaAux->RRN += pessoa->RRN;
                        pessoaAux->RRN++;
                    }

                    if (pessoa->idade == -2) {
                        break;
                    }
                    if (flag[0]!= 0){
                        remove_lista(li, pessoa->idPessoa);
                        pessoa->idPessoa = pessoaAux->idPessoa;
                        index1.idPessoa = pessoa->idPessoa;
                        index1.RRN = pessoaAux->RRN;
                        insere_lista_ordenada(li,index1);
                    }
                    if (flag[1]!= 0){
                        strcpy(pessoa->nomePessoa,pessoaAux->nomePessoa);
                    }
                    if (flag[2]!= 0){
                        pessoa->idade = pessoaAux->idade;
                    }
                    if (flag[3]!= 0){
                        strcpy(pessoa->twitterPessoa,pessoaAux->twitterPessoa);
                    }


                    fseek(binFile, 64, SEEK_SET);
                    fseek(binFile, 64 * pessoaAux->RRN, SEEK_CUR);
                    insereBinario(pessoa, binFile);
                }
                break;

            case 3:
                for (int t = 0;t <4;t++){
                    flag[t] = 0;
                }
                pessoaAux = (Pessoa*)malloc(sizeof(Pessoa));
                fseek(binFile,64,SEEK_SET);
                scanf("%d",&pessoa->idade);

                scanf("%d",&numMudancas);
                for (int j = 0; j < numMudancas ; ++j) {
                    scanf("%s",nomeCampos.nomeCampo1);
                    aux_selecao = comparaCampo(nomeCampos.nomeCampo1);
                    switch (aux_selecao) {
                        case 1:
                            scanf("%d",&pessoaAux->idPessoa);
                            flag[0] =1;
                            break;
                        case 2:
                            scan_quote_string(pessoaAux->nomePessoa);
                            verfica_nulo(pessoaAux);
                            pessoaAux->nomePessoa[39] = '\0';
                            flag[1] =1;
                            break;
                        case 3:
                            scanf("%d",&pessoaAux->idade);
                            flag[2] =1;
                            break;
                        case 4:
                            scan_quote_string(pessoaAux->twitterPessoa);
                            pessoaAux->twitterPessoa[14] ='\0';
                            flag[3] =1;
                            break;
                    }
                }

                int flag_primeiroRRN = 0;
                while (fread(&charAux,sizeof(char),1,binFile) != 0) {
                    fseek(binFile,-1,SEEK_CUR);
                    pessoa = pesquisa_idade(binFile, pessoa->idade,1);
                    if (pessoa->idade == -2) {
                        break;
                    }

                    if(pessoaAux->RRN == 0 && flag_primeiroRRN != 1) {
                            pessoaAux->RRN += pessoa->RRN;
                            flag_primeiroRRN = 1;
                    }
                    else{
                        pessoaAux->RRN += pessoa->RRN;
                        pessoaAux->RRN++;
                    }
                    if (flag[0]!= 0){
                        remove_lista(li, pessoa->idPessoa);
                        pessoa->idPessoa = pessoaAux->idPessoa;
                        index1.idPessoa = pessoa->idPessoa;
                        index1.RRN = pessoaAux->RRN;
                        insere_lista_ordenada(li,index1);
                    }
                    if (flag[1]!= 0){
                        strcpy(pessoa->nomePessoa,pessoaAux->nomePessoa);
                    }
                    if (flag[2]!= 0){
                        pessoa->idade = pessoaAux->idade;
                    }
                    if (flag[3]!= 0){
                        strcpy(pessoa->twitterPessoa,pessoaAux->twitterPessoa);
                    }


                    fseek(binFile, 64, SEEK_SET);
                    fseek(binFile, 64 * pessoaAux->RRN, SEEK_CUR);
                    insereBinario(pessoa, binFile);
                }
                break;

            case 4:
                fseek(binFile,64,SEEK_SET);
                scan_quote_string(pessoa->twitterPessoa);
               pessoa =  pesquisa_twitter(binFile,pessoa->twitterPessoa);
                if(pessoa->idade == -2){
                    fgets(buffer,100,stdin);
                    break;
                }
                int id_aux2;
                scanf("%d",&numMudancas);
                for (int j = 0; j < numMudancas ; ++j) {
                    scanf("%s",nomeCampos.nomeCampo1);
                    aux_selecao = comparaCampo(nomeCampos.nomeCampo1);
                    switch (aux_selecao) {
                        case 1:
                            scanf("%d",&id_aux2);
                            remove_lista(li, pessoa->idPessoa);
                            pessoa->idPessoa = id_aux2;
                            index1.idPessoa = pessoa->idPessoa;
                            index1.RRN = pessoa->RRN;
                            insere_lista_ordenada(li,index1);
                            break;
                        case 2:
                            scan_quote_string(pessoa->nomePessoa);
                            pessoa->nomePessoa[39] = '\0';
                            break;
                        case 3:
                            scanf("%d",&pessoa->idade);
                            break;
                        case 4:
                            scan_quote_string(pessoa->twitterPessoa);
                            pessoa->twitterPessoa[14] ='\0';
                            break;
                    }
                }
                fseek(binFile,64,SEEK_SET);
                fseek(binFile,64 * pessoa->RRN,SEEK_CUR);
                insereBinario(pessoa,binFile);

                break;
        }
    }

    salva_arq(li,indexFile);

    fseek(binFile,0,SEEK_SET);
    fseek(indexFile,0,SEEK_SET);

    fwrite(&c2,sizeof(char),1,binFile);
    fwrite(&c2,sizeof(char),1,indexFile);

    fclose(indexFile);
    fclose(binFile);
    binarioNaTela1(arqPessoa,arqIndexaPessoa);
}



int comparaCampo(char* nomeCampo){

    int a = 0, d = 0;
    char aux_campo[] = "idPessoa";
    if (strcmp(nomeCampo, aux_campo) == 0) {
        while (a < strlen(nomeCampo) && d == 0) {
            if (nomeCampo[a] == aux_campo[a]) {
                d = 0;
            } else {
                d = 1;
            }
            a++;
        }
        if (d == 0){
            return 1;
        }
    }
    a = 0, d = 0;
    char aux_campo2[] = "nomePessoa";
    if (strcmp(nomeCampo, aux_campo2) == 0) {
        while (a < strlen(nomeCampo) && d == 0) {
            if (nomeCampo[a] == aux_campo2[a]) {
                d = 0;
            } else {
                d = 1;
            }
            a++;
        }
        if (d == 0){
            return 2;
        }
    }
    a = 0, d = 0;
    char aux_campo3[] = "idadePessoa";
    if (strcmp(nomeCampo, aux_campo3) == 0) {
        while (a < strlen(nomeCampo) && d == 0) {
            if (nomeCampo[a] == aux_campo3[a]) {
                d = 0;
            } else {
                d = 1;
            }
            a++;
        }
        if (d == 0){
            return 3;
        }
    }
    a = 0, d = 0;
    char aux_campo4[] = "twitterPessoa";
    if (strcmp(nomeCampo, aux_campo4) == 0) {
        while (a < strlen(nomeCampo) && d == 0) {
            if (nomeCampo[a] == aux_campo4[a]) {
                d = 0;
            } else {
                d = 1;
            }
            a++;
        }
        if (d == 0){
            return 4;
        }
    }
    return 0;
}

void verfica_nulo(Pessoa* pessoa){
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
}