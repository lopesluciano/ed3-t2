#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdio>
#include "Cabecalho.h"
#include "Funcionalidades.h"

// Estrutura para armazenar informações de uma tecnologia
struct Technology {
    std::string name;
    int group;
    int inDegree;
    int outDegree;
    int degree;
    // Adicione outros campos conforme necessário

    // Construtor para inicializar a estrutura
    Technology(std::string n, int g)
        : name(std::move(n)), group(g), inDegree(0), outDegree(0), degree(0) {}
};




// Classe para representar um grafo direcionado com lista de adjacência
class Graph {
    int V; // Número de vértices

    // Lista de adjacência (vetor de listas)
    std::vector<std::list<std::pair<std::string, int>>> adjList;

    // Vetor de tecnologias
    std::vector<Technology> vertices;

public:
    // Construtor que inicializa o grafo com V vértices
    Graph(int vertices) : V(vertices), adjList(vertices), vertices() {}

    // Função para buscar um vértice dado o nome da tecnologia
    int findVertex(const std::string& techName) {
        auto it = std::find_if(vertices.begin(), vertices.end(), [&](const Technology& t) {
            return t.name == techName;
        });

        if (it != vertices.end()) {
            return std::distance(vertices.begin(), it);
        }

        return -1; // Retorna -1 se a tecnologia não for encontrada
    }

    // Função para adicionar uma tecnologia como vértice
    void addVertex(const Technology& tech) {
        int idx = findVertex(tech.name);
        if (idx == -1) {
            vertices.push_back(tech);
            adjList.push_back(std::list<std::pair<std::string, int>>());
        }
    }

    // Função para adicionar uma aresta direcionada com um peso
    void addEdge(const std::string& src, const std::string& dest, int weight) {
        int idx_src = findVertex(src);
        int idx_dest = findVertex(dest);

        if (idx_src != -1 && idx_dest != -1) {
            adjList[idx_src].push_back(std::make_pair(dest, weight));

            // Ordenar a lista de adjacência após adicionar um novo elemento
            adjList[idx_src].sort([](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                return a.first < b.first;  // Ordenar com base no nome da tecnologia destino
            });

            // Atualizar os graus
            vertices[idx_src].outDegree++;
            vertices[idx_dest].inDegree++;
            vertices[idx_src].degree++;
            vertices[idx_dest].degree++;
        } else {
            std::cout << "Tecnologia não encontrada!\n";
        }
    }

    // Função para listar as tecnologias de origem para uma tecnologia destino
    void findClickOriginators(const std::string& destTech) {
        int idx_dest = findVertex(destTech);

        if (idx_dest != -1) {
            std::cout << destTech << ": ";
            bool found = false;

            for (size_t i = 0; i < vertices.size(); ++i) {
                for (const auto& edge : adjList[i]) {
                    if (edge.first == destTech) {
                        if (found) {
                            std::cout << ", ";
                        }
                        std::cout << vertices[i].name;
                        found = true;
                        break;
                    }
                }
            }

            if (!found) {
                std::cout << "Registro inexistente.";
            }
        } else {
            std::cout << "Registro inexistente.";
        }
        std::cout << "\n\n";
    }

    // Função para imprimir a lista de adjacência do grafo
    void printGraph() {
        for (size_t i = 0; i < vertices.size(); ++i) {
            std::cout << "Tecnologia: " << vertices[i].name << ", Grupo: " << vertices[i].group
                      << ", Grau de Entrada: " << vertices[i].inDegree << ", Grau de Saída: "
                      << vertices[i].outDegree << ", Grau: " << vertices[i].degree << "\n";

            for (const auto& edge : adjList[i]) {
                std::cout << "-> " << edge.first << " (peso: " << edge.second << ")\n";
            }

            std::cout << std::endl;
        }
    }
};


