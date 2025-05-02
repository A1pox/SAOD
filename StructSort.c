#include <stdio.h>
#include <string.h>

typedef struct {
    char lastName[20];
    char firstName[20];
    char phone[20];
    int age;
} Subscriber;

int less(const Subscriber* X, const Subscriber* Y) {
    int cmp = strcmp(X->lastName, Y->lastName);
    if (cmp < 0) return 1;
    else if (cmp > 0) return 0;
    else {
        if (strcmp(X->phone, Y->phone) < 0) return 1;
        else return 0;
    }
}

void insertSortStruct(Subscriber* arr, int n, int (*less)(const Subscriber*, const Subscriber*)) {
    for (int i = 1; i < n; i++) {
        Subscriber key = arr[i];
        int j = i - 1;
        while (j >= 0 && less(&key, &arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void printDirectory(Subscriber* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%-10s %-10s %-15s %d\n", arr[i].lastName, arr[i].firstName, arr[i].phone, arr[i].age);
    }
}

void StructSort() {
    Subscriber list[] = {
        {"Ivanov", "Petr", "89001234567", 25},
        {"Sidorov", "Alex", "89007654321", 30},
        {"Petrov", "Ivan", "89112223344", 22},
        {"Nosov", "Nikita", "89833002892", 18},
        {"Belov", "Sergey", "89223334455", 27}
    };

    int n = sizeof(list) / sizeof(list[0]);

    printf("\n StructSort:");
    printf("\nИсходный справочник:\n");
    printDirectory(list, n);

    insertSortStruct(list, n, less);

    printf("\nОтсортированный справочник:\n");
    printDirectory(list, n);
}
