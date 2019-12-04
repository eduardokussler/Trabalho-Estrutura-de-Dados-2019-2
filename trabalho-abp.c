#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"

#define conversaoClocksMs 1000
#define numMax 9
/* Exemplo de uso dos argumentos para main
O programa l� um arquivo texto como entrada e gera um arquivo como sa�da com o conte�do do arquivo de entrada convertido para letras mai�sculas
Para chamar, digite "exemplo entrada.txt saida.txt" */



//argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
int main(int argc, char *argv[]) {
    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados


    FILE * entrada;
    FILE  *operacoes;
    FILE * saida;
    int freq = 0; //armazena o calcula da frequencia de uma determinada palavra
    int parametros[2] = {0};
    char *palavra, linha[1000]; // linhas a serem lidas do arquivo
    char separador[]= {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};
    pNodoA *arvore = NULL;
    clock_t inicio, final; //armazena o numero de clocks
    //time_t inicio;//armazena o tempo de quando o programa começou a rodar
    //time_t final; //armazena o tempo de quando o programa terminou de rodar
    double tempo = 0;
    char astericos[] = {"**************************\n"};
    inicio = clock();
    //o numero de parametros esperado � 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arquivo de operações(argv[2]),nome do arq de saida(argv[3])
    if (argc!=4) {
        printf ("Número incorreto de parâmetros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
        return 1;
    }else{

        entrada = fopen (argv[1], "r"); // abre o arquivo para leitura -- argv[1] � o primeiro par�metro ap�s o nome do arquivo.
         //se n�o conseguiu abrir o arquivo
        if (entrada == NULL){
            printf ("Erro ao abrir o arquivo %s",argv[1]);
            return 1;
        }
        operacoes = fopen(argv[2], "r");
        if(operacoes == NULL){//se não conseguiu abrir o arquivo com as operações
            printf("Erro ao abrir o arquivo de operações: %s\n", argv[2]);
            return 1;
        }else{// arquivo de entrada OK
            saida = fopen (argv[3], "w"); // abre o arquivo para saida -- argv[2] � o segundo par�metro ap�s o nome do arquivo.

            //percorre todo o arquivo lendo linha por linha

            comparacoes = 0; //zera as comparações
            //inicio = time(&inicio);

            while (fgets(linha,1000,entrada)){
                //considera qquer caractere n�o alfab�tico como separador
                palavra = strtok (linha, separador); 
                while (palavra != NULL){
                    //fprintf(saida,"%s ", strlwr(palavra)); //strlwr � a fun��o que converte palavras para min�sculo
                    arvore = InsereArvore(arvore, strlwr(palavra));//coloca a palavra lida para minusculas e insere na arvore
                    palavra = strtok (NULL, separador);// separa a proxima palavra
                }
                
            }
            
            fprintf(saida, "***************** Estatísticas Estutura Carregada ABP*****************\n");
            fprintf(saida, "Número de Comparações: %d\n", comparacoes); //coloca as estatisticas do carregamento da estrutura no arquivo de saida
            fprintf(saida,"A altura da arvore é: %d\n", altura(arvore));
            fprintf(saida,"O Fator da arvore é de: %d\n", fatorABP(arvore));
            //final = time(&final);
            //tempo = difftime(final, inicio);
            //tempo *= 1000;
            //calcula o tempo decorrido desde o início do programa;
            final = clock();
            tempo = ((double)(final - inicio)) / CLOCKS_PER_SEC; //clk_per_sec é uma constante com o numero de clocks por segundo
            tempo *= conversaoClocksMs;
            fprintf(saida,"Tempo: %.6fms\n", tempo);
            fprintf(saida,"O numero de rotações necessário foi: 0\n"); //como é ABP nao tem rotações
            fprintf(saida,"O numero total de nodos foi: %d\n", contaNodos(arvore));
            fprintf(saida, "\n\n");
            fprintf(saida, "***************** Estatísticas Operações *****************\n");
			
			inicio = clock();
			comparacoes = 0;
			
            while(fgets(linha, 1000, operacoes)){ //le uma linha do arquivo de operacoes
                //comparacoes = 0; //zera as comparacoes para contar a da proxima operação
                parametros[0] = 0;
                parametros[1] = 0;
                palavra = strtok(linha, separador);
                
                if(strcmp(strlwr(palavra), "c") == 0){ //testa se a operacao é contador
                    //le os parametros da funcao contador
                    fprintf(saida, "C ");
                    parametros[0] = atoi(strtok(NULL, separador)); //le o primeiro parametro, limite inferior
                    parametros[1] = atoi(strtok(NULL, separador)); //le o segundo parametro, limite superior
                    fprintf(saida, "%d %d \n", parametros[0],parametros[1]);//escreve os limites usados no arquivo de saída
                    contador(arvore, parametros[0], parametros[1], saida);
                    //fprintf(saida, "Comparações: %li\n", comparacoes);//imprime o numero de comparaçoes no arquivo de saida
                    fprintf(saida,"\n");
                }else if(strcmp(strlwr(palavra), "f") == 0){//testa se a operacao é frequencia
                    //le a palavra que servira de parametro pra funcao frequencia
                    palavra = strtok(NULL, separador); //busca a palavra que é o parâmetro da função
                    freq = frequencia(arvore, palavra);
                    //imprime as informações no arquivo
                    fprintf(saida, "F ");
                    fprintf(saida, palavra);
                    fprintf(saida, "\n");
                    fprintf(saida, "%s: %d ocorrências.\n", palavra, freq);
                    //fprintf(saida, "Comparações: %li\n", comparacoes);
                    fprintf(saida,"\n");
                    
                }
                fprintf(saida, astericos);//imprime uma linha de asteriscos para indicar que uma operação foi concluída
            }
            printf("\nArquivo %s gerado com sucesso.\n",argv[3]);
            //final = time(&final);
            //tempo = difftime(final, inicio);
            //tempo *= 1000;
            //calcula o tempo total decorrido desde o inicio do programa
            final = clock();
            tempo = ((double)(final - inicio)) / CLOCKS_PER_SEC;
            tempo *= conversaoClocksMs;
            fprintf(saida, "Tempo: %.6fms\n", tempo);
			fprintf(saida, "Comparações %d\n", comparacoes);
            destroi(arvore); //desaloca a memória
            
        }
        fclose (entrada); //fecha os arquivos
        fclose(operacoes);
        fclose (saida);
        return 0;
    }
}
