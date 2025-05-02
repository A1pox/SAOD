#include <stdio.h>
#include <stdlib.h>
#include "BinarySearch.h"

int binarySearchV1(int* arr, int n, int key, int* comparisons) {
    int left = 0, right = n - 1;
    *comparisons = 0;

    while (left <= right) {
        (*comparisons)++;
        int mid = (left + right) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int binarySearchV2(int* arr, int n, int key, int* comparisons) {
    int left = 0, right = n - 1;
    *comparisons = 0;
    int mid;

    while (left < right) {
        mid = (left + right) / 2;
        (*comparisons)++;
        if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid;
    }

    (*comparisons)++;
    if (arr[left] == key)
        return left;
    return -1;
}

void BinarySearch() {
    int sizes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int count = sizeof(sizes) / sizeof(sizes[0]);

    printf("\nБинарный поиск:\n");
    printf("-------------------------------------\n");
    printf("|  N   | Сф I версия | Сф II версия |\n");
    printf("-------------------------------------\n");

    for (int i = 0; i < count; i++) {
        int n = sizes[i];
        int* arr = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) arr[j] = j;

        int cmp1 = 0, cmp2 = 0;

        binarySearchV1(arr, n, arr[0], &cmp1);          // поиск первого
        binarySearchV1(arr, n, arr[n - 1], &cmp1);      // последнего
        binarySearchV1(arr, n, -1, &cmp1);              // несуществующего

        binarySearchV2(arr, n, arr[0], &cmp2);
        binarySearchV2(arr, n, arr[n - 1], &cmp2);
        binarySearchV2(arr, n, -1, &cmp2);

        printf("| %4d | %11d | %12d |\n", n, cmp1, cmp2);
        free(arr);
    }

    printf("-------------------------------------\n");
}
