#include <stdlib.h>

void fillInc(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
}
void fillDec(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i - 1;
}
void fillRand(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 100;
}
int checkSum(const int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum;
}
int runNumber(const int arr[], int n) {
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) count++;
    }
    return count;
}
int theoreticalMplusC(int n) {
    int C = n * (n - 1) / 2;
    int M = 3 * (n - 1);
    return M + C;
}
int theoreticalMplusC_Bubble(int n) {
    return 2 * n * (n - 1);
}
int measureBubble(void (*fill)(int*, int), int n) {
    int* arr = malloc(n * sizeof(int));
    int m = 0, c = 0;
    fill(arr, n);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            c++;
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
                m += 3;
            }
        }
    }
    free(arr);
    return m + c;
}

