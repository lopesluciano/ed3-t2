#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Cabecalho.h"
#include "lista.h"

#ifndef STACKDEV_H_
#define STACKDEV_H_

void readline(char*);
void binarioNaTela(char*);
void scan_quote_string(char*);

int tecnologiaNova(Lista*, char*);
int paresTecnologiasNovas(Lista*, char*, char*);

int leCSV(char*, Cabecalho*, Lista*);
void escreveBinario(char*, Cabecalho*, Lista*);

void readToken(char*, char*, int*);
void parseString(char*, StringVariavel*, int*);
void parseInt(char*, int*, int*);

void PesquisaRRN(char *nomeArquivo, Cabecalho*, int RRN);
void imprimeRegistro(char *nomeArquivo, Cabecalho *cabecalho);
void PesquisaCampo(char *nomeArquivo, char *nomeArquivoIndice, Cabecalho *cabecalho );

void Verifica_se_Nulo(int int_x);
void leCabecalho(char *nomeArquivo, Cabecalho *cabecalho);
void imprimeCampos(char *str1, int int_a, int int_b, int int_f, char *str2, int int_c);


#endif

