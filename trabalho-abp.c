#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"

#define numMax 9
/* Exemplo de uso dos argumentos para main
O programa l� um arquivo texto como entrada e gera um arquivo como sa�da com o conte�do do arquivo de entrada convertido para letras mai�sculas
Para chamar, digite "exemplo entrada.txt saida.txt" */




int main(int argc, char *argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados


    FILE * entrada;
    FILE  *operacoes;
    FILE * saida;
    int freq = 0; //armazena o calcula da frequencia de uma determinada palavra
    int parametros[2] = {0};
    char *palavra, linha[1000]; // linhas a serem lidas do arquivo
    char separador[]= {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};
    pNodoA *arvore = NULL;
    time_t inicio;//armazena o tempo de quando o programa começou a rodar
    time_t final; //armazena o tempo de quando o programa terminou de rodar
    char astericos[] = {"**************************\n"};
    //gettimeofday(&inicio, NULL);
    if (argc!=4)  //o numero de parametros esperado � 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arquivo de operações(argv[2]),nome do arq de saida(argv[3])
    {
        printf ("N�mero incorreto de par�metros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
        return 1;
    }
    else
    {

        entrada = fopen (argv[1], "r"); // abre o arquivo para leitura -- argv[1] � o primeiro par�metro ap�s o nome do arquivo.
        if (entrada == NULL) //se n�o conseguiu abrir o arquivo
        {
            printf ("Erro ao abrir o arquivo %s",argv[1]);
            return 1;
        }
        operacoes = fopen(argv[2], "r");
        if(operacoes == NULL){
            printf("Erro ao abrir o arquivo de operações: %s\n", argv[2]);
            return 1;
        }
        else // arquivo de entrada OK

        {
            saida = fopen (argv[3], "w"); // abre o arquivo para saida -- argv[2] � o segundo par�metro ap�s o nome do arquivo.

            //percorre todo o arquivo lendo linha por linha

            comparacoes = 0; //zera as comparações
            

            while (fgets(linha,1000,entrada))
            {
                inicio = time(&inicio);
                palavra = strtok (linha, separador); //considera qquer caractere n�o alfab�tico como separador
                while (palavra != NULL)
                {
                    //fprintf(saida,"%s ", strlwr(palavra)); //strlwr � a fun��o que converte palavras para min�sculo
                    arvore = InsereArvore(arvore, strlwr(palavra));
                    palavra = strtok (NULL, separador);
                }
                
            }
            
            fprintf(saida, "***************** Estatísticas Estutura Carregada *****************\n");
            fprintf(saida, "Número de Comparações: %d\n", comparacoes); //coloca as estatisticas do carregamento da estrutura no arquivo de saida
            fprintf(saida,"A altura da arvore é: %d\n", altura(arvore));
            fprintf(saida,"O Fator da arvore é de: %d\n", fator(arvore));
            final = time(&final);
            fprintf(saida,"Tempo: %fs\n", difftime(final, inicio));
            fprintf(saida,"O numero de rotações necessário foi 0\n"); //como é ABP nao tem rotações
            fprintf(saida,"O numero total de nodos foi: %d\n", contaNodos(arvore));
            fprintf(saida, "\n\n");
            fprintf(saida, "***************** Estatísticas Operações *****************\n");

            while(fgets(linha, 1000, operacoes)){
                comparacoes = 0; //zera as comparacoes para contar a da proxima operação
                parametros[0] = 0;
                parametros[1] = 0;
                palavra = strtok(linha, separador);
                
                if(strcmp(strlwr(palavra), "c") == 0){
                    //le os parametros da funcao contador
                    fprintf(saida, "C ");
                    parametros[0] = atoi(strtok(NULL, separador));
                    parametros[1] = atoi(strtok(NULL, separador));
                    fprintf(saida, "%d %d \n", parametros[0],parametros[1]);
                    contador(arvore, parametros[0], parametros[1], saida);
                    fprintf(saida, "Comparações: %li\n", comparacoes);
                    fprintf(saida,"\n");
                }else if(strcmp(strlwr(palavra), "f") == 0){
                    //le a palavra que servira de parametro pra funcao frequencia
                    palavra = strtok(NULL, separador);
                    freq = frequencia(arvore, palavra);
                    fprintf(saida, "F ");
                    fprintf(saida, palavra);
                    fprintf(saida, "\n");
                    fprintf(saida, "%s: %d ocorrências.\n", palavra, freq);
                    fprintf(saida, "Comparações: %li\n", comparacoes);
                    fprintf(saida,"\n");
                    
                }
                fprintf(saida, astericos);
            }
            printf("\nArquivo %s gerado com sucesso.\n",argv[3]);
            final = time(&final);
            fprintf(saida, "Tempo: %fs\n", difftime(final,inicio));
            destroi(arvore);
            
        }
        fclose (entrada); //fecha os arquivos
        fclose(operacoes);
        fclose (saida);
        return 0;
    }
}
