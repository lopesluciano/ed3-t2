/**
 * Caroline Severiano Clapis    | NUSP: 13861923
 * Luciano Goncalves Lopes Filho | NUSP: 13676520 
 */

#include "Funcionalidades.h"
#include "Grafo.h"

int main() {
    Grafo grafo(0); // Inicialização do grafo com 0 vértices
    Grafo grafoT(0); // Inicialização do grafo transposto com 0 vértices

    int chave; 
    char NomeArquivo[100]; 
    char TecOrigem[100];
    char TecDestino[100];

    int i;  
    int j = 0;

    scanf("%d", &chave); // Seleciona a Funcionalidade
    scanf("%s", NomeArquivo); // Arquivo Binario de Entrada

    //Funcao que Le o Arquivo Binario e cria o grafo a partir dele
    criaGrafo(NomeArquivo, grafo, grafoT);

    switch (chave)
    {
    case 8:

        //Imprime o Grafo
        grafo.imprimeGrafo(); 

        break;
    case 9:
        
        //Imprime o Grafo transposto
        grafoT.imprimeGrafo();

        break;

    case 10:

        // Le o numero de buscas que serao realizadas
        scanf("%d", &i);
        while (j < i){
            // Le a Tecnologia Buscada
            scan_quote_string(TecDestino);
            // Funcao que encontra
            grafo.listaTecnologiasOriginadas(TecDestino);
            j++;
        }   
        break;

    case 11:

        // Chama a funcao que calcula a quantidade de componentes fortemente conexas
        grafo.encontraNumFC(); 

        break;

    case 12:
        
        // Le o numero de buscas que serao realizadas
        scanf("%d", &i);
        while (j < i){
            // Le as tecnologias 
            scan_quote_string(TecOrigem);
            scan_quote_string(TecDestino);

            // Chama a funcao que calcula a menor distancia entre tecnologias 
            grafo.encontraMenorCaminho(TecOrigem, TecDestino);
            j++;
        }
        break;
    }
        
        return 0;
        
}
