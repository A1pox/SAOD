#include "MergeProcessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define cnt 5

/* Односвязный список */
typedef struct Node {
    int val;
    struct Node *next;
} Node;

/* Вспомогательные: печать, сумма, счёт серий, подсчёт узлов, очистка */
static void list_print(Node *h) {
    while (h) { printf("%d ", h->val); h = h->next; }
    printf("\n");
}
static long list_checksum(Node *h) {
    long s = 0;
    while (h) { s += h->val; h = h->next; }
    return s;
}
static int list_count_runs(Node *h) {
    if (!h) return 0;
    int runs = 1, dir = 0;
    Node *p = h; h = h->next;
    while (h) {
        int d = (h->val > p->val) ? 1 : (h->val < p->val) ? -1 : 0;
        if (dir == 0) { if (d) dir = d; }
        else if (d && d != dir) { runs++; dir = d; }
        p = h; h = h->next;
    }
    return runs;
}
static int list_count_nodes(Node *h) {
    int c = 0;
    while (h) { c++; h = h->next; }
    return c;
}
static void list_clear(Node **h) {
    Node *cur = *h;
    while (cur) {
        Node *nx = cur->next;
        free(cur);
        cur = nx;
    }
    *h = NULL;
}

/* 2. Расщепление списка (через один элемент) */
static void split_list(Node *src, Node **a, Node **b) {
    *a = *b = NULL;
    Node *ta = NULL, *tb = NULL;
    int toggle = 1;
    while (src) {
        Node *n = src;
        src = src->next;
        n->next = NULL;
        if (toggle) {
            if (!*a) *a = ta = n;
            else { ta->next = n; ta = n; }
        } else {
            if (!*b) *b = tb = n;
            else { tb->next = n; tb = n; }
        }
        toggle = !toggle;
    }
}

/* 3. Natural merge sort (слияние серий) */
static Node* natural_merge(Node *src, long *cf, long *mf, int *runs_out) {
    /* разбить на монотонные серии */
    Node *runs[128];
    int rc = 0;
    while (src) {
        runs[rc++] = src;
        while (src->next && src->val <= src->next->val) {
            (*cf)++;
            src = src->next;
        }
        Node *next = src->next;
        src->next = NULL;
        src = next;
    }
    *runs_out = rc;
    /* слияние пар серий до одной */
    while (rc > 1) {
        int w = 0;
        for (int i = 0; i < rc; i += 2) {
            if (i+1 < rc) {
                Node *a = runs[i], *b = runs[i+1], *t = NULL, **tail = &t;
                while (a && b) {
                    (*cf)++;
                    if (a->val <= b->val) {
                        *tail = a; a = a->next;
                    } else {
                        *tail = b; b = b->next;
                    }
                    (*mf)++;
                    tail = &(*tail)->next;
                }
                Node *r = a ? a : b;
                while (r) {
                    *tail = r; r = r->next;
                    (*mf)++;
                    tail = &(*tail)->next;
                }
                *tail = NULL;
                runs[w++] = t;
            } else {
                runs[w++] = runs[i];
            }
        }
        rc = w;
    }
    return runs[0];
}

/* 4. Прямое слияние (рекурсивно) */
static Node* merge_sort_list(Node *h, long *cf, long *mf) {
    if (!h || !h->next) return h;
    /* разделить пополам */
    Node *slow = h, *fast = h->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node *mid = slow->next;
    slow->next = NULL;
    Node *L = merge_sort_list(h, cf, mf);
    Node *R = merge_sort_list(mid, cf, mf);
    /* слияние */
    Node *t = NULL, **tail = &t;
    while (L && R) {
        (*cf)++;
        if (L->val <= R->val) {
            *tail = L; L = L->next;
        } else {
            *tail = R; R = R->next;
        }
        (*mf)++;
        tail = &(*tail)->next;
    }
    Node *r = L?L:R;
    while (r) {
        *tail = r; r = r->next;
        (*mf)++;
        tail = &(*tail)->next;
    }
    *tail = NULL;
    return t;
}

