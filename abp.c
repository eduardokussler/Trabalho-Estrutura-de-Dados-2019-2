
#include <stdio.h>
#include <stdlib.h>
#include "abp.h"
#include <string.h>
//codigo da Professora Renata Galante


pNodoA* InsereArvore(pNodoA *a, char palavra[tamMax])
{
     if (a == NULL)
     {
         comparacoes++;
         a =  (pNodoA*) malloc(sizeof(pNodoA));
         strcpy(a->palavra, palavra);
         a->esq = NULL;
         a->dir = NULL;
         a->frequencia = 1;
         return a;
     }
     else
          if (strcmp(a->palavra, palavra) > 0){
              comparacoes++;
              a->esq = InsereArvore(a->esq,palavra);
          }
          else if (strcmp(a->palavra, palavra) < 0){
              comparacoes++;
              a->dir = InsereArvore(a->dir,palavra);
          }else{
              a->frequencia++;
          }
     return a;
}

void preFixado(pNodoA *a)
{
     if (a!= NULL)
     {
          printf("%s\n",a->palavra);
          preFixado(a->esq);
          preFixado(a->dir);
      }
}

void Central(pNodoA *a)
{
     if (a!= NULL)
     {
          Central(a->dir);
          printf("%s\n",a->palavra);
          Central(a->esq);
      }
}
void CentralArq(pNodoA *a, FILE *arq)
{
     if (a!= NULL)
     {
          CentralArq(a->dir, arq);
          fprintf(arq, "%s\n",a->palavra);
          CentralArq(a->esq, arq);
      }
}

void posFixado(pNodoA *a)
{
     if (a!= NULL)
     {
          posFixado(a->esq);
          posFixado(a->dir);
          printf("%s\n",a->palavra);
      }
}

//desaloca a memoria usada pela arvore
void destroi(pNodoA *a){
    pNodoA *dir = NULL;
    pNodoA *esq = NULL;
    if(a != NULL){
        dir = a->dir;
        esq = a->esq;
        free(a);
        destroi(dir);
        destroi(esq);
    }

}

pNodoA* consultaABP(pNodoA *a, char palavra[tamMax]) {

    while (a!=NULL){
          if (strcmp(a->palavra, palavra) == 0)
             return a; //achou ent�o retorna o ponteiro para o nodo
          else
            if (strcmp(a->palavra, palavra) > 0)
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

int altura(pNodoA* a){
    int altDir = 0;
    int altEsq = 0;
    if(a != NULL){
        altDir = 1 + altura(a->dir);
        altEsq = 1 + altura(a->esq);
        return (altDir > altEsq)?altDir:altEsq;
    }else{
        return 0;
    }
}
//calcula o fator de uma subarvore
int fator(pNodoA* a){ 
    return (altura(a->esq)-altura(a->dir));
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
        return -1;
    }else{
        if(strcmp(a->palavra, palavra) == 0){
            comparacoes++;
            return a->frequencia;
        }else if(strcmp(a->palavra, palavra) > 0){
            comparacoes++;
            return frequencia(a->esq, palavra);
        }else{
            comparacoes++;
            return frequencia(a->dir, palavra);
        }
    }
}

//insere na arvore porem usa a frequencia como parametro
pNodoA* InsereArvoreFreq(pNodoA *src, pNodoA* dest)
{
     if (dest == NULL)
     {
         comparacoes++;
         dest =  (pNodoA*) malloc(sizeof(pNodoA));
         strcpy(dest->palavra, src->palavra);
         dest->esq = NULL;
         dest->dir = NULL;
         dest->frequencia = src->frequencia;
         return dest;
     }
     else
          if (src->frequencia < dest->frequencia){
              comparacoes++;
              dest->esq = InsereArvoreFreq(src,dest->esq);
          }
          else if (src->frequencia > dest->frequencia){
              comparacoes++;
              dest->dir = InsereArvoreFreq(src, dest->dir);
          }else{
              comparacoes++;
              if(strcmp(src->palavra, dest->palavra) < 0){
                  dest->esq = InsereArvoreFreq(src, dest->esq);
              }else{
                  dest->dir = InsereArvoreFreq(src, dest->dir);
              }
             
          }
     return dest;
}
//insere todos os elementos da arvore de entrada, na arvore de saída, porém
//usa a frequencia como parâmetro para ordenar a abp
pNodoA* copiaArvore(pNodoA *a, pNodoA *nova, int k1, int k2){
    if(a != NULL){
        if(a->frequencia >= k1 && a->frequencia <= k2){
            nova = InsereArvoreFreq(a, nova);
        }
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
        fprintf(arq, "Intervalo Inválido. k1 deve ser menor ou igual a k2");
    }else{
        arvAux = copiaArvore(a,arvAux, k1, k2);

        CentralArq(arvAux, arq);
    }
}
