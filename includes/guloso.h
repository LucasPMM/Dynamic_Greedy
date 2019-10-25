typedef struct {
    int cost;
    int pontuation;
    double custoPerPontuation;
} GreedyIsland;

// #1)
void merge(GreedyIsland *arr, int l, int m, int r);
// #2)
void mergeSort(GreedyIsland *arr, int l, int r);
// #3)
void calcTripInformations(GreedyIsland *islands, int budget, int numberOfIslands);
// #4)
void fillObject(GreedyIsland *islands, int *costs, int *pontuations, int size);
// #5)
void initGreedSoluction(int N, int M, int *costs, int *pontuations);