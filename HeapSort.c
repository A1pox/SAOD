#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

static int Heap(int L, int R, int A[], int *LABOR)
{
    int M = 0, C = 0;
    int X = A[L], i = L, j;
    M++;
    while (1)
    {
        j = 2 * i;
        if (j > R) break;
        C++;
        if (j < R && A[j + 1] <= A[j]) j++;
        C++;
        if (X <= A[j]) break;
        A[i] = A[j]; M++;
        i = j;
    }
    A[i] = X; M++;
    *LABOR += C + M;
    return C + M;
}

static void heapSort(int A[], int n, int *M_out, int *C_out)
{
    int M = 0, C = 0;
    for (int L = (n + 1) / 2; L >= 1; L--)
    {
        int labor = 0;
        Heap(L, n, A, &labor);
        C += labor;
    }
    int R = n;
    while (R > 1)
    {
        int tmp = A[1];
        A[1] = A[R];
        A[R] = tmp;
        M += 3;
        R--;
        int labor = 0;
        Heap(1, R, A, &labor);
        C += labor;
    }
    *M_out = M;
    *C_out = C;
}

static void printTableHeader2(void)
{
    puts(" ----- ------------- -------------------------- ");
    puts("|  N  |     M+C     |       ishodn M+C         |");
    puts("|-----|-------------|--------------------------|");
    puts("|     |     teor    | dec. | rand. | inc.      |");
    puts(" ----- ------------- -------------------------- ");
}

static void printTableRow2(int n, int theoretical, int orig_dec, int orig_rand, int orig_inc)
{
    printf("| %3d | %11d | %5d | %6d | %6d |\n",
           n, theoretical, orig_dec, orig_rand, orig_inc);
}

static void printTableFooter2(void)
{
    puts(" ----- ------------- -------------------------- ");
}

static void printTableHeader22(void)
{
    puts(" ----- -------------------------- ");
    puts("|  N  |       ishodn M+C         |");
    puts("|-----|--------------------------|");
    puts("|     | dec.  | rand. | inc.     |");
    puts(" ----- -------------------------- ");
}

static void printTableRow22(int n, int orig_dec, int orig_rand, int orig_inc)
{
    printf("| %3d | %6d | %6d | %6d |\n",
           n, orig_dec, orig_rand, orig_inc);
}

static void printTableFooter22(void)
{
    puts(" ----- -------------------------- ");
}

static void FillInc(int A[], int n)  { for (int i = 1; i <= n; i++) A[i] = i; }
static void FillDec(int A[], int n)  { for (int i = 1; i <= n; i++) A[i] = n - i + 1; }
static void FillRand(int A[], int n) { for (int i = 1; i <= n; i++) A[i] = rand() % 1000; }

static int Labor_Heap(int n)
{
    double lg = (n > 1 ? log2(n) : 0);
    return (int)ceil(2*lg) + (int)ceil(lg + 2);
}

void HeapSort(void)
{
    srand((unsigned)time(NULL));

    printTableHeader2();
    for (int i = 100; i <= 500; i += 100)
    {
        int *a_dec  = malloc((i+1)*sizeof(int));
        int *a_rand = malloc((i+1)*sizeof(int));
        int *a_inc  = malloc((i+1)*sizeof(int));

        FillDec(a_dec,  i);
        FillRand(a_rand, i);
        FillInc(a_inc,  i);

        int c_dec=0, c_rand=0, c_inc=0;
        Heap(1, i, a_dec,  &c_dec);
        Heap(1, i, a_rand, &c_rand);
        Heap(1, i, a_inc,  &c_inc);

        printTableRow2(i, Labor_Heap(i), c_dec, c_rand, c_inc);

        free(a_dec);
        free(a_rand);
        free(a_inc);
    }
    printTableFooter2();

    printTableHeader22();
    for (int i = 100; i <= 500; i += 100)
    {
        int *dec  = malloc((i+1)*sizeof(int));
        int *rnd  = malloc((i+1)*sizeof(int));
        int *inc  = malloc((i+1)*sizeof(int));

        FillDec(dec,  i);
        FillRand(rnd,  i);
        FillInc(inc,  i);

        int M, C;

        heapSort(dec,  i, &M, &C);
        int mc_dec = M + C;
        heapSort(rnd,  i, &M, &C);
        int mc_rnd = M + C;
        heapSort(inc,  i, &M, &C);
        int mc_inc = M + C;

        printTableRow22(i, mc_dec, mc_rnd, mc_inc);

        free(dec);
        free(rnd);
        free(inc);
    }
    printTableFooter22();
}
