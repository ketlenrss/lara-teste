#ifndef CIDADES_H 
#define CIDADES_H 
 
typedef struct { 
    char Nome[256];     // Nome do cidade 
    int Posicao;        // PosiÃ§Ã£o da cidade 
} Cidade; 
 
typedef struct { 
    int N;              // NÃºmero de cidades 
    int T;              // Comprimento da estrada 
    Cidade *C;          // Vetor de cidades 
} Estrada; 
 
Estrada *getEstrada(const char *nomeArquivo);               // Inicializa cidades no TAD indicado acima. 
double calcularMenorVizinhanca(const char *nomeArquivo);    // Retorna a menor vizinhanÃ§a. 
char *cidadeMenorVizinhanca(const char *nomeArquivo);   // Retorna a cidade que tem menor vizinhanÃ§a. 
 
#endif 
