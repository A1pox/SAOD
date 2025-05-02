#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BubbleSort.h"
#include "Utils.h"

void bubbleSort(int arr[], int n, int* moveCount, int* compCount) {
    *moveCount = 0;
    *compCount = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*compCount)++;
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                *moveCount += 3;
            }
        }
    }
}
void BubbleSort() {
    srand(time(NULL));
    int sizes[] = {100, 200, 300, 400, 500};
    int count = sizeof(sizes) / sizeof(sizes[0]);

    printf("\n BubbleSort: \n");

    printf("--------------------------------------------------------------------------------------\n");
    printf("|  N  | M+C (теор.) |         Mфакт + Cфакт (BubbleSort) по типу массива              |\n");
    printf("|     |             |          Убыв.         |        Случ.      |         Возр.      |\n");
    printf("--------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        int n = sizes[i];
        int theor = theoreticalMplusC_Bubble(n);
        int worst = measureBubble(fillDec, n);
        int avg   = measureBubble(fillRand, n);
        int best  = measureBubble(fillInc, n);

        printf("| %3d | %11d | %13d          | %13d     | %13d      |\n", n, theor, worst, avg, best);
    }

    printf("--------------------------------------------------------------------------------------\n");
}
