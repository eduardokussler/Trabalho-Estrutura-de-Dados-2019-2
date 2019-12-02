#define tamMax 100//tamanho maxima da string
//codigo base da professora Renata Galante

struct TNodoA{
        char palavra[tamMax];
        int frequencia; //frequencia da palavra no texto
        struct TNodoA *esq; //subarvore esquerda
        struct TNodoA *dir; //subarvore direita

};

long int comparacoes;//conta o numero de comparações. Deve ser zerado antes de uma nova operação

typedef struct TNodoA pNodoA;
//insere a palavra no arquivo, usando a ordem alfabetica para ordenar a ABP
pNodoA* InsereArvore(pNodoA *a, char palavra[tamMax] );

//imprime o caminhamento preFixado a esquerda
void preFixado(pNodoA *a);

//imprime o caminhameto posFixado a direita
void posFixado(pNodoA *a);

//imprime o caminhamento central a esquerda
void Central(pNodoA *a);

pNodoA* consultaABP(pNodoA *a, char palavra[tamMax]);
pNodoA* consultaABP2(pNodoA *a, char palavra[tamMax]);

//Calcula a altura da subarvore a partir da raiz fornecidaa
int altura(pNodoA *a);

//Calula o fator de desbalanceamento alt_esq - alt_dir
int fator(pNodoA *a);

//Conta o total de nodos da arvore
int contaNodos(pNodoA *a);


//Dada uma palavra, procura e retorna a frequencia da palavra
int frequencia(pNodoA *a, char* palavra);

//desaloca a memória utilizada pela arvore
void destroi(pNodoA *a);

//Imprime todas a palvras com frequencias entre k1 e k2, de forma decrescente
void contador(pNodoA *a, int k1, int k2, FILE* arq);

