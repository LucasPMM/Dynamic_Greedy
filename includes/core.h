typedef struct {
    int cost;
    int pontuation;
    double custoPerPontuation;
} Island;

// Dynamic functions:

// #1)
int max(int a, int b);
// #2)
void knapSack(int **K, int W, int wt[], int val[], int n, Island *islands);
// #3)
void initDynamicSoluction(Island *islands, int N, int M, int *costs, int *pontuations);


// Greedy functions:

// #1)
void merge(Island *arr, int l, int m, int r);
// #2)
void mergeSort(Island *arr, int l, int r);
// #3)
void calcTripInformations(Island *islands, int budget, int numberOfIslands);
// #4)
void initGreedSoluction(Island *islands, int N, int M, int *costs, int *pontuations);


// Utils functions:

// #1) Fill island object with file informations
void fillObject(Island *islands, int *costs, int *pontuations, int size);
// #2) Read all informations and calc solutions
void initProgram (FILE *file);