#include "Funcionalidades.h"
#include "Cabecalho.h"
#include "lista.h"

void readline(char *string)
{
    char c = 0;

    do
    {
        c = (char)getchar();

    } while (c == '\n' || c == '\r');

    int i = 0;

    do
    {
        string[i] = c;
        i++;
        c = getchar();
    } while (c != '\n' && c != '\r');

    string[i] = '\0';
}

void binarioNaTela(char *nomeArquivoBinario)
{ /* Você não precisa entender o código dessa função. */

    /* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
     *  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

    unsigned long i, cs;
    unsigned char *mb;
    size_t fl;
    FILE *fs;
    if (nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb")))
    {
        fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
        return;
    }
    fseek(fs, 0, SEEK_END);
    fl = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    mb = (unsigned char *)malloc(fl);
    fread(mb, 1, fl, fs);

    cs = 0;
    for (i = 0; i < fl; i++)
    {
        cs += (unsigned long)mb[i];
    }
    printf("%lf\n", (cs / (double)100));
    free(mb);
    fclose(fs);
}

void scan_quote_string(char *str)
{

    /*
     *	Use essa função para ler um campo string delimitado entre aspas (").
     *	Chame ela na hora que for ler tal campo. Por exemplo:
     *
     *	A entrada está da seguinte forma:
     *		nomeDoCampo "MARIA DA SILVA"
     *
     *	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
     *		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
     *		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
     *
     */

    char R;

    while ((R = getchar()) != EOF && isspace(R))
        ; // ignorar espaços, \r, \n...

    if (R == 'N' || R == 'n')
    { // campo NULO
        getchar();
        getchar();
        getchar();       // ignorar o "ULO" de NULO.
        strcpy(str, ""); // copia string vazia
    }
    else if (R == '\"')
    {
        if (scanf("%[^\"]", str) != 1)
        { // ler até o fechamento das aspas
            strcpy(str, "");
        }
        getchar(); // ignorar aspas fechando
    }
    else if (R != EOF)//Dei uma leve modificada nessa parte do codigo
    { // Caso a String nao possua aspas
        ungetc(R, stdin); // volta o caracter para a entrada
        if (scanf("%s", str) != 1)
        {
            strcpy(str, ""); // Cuida de erros de leitura
        }
    }
    else
    { // EOF
        strcpy(str, "");
    }
}

int tecnologiaNova(Lista *lista, char *nomeTecnologia)
{
    Node *aux = lista->ini;

    while (aux != NULL)
    {
        if (strcmp(aux->dado->tecnologiaOrigem.nome, nomeTecnologia) == 0)
            return 0;

        if (strcmp(aux->dado->tecnologiaDestino.nome, nomeTecnologia) == 0)
            return 0;

        aux = aux->prox;
    }

    return 1;
}

int paresTecnologiasNovas(Lista *lista, char *nomeTecnologiaOrigem, char *nomeTecnologiaDestino)
{

    Node *aux = lista->ini;

    // int encontrou;
    while (aux != NULL)
    {
        // encontrou = 0;

        if(strlen(nomeTecnologiaOrigem) == 0 || strlen(nomeTecnologiaDestino) == 0)
        {
            return 0;
        }

        if (strcmp(aux->dado->tecnologiaOrigem.nome, nomeTecnologiaOrigem) == 0 && strcmp(aux->dado->tecnologiaDestino.nome, nomeTecnologiaDestino) == 0)
        {
            return 0;
        }

        aux = aux->prox;
    }

    return 1;
}

// Le buffer a partir da posição i e tokeniza
void readToken(char *token, char *buffer, int *i)
{

    // printf("The first %c\n", buffer[i]);

    int j = 0;
    while (buffer[*i] != ',' && buffer[*i] != 0)
        token[j++] = buffer[(*i)++];
    token[j] = 0;
    (*i)++;
}

void parseString(char *buffer, StringVariavel *tecnologia, int *i)
{
    char token[200];

    readToken(token, buffer, i);
    tecnologia->tamanho = strlen(token);
    if (tecnologia->tamanho > 0)
    {
        tecnologia->nome = (char *)malloc(sizeof(char) * strlen(token));
    }
    else
    {
        tecnologia->nome = (char *)malloc(sizeof(char));
    }
    strcpy(tecnologia->nome, token);
}

void parseInt(char *buffer, int *valor, int *i)
{
    char token[200];

    readToken(token, buffer, i);
    if (strlen(token) == 0)
        *valor = -1;
    else
        *valor = atoi(token);
}


void leCabecalho(char *nomeArquivo, Cabecalho *cabecalho)
{
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }

    // Ler cabecalho
    fread(&cabecalho->status, sizeof(cabecalho->status), 1, arquivo);
    fread(&cabecalho->proxRRN, sizeof(cabecalho->proxRRN), 1, arquivo);
    fread(&cabecalho->nroTecnologias, sizeof(cabecalho->nroTecnologias), 1, arquivo);
    fread(&cabecalho->nroParesTecnologias, sizeof(cabecalho->nroParesTecnologias), 1, arquivo);

    if(cabecalho->status == '0'){//verifica se o arquivo eh valido
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivo);
        exit(0);
    }
    fclose(arquivo);
}


void Verifica_se_Nulo(int int_x){
    if(int_x == -1){//se o valor do campo eh invalido, imprimir como NULO
        printf(", NULO");
    }
    else{
        printf(", %d", int_x);//caso contrario, imprimir o valor do campo
    }
}


void imprimeCampos(char *str1, int int_a, int int_b, int int_f, char *str2, int int_c) {
    printf("%s", str1);
    Verifica_se_Nulo(int_a);//essa funcao verifica se i valor do campo eh nulo
    Verifica_se_Nulo(int_b);

    if (int_f == 0) {
        printf(", NULO");
    } else {
        printf(", %s", str2);
    }

    Verifica_se_Nulo(int_c);
    printf("\n");
}
