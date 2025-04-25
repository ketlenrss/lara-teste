#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// FunÃ§Ã£o auxiliar para comparar as posiÃ§Ãµes das cidades (necessÃ¡ria para a ordenaÃ§Ã£o)
int compararCidades(const void *a, const void *b) {
    Cidade *c1 = (Cidade *)a;
    Cidade *c2 = (Cidade *)b;
    return c1->Posicao - c2->Posicao;
}

// FunÃ§Ã£o que lÃª os dados do arquivo e retorna a estrutura Estrada
Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) return NULL;

    // Leitura do tamanho da estrada e nÃºmero de cidades
    int T, N;
    if (fscanf(arquivo, "%d", &T) != 1 || T < 3 || T > 1000000) {
        fclose(arquivo);
        return NULL;
    }

    if (fscanf(arquivo, "%d", &N) != 1 || N < 2 || N > 10000) {
        fclose(arquivo);
        return NULL;
    }

    // AlocaÃ§Ã£o da estrutura Estrada
    Estrada *estrada = malloc(sizeof(Estrada));
    if (!estrada) {
        fclose(arquivo);
        return NULL;
    }

    estrada->T = T;
    estrada->N = N;
    estrada->C = malloc(sizeof(Cidade) * N);
    if (!estrada->C) {
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    int *posicoes = malloc(sizeof(int) * N);
    if (!posicoes) {
        free(estrada->C);
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    // Leitura das cidades e verificaÃ§Ã£o da validade dos dados
    for (int i = 0; i < N; i++) {
        if (fscanf(arquivo, "%d %255s", &estrada->C[i].Posicao, estrada->C[i].Nome) != 2) {
            free(posicoes);
            free(estrada->C);
            free(estrada);
            fclose(arquivo);
            return NULL;
        }

        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= T) {
            free(posicoes);
            free(estrada->C);
            free(estrada);
            fclose(arquivo);
            return NULL;
        }

        // Verifica se a posiÃ§Ã£o da cidade jÃ¡ foi utilizada
        for (int j = 0; j < i; j++) {
            if (estrada->C[i].Posicao == posicoes[j]) {
                free(posicoes);
                free(estrada->C);
                free(estrada);
                fclose(arquivo);
                return NULL;
            }
        }
        posicoes[i] = estrada->C[i].Posicao;
    }

    // Ordena as cidades pela posiÃ§Ã£o
    qsort(estrada->C, estrada->N, sizeof(Cidade), compararCidades);

    free(posicoes);
    fclose(arquivo);
    return estrada;
}

// FunÃ§Ã£o para calcular a menor vizinhanÃ§a (distÃ¢ncia) entre as cidades
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return -1;

    double menorVizinhanca = estrada->T;

    for (int i = 0; i < estrada->N; i++) {
        double inicio, fim;

        if (i == 0)
            inicio = 0;
        else
            inicio = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;

        if (i == estrada->N - 1)
            fim = estrada->T;
        else
            fim = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;

        double vizinhanca = fim - inicio;
        if (vizinhanca < menorVizinhanca)
            menorVizinhanca = vizinhanca;
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

// FunÃ§Ã£o que retorna o nome da cidade com a menor vizinhanÃ§a
char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return NULL;

    double menorVizinhanca = estrada->T;
    int indiceMenor = -1;

    for (int i = 0; i < estrada->N; i++) {
        double inicio, fim;

        if (i == 0)
            inicio = 0;
        else
            inicio = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;

        if (i == estrada->N - 1)
            fim = estrada->T;
        else
            fim = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;

        double vizinhanca = fim - inicio;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            indiceMenor = i;
        }
    }

    char *nome = malloc(strlen(estrada->C[indiceMenor].Nome) + 1);
    if (nome)
        strcpy(nome, estrada->C[indiceMenor].Nome);

    free(estrada->C);
    free(estrada);
    return nome;
}