void LeRegistro(char *nomeArquivo, Graph &graph){

    //Abre o arquivo das tecnlologias no modo leitura binaria
    FILE *f_tecnologia = fopen(nomeArquivo, "rb");

    //se o arquivo nao existe, retorna erro
    if (f_tecnologia == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }   

    //structs
    Cabecalho tecnologia_cabecalho; //struct de cabecalho

    //le o cabecalho do arquivo de registro e verifica se eh inconsistente
    fread(&tecnologia_cabecalho.status, sizeof(char), 1, f_tecnologia);
    if(tecnologia_cabecalho.status != '1'){
        printf("Falha no processamento do arquivo.\n");
        fclose(f_tecnologia);
        return;
    }

    Dado *d = (Dado *)malloc(sizeof(Dado));

    //le os campos restantes do cabecalho de tecnologia
    fread(&tecnologia_cabecalho.proxRRN , sizeof(int), 1 , f_tecnologia);
    fread(&tecnologia_cabecalho.nroTecnologias, sizeof(int), 1 , f_tecnologia);
    fread(&tecnologia_cabecalho.nroParesTecnologias, sizeof(int), 1 , f_tecnologia);

    //le cada registro de tecnologia e insere na arvore B
    int indice = 0;
    while(indice < tecnologia_cabecalho.proxRRN){
        //byte offset do atual registro

        //le o atual dado 
        fread(&d->removido, sizeof(char), 1, f_tecnologia);
        //se o registro atual for removido, nao havera insercao
        if(d->removido == '1'){
            fseek(f_tecnologia, 75, SEEK_CUR);
            indice++;
            continue;
        }

        //le o dado atual do registro
        fread(&d->grupo, sizeof(int), 1, f_tecnologia);
        fread(&d->popularidade, sizeof(int), 1, f_tecnologia);
        fread(&d->peso, sizeof(int), 1, f_tecnologia);

        fread(&d->tecnologiaOrigem.tamanho, sizeof(int), 1, f_tecnologia); // Tamanho da str1
        d->tecnologiaOrigem.nome = (char*)malloc(d->tecnologiaOrigem.tamanho + 1);//adiciona +1 para o termino nulo
        fread(d->tecnologiaOrigem.nome, d->tecnologiaOrigem.tamanho, sizeof(char), f_tecnologia);
        d->tecnologiaOrigem.nome[d->tecnologiaOrigem.tamanho] = '\0'; // termina nulo
     

        fread(&d->tecnologiaDestino.tamanho, sizeof(int), 1, f_tecnologia); // Tamanho da str1
        d->tecnologiaDestino.nome = (char*)malloc(d->tecnologiaDestino.tamanho + 1);//adiciona +1 para o termino nulo
        fread(d->tecnologiaDestino.nome, d->tecnologiaDestino.tamanho, sizeof(char), f_tecnologia);
        d->tecnologiaDestino.nome[d->tecnologiaDestino.tamanho] = '\0'; // termina nulo

        fseek(f_tecnologia, 76 - (21+d->tecnologiaOrigem.tamanho+d->tecnologiaDestino.tamanho), SEEK_CUR);
        
        // Função para adicionar uma tecnologia somente se ela não existir
        auto addTechnology = [&](const Technology& tech) {
            int idx = graph.findVertex(tech.name);
            if (idx == -1) {
                graph.addVertex(tech);
            }
        };


        addTechnology(Technology(d->tecnologiaDestino.nome, d->grupo));
        addTechnology(Technology(d->tecnologiaOrigem.nome, d->grupo));

        graph.addEdge(d->tecnologiaOrigem.nome, d->tecnologiaDestino.nome, d->peso);


        //incrementa o indice
        free(d->tecnologiaDestino.nome);
        free(d->tecnologiaOrigem.nome);
        indice++;
    }


        //fecha os arquivos
        free(d);
        fclose(f_tecnologia);

        return;
}



int main() {
    Graph graph(0); // Inicialização do grafo com 0 vértices

    // Função para adicionar uma tecnologia somente se ela não existir
    auto addTechnology = [&](const Technology& tech) {
        int idx = graph.findVertex(tech.name);
        if (idx == -1) {
            graph.addVertex(tech);
        }
    };

    /*// Adicionando algumas tecnologias como vértices
    addTechnology(Technology("AZURE", 2));
    addTechnology(Technology(".NET", 22));
    // Adicione outras tecnologias conforme necessário
        
        int index = graph.findVertex("AZURE");
        printf("%d", index);

        // Adicionando algumas relações entre tecnologias (arestas)
        graph.addEdge("AZURE", ".NET", 10);
        graph.addEdge(".NET", "SQL-SERVER", 20);
        // Adicione outras relações conforme necessário
        */
		

        // Imprimindo a lista de adjacência do grafo
        char NomeArquivo[100];
        char TecDestino[100];
        scanf("%s", NomeArquivo);
        //scanf("%s", TecDestino);
        scan_quote_string(TecDestino);
        LeRegistro(NomeArquivo, graph);
        graph.findClickOriginators(TecDestino);

        //graph.printGraph();

        return 0;
        
}


