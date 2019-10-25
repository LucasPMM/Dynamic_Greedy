#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/core.h"

#define SIZE 500

// ---------------------------- Init Dynamic Solution ---------------------------- //

int max(int a, int b) { return (a > b) ? a : b; }

void knapSack(int **K, int W, int wt[], int val[], int n, Island *islands, int *daysDynamic, int *pontuationDynamic) {
    int i, j, w;

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            } else if (wt[i - 1] <= w) {
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

	i = n;
	j = W;
    int days = 0;
	while(i >= 1) {
		if(K[i][j] != K[i-1][j]) {
			days++;
			j = j - islands[i-1].cost;
		}
		i--;
	}

    *daysDynamic = days;
    *pontuationDynamic = K[n][W];
}

void initDynamicSolution(Island *islands, int N, int M, int *costs, int *pontuations, int *daysDynamic, int *pontuationDynamic) {
    int i;
    // Allocate matrix
    int **K = (int**)calloc(M + 1, sizeof(int*)); 
    for (i = 0; i < M + 1; i++) 
        K[i] = (int*)calloc(N + 1, sizeof(int)); 

    knapSack(K, N, costs, pontuations, M, islands, daysDynamic, pontuationDynamic);

    // Free matrix
    for (i = 0; i < M + 1; i++) {
        free(K[i]);
    }
    free(K);
}

// ---------------------------- Finish Dynamic Solution ---------------------------- //

// ------------------------------ Init Greedy Solution ----------------------------- //

void merge(Island *arr, int l, int m, int r) { 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m; 

	Island L[n1], R[n2]; 

	for (i = 0; i < n1; i++) { L[i] = arr[l + i]; }
	for (j = 0; j < n2; j++) { R[j] = arr[m + 1+ j]; }

	i = 0; 
	j = 0; 
	k = l; 
	while (i < n1 && j < n2) { 
		if (L[i].custoPerPontuation <= R[j].custoPerPontuation) { 
			arr[k] = L[i]; 
			i++; 
		} 
		else { 
			arr[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 

	while (i < n1) { 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 

	while (j < n2) { 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 

void mergeSort(Island *arr, int l, int r) { 
	if (l < r) { 
		int m = l+(r-l)/2; 
		mergeSort(arr, l, m); 
		mergeSort(arr, m+1, r); 
		merge(arr, l, m, r); 
	} 
} 

void calcTripInformations(Island *islands, int budget, int numberOfIslands, int *daysGreedy, int *pontuationsGreedy) {
    int pontuation = 0, days = 0, spent = 0, i;

    for (i = 0; i < numberOfIslands; i++) {
        int dayQtd = (budget - spent) / islands[i].cost;
        days += dayQtd;
        pontuation += islands[i].pontuation * dayQtd;
        spent += islands[i].cost * dayQtd;
    }

    *daysGreedy = days;
    *pontuationsGreedy = pontuation; 
}

void initGreedSolution(Island *islands, int N, int M, int *costs, int *pontuations, int *daysGreedy, int *pontuationGreedy) {
	mergeSort(islands, 0, M - 1); 
    calcTripInformations(islands, N, M, daysGreedy, pontuationGreedy);
} 

// ---------------------------- Finish Greedy Solution ---------------------------- //

void fillObject(Island *islands, int *costs, int *pontuations, int size) {
    int i;
    for (i = 0; i < size; i++) {
        islands[i].cost = costs[i];
        islands[i].pontuation = pontuations[i];
        islands[i].custoPerPontuation = (double)costs[i] / (double)pontuations[i];
    }
}

void initProgram (FILE *file) {
    // Read data:

    // N -> Max value to spend
    // M -> Number of islands
    int N, M, *costs, *pontuations;

    int charCtrl = 0, infoCtrl = 0;
    char linhaAlfanumerica[SIZE], *info;

    // Extract informations:

    while(fscanf(file, "%s", linhaAlfanumerica) != EOF) {
        info = strtok(linhaAlfanumerica, " ");
        while (info != NULL) {
            if (charCtrl == 0) { // Max value to spend
                N = atoi(info);
                if (!N) { return; }
            }
            else if (charCtrl == 1) { // Númemro de ilhas
                M = atoi(info);
                if (!M) { return; }
                costs = (int*)calloc(M, sizeof(int));
                pontuations = (int*)calloc(M, sizeof(int));
            }
            else if (charCtrl > 1) { // costs and pontuations
                if (charCtrl % 2 == 0) { // Cost of i-esima island
                    costs[infoCtrl] = atoi(info);
                } else { // Pontuation of i-esima island
                    pontuations[infoCtrl] = atoi(info);
                    infoCtrl++;
                }
            }
            charCtrl++;
            info = strtok(NULL, " ");
        }

    }

    // Fill structures and find solutions

    int daysGreedy, pontuationGreedy;
    int daysDynamic, pontuationDynamic;

    Island *islands;
    islands = (Island*)calloc(M, sizeof(Island));
    fillObject(islands, costs, pontuations, M);

    initDynamicSolution(islands, N, M, costs, pontuations, &daysDynamic, &pontuationDynamic);
    initGreedSolution(islands, N, M, costs, pontuations, &daysGreedy, &pontuationGreedy);

    printf("%d %d\n", pontuationGreedy, daysGreedy);
    printf("%d %d\n", pontuationDynamic, daysDynamic);

    // Free memory
    free(costs);
    free(pontuations);
    free(islands);
}
