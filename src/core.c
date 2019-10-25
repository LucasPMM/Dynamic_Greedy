#include <stdio.h>
#include "../includes/core.h"
#include <stdlib.h>
#include <string.h>

#define SIZE 500

void printAllInformations(int N, int M, int *costs, int *pontuations) {
    printf("\nValor total a ser gasto: %d", N);
    printf("\nNúmero total de ilhas: %d", M);
    printf("\nCustos:\n");
    for (int i = 0; i < M; i++) {
        printf("%d\t%d\n", costs[i], pontuations[i]);
    }
}

void initProgram (FILE *file) {
    // Leitura de dados

    // Variaveis com as informações informação:
    // N -> valor máximo a ser gasto
    // M -> número de ilhas
    int N, M, *costs, *pontuations;

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
                costs = (int*)calloc(M, sizeof(int));
                pontuations = (int*)calloc(M, sizeof(int));
            }
            else if (charCtrl > 1) { // custos e pontuações
                if (charCtrl % 2 == 0) { // Custo da i-esima ilha
                    costs[infoCtrl] = atoi(info);
                } else { // Pontuação da i-esima ilha
                    pontuations[infoCtrl] = atoi(info);
                    infoCtrl++;
                }
            }
            charCtrl++;
            info = strtok(NULL, " ");
        }

    }

    // --------------------------------------------------------------------------------------------------------------- // 
    printAllInformations(N, M, costs, pontuations);

    initGreedSoluction(N, M, costs, pontuations);

    free(costs);
    free(pontuations);
}