/* 5. Слияние для массивов */
static void fill_array(int *a, int n, int type) {
    for (int i = 0; i < n; i++) {
        if (type == 0) a[i] = n - i;
        else if (type == 1) a[i] = i;
        else a[i] = rand() % n;
    }
}
static void merge_arr(int *a, int l, int m, int r, long *cf, long *mf) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1*sizeof(int)), *R = malloc(n2*sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = a[l+i];
    for (int j = 0; j < n2; j++) R[j] = a[m+1+j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        (*cf)++;
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
        (*mf)++;
    }
    while (i < n1) { a[k++] = L[i++]; (*mf)++; }
    while (j < n2) { a[k++] = R[j++]; (*mf)++; }
    free(L); free(R);
}
static void merge_sort_arr(int *a, int l, int r, long *cf, long *mf) {
    if (l < r) {
        int m = (l + r) / 2;
        merge_sort_arr(a, l, m, cf, mf);
        merge_sort_arr(a, m+1, r, cf, mf);
        merge_arr(a, l, m, r, cf, mf);
    }
}

/* 6. Быстрая и пирамидальная для графика */
static void quick_sort_arr(int *a, int l, int r, long *cf, long *mf) {
    if (l < r) {
        int i = l, j = r, pivot = a[(l+r)/2];
        while (i <= j) {
            while (a[i] < pivot) { (*cf)++; i++; }
            while (a[j] > pivot) { (*cf)++; j--; }
            if (i <= j) {
                int t = a[i]; a[i] = a[j]; a[j] = t;
                (*mf) += 3;
                i++; j--;
            }
        }
        if (l < j) quick_sort_arr(a, l, j, cf, mf);
        if (i < r) quick_sort_arr(a, i, r, cf, mf);
    }
}
static void heap_sift(int *a, int root, int end, long *cf, long *mf) {
    while (2*root+1 <= end) {
        int child = 2*root+1, swap_idx = root;
        if (( *cf += 1 ) && a[swap_idx] < a[child]) swap_idx = child;
        if (child+1 <= end && (++*cf && a[swap_idx] < a[child+1])) swap_idx = child+1;
        if (swap_idx == root) break;
        int t = a[root]; a[root]=a[swap_idx]; a[swap_idx]=t; *mf += 3;
        root = swap_idx;
    }
}
static void heap_sort_arr(int *a, int n, long *cf, long *mf) {
    for (int start = n/2-1; start >= 0; start--)
        heap_sift(a, start, n-1, cf, mf);
    for (int end = n-1; end > 0; end--) {
        int t = a[0]; a[0]=a[end]; a[end]=t; *mf += 3;
        heap_sift(a, 0, end-1, cf, mf);
    }
}

