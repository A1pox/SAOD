#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct stack {
    struct stack *next;
    union {
        int data;
        unsigned char digit[sizeof(int)];
    };
};

struct Queue {
    struct stack *head;
    struct stack *tail;
};

void FillQueueFromText(struct stack **head, struct stack **tail, const char *text) {
    struct stack *p;
    while (*text) {
        p = (struct stack *)malloc(sizeof(struct stack));
        p->data = (int)(*text);
        if (*head == NULL) {
            *head = p;
        } else {
            (*tail)->next = p;
        }
        *tail = p;
        text++;
    }
    (*tail)->next = NULL;
}

void DeleteQueue(struct stack **head, struct stack **tail) {
    struct stack *p = *head;
    while (p != NULL) {
        *head = p->next;
        free(p);
        p = *head;
    }
    *tail = NULL;
}

void Hash(int m, struct stack **head, struct stack **tail, struct Queue q[]) {
    struct stack *p = *head;
    while (p != NULL) {
        struct stack *next = p->next;
        int j = p->data % m;

        struct stack *z = q[j].head;
        int found = 0;
        while (z != NULL) {
            if (z->data == p->data) {
                found = 1;
                break;
            }
            z = z->next;
        }

        if (!found) {
            p->next = NULL;
            if (q[j].head == NULL) {
                q[j].head = p;
            } else {
                q[j].tail->next = p;
            }
            q[j].tail = p;
        } else {
            free(p);
        }

        p = next;
    }

    *head = NULL;
    *tail = NULL;
}

int CountCollisions(struct Queue q[], int m) {
    int collisions = 0;
    for (int i = 0; i < m; i++) {
        struct stack *p = q[i].head;
        int count = 0;
        while (p != NULL) {
            count++;
            p = p->next;
        }
        if (count > 1) {
            collisions += (count - 1);
        }
    }
    return collisions;
}

int CountUniqueChars(const char *text) {
    int unique[256] = {0};
    int count = 0;
    while (*text) {
        unsigned char c = *text;
        if (!unique[c]) {
            unique[c] = 1;
            count++;
        }
        text++;
    }
    return count;
}

void PrintHesh() {
    struct stack *head, *tail;
    int primes[] = {11, 17, 23, 31, 37, 47, 59, 67, 79, 101};
    int num_primes = sizeof(primes) / sizeof(primes[0]);

    char text[] = "In the heart of the ancient forest, countless creatures roam freely: "
                  "majestic deer, swift foxes, colorful birds, and curious squirrels. "
                  "The sunlight filters softly through the dense canopy, creating a mosaic "
                  "of light and shadow on the forest floor. Nearby, a gentle stream babbles, "
                  "inviting all to pause and listen to the symphony of nature. "
                  "Each season brings new wonders, from blooming flowers in spring to "
                  "golden leaves in autumn, painting the landscape with vibrant hues.";
    int n = (int)strlen(text);
    int unique_count = CountUniqueChars(text);

    printf("Text for hashing:\n \"%s\"\n", text);
    printf("--------------------------------------------------------------\n");
    printf("| Hash table size | Unique characters | Number of collisions |\n");
    printf("--------------------------------------------------------------\n");

    for (int k = 0; k < num_primes; k++) {
        int m = primes[k];
        head = NULL;
        tail = NULL;

        FillQueueFromText(&head, &tail, text);

        struct Queue q[m];
        for (int i = 0; i < m; i++) {
            q[i].head = NULL;
            q[i].tail = NULL;
        }

        Hash(m, &head, &tail, q);
        int collisions = CountCollisions(q, m);
        printf("| %15d | %17d | %20d |\n", m, unique_count, collisions);

        for (int i = 0; i < m; i++) {
            DeleteQueue(&(q[i].head), &(q[i].tail));
        }
    }

    printf("--------------------------------------------------------------\n");
}