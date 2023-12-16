#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdio>
#include "Cabecalho.h"
#include "Funcionalidades.h"
#include <queue>
#include <limits>

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
        //Encontra o vertice com base no nome da tecnologia usando find_if da biblioteca STL do C++
        auto it = std::find_if(vertices.begin(), vertices.end(), [&](const Technology& t) {
            return t.name == techName;
        });

        //Verifica se o vertice foi encontrado
        if (it != vertices.end()) {
            // Retorna a distancia do inicio do vetor (vertices.begin) ate o iterador encontrado
            return std::distance(vertices.begin(), it);
        }
        return -1; // Retorna -1 se a tecnologia não for encontrada
    }

    // Função para adicionar uma tecnologia como vértice
    void addVertex(const Technology& tech) {
        // Verifica se o vertice nao existe
        int idx = findVertex(tech.name); 
        if (idx == -1) {
            // Caso exista, adiciona mais um vertice na lista de vertices
            vertices.push_back(tech);
            // Adiciona uma lista de vazia correspondente a lista de adjacencias
            adjList.push_back(std::list<std::pair<std::string, int>>());
        }
    }

    // Função para adicionar uma aresta direcionada com um peso
    void addEdge(const std::string& src, const std::string& dest, int weight) {
        int idx_src = findVertex(src); // Encontra o indice do vertice de Origem
        int idx_dest = findVertex(dest); // Encontra o indice do vertice de Destino

        // Verifica se os vertices de origem e destino existem no Grafo
        if (idx_src != -1 && idx_dest != -1) {
            adjList[idx_src].push_back(std::make_pair(dest, weight)); // Adiciona a aresta no na lista de adjacencias do vertice de origem

            // Atualizar os graus dos vertices da aresta
            vertices[idx_src].outDegree++;
            vertices[idx_dest].inDegree++;
            vertices[idx_src].degree++;
            vertices[idx_dest].degree++;

            // Ordenar a lista de adjacência após adicionar um novo elemento
            adjList[idx_src].sort([](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                return a.first < b.first;  // Ordenar com base no nome da tecnologia destino
            });
        } else {
            // Caso a tecnologia nao esteja no Grafo
            std::cout << "Tecnologia não encontrada!\n";
        }
    }


    // Função para listar as tecnologias de origem para uma tecnologia destino
    void findClickOriginators(const std::string& destTech) {
        int idx_dest = findVertex(destTech); // Verifica a tecnologia destino

        if (idx_dest != -1) {
            // Se a tecnologia destino foi encontrada, imprime tecnologia de destino
            std::cout << destTech << ": ";
            bool found = false;
            std::vector<std::string> originators; // Armazena as tecnologias de origem

            // Coleta as tecnologias de origem para a tecnologia destino
            for (size_t i = 0; i < vertices.size(); ++i) {
                for (const auto& edge : adjList[i]) {
                    if (edge.first == destTech) {
                        originators.push_back(vertices[i].name); // Armazena a tecnologia de origem
                        break;
                    }
                }
            }

            // Ordena as tecnologias de origem em ordem alfabética
            std::sort(originators.begin(), originators.end());

            // Imprime as tecnologias de origem ordenadas
            for (size_t i = 0; i < originators.size(); ++i) {
                if (i > 0) {
                    std::cout << ", ";
                }
                std::cout << originators[i]; //Imprime o vetor de tecnologias de origem
                found = true;
            }

            if (!found) {
                std::cout << "Registro inexistente.";// Caso a tecnologia nao seja encontrada
            }
        } else {
            std::cout << "Registro inexistente.";// Caso a tecnologia nao seja encontrada
        }
        std::cout << "\n\n";
    }

    // Função para imprimir a lista de adjacência do grafo
    void printGraph() {
        // Cria uma cópia dos vértices para não alterar a estrutura original
        std::vector<Technology> sortedVertices = vertices;

        // Ordena os vértices pelo nome da tecnologia
        std::sort(sortedVertices.begin(), sortedVertices.end(),
                [](const Technology& a, const Technology& b) {
                    return a.name < b.name;
                });

        // Percorre os vértices ordenados
        for (const auto& vertex : sortedVertices) {
            // Encontra o índice do vértice na lista de adjacência
            int idx = findVertex(vertex.name);

            // Imprime as informações do vértice
            for (const auto& edge : adjList[idx]) {
                std::cout << vertex.name << " " << vertex.group << " "
                        << vertex.inDegree << " " << vertex.outDegree << " "
                        << vertex.degree << " "
                        << edge.first << " " << edge.second << "\n";
            }
        }
    }

    // Funcao que procura a menor distancia entre duas tecnologias
    void dijkstra(const std::string& src, const std::string& dest) {
        // Verifica se as tecnologias de origem e destino foram encontradas no grafo
        int srcIdx = findVertex(src);
        int destIdx = findVertex(dest);
        if (srcIdx == -1 || destIdx == -1) {
            std::cout << "Tecnologia de origem ou destino não encontrada!\n";
            return;
        }

        // Inicializa um vetor para armazenar as distancias dos vertices da origem
        std::vector<int> dist(999999, std::numeric_limits<int>::max());
        dist[srcIdx] = 0; // Define a distancia do vertice origem para si mesmo como 0

        // Utiliza uma fila de prioridade para explorar os vertices de forma ordenada 
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push(std::make_pair(0, srcIdx)); // Insere o vertice origem na fila de prioridade

        // Algoritmo de Dijkstra para encontrar o menor caminho
        while (!pq.empty()) {
            int u = pq.top().second; // Obtem o vertice com a menor distancia da origem
            pq.pop();// Remove o vertice da fila de prioridade

            // Itera sobre os vizinhos do vertice atual
            for (const auto& neighbor : adjList[u]) {
                int v = findVertex(neighbor.first); // Verifica a existencia do vertice vizinho
                int weight = neighbor.second; // Obtem o peso da aresta entre u e v

                // Atualiza a pagina se um caminho mais curto foi encontrado
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push(std::make_pair(dist[v], v)); // Insere v na fila de prioridade com a nova distancia
                }
            }
        }

        // Verifica se um caminho foi encontrado e exibe a menor distancia
        if (dist[destIdx] != std::numeric_limits<int>::max()) {
            std::cout << src << " " << dest << ": " << dist[destIdx] << std::endl;
        } else {
            std::cout << src << " " << dest << ": "<< "CAMINHO INEXISTENTE."<< std::endl;
        }
    }

};

