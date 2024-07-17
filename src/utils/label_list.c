#include <stdlib.h>
#include <string.h>

#include "label_list.h"

void add_label(LabelList *list, char *label) {
    if (list->label_table == NULL) {
        list->size = 1;
        char **temp = malloc(sizeof(char *));
        if (temp != NULL) {
            list->label_table = temp;
            list->label_table[0] = label;
        }

        return;
    }
    else {
        list->size++;
        size_t temp_size = list->size;
        char **temp = realloc(list->label_table, temp_size * sizeof(char *));
        if (temp != NULL) {
            list->label_table = temp;
            list->label_table[temp_size-1] = label;
        }

        return;
    }
}

int check_if_exists(LabelList list, char *to_check) {
    size_t length = list.size;
    int exists;

    for (size_t i = 0; i < length; i++) {
        exists = strcmp(list.label_table[i], to_check);
        if (exists == 0) return i;
    }

    return -1;
}

void free_label_list(LabelList *list) {
    size_t size = list->size;

    for (size_t i = 0; i < size; i++) {
        free(list->label_table[i]);
    }

    free(list->label_table);
}