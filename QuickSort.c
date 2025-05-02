#include "QuickSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Контекст для подсчёта Mf, Cf и глубины рекурсии
typedef struct {
    int *arr;
    size_t n;
    long mf, cf;
    int recursion_depth, max_depth;
} SortContext;

static void reset_ctx(SortContext *ctx) {
    ctx->mf = ctx->cf = ctx->recursion_depth = ctx->max_depth = 0;
}

static void swap_ctx(SortContext *ctx, int *a, int *b) {
    int t = *a; *a = *b; *b = t;
    ctx->mf += 3;
}

static int partition_h(SortContext *ctx, int lo, int hi) {
    int pivot = ctx->arr[(lo + hi) / 2];
    int i = lo, j = hi;
    while (i <= j) {
        while (ctx->arr[i] < pivot) { ctx->cf++; i++; }
        while (ctx->arr[j] > pivot) { ctx->cf++; j--; }
        if (i <= j) {
            swap_ctx(ctx, &ctx->arr[i], &ctx->arr[j]);
            i++; j--;
        }
    }
    return i;
}

static void quicksort1(SortContext *ctx, int lo, int hi) {
    if (lo < hi) {
        ctx->recursion_depth++;
        if (ctx->recursion_depth > ctx->max_depth)
            ctx->max_depth = ctx->recursion_depth;
        int idx = partition_h(ctx, lo, hi);
        quicksort1(ctx, lo, idx - 1);
        quicksort1(ctx, idx, hi);
        ctx->recursion_depth--;
    }
}

static void quicksort2(SortContext *ctx, int lo, int hi) {
    while (lo < hi) {
        ctx->recursion_depth++;
        if (ctx->recursion_depth > ctx->max_depth)
            ctx->max_depth = ctx->recursion_depth;
        int idx = partition_h(ctx, lo, hi);
        if (idx - lo < hi - idx) {
            quicksort2(ctx, lo, idx - 1);
            lo = idx;
        } else {
            quicksort2(ctx, idx, hi);
            hi = idx - 1;
        }
        ctx->recursion_depth--;
    }
}

static void shellsort(SortContext *ctx) {
    size_t n = ctx->n;
    for (size_t gap = n/2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; i++) {
            int tmp = ctx->arr[i]; ctx->mf++;
            size_t j = i;
            while (j >= gap && (ctx->cf++, ctx->arr[j-gap] > tmp)) {
                ctx->arr[j] = ctx->arr[j-gap]; ctx->mf++;
                j -= gap;
            }
            ctx->arr[j] = tmp; ctx->mf++;
        }
    }
}

static void sift_down(SortContext *ctx, int root, int end) {
    while (2*root + 1 <= end) {
        int child = 2*root + 1, swap_idx = root;
        if ((ctx->cf++, ctx->arr[swap_idx] < ctx->arr[child]))
            swap_idx = child;
        if (child+1 <= end && (ctx->cf++, ctx->arr[swap_idx] < ctx->arr[child+1]))
            swap_idx = child+1;
        if (swap_idx == root) break;
        swap_ctx(ctx, &ctx->arr[root], &ctx->arr[swap_idx]);
        root = swap_idx;
    }
}

static void heapsort(SortContext *ctx) {
    size_t n = ctx->n;
    for (int start = (int)(n/2 - 1); start >= 0; start--)
        sift_down(ctx, start, n-1);
    for (int end = (int)n-1; end > 0; end--) {
        swap_ctx(ctx, &ctx->arr[0], &ctx->arr[end]);
        sift_down(ctx, 0, end-1);
    }
}

static void fill_array(int *a, size_t n, int type) {
    for (size_t i = 0; i < n; i++) {
        if (type == 0)      a[i] = (int)(n - i);
        else if (type == 1) a[i] = (int)i;
        else                a[i] = rand() % (int)n;
    }
}

static long checksum(int *a, size_t n) {
    long s = 0;
    for (size_t i = 0; i < n; i++) s += a[i];
    return s;
}

static int count_runs(int *a, size_t n) {
    if (n == 0) return 0;
    int runs = 1;
    for (size_t i = 1; i < n; i++) {
        if ((a[i] > a[i-1] && (i+1<n ? a[i+1] < a[i] : 1)) ||
            (a[i] < a[i-1] && (i+1<n ? a[i+1] > a[i] : 1)))
            runs++;
    }
    return runs;
}

static double theor_M(size_t n) { return 3.0 * n * log2(n); }
static double theor_C(size_t n) { return 2.0 * n * log2(n); }

