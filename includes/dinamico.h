typedef struct {
    int cost;
    int pontuation;
    double custoPerPontuation;
} DynamicIsland;

// #1)
void initDynamicSoluction(int N, int M, int *costs, int *pontuations);
// #2)
void fillObjectDynamic(DynamicIsland *islands, int *costs, int *pontuations, int size);
// #3)
void knapSack(int **K, int W, int wt[], int val[], int n, DynamicIsland *islands);
// #4)
void printMatrix(int **mat, int m, int n);
// #5)
int max(int a, int b);