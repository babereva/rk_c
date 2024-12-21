#include <stdio.h>
#include "list.h"

size_t create_node(node_t **node, char *str)
{
    *node = malloc(sizeof(node_t));
    if (*node == NULL)
        return ALLOCATION_MEMORY_ERROR;
    (*node)->next = NULL;
    (*node)->data = strdup(str);
    return OK;
}

static size_t append_list(node_t **node, char *str)
{
    if (*node == NULL)
        return create_node(node, str);
    return append_list(&(*node)->next, str);
}

void destroy_list(node_t *node)
{
    while (node)
    {
        node_t *temp = node;
        node = node->next;
        free(temp->data);
        free(temp);
    }
}

static size_t count_words(const char *str)
{
    size_t cnt = 1;
    while (*str != '\0')
    {
        if (*str == ' ')
            cnt++;
        str++;
    }
    return cnt;
}

size_t rebuild_list(node_t **head)
{
    node_t *curr = *head;
    node_t *prev = NULL;

    while (curr != NULL) 
    {
        if (count_words(curr->data) > 1)
        {
            char *sentence = curr->data;
            char *word = strtok(sentence, " ");
            
            while (word != NULL) {
                node_t *node = NULL;
                size_t rc = create_node(&node, word);
                if (rc != OK)
                    return rc;

                if (prev == NULL)
                    *head = node;
                else
                    prev->next = node;
                prev = node;
                word = strtok(NULL, " ");
            }
        }
        else
        {
            for (char *ptr = curr->data; *ptr != '\0'; ptr++)
            {
                char *word = malloc(2 * sizeof(char));
                word[0] = *ptr;
                word[1] = '\0';
                node_t *node = NULL;
                size_t rc = create_node(&node, word);
                if (rc != OK)
                    return rc;
                
                if (prev == NULL)
                    *head = node;
                else
                    prev->next = node;
                prev = node;
                free(word);
            }
        }
        
        node_t *temp = curr;
        curr = curr->next;
        free(temp->data);
        free(temp);
    }

    return OK;
}

size_t read_words_from_file(FILE *f, node_t **head)
{
    char *ptr = NULL;
    size_t len = 0;
    while (getline(&ptr, &len, f) != -1)
    {
        ptr[strcspn(ptr, "\n")] = '\0';
        append_list(head, ptr);
    }
    free(ptr);
    return OK;
}

void write_words_to_file(FILE *f, node_t *head)
{
    while (head)
    {
        fprintf(f, "%s\n", head->data);
        head = head->next;
    }
}
