
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
          Central(a->esq);
          printf("%s\n",a->palavra);
          Central(a->dir);
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

int fator(pNodoA* a){
    return (altura(a->esq)-altura(a->dir));
}

int contaNodos(pNodoA *a){
    if(a != NULL){
        return 1 + contaNodos(a->dir) + contaNodos(a->esq);
    }else{
        return 0;
    }
}


int frequencia(pNodoA *a, char* palavra){
    if(a == NULL){
        return -1;
    }else{
        if(strcmp(a->palavra, palavra) == 0){
            return a->frequencia;
        }else if(strcmp(a->palavra, palavra) > 0){
            return frequencia(a->esq, palavra);
        }else{
            return frequencia(a->dir, palavra);
        }
    }
}

int contador(pNodoA *a, int k1, int k2){

}
