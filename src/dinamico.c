#include <stdlib.h>
#include <stdio.h>
#include "../includes/dinamico.h"

int max(int a, int b) { return (a > b) ? a : b; }

void printMatrix(int **mat, int m, int n) {
    int i, j;
    printf("\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int knapSack(int **K, int W, int wt[], int val[], int n) {
    int i, w;

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    return K[n][W];
}

void initDynamicSoluction(int N, int M, int *costs, int *pontuations) {
    int i;
    int **K = (int**)calloc(M + 1, sizeof(int*)); 
    for (i = 0; i < M + 1; i++) 
        K[i] = (int*)calloc(N + 1, sizeof(int)); 

    printf("\nsolução knapSack %d\n", knapSack(K, N, costs, pontuations, M));

    // TODO: calcular o número de dias.
    // printMatrix(K, M + 1, N + 1);
}
