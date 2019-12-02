
#include <stdio.h>
#include <stdlib.h>
#include "abp.h"
#include <string.h>
//codigo da Professora Renata Galante


//utiliza a ordem alfabetica para ordenar a arvore
pNodoA* InsereArvore(pNodoA *a, char palavra[tamMax]){
    //se chegou a um nodo livre, aloca memória e atribui os dados
    if (a == NULL){
        comparacoes++;
        a =  (pNodoA*) malloc(sizeof(pNodoA));
        strcpy(a->palavra, palavra);
        a->esq = NULL;
        a->dir = NULL;
        a->frequencia = 1;
        return a;
    }else if (strcmp(a->palavra, palavra) > 0){ //se não, compara usando a ordem alfabetica para decidir em qual subarvore inserir
            comparacoes++;
            a->esq = InsereArvore(a->esq,palavra);
        }else if (strcmp(a->palavra, palavra) < 0){
            comparacoes++;
            a->dir = InsereArvore(a->dir,palavra);
        }else{//se for igual, apenas atualiza a frequencia da palavra
            a->frequencia++;
        }
    return a;
}

//imprime o caminhamento pre-fixado a esquerda
void preFixado(pNodoA *a){
    if (a!= NULL){
        printf("%s\n",a->palavra);
        preFixado(a->esq);
        preFixado(a->dir);
    }
}

//imprime no arquivo passado atraves de arq, o caminhamento prefixado a direita
void preFixadoDirArq(pNodoA *a, FILE *arq){
    if (a!= NULL){
        fprintf(arq,"%s\n",a->palavra);
        preFixadoDirArq(a->dir, arq);
        preFixadoDirArq(a->esq, arq);
    }
}

//imprime o caminhamento central a direita
void Central(pNodoA *a){
    if (a!= NULL){
        Central(a->dir);
        printf("%s\n",a->palavra);
        Central(a->esq);
    }
}

//imprime o caminhamento central a direita no arquivo passado por arq
void CentralArq(pNodoA *a, FILE *arq){
    if (a!= NULL){
        CentralArq(a->dir, arq);
        fprintf(arq, "%s %d\n",a->palavra, a->frequencia);
        CentralArq(a->esq, arq);
    }
}

//Imprime o caminhamento pos fixado a esquerda
void posFixado(pNodoA *a){
    if (a!= NULL){
        posFixado(a->esq);
        posFixado(a->dir);
        printf("%s\n",a->palavra);
    }
}

//desaloca a memoria usada pela arvore
void destroi(pNodoA *a){
    //variaveis temporarias para salvar as subarvores
    pNodoA *dir = NULL;
    pNodoA *esq = NULL;
    if(a != NULL){
        dir = a->dir;
        esq = a->esq;
        free(a); //desaloca a memoria da raiz
        //chama a funcao para desalocar a memória da subarvore esquerda e direita
        destroi(dir);
        destroi(esq);
    }

}
//procura a palavra na arvore, retornando seu ponteiro
pNodoA* consultaABP(pNodoA *a, char palavra[tamMax]) {

    while (a!=NULL){
        if (strcmp(a->palavra, palavra) == 0)
            return a; //achou ent�o retorna o ponteiro para o nodo
        else if (strcmp(a->palavra, palavra) > 0)
               a = a->esq;
            else
               a = a->dir;
    }
    return NULL; //se n�o achou
}

pNodoA* consultaABP2(pNodoA *a, char palavra[tamMax]) {
    if (a!=NULL) {


       if (strcmp(a->palavra,palavra) == 0)
         return a;
       else
           if (strcmp(a->palavra, palavra) > 0)
                return consultaABP2(a->esq,palavra);
            if (strcmp(a->palavra, palavra) < 0)
                return consultaABP2(a->dir,palavra);

            else return a;
       }
       else return NULL;
}


