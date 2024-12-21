#include "array.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

size_t init_array(array_t *array)
{
    array->data = malloc(START_SIZE * sizeof(pair_t));
    if (!array->data)
        return ALLOCATION_MEMORY_ERROR;
    array->capacity = START_SIZE;
    array->size = 0;
    return OK;
}

static size_t append_array(array_t *array, char *word)
{
    if (array->size == array->capacity) {
        array->capacity *= 2;
        pair_t *buf= realloc(array->data, array->capacity * sizeof(pair_t));
        if (buf == NULL)
            return ALLOCATION_MEMORY_ERROR;
        array->data = buf;
    }
    array->data[array->size].first = strdup(word);
    array->data[array->size].second = 1;
    array->size++;
    return OK;
}

void destroy_array(array_t *array)
{
    for (size_t i = 0; i < array->size; i++)
        free(array->data[i].first);
    free(array->data);
}

static int cmp_pairs(const void *val1, const void *val2)
{
    const pair_t *first = val1;
    const pair_t *second = val2;
    return strcmp(first->first, second->first);
}

void sort_pairs(array_t *array)
{
    qsort(array->data, array->size, sizeof(pair_t), cmp_pairs);
}

size_t read_words_from_file(FILE *f, array_t *array)
{
    char *ptr = NULL;
    size_t len = 0;
    while (getline(&ptr, &len, f) != -1)
    {
        ptr[strcspn(ptr, "\n")] = '\0';
        bool add = false;
        for (size_t i = 0; i < array->size; i++)
        {
            if (strcmp(array->data[i].first, ptr) == 0)
            {
                array->data[i].second++;
                add = true;
            }
        }

        if (!add)
        {
            size_t rc = append_array(array, ptr);
            if (rc != OK)
            {
                free(ptr);
                return rc;
            }
        }
    }
    free(ptr);
    return OK;
}

void write_array_to_file(FILE *f, array_t array)
{
    for (size_t i = 0; i < array.size; i++)
        fprintf(f, "%s: %zu\n", array.data[i].first, array.data[i].second);
}
