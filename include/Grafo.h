/**
 * Caroline Severiano Clapis    | NUSP: 13861923
 * Luciano Goncalves Lopes Filho | NUSP: 13676520 
 */

#ifndef GRAFO_H
#define GRAFO_H

#include "Funcionalidades.h"
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <list>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdio>
#include "Cabecalho.h"
#include <queue>
#include <limits>
#include "Grafo.h"

// Estrutura para armazenar informações de uma tecnologia
struct Technology {
    std::string nome;
    int grupo;
    int grauEntrada;
    int grauSaida;
    int grauTotal;

    Technology(std::string n, int g)
        : nome(std::move(n)), grupo(g), grauEntrada(0), grauSaida(0), grauTotal(0) {}
};

// Classe para representar um grafo direcionado com lista de adjacência
class Grafo {
    int V; // Número de vértices

    // Vetor de tecnologias
    std::vector<std::list<std::pair<std::string, int>>> adjList; 

    // Vetor de tecnologias    
    std::vector<Technology> vertices;

//Definicao dos metodos da classe
public:
    Grafo(int vertices);

    int buscaVertice(const std::string& techName);
    void adicionaVertice(const Technology& tech);
    void adicionaAresta(const std::string& src, const std::string& dest, int weight);
    void listaTecnologiasOriginadas(const std::string& destTech);
    void imprimeGrafo();
    void encontraMenorCaminho(const std::string& src, const std::string& dest);
    void dfsTarjan(const int& techIdx, int& curTime, std::vector<int>& tin, std::vector<int>& lowlink, std::vector<bool>& onStack, std::vector<int>& stack, int& numSCCs);
    void encontraNumFC();
};

//Funcao auxiliar que cria o grafo a partir da leitura do arquivo binario
void criaGrafo(char *nomeArquivo, Grafo &graph, Grafo &graphT);

#endif // GRAFO_H