//calcula a altura da subarvore passada por pnodo A
int altura(pNodoA* a){
    int altDir;
    int altEsq;
    if(a != NULL){
        altDir = 1 + altura(a->dir);
        altEsq = 1 + altura(a->esq);
        return (altDir > altEsq)?altDir:altEsq; //retorna a maior das alturas
    }else{
        return 0;
    }
}
//calcula o fator de uma subarvore
int fator(pNodoA* a){ 
    return (altura(a->esq) - altura(a->dir));
}
//conta o total de nodos da arvore
int contaNodos(pNodoA *a){
    if(a != NULL){
        return 1 + contaNodos(a->dir) + contaNodos(a->esq);
    }else{
        return 0;
    }
}

//dada uma palavra, retorna quantas vezes ela apareceu no texto
int frequencia(pNodoA *a, char* palavra){
    if(a == NULL){
        comparacoes++;
        return 0;
    }else{
        if(strcmp(a->palavra, palavra) == 0){ //achou a palavra procurada
            comparacoes++;
            return a->frequencia;
        }else if(strcmp(a->palavra, palavra) > 0){ //está antes no alfabeto
            comparacoes++;
            return frequencia(a->esq, palavra);
        }else{ //está depois no alfabeto
            comparacoes++;
            return frequencia(a->dir, palavra);
        }
    }
}

//insere na arvore porem usa a frequencia como parametro
pNodoA* InsereArvoreFreq(pNodoA *src, pNodoA* dest){
    //se chegou em um nodo vazio, aloca memória e atribui os dados
    if (dest == NULL){
        comparacoes++;
        dest =  (pNodoA*) malloc(sizeof(pNodoA));
        strcpy(dest->palavra, src->palavra);
        dest->esq = NULL;
        dest->dir = NULL;
        dest->frequencia = src->frequencia;
        return dest;
    }else if (src->frequencia < dest->frequencia){ //se a frequencia for menor do que a raiz, vai pra subarvore esquerda
            comparacoes++;
            dest->esq = InsereArvoreFreq(src,dest->esq);
        }else if (src->frequencia > dest->frequencia){
            comparacoes++;
            dest->dir = InsereArvoreFreq(src, dest->dir); //se a frequencia for maior do que a da raiz, vai pra subarvore direita
        }else{
            comparacoes++;
            //se for igual, analisa a ordem alfabetica pra definir em qual subarvore inserir
            if(strcmp(src->palavra, dest->palavra) < 0){
                dest->esq = InsereArvoreFreq(src, dest->esq);
            }else{
                dest->dir = InsereArvoreFreq(src, dest->dir);
            }
             
        }
    return dest;
}
//insere todos os elementos da arvore de entrada, em uma outra abp, porém
//usa a frequencia como parâmetro para ordenar a abp
pNodoA* copiaArvore(pNodoA *a, pNodoA *nova, int k1, int k2){
    if(a != NULL){
        //se a frequencia da palavra esta dentro do intervalo pedido
        //insere na nova arvore
        if(a->frequencia >= k1 && a->frequencia <= k2){
            nova = InsereArvoreFreq(a, nova); 
        }
        //chama a funcao recursivamente para buscar todas as palavras
        //cuja frequencia esta no intervalo
        nova = copiaArvore(a->esq,nova, k1, k2);
        nova = copiaArvore(a->dir, nova, k1, k2);   
        return nova;
    }
    return nova;
}

//dados dois valores, procura na arvore todas palavras que tenham frequencia entre k1 e k2
void contador(pNodoA *a, int k1, int k2, FILE *arq){
    pNodoA* arvAux = NULL;
    if(k2 < k1){
        fprintf(arq, "Intervalo Inválido. k1 deve ser menor ou igual a k2\n");
    }else{
        arvAux = copiaArvore(a,arvAux, k1, k2);
        //imprime usando o caminhamento central a esquerda para que o fique ordenada de forma
        //decrescente 
        CentralArq(arvAux, arq);
        destroi(arvAux);//desaloca a memoria usada pela arvore auxiliar
    }
}
