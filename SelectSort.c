#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SelectSort.h"
#include "Utils.h"

void selectionSort(int arr[], int n, int *moveCount, int *compCount) {
    *moveCount = 0;
    *compCount = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            (*compCount)++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
        (*moveCount) += 3;
    }
}
void selectionSortImproved(int arr[], int n, int *moveCount, int *compCount) {
    *moveCount = 0;
    *compCount = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            (*compCount) ++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            (*moveCount) += 3;
        }
    }
}
int measureSort(void (*fillFunc)(int*,int),
                void (*sortFunc)(int*,int,int*,int*),
                int n)
{
    int *arr = (int*)malloc(n * sizeof(int));
    fillFunc(arr, n);
    int moveCount, compCount;
    sortFunc(arr, n, &moveCount, &compCount);
    free(arr);
    return (moveCount + compCount);
}
void SelectSort() {
    srand(time(NULL));

    int origDec10, origRand10, origInc10;
    int imprDec10, imprRand10, imprInc10;
    int origDec100, origRand100, origInc100;
    int imprDec100, imprRand100, imprInc100;
    int MplusC_theor_10   = theoreticalMplusC(10);
    int MplusC_theor_100  = theoreticalMplusC(100);

    origDec10  = measureSort(fillDec,  selectionSort, 10);
    origRand10 = measureSort(fillRand, selectionSort, 10);
    origInc10  = measureSort(fillInc,  selectionSort, 10);
    imprDec10  = measureSort(fillDec,  selectionSortImproved, 10);
    imprRand10 = measureSort(fillRand, selectionSortImproved, 10);
    imprInc10  = measureSort(fillInc,  selectionSortImproved, 10);
    origDec100  = measureSort(fillDec,  selectionSort, 100);
    origRand100 = measureSort(fillRand, selectionSort, 100);
    origInc100  = measureSort(fillInc,  selectionSort, 100);
    imprDec100  = measureSort(fillDec,  selectionSortImproved, 100);
    imprRand100 = measureSort(fillRand, selectionSortImproved, 100);
    imprInc100  = measureSort(fillInc,  selectionSortImproved, 100);

    printf("\n SelectSort: \n");

    printf("--------------------------------------------------------------------------\n");
    printf("|  N  | M+C (теор.)|    Исходный (Mф+Cф)      |    Улучшенный (Mф+Cф)    |\n");
    printf("|     |            | Убыв. | Случ. | Возр.    | Убыв. | Случ. | Возр.    |\n");
    printf("--------------------------------------------------------------------------\n");

    printf("| %3d | %10d | %5d | %5d | %5d    | %5d | %5d | %5d    |\n",
           10, MplusC_theor_10,
           origDec10, origRand10, origInc10,
           imprDec10, imprRand10, imprInc10);

    printf("| %3d | %10d | %5d | %5d | %5d    | %5d | %5d | %5d    |\n",
           100, MplusC_theor_100,
           origDec100, origRand100, origInc100,
           imprDec100, imprRand100, imprInc100);

    printf("--------------------------------------------------------------------------\n");
}