/* Основная точка входа */
void MergeProcessing(void) {
    size_t n;
    printf("Введите n (n>=20): ");
    if (scanf("%zu", &n) != 1 || n < 20) return;
    srand((unsigned)time(NULL));

    /* создаём исходный список */
    Node *src = NULL, *tail = NULL;
    for (size_t i = 0; i < n; i++) {
        Node *u = malloc(sizeof(Node));
        u->val = rand() % 100;
        u->next = NULL;
        if (!src) src = tail = u;
        else { tail->next = u; tail = u; }
    }
    printf("\nИсходный список (%zu элементов):\n", n);
    list_print(src);

    /* 2. Расщепление */
    Node *l1, *l2;
    split_list(src, &l1, &l2);
    int c1 = list_count_nodes(l1), c2 = list_count_nodes(l2);
    printf("\nСписок 1 (%d): ", c1); list_print(l1);
    printf("Список 2 (%d): ", c2); list_print(l2);

    /* 3. Слияние серий */
    long cf_nm = 0, mf_nm = 0;
    int runs_nm = 0;
    long cs_src = list_checksum(src);
    Node *nm = natural_merge(src, &cf_nm, &mf_nm, &runs_nm);
    long cs_nm = list_checksum(nm);
    printf("\nСлияние серий:\n");
    printf("Исходных серий: %d, контрольная сумма: %ld\n", runs_nm, cs_src);
    printf("После слияния: серий = 1, контрольная сумма: %ld\n", cs_nm);
    printf("Cф = %ld, Mf = %ld\n", cf_nm, mf_nm);
    double th = n * log2(n);
    printf("Теоретически C ≈ %.0f, M ≈ %.0f\n", th, th);

    /* 4. Прямое слияние (MergeSort) */
    long cf_ms = 0, mf_ms = 0;
    Node *ms = merge_sort_list(src, &cf_ms, &mf_ms);
    long cs_ms = list_checksum(ms);
    printf("\nПрямое слияние (MergeSort):\n");
    printf("Контрольная сумма: %ld\n", cs_ms);
    printf("Cф = %ld, Mf = %ld\n", cf_ms, mf_ms);
    printf("Теоретически C ≈ %.0f, M ≈ %.0f\n", th, th);

    /* 5. Таблица для массивов */
    printf("\nТрудоёмкость прямого слияния на массивах\n");
    printf(" N  | M+C теор. | Убыв. | Случ. | Возр.\n");
    printf("---------------------------------------\n");
    for (int N = 100; N <= 500; N += 100) {
        double tc = 2.0 * N * log2(N);
        printf("%3d | %9.0f |", N, tc);
        for (int t = 0; t < 3; t++) {
            int *a = malloc(N * sizeof(int));
            fill_array(a, N, t);
            long cf = 0, mf = 0;
            merge_sort_arr(a, 0, N-1, &cf, &mf);
            printf(" %5ld |", cf + mf);
            free(a);
        }
        printf("\n");
    }

    /* 6. ASCII‑график для QS, HS, MergeSort на случайных */

    int xs[cnt] = {100,200,300,400,500};
    double vq[cnt], vh[cnt], vm[cnt], mx = 0;
    for (int i = 0; i < cnt; i++) {
        int N = xs[i];
        int *a = malloc(N*sizeof(int));
        fill_array(a, N, 2);
        long cf=0,mf=0; quick_sort_arr(a,0,N-1,&cf,&mf); vq[i]=cf+mf;
        fill_array(a, N, 2); cf=mf=0; heap_sort_arr(a, N, &cf, &mf); vh[i]=cf+mf;
        fill_array(a, N, 2); cf=mf=0; merge_sort_arr(a, 0, N-1, &cf, &mf); vm[i]=cf+mf;
        free(a);
        mx = fmax(mx, fmax(vq[i], fmax(vh[i], vm[i])));
    }
    int H = 20;
    char grid[H][cnt];
    for (int y = 0; y < H; y++)
        for (int x = 0; x < cnt; x++)
            grid[y][x] = ' ';
    for (int i = 0; i < cnt; i++) {
        int y = H-1 - (int)(vq[i]/mx*(H-1)); grid[y][i] = '*';
        y = H-1 - (int)(vh[i]/mx*(H-1)); grid[y][i] = 'o';
        y = H-1 - (int)(vm[i]/mx*(H-1)); grid[y][i] = '+';
    }
    printf("\nГрафик Mf+Cf vs N  (* QS, o HS, + MS)\n");
    for (int y = 0; y < H; y++) {
        printf("%8.0f |", mx*(H-1-y)/(H-1));
        for (int x = 0; x < cnt; x++) printf("%c ", grid[y][x]);
        printf("\n");
    }
    printf("         "); for(int i=0;i<cnt*2;i++) printf("-"); printf("\n         ");
    for (int i=0;i<cnt;i++) printf("%d ", xs[i]); printf("\n");
}
