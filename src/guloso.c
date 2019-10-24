#include<stdlib.h> 
#include<stdio.h> 

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(float *arr, int l, int m, int r) { 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m; 

	/* create temp arrays */
	int L[n1], R[n2]; 

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1+ j]; 

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2) { 
		if (L[i] <= R[j]) { 
			arr[k] = L[i]; 
			i++; 
		} 
		else { 
			arr[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 

	/* Copy the remaining elements of L[], if there 
	are any */
	while (i < n1) { 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 

	/* Copy the remaining elements of R[], if there 
	are any */
	while (j < n2) { 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 

void mergeSort(float *arr, int l, int r) { 
	if (l < r) { 
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l+(r-l)/2; 

		// Sort first and second halves 
		mergeSort(arr, l, m); 
		mergeSort(arr, m+1, r); 

		merge(arr, l, m, r); 
	} 
} 

void printArray(float *A, int size) { 
	int i; 
	for (i=0; i < size; i++) 
		printf("%f ", A[i]); 
	printf("\n"); 
}

void printFloat(float *A, int size) { 
	int i; 
	for (i=0; i < size; i++) 
		printf("%f ", A[i]); 
	printf("\n"); 
}

float *calcPricePerPoints(int *custos, int *pontuacoes, int size) {
    int i;
    float *custoPorPontuacao;
    custoPorPontuacao = (float*)calloc(size, sizeof(float));

    for (i = 0; i < size; i++) {
        custoPorPontuacao[i] = custos[i] / pontuacoes[i];
    }

    return custoPorPontuacao;
}

void calcTripDays(float *custoPorPontuacao, int *custos, int *pontuacoes, int orcamento, int ilhas) {
    int pontuacao = 0, dias = 0, gasto = 0, i;

    for (i = 0; i < ilhas; i++) {
        int dayQtd = (orcamento - gasto) /custos[i];
        dias += dayQtd;
        pontuacao += pontuacoes[i] * dayQtd;
        gasto += custos[i] * dayQtd;
    }
    printf("%d %d\n", pontuacao, dias);
}

// void calcTripDays(float *custoPorPontuacao, int *custos, int *pontuacoes, int orcamento, int ilhas) {
//     int pontuacao = 0, dias = 0, gasto = 0, i, islandCtrl = 0;
//     while (gasto < orcamento && islandCtrl != ilhas) {
//         for (i = 0; i < ilhas; i++) {
//             if (custoPorPontuacao[islandCtrl] == custos[i] / pontuacoes[i]) {
//                 int dayQtd = (orcamento - gasto) /custos[i];
//                 dias += dayQtd;
//                 pontuacao += pontuacoes[i] * dayQtd;
//                 gasto += custos[i] * dayQtd;
//                 islandCtrl++;
//                 break;
//             }
//         }
//     }
//     printf("%d %d\n", pontuacao, dias);
// }

void initGreedSoluction(int N, int M, int *custos, int *pontuacoes) {
    float *custoPorPontuacao;
    custoPorPontuacao = calcPricePerPoints(custos, pontuacoes, M);

	mergeSort(custoPorPontuacao, 0, M - 1); 

    int arr1[] = {1000, 2200, 5000, 2000, 500}; 
    int arr2[] = {30, 45, 90, 32, 4}; 


    calcTripDays(custoPorPontuacao, arr1, arr2, N, M);

    free(custoPorPontuacao);
} 
