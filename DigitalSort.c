#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct stack {
    struct stack *next;
    unsigned char digit[sizeof(int)];
    int data;
} stack;

typedef struct {
    stack *head;
    stack **tail;
} Queue;

int Mprak = 0;
int Mfakt = 0;

void FreeList(stack **head) {
    while (*head) {
        stack *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void UpdateDigits(stack *head, int byteSize) {
    while (head) {
        memcpy(head->digit, &head->data, byteSize);
        head = head->next;
    }
}

void DigitalSort(stack **head, int byteSize) {
    if (!head || !*head) return;

    Queue q[256];
    stack *p;
    int i, j, d;
    Mfakt = 0;
    for (j = 0; j < byteSize; j++) {
        for (i = 0; i < 256; i++) {
            q[i].head = NULL;
            q[i].tail = &q[i].head;
        }

        p = *head;
        while (p) {
            d = p->digit[j];
            *q[d].tail = p;
            q[d].tail = &(p->next);
            p = p->next;
            Mfakt++;
        }

        stack **pp = head;
        for (i = 0; i < 256; i++) {
            if (q[i].head) {
                *pp = q[i].head;
                pp = q[i].tail;
            }
        }
        *pp = NULL;
    }
    Mprak = byteSize * Mfakt / byteSize;
}

void FillRandList(stack **head, int n, int maxValue, int byteSize) {
    stack *tail = NULL;
    for (int i = 0; i < n; i++) {
        stack *p = (stack*)malloc(sizeof(stack));
        p->data = rand() % maxValue;
        memcpy(p->digit, &p->data, byteSize);
        p->next = NULL;

        if (!*head) *head = tail = p;
        else tail = tail->next = p;
    }
}

void FillIncList(stack **head, int n, int byteSize) {
    stack *tail = NULL;
    for (int i = 0; i < n; i++) {
        stack *p = (stack*)malloc(sizeof(stack));
        p->data = i;
        memcpy(p->digit, &p->data, byteSize);
        p->next = NULL;

        if (!*head) *head = tail = p;
        else tail = tail->next = p;
    }
}

void FillDecList(stack **head, int n, int byteSize) {
    stack *tail = NULL;
    for (int i = n-1; i >= 0; i--) {
        stack *p = (stack*)malloc(sizeof(stack));
        p->data = i;
        memcpy(p->digit, &p->data, byteSize);
        p->next = NULL;

        if (!*head) *head = tail = p;
        else tail = tail->next = p;
    }
}

int CheckSum(stack *head) {
    int sum = 0;
    while (head) {
        sum += head->data;
        head = head->next;
    }
    return sum;
}

int CountSeries(stack *head) {
    if (!head) return 0;
    int count = 1;
    while (head->next) {
        if (head->data > head->next->data)
            count++;
        head = head->next;
    }
    return count;
}

void PrintList(stack *head, const char* title) {
    printf("\n%s\n", title);
    int count = 0;
    while (head) {
        printf("%5d ", head->data);
        head = head->next;
        if (++count % 10 == 0) printf("\n");
    }
    printf("\n");
}

void RunDigitalSort() {
    srand(time(NULL));

    int n = 20;
    int byteSize = sizeof(int);
    int maxValue = 1000;

    stack *list = NULL;
    FillRandList(&list, n, maxValue, byteSize);
    PrintList(list, "Original list:");

    UpdateDigits(list, byteSize);
    DigitalSort(&list, byteSize);
    PrintList(list, "Sorted list:");

    printf("CheckSum: %d\n", CheckSum(list));
    printf("RunNumber: %d\n", CountSeries(list));
    FreeList(&list);

    void tableDigitalSort(int byteSize, int maxValue, const char* title)
    {
        printf("\n%s\n", title);
        for (int j = 0; j < 70; j++) printf("-");
        printf("\n|   N   |  M (teor)   |  Mprak (Dec) |  Mprak (Rand) |   Mprak (Inc) |\n");
        for (int j = 0; j < 70; j++) printf("-");

        for (int n = 100; n <= 500; n += 100) {
            int Mteor = byteSize * n;

            stack *list = NULL;
            FillDecList(&list, n, byteSize);
            UpdateDigits(list, byteSize);
            DigitalSort(&list, byteSize);
            int Mdec = Mfakt;
            FreeList(&list);

            FillRandList(&list, n, maxValue, byteSize);
            UpdateDigits(list, byteSize);
            DigitalSort(&list, byteSize);
            int Mrand = Mfakt;
            FreeList(&list);

            FillIncList(&list, n, byteSize);
            UpdateDigits(list, byteSize);
            DigitalSort(&list, byteSize);
            int Minc = Mfakt;
            FreeList(&list);

            printf("\n| %4d  | %10d | %13d | %13d | %13d |\n",
                  n, Mteor, Mdec, Mrand, Minc);
            for (int j = 0; j < 70; j++) printf("-");
        }
        printf("\n");
    }

    tableDigitalSort(sizeof(short), 65536, "DigitalSort 2 byte (short)");
    tableDigitalSort(sizeof(int), 2147483647, "DigitalSort 4 byte (int)");
}
