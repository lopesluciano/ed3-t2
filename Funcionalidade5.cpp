 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcionalidades.h"
#include "Cabecalho.h"

char *concatenarStrings(Dado *d) {
    // Verifica se as strings não são nulas e têm comprimento positivo
    if (d->tecnologiaOrigem.nome != NULL && d->tecnologiaOrigem.tamanho > 0 &&
        d->tecnologiaDestino.nome != NULL && d->tecnologiaDestino.tamanho > 0) {

        // Aloca memória para a string resultante
        int tamanhoTotal = d->tecnologiaOrigem.tamanho + d->tecnologiaDestino.tamanho + 1;
        char *stringConcatenada = (char *)malloc(tamanhoTotal * sizeof(char));

        // Verifica se a alocação de memória foi bem-sucedida
        if (stringConcatenada != NULL) {
            // Copia a primeira string para a string resultante
            strcpy(stringConcatenada, d->tecnologiaOrigem.nome);

            // Concatena a segunda string à string resultante
            strcat(stringConcatenada, d->tecnologiaDestino.nome);

            // Retorna a string resultante
            return stringConcatenada;
        } else {
            printf("Erro ao alocar memória.\n");
            return NULL;
        }
    } else {
        printf("As strings estão vazias ou nulas.\n");
        return NULL;
    }
}

void cria_ArvoreB(char *nomeArquivo, char *NomeArquivoIndice){

    //Abre o arquivo das tecnlologias no modo leitura binaria
    FILE *f_tecnologia = fopen(nomeArquivo, "rb");

    //se o arquivo nao existe, retorna erro
    if (f_tecnologia == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }   

    //structs
    Cabecalho tecnologia_cabecalho; //struct de cabecalho
    Dado      tecnologia_dados;    //struct de registro

    //le o cabecalho do arquivo de registro e verifica se eh inconsistente
    fread(&tecnologia_cabecalho.status, sizeof(char), 1, f_tecnologia);
    if(tecnologia_cabecalho.status != '1'){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    //abre o arquivo de indice da arvore b no mode de escrita binaria
    FILE *f_arvoreb = fopen(NomeArquivoIndice, "wb"); //arquivo da arvore b
    //se o arquivo nao existe, retorna erro
    if (f_arvoreb == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    //struct de cabecalho 
    header arvoreb_cabecalho;

    //define os valores iniciais do cabecalhoz
    arvoreb_cabecalho.status = '0';
    arvoreb_cabecalho.noRaiz = -1;
    arvoreb_cabecalho.RRNproxNO = 0;
    memset(&(arvoreb_cabecalho.lixo), '$', 193); //insere o lixo

    //escreve o status da arvore b no disco
    fwrite(&arvoreb_cabecalho.status, sizeof(char), 1, f_arvoreb);

    //le os campos restantes do cabecalho de tecnologia
    fread(&tecnologia_cabecalho.nroTecnologias, sizeof(int), 1 , f_tecnologia);
    fread(&tecnologia_cabecalho.proxRRN , sizeof(int), 1 , f_tecnologia);

    //move o ponteiro para o comeco do primeiro registro de dados
    fseek(f_tecnologia, 11, SEEK_SET);

    //le cada registro dos veiculos e insere na arvore B
    int indice = 0;
    while(indice < tecnologia_cabecalho.nroTecnologias){
        //byte offset do atual registro
        long byte_offset = ftell(f_tecnologia);

        //le o atual dado pula para o proximo regitro
        fread(&tecnologia_dados.removido, sizeof(char), 1, f_arvoreb);

        //se o registro atual for removido, nao havera insercao
        if(tecnologia_dados.removido == '1'){
            fseek(f_tecnologia, 76, SEEK_CUR);
            continue;
        }

        //le o dado atual do registro
        fread(&tecnologia_dados.grupo, sizeof(int), 1, f_tecnologia);
        fread(&tecnologia_dados.popularidade, sizeof(int), 1, f_tecnologia);
        fread(&tecnologia_dados.peso, sizeof(int), 1, f_tecnologia);
        fread(&tecnologia_dados.tecnologiaOrigem.tamanho, sizeof(int), 1, f_tecnologia); // Tamanho da str1
        char str1[tecnologia_dados.tecnologiaOrigem.tamanho + 1]; // adiciona +1 para o termino nulo
        fread(str1, sizeof(char), tecnologia_dados.tecnologiaOrigem.tamanho, f_tecnologia);
        str1[tecnologia_dados.tecnologiaOrigem.tamanho] = '\0'; // termina nulo

        fread(&fread, sizeof(int), 1, f_tecnologia); // Tamanho da str2
        char str2[tecnologia_dados.tecnologiaDestino.tamanho + 1]; // adiciona +1 para o termino nulo
        fread(str2, sizeof(char), tecnologia_dados.tecnologiaDestino.tamanho, f_tecnologia);
        str2[tecnologia_dados.tecnologiaOrigem.tamanho] = '\0'; // termina nulo

        fseek(f_tecnologia, 76, SEEK_CUR);

       
        char *chave =  concatenarStrings(&tecnologia_dados);
               //insere a tecnologia na arvore
//               insere_arvoreB(chave, byte_offset, f_arvoreb, &arvoreb_cabecalho.noRaiz, &arvoreb_cabecalho.RRNproxNO);
    
        //incrementa o indice
        indice++;
    }
        //define o cabecalho da arvore b para 1
        arvoreb_cabecalho.status = '1';
        fseek(f_arvoreb, 0, SEEK_SET);
        fwrite(&arvoreb_cabecalho.status, sizeof(char), 1, f_arvoreb);

        //fecha os arquivos
        fclose(f_tecnologia);
        fclose(f_arvoreb);

        return;

}

    