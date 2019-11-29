#define tamMax 100
//codigo base da professora Renata Galante

struct TNodoA{
        char palavra[tamMax];
        int frequencia;
        struct TNodoA *esq;
        struct TNodoA *dir;

};

long int comparacoes;//conta o numero de comparações

typedef struct TNodoA pNodoA;

pNodoA* InsereArvore(pNodoA *a, char palavra[tamMax] );
void preFixado(pNodoA *a);
void posFixado(pNodoA *a);
void Central(pNodoA *a);
pNodoA* consultaABP(pNodoA *a, char palavra[tamMax]);
pNodoA* consultaABP2(pNodoA *a, char palavra[tamMax]);
int altura(pNodoA *a);
int fator(pNodoA *a);

