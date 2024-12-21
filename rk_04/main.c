#include <stdio.h>
#include "list.h"

int main(void)
{   
    FILE *in = fopen("in.txt", "r");
    FILE *out = fopen("out.txt", "w");
    if (in == NULL || out == NULL)
    {
        fclose(in);
        fclose(out);
        return OPEN_FILE_ERROR;
    }

    node_t *head = NULL;
    size_t rc = read_words_from_file(in, &head);
    if (rc != OK)
    {
        destroy_list(head);
        fclose(in);
        fclose(out);
        return rc;
    }

    rc = rebuild_list(&head);
    if (rc == OK)
        write_words_to_file(out, head);

    destroy_list(head);
    fclose(in);
    fclose(out);
    return OK;
}
