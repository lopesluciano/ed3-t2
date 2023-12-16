/**
 * Caroline Severiano Clapis    | NUSP: 13861923
 * Luciano Goncalves Lopes Filho | NUSP: 13676520 
 */

#include "Funcionalidades.h"

//Funcionalidades fornecidas em trabalhos anteriores

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