// Essa funcao cria um grafo e sua transposta a partir de um arquivo de entrada
void LeRegistro(char *nomeArquivo, Graph &graph, Graph &graphT){

    // Abre o arquivo das tecnlologias no modo leitura binaria
    FILE *f_tecnologia = fopen(nomeArquivo, "rb");

    // Se o arquivo nao existe, retorna erro
    if (f_tecnologia == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }   

    // Struct de cabecalho
    Cabecalho tecnologia_cabecalho;

    // Le o cabecalho do arquivo de registro e verifica se eh inconsistente
    fread(&tecnologia_cabecalho.status, sizeof(char), 1, f_tecnologia);
    if(tecnologia_cabecalho.status != '1'){
        printf("Falha no processamento do arquivo.\n");
        fclose(f_tecnologia);
        return;
    }

    // Struct utilizada na leituras de Registros
    Dado *d = (Dado *)malloc(sizeof(Dado));

    // Le os campos restantes do cabecalho de tecnologia
    fread(&tecnologia_cabecalho.proxRRN , sizeof(int), 1 , f_tecnologia);
    fread(&tecnologia_cabecalho.nroTecnologias, sizeof(int), 1 , f_tecnologia);
    fread(&tecnologia_cabecalho.nroParesTecnologias, sizeof(int), 1 , f_tecnologia);

    // Le cada registro de tecnologia e cria os vertices do grafo
    int indice = 0;
    while(indice < tecnologia_cabecalho.proxRRN){
        //byte offset do atual registro

        // Le o atual dado 
        fread(&d->removido, sizeof(char), 1, f_tecnologia);
        // Se o registro atual for removido, nao havera insercao
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
        
        // Função anonima para adicionar uma tecnologia somente se ela não existir
        auto addTechnology = [&](const Technology& tech) {
            // Verifica se a tecnologia ja nao foi criada no grafo usando uma funcao de busca por vertice
            int idx = graph.findVertex(tech.name);
            if (idx == -1) {
                // Caso nao a tecnologia nao exista (idx == -1), chama a funcao que adiciona vertices ao grafo
                graph.addVertex(tech);
            }
        };
        auto addTechnologyT = [&](const Technology& tech) {
            int idx = graphT.findVertex(tech.name);
            if (idx == -1) {
                graphT.addVertex(tech);
            }
        };

        // Adiciona se a tecnologia de origem tanto no grafo quanto no grafo transposto
        addTechnology(Technology(d->tecnologiaOrigem.nome, d->grupo));
        addTechnologyT(Technology(d->tecnologiaOrigem.nome, d->grupo));


        // Libera memoria e incrementa o indice
        free(d->tecnologiaDestino.nome);
        free(d->tecnologiaOrigem.nome);
        indice++;
    }
    
    // Fecha o arquivo para reabrir de novo e realizar um leitura dos registros novamente 
    // (por algum motivo usar o fseek para retornar ao comeco do arquivo nao funcionava)
    fclose(f_tecnologia);
    f_tecnologia = fopen(nomeArquivo, "rb");

    // Se o arquivo nao existe, retorna erro
    if (f_tecnologia == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }   



    // Se o cabecalho do arquivo de registro e verifica se eh inconsistente
    fread(&tecnologia_cabecalho.status, sizeof(char), 1, f_tecnologia);
    if(tecnologia_cabecalho.status != '1'){
        printf("Falha no processamento do arquivo.\n");
        fclose(f_tecnologia);
        return;
    }

    // Le os campos restantes do cabecalho de tecnologia
    fread(&tecnologia_cabecalho.proxRRN , sizeof(int), 1 , f_tecnologia);
    fread(&tecnologia_cabecalho.nroTecnologias, sizeof(int), 1 , f_tecnologia);
    fread(&tecnologia_cabecalho.nroParesTecnologias, sizeof(int), 1 , f_tecnologia);

    // Le cada registro de tecnologia e cria as arestas do grafo
    indice = 0;
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
        
        // Função anonima para adicionar uma tecnologia somente se ela não existir
        auto addTechnology = [&](const Technology& tech) {
            //Verifica se a tecnologia ja nao foi criada no grafo usando uma funcao de busca por vertice
            int idx = graph.findVertex(tech.name);
            if (idx == -1) {
                //Caso nao a tecnologia nao exista (idx == -1), chama a funcao que adiciona vertices ao grafo
                graph.addVertex(tech);
            }
        };
        auto addTechnologyT = [&](const Technology& tech) {
            int idx = graphT.findVertex(tech.name);
            if (idx == -1) {
                graphT.addVertex(tech);
            }
        };

        // Adiciona Tecnologias de Destino caso elas nao tenham sido criadas como vertices de origem anteriormente
        addTechnology(Technology(d->tecnologiaDestino.nome, d->grupo));;
        addTechnologyT(Technology(d->tecnologiaDestino.nome, d->grupo));

        // Adiciona a aresta somente se possuir um campo peso valido
        if(d->peso != -1){
            // Adiciona a aresta no Grafo
            graph.addEdge(d->tecnologiaOrigem.nome, d->tecnologiaDestino.nome, d->peso);
            // Adiciona a aresta no Grafo Transposto, note que a ordem das tecnologias foi invertida
            graphT.addEdge(d->tecnologiaDestino.nome, d->tecnologiaOrigem.nome, d->peso);
        }

        // Incrementa o indice e libera memoria
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
    Graph graphT(0); // Inicialização do grafo transposto com 0 vértices

    int chave; 
    char NomeArquivo[100]; 
    char TecOrigem[100];
    char TecDestino[100];

    int i;  
    int j = 0;

    scanf("%d", &chave); // Seleciona a Funcionalidade
    scanf("%s", NomeArquivo); // Arquivo Binario de Entrada

    //Funcao que Le o Arquivo Binario e cria o grafo a partir dele
    LeRegistro(NomeArquivo, graph, graphT);

    switch (chave)
    {
    case 8:

        //Imprime o Grafo
        graph.printGraph(); 

        break;
    case 9:
        
        //Imprime o Grafo transposto
        graphT.printGraph();

        break;

    case 10:


        // Le o numero de buscas que serao realizadas
        scanf("%d", &i);
        while (j < i){
            // Le a Tecnologia Buscada
            scan_quote_string(TecDestino);
            // Funcao que encontra
            graph.findClickOriginators(TecDestino);
            j++;
        }   
        break;  
    case 12:
        
        // Le o numero de buscas que serao realizadas
        scanf("%d", &i);
        while (j < i){
            // Le as tecnologias 
            scan_quote_string(TecOrigem);
            scan_quote_string(TecDestino);

            // Chama a funcao que calcula a menor distancia entre tecnologias 
            graph.dijkstra(TecOrigem, TecDestino);
            j++;
        }
        break;
    }
    // Função para adicionar uma tecnologia somente se ela não existir
    auto addTechnology = [&](const Technology& tech) {
        int idx = graph.findVertex(tech.name);
        if (idx == -1) {
            graph.addVertex(tech);
        }
    };
        
        return 0;
        
}


