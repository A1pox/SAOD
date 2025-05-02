#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ShellSort.h"
#include "Utils.h"
#include "InsertSort.h"

void shellSort(int arr[], int n, int* moveCount, int* compCount) {
    *moveCount = 0;
    *compCount = 0;

    int h = 1;
    while (h < n / 3) {
        h = h * 3 + 1;
    }

    while (h >= 1) {
        for (int i = h; i < n; i++) {
            int key = arr[i];
            int j = i;
            (*moveCount)++;
            while (j >= h && (++(*compCount), arr[j - h] > key)) {
                arr[j] = arr[j - h];
                (*moveCount)++;
                j -= h;
            }
            arr[j] = key;
            (*moveCount)++;
        }
        h /= 3;
    }
}

void printKnuthSteps(int n) {
    int steps[50];
    int count = 0;
    int h = 1;
    while (h < n) {
        steps[count++] = h;
        h = h * 3 + 1;
    }
    for (int i = count - 1; i >= 0; i--) {
        printf("%d", steps[i]);
        if (i > 0) printf(", ");
    }
}

int measureShellSort(int n) {
    int* arr = malloc(n * sizeof(int));
    fillRand(arr, n);
    int m, c;
    shellSort(arr, n, &m, &c);
    free(arr);
    return m + c;
}

void ShellSort() {
    srand(time(NULL));
    int sizes[] = {100, 200, 300, 400, 500};
    int count = sizeof(sizes) / sizeof(sizes[0]);

    printf("\nShell Sort (по формуле Кнута):\n");
    printf("--------------------------------------------------------------------------------------------------------\n");
    printf("|  n  | h1, ..., hm по формуле Кнута      | Insert Mф+Сф | Shell Mф+Сф                                 |\n");
    printf("--------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        int n = sizes[i];
        printf("| %3d | ", n);
        printKnuthSteps(n);
        int insert = measureInsert(fillRand, n);
        int shell  = measureShellSort(n);
        printf(" | %13d | %13d |\n", insert, shell);
    }

    printf("--------------------------------------------------------------------------------------------------------\n");
}
