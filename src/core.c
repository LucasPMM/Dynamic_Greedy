#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/core.h"
#include <time.h>
#include <math.h>

#define N_TESTS 20
#define SIZE 500

// ---------------------------- Init Dynamic Solution ---------------------------- //

void calcDynamicTripInformations(int **K, int budget, int *costs, int *pontuations, int numberOfIslands, Island *islands, int *daysDynamic, int *pontuationDynamic) {
    int i, j, w;

    // Mount the matrix of opt values
    for (i = 0; i <= numberOfIslands; i++) {
        for (w = 0; w <= budget; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            } else if (costs[i - 1] <= w) {
                if (pontuations[i - 1] + K[i - 1][w - costs[i - 1]] > K[i - 1][w]) {
                    K[i][w] = pontuations[i - 1] + K[i - 1][w - costs[i - 1]];
                } else {
                    K[i][w] = K[i - 1][w];
                }
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    // Find the number of days of the trip using backtracking:
	i = numberOfIslands;
	j = budget;
    int days = 0;
	while(i >= 1) {
		if(K[i][j] != K[i-1][j]) {
			days++;
			j = j - islands[i-1].cost;
		}
		i--;
	}

    *daysDynamic = days;
    *pontuationDynamic = K[numberOfIslands][budget];
}

void initDynamicSolution(Island *islands, int N, int M, int *costs, int *pontuations, int *daysDynamic, int *pontuationDynamic) {
    int i;
    // Allocate matrix
    int **K = (int**)calloc(M + 1, sizeof(int*)); 
    for (i = 0; i < M + 1; i++) 
        K[i] = (int*)calloc(N + 1, sizeof(int)); 

    calcDynamicTripInformations(K, N, costs, pontuations, M, islands, daysDynamic, pontuationDynamic);

    // Free matrix
    for (i = 0; i < M + 1; i++) {
        free(K[i]);
    }
    free(K);
}

// ---------------------------- Finish Dynamic Solution ---------------------------- //

// ------------------------------ Init Greedy Solution ----------------------------- //

// Code developed from the data structure discipline material
void merge(Island *islands, int l, int m, int r) { 
	int i, j, k, arr1Ctrl = m - l + 1, arr2Ctlr = r - m;
	Island L[arr1Ctrl], R[arr2Ctlr];

	for (i = 0; i < arr1Ctrl; i++) { L[i] = islands[l + i]; }
	for (j = 0; j < arr2Ctlr; j++) { R[j] = islands[m + 1 + j]; }

	i = 0;
	j = 0;
	k = l;

	while (i < arr1Ctrl && j < arr2Ctlr) {
		if (L[i].custoPerPontuation <= R[j].custoPerPontuation) {
			islands[k] = L[i];
			i++;
		}
		else {
			islands[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < arr1Ctrl) {
		islands[k] = L[i];
		i++;
		k++;
	}

	while (j < arr2Ctlr) {
		islands[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(Island *arr, int l, int r) { 
	if (l < r) { 
		int m = l + (r - l) / 2; 
		mergeSort(arr, l, m); 
		mergeSort(arr, m + 1, r); 
		merge(arr, l, m, r); 
	} 
} 

void calcGreedyTripInformations(Island *islands, int budget, int numberOfIslands, int *daysGreedy, int *pontuationsGreedy) {
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
    calcGreedyTripInformations(islands, N, M, daysGreedy, pontuationGreedy);
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

void calcAndSaveTests(double *time, int N) {
    int i;
    double sum = 0.0, average, sd;

    // Calc average
    for (i = 0; i < N_TESTS; i++) {
        sum += time[i];
    }
    average = sum / N_TESTS;

    sum = 0.0;
    // Calc standard deviation
    for (i = 0; i < N_TESTS; i++) {
        double sub = fabs(time[i] - average);
        sum += pow(sub, 2);
    }
    sd = sqrt(sum / (N_TESTS - 1));

    // Save data on file:
    FILE *file = fopen("../tests/out-greedy.txt", "a+");
    // FILE *file = fopen("../tests/out-dynamic.txt", "a+");
    fprintf (file, "Número de ilhas %d - Média: %f - Desvio Padrão: %lf\n", N, average, sd);
    fclose(file);
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
                // if (!N) { return; }
            }
            else if (charCtrl == 1) { // Number of islands
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

    // Algorithm to calc time execution: 
    // double executionTime[N_TESTS];
    // int clk = 0;
    // for (clk = 0; clk < N_TESTS; clk++) {
    //     clock_t tempoInicial;
    //     clock_t tempoFinal;
    //     tempoInicial = clock();


        Island *islands;
        islands = (Island*)calloc(M, sizeof(Island));
        fillObject(islands, costs, pontuations, M);

        initDynamicSolution(islands, N, M, costs, pontuations, &daysDynamic, &pontuationDynamic);
        initGreedSolution(islands, N, M, costs, pontuations, &daysGreedy, &pontuationGreedy);

        free(islands);

    //     tempoFinal = clock();
    //     executionTime[clk] = (tempoFinal- tempoInicial) * 1000.0 / CLOCKS_PER_SEC;
    // }

    printf("%d %d\n", pontuationGreedy, daysGreedy);
    printf("%d %d\n", pontuationDynamic, daysDynamic);

    // calcAndSaveTests(executionTime, M);

    // Free memory
    free(costs);
    free(pontuations);
}
