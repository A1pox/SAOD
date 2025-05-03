#include <stdio.h>
#include "BinarySearch.h"
#include "BubbleSort.h"
#include "DigitalSort.h"
#include "HeapSort.h"
#include "InsertSort.h"
#include "Phonebook.h"
#include "QuickSort.h"
#include "ShakerSort.h"
#include "ShellSort.h"
#include "StructSort.h"
#include "ListProcessing.h"
#include "MergeProcessing.h"
#include "hesh1.h"
#include "hesh2.h"

void InsertSort(void);

int main() {
    char n;
    printf("Список лаб:"
           "\n 1. Лаб 1.1"
           "\n 2. Лаб 1.2"
           "\n 3. Лаб 1.3"
           "\n 4. Лаб 1.4"
           "\n 5. Лаб 1.5"
           "\n 6. Лаб 1.6"
           "\n 7. Лаб 1.7"
           "\n 8. Лаб 1.8"
           "\n 9. Лаб 1.9"
           "\n 10. Лаб 1.10"
           "\n 11. АЛГОРИТМЫ ОБРАБОТКИ СПИСКОВ И ХЕШИРОВАНИЯ"
           "\n 12. Задания по сортировке прямого слияния MergeSort"
           "\n 13. Задания по цифровой сортировке DigitalSort"
           "\n 14. Задания по хешированию методом прямого связывания"
           "\n 15. Задания по хешированию методом открытой адресации"
           "\n> ");

    scanf(" %d", &n);

    switch (n) {
        case 1:  SelectSort();      break;
        case 2:  BubbleSort();      break;
        case 3:  ShakerSort();      break;
        case 4:  InsertSort();      break;
        case 5:  ShellSort();       break;
        case 6:  BinarySearch();    break;
        case 7:  StructSort();      break;
        case 8:  Phonebook();       break;
        case 9:  HeapSort();        break;
        case 10: QuickSort();       break;
        case 11: ListProcessing();  break;
        case 12: MergeProcessing(); break;
        case 13: RunDigitalSort();  break;
        case 14: PrintHesh();       break;
        case 15: PrintHesh2();       break;
    }

    return 0;
}
