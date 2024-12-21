#include <stdio.h>
#include "array.h"

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

    array_t array;
    size_t rc = init_array(&array);
    if (rc != OK)
    {
        fclose(in);
        fclose(out);
        return rc;
    }

    rc = read_words_from_file(in, &array);
    if (rc != OK)
    {
        destroy_array(&array);
        fclose(in);
        fclose(out);
        return rc;
    }

    sort_pairs(&array);
    write_array_to_file(out, array);

    destroy_array(&array);
    fclose(in);
    fclose(out);
    return OK;
}
