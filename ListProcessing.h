#ifndef LISTPROCESSING_H
#define LISTPROCESSING_H

#include <stddef.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Queue;

/* 1. Заполнение стека */
void stack_fill_inc(Node **top, size_t n);
void stack_fill_dec(Node **top, size_t n);
void stack_fill_rand(Node **top, size_t n);

/* 2. Заполнение очереди */
void queue_fill_inc(Queue *q, size_t n);
void queue_fill_dec(Queue *q, size_t n);
void queue_fill_rand(Queue *q, size_t n);

/* 3. Операции со списком */
void list_print(Node *head);
long list_checksum(Node *head);
int  list_count_runs(Node *head);

/* 4*. Удаление всех элементов списка */
void list_clear(Node **head);

/* 5*. Рекурсивная печать списка */
void list_print_rec(Node *head);
void list_print_rev_rec(Node *head);

void ListProcessing(void);

#endif // LISTPROCESSING_H
