#include<stdlib.h> 
#include<stdio.h> 
#include "../includes/guloso.h"

void merge(GreedyIsland *arr, int l, int m, int r) { 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m; 

	GreedyIsland L[n1], R[n2]; 

	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1+ j]; 

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

void mergeSort(GreedyIsland *arr, int l, int r) { 
	if (l < r) { 
		int m = l+(r-l)/2; 
		mergeSort(arr, l, m); 
		mergeSort(arr, m+1, r); 
		merge(arr, l, m, r); 
	} 
} 

void calcTripInformations(GreedyIsland *islands, int budget, int numberOfIslands) {
    int pontuation = 0, days = 0, spent = 0, i;

    for (i = 0; i < numberOfIslands; i++) {
        int dayQtd = (budget - spent) / islands[i].cost;
        days += dayQtd;
        pontuation += islands[i].pontuation * dayQtd;
        spent += islands[i].cost * dayQtd;
    }
    printf("%d %d\n", pontuation, days);
}

void fillObject(GreedyIsland *islands, int *costs, int *pontuations, int size) {
    int i;
    for (i = 0; i < size; i++) {
        islands[i].cost = costs[i];
        islands[i].pontuation = pontuations[i];
        islands[i].custoPerPontuation = (double)costs[i] / (double)pontuations[i];
    }
}

void initGreedSoluction(int N, int M, int *costs, int *pontuations) {
    GreedyIsland *islands;
    islands = (GreedyIsland*)calloc(M, sizeof(GreedyIsland));
    fillObject(islands, costs, pontuations, M);

	mergeSort(islands, 0, M - 1); 

    calcTripInformations(islands, N, M);
    free(islands);
} 
