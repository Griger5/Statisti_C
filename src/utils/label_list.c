#include <stdlib.h>

#include <stdio.h>

#include "label_list.h"

void initialize_list(LabelList *list) {
    list->head = NULL;
}

void add_element(LabelList *list, int number, char *label) {
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL) return;

    new_node->number = number;
    new_node->label = label;

    Node *previous = NULL;
    Node *current = list->head;

    while (current != NULL) {
        previous = current;      
        current = current->next; 
    }

    new_node->next = current; 
    
    if (previous == NULL) {
        list->head = new_node;
    }
    else previous->next = new_node; 
}

char *get_label_by_idx(LabelList *list, int index) {
    int i = 0;
    Node *current = list->head;
    
    while (current->next != NULL && i < index) {
        current = current->next;
        i++;
    }

    if (i < index) return 0;

    return current->label;
}

int count_elements(LabelList *list) {
    int count = 0;
    Node *current = list->head;

    while (current != NULL) {
        current = current->next;
        count++;
    }

    return count;
}