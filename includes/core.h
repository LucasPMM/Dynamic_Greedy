// Struct that represents the island
typedef struct {
    int cost;
    int pontuation;
    double custoPerPontuation; // == cost / pontuation
} Island;


// Dynamic functions:

// #1) Return the max value between a and b
int max(int a, int b);
// #2) Run knapSack to find the optimal solution 
void knapSack(int **K, int W, int wt[], int val[], int n, Island *islands, int *daysDynamic, int *pontuationDynamic);
// #3) Start the dynamic programing process
void initDynamicSolution(Island *islands, int N, int M, int *costs, int *pontuations, int *daysDynamic, int *pontuationDynamic);


// Greedy functions:

// #1) Sort object of islands
void merge(Island *arr, int l, int m, int r);
// #2) Sort object of islands
void mergeSort(Island *arr, int l, int r);
// #3) Calc solution for greedy process
void calcTripInformations(Island *islands, int budget, int numberOfIslands, int *daysGreedy, int *pontuationsGreedy);
// #4) Start the greedy programing process
void initGreedSolution(Island *islands, int N, int M, int *costs, int *pontuations, int *daysGreedy, int *pontuationGreedy);


// Utils functions:

// #1) Fill island object with file informations
void fillObject(Island *islands, int *costs, int *pontuations, int size);
// #2) Read all informations and calc solutions
void initProgram (FILE *file);
// #3) Calc average and standard deviation 
void calcAndSaveTests(double *time, int N);
