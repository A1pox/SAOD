#ifndef SELECT_SORT_H
#define SELECT_SORT_H

void SelectSort();
int measureSort(void (*fill)(int*, int), void (*sort)(int*, int, int*, int*), int n);
void selectionSort(int*, int, int*, int*);

#endif
