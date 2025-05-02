#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ShakerSort.h"
#include "Utils.h"



void shakerSort(int arr[], int n, int* moveCount, int* compCount) {
    *moveCount = 0;
    *compCount = 0;
    int left = 0, right = n - 1;
    while (left < right) {
        for (int i = left; i < right; i++) {
            (*compCount)++;
            if (arr[i] > arr[i + 1]) {
                int t = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = t;
                *moveCount += 3;
            }
        }
        right--;
        for (int i = right; i > left; i--) {
            (*compCount)++;
            if (arr[i - 1] > arr[i]) {
                int t = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = t;
                *moveCount += 3;
            }
        }
        left++;
    }
}

int measureShaker(void (*fill)(int*, int), int n) {
    int* arr = malloc(n * sizeof(int));
    int m, c;
    fill(arr, n);
    shakerSort(arr, n, &m, &c);
    free(arr);
    return m + c;
}

void ShakerSort() {
    srand(time(NULL));
    int sizes[] = {100, 200, 300, 400, 500};
    int count = sizeof(sizes) / sizeof(sizes[0]);

    printf("\n ShakerSort: \n");

    printf("-----------------------------------------------------------------------------------------------------------\n");
    printf("|  N  | Mф+Сф пузырьковой                 | Mф+Сф шейкерной                                               |\n");
    printf("|     | Убыв.     | Случ.     | Возр.     | Убыв.     | Случ.     | Возр.                                 |\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        int n = sizes[i];

        int bubbleDec = measureBubble(fillDec, n);
        int bubbleRand = measureBubble(fillRand, n);
        int bubbleInc = measureBubble(fillInc, n);

        int shakerDec = measureShaker(fillDec, n);
        int shakerRand = measureShaker(fillRand, n);
        int shakerInc = measureShaker(fillInc, n);

        printf("| %3d | %9d | %9d | %9d | %9d | %9d | %9d                             |\n",
               n, bubbleDec, bubbleRand, bubbleInc,
               shakerDec, shakerRand, shakerInc);
    }

    printf("-----------------------------------------------------------------------------------------------------------\n");
}