// ===== Пункт 3: Таблица Mf+Cf + теория + проверка =====
static void print_sort_table(void) {
    const char *tname[3] = {"Убыв.", "Возр.", "Случ."};
    const int ns[5]      = {100, 200, 300, 400, 500};
    printf("+-----+----------+----------+----------+\n");
    printf("|  N  | %-8s    | %-8s    | %-8s    |\n",
           tname[0], tname[1], tname[2]);
    printf("+-----+----------+----------+----------+\n");

    for (int i = 0; i < 5; i++) {
        int n = ns[i];
        long results[3];
        for (int t = 0; t < 3; t++) {
            SortContext ctx = {0};
            ctx.n   = n;
            ctx.arr = malloc(n * sizeof(int));
            fill_array(ctx.arr, n, t);
            reset_ctx(&ctx);
            quicksort1(&ctx, 0, n - 1);
            results[t] = ctx.mf + ctx.cf;
            free(ctx.arr);
        }

        printf("| %3d | %8ld | %8ld | %8ld |\n",
               n, results[0], results[1], results[2]);
        printf("+-----+----------+----------+----------+\n");
    }
}



// // ===== Пункт 4: Глубина рекурсии =====
// static void print_depth_table(void) {
//     const char *tname[3] = {"Убыв.", "Случ.", "Возр."};
//     printf("\nГлубина рекурсии QuickSort1 vs QuickSort2\n");
//     printf(" N   |  QS1: Убыв Случ Возр |  QS2: Убыв Случ Возр\n");
//     printf("---------------------------------------------------\n");
//     for (int n = 100; n <= 500; n += 100) {
//         printf("%4d |", n);
//         for (int ver = 1; ver <= 2; ver++) {
//             for (int t = 0; t < 3; t++) {
//                 SortContext ctx = {0};
//                 ctx.n = n;
//                 ctx.arr = malloc(n * sizeof(int));
//                 fill_array(ctx.arr, n, t);
//                 reset_ctx(&ctx);
//                 if (ver == 1) quicksort1(&ctx, 0, n-1);
//                 else          quicksort2(&ctx, 0, n-1);
//                 printf(" %4d", ctx.max_depth);
//                 free(ctx.arr);
//             }
//             printf(ver==1 ? " |" : "\n");
//         }
//     }
// }
//
// // ===== Пункт 5: ASCII‑график Mf+Cf vs N =====
// static void print_graph(void) {
//     const int ns[] = {100,200,300,400,500};
//     const int cnt = 5, H = 20;
//     double vq[cnt], vh[cnt], vs[cnt], mx = 0;
//     SortContext ctx = {0};
//     for (int i = 0; i < cnt; i++) {
//         int n = ns[i];
//         ctx.n = n;
//         ctx.arr = malloc(n*sizeof(int));
//         fill_array(ctx.arr,n,2); reset_ctx(&ctx);
//         quicksort1(&ctx,0,n-1); vq[i]=ctx.mf+ctx.cf;
//         fill_array(ctx.arr,n,2); reset_ctx(&ctx);
//         heapsort(&ctx); vh[i]=ctx.mf+ctx.cf;
//         fill_array(ctx.arr,n,2); reset_ctx(&ctx);
//         shellsort(&ctx); vs[i]=ctx.mf+ctx.cf;
//         free(ctx.arr);
//         if (vq[i]>mx) mx=vq[i];
//         if (vh[i]>mx) mx=vh[i];
//         if (vs[i]>mx) mx=vs[i];
//     }
//     char grid[H][cnt];
//     for(int y=0;y<H;y++)for(int x=0;x<cnt;x++)grid[y][x]=' ';
//     for(int i=0;i<cnt;i++){
//         int yq=H-1-(int)(vq[i]/mx*(H-1)); grid[yq][i]='*';
//         int yh=H-1-(int)(vh[i]/mx*(H-1)); grid[yh][i]='o';
//         int ys=H-1-(int)(vs[i]/mx*(H-1)); grid[ys][i]='+';
//     }
//     printf("\nГрафик Mf+Cf vs N (* QS, o HS, + SS)\n");
//     for(int y=0;y<H;y++){
//         printf("%8.0f |", mx*(H-1-y)/(H-1));
//         for(int x=0;x<cnt;x++) printf("%c ", grid[y][x]);
//         printf("\n");
//     }
//     printf("           "); for(int i=0;i<cnt*2;i++) printf("-"); printf("\n           ");
//     for(int i=0;i<cnt;i++) printf("%d ", ns[i]); printf("\n");
// }
//
static void run_all(void) {
    srand((unsigned)time(NULL));
    print_sort_table();
    // print_depth_table();
    // print_graph();
}

void QuickSort(void) {
    run_all();
}


