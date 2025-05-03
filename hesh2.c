#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1000

typedef struct {
    char *table;
    int size;
    int collisions;     
    int inserted;
} HashTable;

void init_table(HashTable *ht, int size) {
    ht->size = size;
    ht->collisions = 0;
    ht->inserted = 0;
    ht->table = (char *)malloc(size * sizeof(char));
    if (!ht->table) {
        fprintf(stderr, "Oshibka vydeleniya pamyati\n");
        exit(EXIT_FAILURE);
    }
    memset(ht->table, 0, size * sizeof(char));
}

void free_table(HashTable *ht) {
    free(ht->table);
    ht->table = NULL;
}

void insert_linear(HashTable *ht, char key) {
    int m = ht->size;
    int h = key % m;

    for (int i = 0; i < m; i++) {
        int index = (h + i) % m;
        if (ht->table[index] == 0) {
            ht->table[index] = key;
            ht->inserted++;
            return;
        }
        if (ht->table[index] == key)
            return; 
        ht->collisions++;
    }
}

void insert_quadratic(HashTable *ht, char key) {
    int m = ht->size;
    int h = key % m;
    int d = 1;

    for (int i = 0; i < m; i++) {
        int index = (h + d) % m;
        if (ht->table[index] == 0) {
            ht->table[index] = key;
            ht->inserted++;
            return;
        }
        if (ht->table[index] == key)
            return; 
        ht->collisions++;
        d += 2;
    }
}

void print_table_contents(HashTable *linear, HashTable *quadratic) {
    printf("\nNomer yacheyki      : ");
    for (int i = 0; i < linear->size; i++) {
        printf("%2d ", i);
    }

    printf("\nLineynaya proby     : ");
    for (int i = 0; i < linear->size; i++) {
        printf(" %c ", linear->table[i] ? linear->table[i] : '.');
    }

    printf("\nKvadratnaya proby   : ");
    for (int i = 0; i < quadratic->size; i++) {
        printf(" %c ", quadratic->table[i] ? quadratic->table[i] : '.');
    }
    printf("\n");
}

void PrintHesh2() {
    const char text[] = "In the heart of the ancient forest, countless creatures roam freely: "
                  "majestic deer, swift foxes, colorful birds, and curious squirrels. "
                  "The sunlight filters softly through the dense canopy, creating a mosaic "
                  "of light and shadow on the forest floor. Nearby, a gentle stream babbles, "
                  "inviting all to pause and listen to the symphony of nature. "
                  "Each season brings new wonders, from blooming flowers in spring to "
                  "golden leaves in autumn, painting the landscape with vibrant hues.";

    int sizes[] = {11, 17, 23, 31, 37, 47, 59, 67, 79, 101};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    int text_len = (int)strlen(text);
    int unique[256] = {0};
    char unique_chars[256];
    int unique_count = 0;

    for (int i = 0; i < text_len; i++) {
        unsigned char c = text[i];
        if (!unique[c]) {
            unique[c] = 1;
            unique_chars[unique_count++] = c;
        }
    }

    int preview_size = 31;
    HashTable linear_preview, quadratic_preview;
    init_table(&linear_preview, preview_size);
    init_table(&quadratic_preview, preview_size);

    for (int i = 0; i < text_len; i++) {
        insert_linear(&linear_preview, text[i]);
        insert_quadratic(&quadratic_preview, text[i]);
    }

    printf("\nSoderzhimoe khesh-tablicy pri razmere %d:\n", preview_size);
    print_table_contents(&linear_preview, &quadratic_preview);
    printf("\nIshodnyy tekst dlya khesh-funktsii:\n\"%s\"\n", text);

    free_table(&linear_preview);
    free_table(&quadratic_preview);

    printf("\nSravnenie kolichestva kolliziy dlya raznykh razmerov tablic:\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("| Razmer tablicy | Unikal. simvoly  | Kollizii (Lineynaya) | Kollizii (Kvadratnaya)  |\n");
    printf("--------------------------------------------------------------------------------------\n");

    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];

        HashTable linear_table, quadratic_table;
        init_table(&linear_table, size);
        init_table(&quadratic_table, size);

        for (int i = 0; i < text_len; i++) {
            insert_linear(&linear_table, text[i]);
            insert_quadratic(&quadratic_table, text[i]);
        }

        printf("| %14d | %16d | %20d | %23d |\n", 
               size, 
               unique_count,  
               linear_table.collisions, 
               quadratic_table.collisions);
        
        free_table(&linear_table);
        free_table(&quadratic_table);
    }
    printf("--------------------------------------------------------------------------------------\n");
}