#include <stdio.h>
#include <string.h>

typedef enum {
    NAME_PHONE,
    PHONE_NAME,
    ID_NAME
} SortKey;

typedef enum {
    ASCENDING,
    DESCENDING
} SortDirection;

typedef struct {
    int id;
    char name[30];
    long long phone;
    int bornDay;
} Abonent;

typedef struct {
    int id;
    long long phone;
    char name[30];
    char lastname[30];
} Record;

Abonent users[] = {
    {1, "1", 800000000000, 30},
    {2, "2", 800000000002, 28},
    {3, "5", 800000000006, 31},
    {4, "20", 800000000020, 4},
    {5, "6", 80000000528734, 3}
};

Record records[] = {
    {1, 8913772702288, "20", "200"},
    {2, 8913764907799, "15", "300"},
    {3, 8913903345100, "10", "400"},
    {4, 8913396652908, "100", "500"}
};

int pindexMassive[] = {0, 1, 2, 3};
int nindexMassive[] = {0, 1, 2, 3};

int lessAbonent(const Abonent* x, const Abonent* y, SortKey key, SortDirection dir) {
    int direction = (dir == ASCENDING) ? 1 : -1;

    switch (key) {
        case NAME_PHONE:
            if (strcmp(x->name, y->name) != 0)
                return direction * strcmp(x->name, y->name) < 0;
            return direction * (x->phone < y->phone ? -1 : (x->phone > y->phone ? 1 : 0)) < 0;

        case PHONE_NAME:
            if (x->phone != y->phone)
                return direction * (x->phone < y->phone ? -1 : 1) < 0;
            return direction * strcmp(x->name, y->name) < 0;

        case ID_NAME:
            if (x->id != y->id)
                return direction * (x->id < y->id ? -1 : 1) < 0;
            return direction * strcmp(x->name, y->name) < 0;
    }
    return 0;
}

void indexSortUsers(int indexArr[], const Abonent users[], int n, SortKey key, SortDirection dir) {
    for (int i = 0; i < n; i++) {
        indexArr[i] = i;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (lessAbonent(&users[indexArr[j]], &users[indexArr[j - 1]], key, dir)) {
                int tmp = indexArr[j];
                indexArr[j] = indexArr[j - 1];
                indexArr[j - 1] = tmp;
            }
        }
    }
}

void printUsersIndexed(const Abonent arr[], const int indexArr[], int n) {
    for (int i = 0; i < n; i++) {
        int idx = indexArr[i];
        printf("ID: %d, Name: %s, Phone: %lld, Born Day: %d\n",
               arr[idx].id, arr[idx].name, arr[idx].phone, arr[idx].bornDay);
    }
}

void printIndexes(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void phonesSort(int namesIndexArr[], int phonesIndexArr[], const Record arr[], int n) {
    for (int i = 1; i < n; i++) {
        int t = namesIndexArr[i];
        int j = i - 1;
        while (j >= 0 && strcmp(arr[t].name, arr[namesIndexArr[j]].name) < 0) {
            namesIndexArr[j + 1] = namesIndexArr[j];
            j--;
        }
        namesIndexArr[j + 1] = t;
    }

    for (int i = 1; i < n; i++) {
        int t = phonesIndexArr[i];
        int j = i - 1;
        while (j >= 0 && strcmp(arr[t].name, arr[phonesIndexArr[j]].name) < 0) {
            phonesIndexArr[j + 1] = phonesIndexArr[j];
            j--;
        }
        phonesIndexArr[j + 1] = t;
    }
}

void Phonebook() {
    int n_users = sizeof(users) / sizeof(users[0]);
    int n_records = sizeof(records) / sizeof(records[0]);
    int userIndexArr[5];

    printf("Изначальный список пользователей:\n");
    printUsersIndexed(users, (int[]){0, 1, 2, 3, 4}, n_users);
    printf("\n");

    indexSortUsers(userIndexArr, users, n_users, NAME_PHONE, ASCENDING);

    printf("Пользователи после индексной сортировки по имени и телефону:\n");
    printIndexes(userIndexArr, n_users);
    printUsersIndexed(users, userIndexArr, n_users);
    printf("\n");

    printf("Изначальные индексы записей:\n");
    printIndexes(pindexMassive, n_records);
    printf("\n");

    phonesSort(nindexMassive, pindexMassive, records, n_records);

    printf("Индексный массив pindexMassive после сортировки:\n");
    printIndexes(pindexMassive, n_records);
    printf("\n");

    printf("Индексный массив nindexMassive после сортировки:\n");
    printIndexes(nindexMassive, n_records);
    printf("\n");

    printf("Сортировка записей по pindexMassive:\n");
    for (int i = 0; i < n_records; i++) {
        printf("ID: %d, Name: %s, Lastname: %s, Phone: %lld\n",
               records[pindexMassive[i]].id,
               records[pindexMassive[i]].name,
               records[pindexMassive[i]].lastname,
               records[pindexMassive[i]].phone);
    }

    printf("\n");

    printf("Сортировка записей по nindexMassive:\n");
    for (int i = 0; i < n_records; i++) {
        printf("ID: %d, Name: %s, Lastname: %s, Phone: %lld\n",
               records[nindexMassive[i]].id,
               records[nindexMassive[i]].name,
               records[nindexMassive[i]].lastname,
               records[nindexMassive[i]].phone);
    }
}
