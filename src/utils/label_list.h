#ifndef LABEL_LIST_H
#define LABEL_LIST_H

typedef struct _Node {
    int number;
    char *label;
    struct _Node *next;
} Node;

typedef struct _LabelList {
    Node *head;
} LabelList;

void initialize_list(LabelList *);

void add_element(LabelList *, int, char *);

char *get_label_by_idx(LabelList *, int);

int count_elements(LabelList *);

#endif