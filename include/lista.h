#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cabecalho.h"

#ifndef LISTA_H_
#define LISTA_H_

typedef struct node{
	struct dado *dado;
	struct node *prox;
} Node;

typedef struct Lista{
	struct node *ini;
	struct node *fim;
	int tamanho;
} Lista;

Lista *criarLista();

Node *criarNode(Dado* dado);

void inserir(Lista *lista, Dado *dado);

void imprimir(Lista *lista);



#endif
