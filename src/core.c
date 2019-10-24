#include <stdio.h>
#include "../includes/core.h"
#include <stdlib.h>
#include <string.h>

#define SIZE 500

void printAllInformations(int N, int M, int *custos, int *pontuacoes) {
    printf("\nValor total a ser gasto: %d", N);
    printf("\nNúmero total de ilhas: %d", M);
    printf("\nCustos:\n");
    for (int i = 0; i < M; i++) {
        printf("%d\t%d\n", custos[i], pontuacoes[i]);
    }
}

void initProgram (FILE *file) {
    // Leitura de dados

    // Variaveis com as informações informação:
    // N -> valor máximo a ser gasto
    // M -> número de ilhas
    int N, M, *custos, *pontuacoes;

    int charCtrl = 0, infoCtrl = 0;
    char linhaAlfanumerica[SIZE], *info;

    // Extração de informações:

    while(fscanf(file, "%s", linhaAlfanumerica) != EOF) {
        info = strtok(linhaAlfanumerica, " ");
        while (info != NULL) {
            if (charCtrl == 0) { // Valor máximo a ser gasto
                N = atoi(info);
                if (!N) { return; }
            }
            else if (charCtrl == 1) { // Númemro de ilhas
                M = atoi(info);
                if (!M) { return; }
                custos = (int*)calloc(M, sizeof(int));
                pontuacoes = (int*)calloc(M, sizeof(int));
            }
            else if (charCtrl > 1) { // Custos e pontuações
                if (charCtrl % 2 == 0) { // Custo da i-esima ilha
                    custos[infoCtrl] = atoi(info);
                } else { // Pontuação da i-esima ilha
                    pontuacoes[infoCtrl] = atoi(info);
                    infoCtrl++;
                }
            }
            charCtrl++;
            info = strtok(NULL, " ");
        }

    }

    // --------------------------------------------------------------------------------------------------------------- // 
    printAllInformations(N, M, custos, pontuacoes);


    // TODO: criar um array de struct para armazenar as informações de cada ilha (tanto o preço quanto a pontuação)

    initGreedSoluction(N, M, custos, pontuacoes);

    free(custos);
    free(pontuacoes);
}