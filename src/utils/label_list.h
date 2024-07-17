#ifndef LABEL_LIST_H
#define LABEL_LIST_H

typedef struct _LabelList {
    size_t size;
    char **label_table;
} LabelList;

void add_label(LabelList *, char *);

int check_if_exists(LabelList, char *);

void free_label_list(LabelList *);

#endif