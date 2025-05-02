#include "ListProcessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Вспомогательные */
static void push(Node **top, int v) {
    Node *n = malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->val = v; n->next = *top; *top = n;
}
static void enqueue(Queue *q, int v) {
    Node *n = malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->val = v; n->next = NULL;
    if (!q->head) q->head = q->tail = n;
    else { q->tail->next = n; q->tail = n; }
}

/* 1. Заполнение стека */
void stack_fill_inc(Node **top, size_t n) {
    *top = NULL;
    for (size_t i = 1; i <= n; ++i) push(top, (int)i);
}
void stack_fill_dec(Node **top, size_t n) {
    *top = NULL;
    for (size_t i = 0; i < n; ++i) push(top, (int)(n - i));
}
void stack_fill_rand(Node **top, size_t n) {
    *top = NULL;
    for (size_t i = 0; i < n; ++i) push(top, rand());
}

/* 2. Заполнение очереди */
void queue_fill_inc(Queue *q, size_t n) {
    q->head = q->tail = NULL;
    for (size_t i = 1; i <= n; ++i) enqueue(q, (int)i);
}
void queue_fill_dec(Queue *q, size_t n) {
    q->head = q->tail = NULL;
    for (size_t i = 0; i < n; ++i) enqueue(q, (int)(n - i));
}
void queue_fill_rand(Queue *q, size_t n) {
    q->head = q->tail = NULL;
    for (size_t i = 0; i < n; ++i) enqueue(q, rand());
}

/* 3. Печать, контрольная сумма и подсчёт серий */
void list_print(Node *head) {
    for (; head; head = head->next) printf("%d ", head->val);
    printf("\n");
}
long list_checksum(Node *head) {
    long s = 0;
    for (; head; head = head->next) s += head->val;
    return s;
}
int list_count_runs(Node *head) {
    if (!head) return 0;
    int runs = 1, dir = 0;
    Node *p = head;
    head = head->next;
    while (head) {
        int d = (head->val > p->val) ? 1
              : (head->val < p->val) ? -1
              : 0;
        if (dir == 0) { if (d) dir = d; }
        else if (d && d != dir) { runs++; dir = d; }
        p = head; head = head->next;
    }
    return runs;
}

/* 4*. Очистка списка */
void list_clear(Node **head) {
    Node *cur = *head;
    while (cur) {
        Node *nx = cur->next;
        free(cur);
        cur = nx;
    }
    *head = NULL;
}

/* 5*. Рекурсивная печать */
void list_print_rec(Node *head) {
    if (!head) return;
    printf("%d ", head->val);
    list_print_rec(head->next);
}
void list_print_rev_rec(Node *head) {
    if (!head) return;
    list_print_rev_rec(head->next);
    printf("%d ", head->val);
}

/* Точка входа ЛР 2.1 */
void ListProcessing(void) {
    size_t n;
    printf("Введите число элементов: ");
    if (scanf("%zu", &n) != 1) return;
    srand((unsigned)time(NULL));

    Node *stk = NULL;
    Queue q = {0};

    /* 1. Стек возрастающий */
    printf("\nСтек возрастающий:\n");
    stack_fill_inc(&stk, n);
    list_print(stk);
    printf("Сумма=%ld, серий=%d\n",
           list_checksum(stk), list_count_runs(stk));
    list_clear(&stk);

    /* 1. Стек убывающий */
    printf("\nСтек убывающий:\n");
    stack_fill_dec(&stk, n);
    list_print(stk);
    printf("Сумма=%ld, серий=%d\n",
           list_checksum(stk), list_count_runs(stk));
    list_clear(&stk);

    /* 1. Стек случайный */
    printf("\nСтек случайный:\n");
    stack_fill_rand(&stk, n);
    list_print(stk);
    printf("Сумма=%ld, серий=%d\n",
           list_checksum(stk), list_count_runs(stk));
    list_clear(&stk);

    /* 2. Очередь возрастающая */
    printf("\nОчередь возрастающая:\n");
    queue_fill_inc(&q, n);
    list_print(q.head);
    printf("Сумма=%ld, серий=%d\n",
           list_checksum(q.head), list_count_runs(q.head));
    list_clear(&q.head);

    /* 2. Очередь убывающая */
    printf("\nОчередь убывающая:\n");
    queue_fill_dec(&q, n);
    list_print(q.head);
    printf("Сумма=%ld, серий=%d\n",
           list_checksum(q.head), list_count_runs(q.head));
    list_clear(&q.head);

    /* 2. Очередь случайная */
    printf("\nОчередь случайная:\n");
    queue_fill_rand(&q, n);
    list_print(q.head);
    printf("Сумма=%ld, серий=%d\n",
           list_checksum(q.head), list_count_runs(q.head));
    list_clear(&q.head);

    /* 5*. Рекурсивная печать */
    printf("\nРекурсивная печать (прямой):\n");
    stack_fill_inc(&stk, n);
    list_print_rec(stk);
    printf("\nРекурсивная печать (обратный):\n");
    list_print_rev_rec(stk);
    printf("\n");
    list_clear(&stk);
}
