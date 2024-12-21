#ifndef LIST_H
#define LIST_H

#include <string.h>
#include <stdlib.h>

#define OK 0
#define OPEN_FILE_ERROR 1
#define ALLOCATION_MEMORY_ERROR 2

typedef struct node_t
{
    char *data;
    struct node_t *next;
} node_t;

size_t create_node(node_t **node, char *str);
void destroy_list(node_t *node);
size_t rebuild_list(node_t **head);
size_t read_words_from_file(FILE *f, node_t **head);
void write_words_to_file(FILE *f, node_t *head);

#endif // LIST_H
