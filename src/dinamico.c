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

void knapSack(int **K, int W, int wt[], int val[], int n, DynamicIsland *islands) {
    int i, j, w;

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

	i = n;
	j = W;
    int days = 0;
	while(i >= 1) {
		if(K[i][j] != K[i-1][j]) {
			days++;
			j = (int)(j-islands[i-1].cost);
		}
		i--;
	}

    printf("%d %d\n", K[n][W], days);
}

void fillObjectDynamic(DynamicIsland *islands, int *costs, int *pontuations, int size) {
    int i;
    for (i = 0; i < size; i++) {
        islands[i].cost = costs[i];
        islands[i].pontuation = pontuations[i];
        islands[i].custoPerPontuation = (double)costs[i] / (double)pontuations[i];
    }
}

void initDynamicSoluction(int N, int M, int *costs, int *pontuations) {
    int i;
    int **K = (int**)calloc(M + 1, sizeof(int*)); 
    for (i = 0; i < M + 1; i++) 
        K[i] = (int*)calloc(N + 1, sizeof(int)); 

    DynamicIsland *islands;
    islands = (DynamicIsland*)calloc(M, sizeof(DynamicIsland));
    fillObjectDynamic(islands, costs, pontuations, M);

    knapSack(K, N, costs, pontuations, M, islands);

    for (i = 0; i < M; i++) {
        free(K[i]);
    }
    free(K);
}
