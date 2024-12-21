#ifndef ARRAY_H
#define ARRAY_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define OK 0
#define OPEN_FILE_ERROR 1
#define ALLOCATION_MEMORY_ERROR 2

#define START_SIZE 3

typedef struct
{
    char *first;
    size_t second;
} pair_t;

typedef struct
{
    pair_t *data;
    size_t capacity;
    size_t size;
} array_t;

size_t init_array(array_t *array);
void destroy_array(array_t *array);
void sort_pairs(array_t *array);
size_t read_words_from_file(FILE *f, array_t *array);
void write_array_to_file(FILE *f, array_t array);

#endif // ARRAY_H
