#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "InsertSort.h"
#include "Utils.h"
#include "BubbleSort.h"
#include "SelectSort.h"
#include "ShakerSort.h"

void insertSort(int arr[], int n, int* moveCount, int* compCount) {
    *moveCount = 0;
    *compCount = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        (*moveCount)++;
        while (j >= 0 && (++(*compCount), arr[j] > key)) {
            arr[j + 1] = arr[j];
            (*moveCount)++;
            j--;
        }
        arr[j + 1] = key;
        (*moveCount)++;
    }
}

int measureInsert(void (*fill)(int*, int), int n) {
    int* arr = malloc(n * sizeof(int));
    int m, c;
    fill(arr, n);
    insertSort(arr, n, &m, &c);
    free(arr);
    return m + c;
}

int theoreticalInsert(int n) {
    int C = n * (n - 1) / 2;
    int M = n * (n - 1) / 2 + n;
    return M + C;
}

void compareAllRandom() {
    int sizes[] = {100, 200, 300, 400, 500};
    int count = sizeof(sizes) / sizeof(sizes[0]);

    printf("\nТрудоемкость квадратичных методов сортировки: ");
    printf("\n");
    printf("---------------------------------------------------------------\n");
    printf("|                                M+C                          |\n");
    printf("|  n  |   Select    |    Bubble   |    Shaker   |    Insert   |\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        int n = sizes[i];
        int select = measureSort(fillRand, selectionSort, n);
        int bubble = measureBubble(fillRand, n);
        int shaker = measureShaker(fillRand, n);
        int insert = measureInsert(fillRand, n);

        printf("| %3d | %10d | %10d | %10d | %10d     |\n", n, select, bubble, shaker, insert);
    }

    printf("---------------------------------------------------------------\n");
}

void InsertSort() {
    srand(time(NULL));
    int sizes[] = {100, 200, 300, 400, 500};
    int count = sizeof(sizes) / sizeof(sizes[0]);

    printf("\nInsertion Sort:\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("|  N  | M+C (теор.) |       Mфакт + Cфакт (InsertSort) по типу массива                |\n");
    printf("|     |             |      Убыв.     |     Случ.      |     Возр.                     |\n");
    printf("--------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        int n = sizes[i];
        int theor = theoreticalInsert(n);
        int worst = measureInsert(fillDec, n);
        int avg   = measureInsert(fillRand, n);
        int best  = measureInsert(fillInc, n);

        printf("| %3d | %11d | %13d  | %13d   | %13d                |\n", n, theor, worst, avg, best);
    }

    printf("--------------------------------------------------------------------------------------\n");

    compareAllRandom();
}
