
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct ConfigEntry {
    char *key;      // dynamic heap string
    char *value;    // dynamic heap string    
} ConfigEntry;

typedef struct ConfigTable {
    char *name;             // dynamic heap string (table name)
    ConfigEntry *entries;   // dynamic heap array of ConfigEntry structs
    size_t count;           // number of active entries
    size_t capacity;        // maximum allocated capacity
} ConfigTable;


ConfigTable *create_table(const char *name, size_t initial_capacity) {
    ConfigTable *ptr = malloc(sizeof *ptr);
    if (ptr == NULL) return NULL;

    ptr->name = NULL;
    ptr->entries = NULL;

    ptr->name = malloc(strlen(name) + 1);
    if (ptr->name == NULL) goto cleanup;

    ptr->entries = malloc(initial_capacity * sizeof(ConfigEntry));
    if (ptr->entries == NULL) goto cleanup;

    strcpy(ptr->name, name);
    ptr->count = 0;
    ptr->capacity = initial_capacity;

    return ptr;

cleanup:
    free(ptr->name);
    free(ptr->entries);
    free(ptr);
    return NULL;
}


int add_entry(ConfigTable *table, const char *key, const char *value) {
    if (table->count == table->capacity) {
        table->capacity *= 2;
        ConfigEntry *temp = realloc(table->entries, table->capacity * sizeof(ConfigEntry));

        if (temp == NULL) {
            table->capacity /= 2;
            return -1;
        }

        table->entries = temp;
    }

    table->entries[table->count].key = NULL;
    table->entries[table->count].value = NULL;

    table->entries[table->count].key = malloc(strlen(key) + 1);
    if (table->entries[table->count].key == NULL) goto cleanup;

    table->entries[table->count].value = malloc(strlen(value) + 1);
    if (table->entries[table->count].value == NULL) goto cleanup;

    strcpy(table->entries[table->count].key, key);
    strcpy(table->entries[table->count].value, value);
    table->count++;

    return 0;

cleanup:
    free(table->entries[table->count].key);
    free(table->entries[table->count].value);

    return -1;
}


ConfigTable *shallow_clone_table(const ConfigTable *src) {
    ConfigTable *shallow_ptr = malloc(sizeof *shallow_ptr);

    if (shallow_ptr == NULL) return NULL;

    shallow_ptr->capacity = src->capacity;
    shallow_ptr->count = src->count;
    shallow_ptr->entries = src->entries;
    shallow_ptr->name = src->name;

    return shallow_ptr;
}


ConfigTable *deep_clone_table(const ConfigTable *src) {
    ConfigTable *ptr = malloc(sizeof *ptr);
    if (ptr == NULL) return NULL;

    ptr->name = NULL;
    ptr->entries = NULL;

    ptr->name = malloc(strlen(src->name) + 1);
    if (ptr->name == NULL) goto cleanup_outside;

    ptr->entries = malloc(src->capacity * sizeof(ConfigEntry));
    if (ptr->entries == NULL) goto cleanup_outside;

    strcpy(ptr->name, src->name);
    ptr->count = 0;
    ptr->capacity = src->capacity;

    for (size_t i = 0; i < src->count; i++) {
        ptr->entries[i].key = NULL;
        ptr->entries[i].value = NULL;

        ptr->count++;

        ptr->entries[i].key = malloc(strlen(src->entries[i].key) + 1);
        if (ptr->entries[i].key == NULL) goto cleanup_inside;

        ptr->entries[i].value = malloc(strlen(src->entries[i].value) + 1);
        if (ptr->entries[i].value == NULL) goto cleanup_inside;

        strcpy(ptr->entries[i].key, src->entries[i].key);
        strcpy(ptr->entries[i].value, src->entries[i].value);
    }

    return ptr;

cleanup_inside:
    for (size_t i = 0; i < ptr->count; i++) {
        free(ptr->entries[i].key);
        free(ptr->entries[i].value);
    }

cleanup_outside:
    free(ptr->name);
    free(ptr->entries);
    free(ptr);

    return NULL;
}


void destroy_table(ConfigTable *table) {
    for (size_t i = 0; i < table->count; i++) {
        free(table->entries[i].key);
        free(table->entries[i].value);
    }

    free(table->entries);
    free(table->name);
    free(table);
}


void printing_values(ConfigTable *table) {
    printf("%s\n------------------------\n", table->name);

    for (size_t i = 0; i < table->count; i++) {
        printf("%s >>> %s\n", table->entries[i].key, table->entries[i].value);
    }
}


int main(void) {
    ConfigTable *original_ptr = create_table("Config Table", 2);
    if (original_ptr == NULL) {
        printf("Table creation failed.\n");
        return 1;
    }

    add_entry(original_ptr, "1", "cristiano ronaldo");
    add_entry(original_ptr, "2", "rafa nadal");
    add_entry(original_ptr, "3", "m");

    ConfigTable *deep_ptr = deep_clone_table(original_ptr);
    if (deep_ptr == NULL) {
        printf("Deep clone table creation failed.\n");
        return 1;
    }

    destroy_table(original_ptr);
    original_ptr = NULL;

    printing_values(deep_ptr);

    destroy_table(deep_ptr);
    deep_ptr = NULL;

    return 0;
}