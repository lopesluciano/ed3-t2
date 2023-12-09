#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DATATYPESDEF_H_
#define DATATYPESDEF_H_


#pragma pack(push,1)
typedef struct cabecalho{
	char status;
	int proxRRN;
	int nroTecnologias;
	int nroParesTecnologias;
} Cabecalho;
#pragma pack(pop)

typedef struct stringVariavel{
    int tamanho;
    char *nome;
} StringVariavel;	

typedef struct dado{
	int grupo;
	int popularidade;
	int peso;
	StringVariavel tecnologiaOrigem;
	StringVariavel tecnologiaDestino;
	char removido;
} Dado;

#endif