#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>

#include "data_point.h"
#include "labeled_data_point.h"
#include "../../utils/file_operation.h"

void print_labeled_data(DataPoint *a) {
    for (size_t i = 0; i<a->dims; i++) {
        printf("%f\n", a->values[i]);
    }
    printf("label_num: %d\n", a->label_num);
}

DataPoint *create_labeled_datapoint_csv(char *data, size_t field_count, LabelList *label_list) {
    char *token;
    char *end;
    DataPoint *point = malloc(sizeof(DataPoint) + field_count*sizeof(double));
    
    point->dims = field_count-1;

    token = strtok(data, ",");
    point->values[0] = atof(token);

    for (size_t i = 1; i < field_count-1; i++) {
        token = strtok(NULL, ",");
        point->values[i] = atof(token);
    };

    token = strtok(NULL, ",");
    end = token + strlen(token) - 1;
    while(end > token && isspace((unsigned char)*end)) end--;
    end[1] = '\0';

    char *token_copy = malloc(strlen(token)+1);
    strcpy(token_copy, token);

    int index_in_list = check_if_exists(*label_list, token);

    if (index_in_list == -1) {
        add_label(label_list, token_copy);
        point->label_num = label_list->size-1;
    }
    else {
        point->label_num = index_in_list;
        free(token_copy);
    }

    return point;
}

DataSet load_labeled_data_csv(FILE *file, size_t rec_count, size_t field_count, LabelList *label_list) {
    DataSet all_data;

    all_data.rec_count = rec_count;
    all_data.field_count = field_count-1; 
    all_data.data = malloc(rec_count*(sizeof(DataPoint) + field_count*sizeof(double)));

    DataPoint *current_data_point;
    char *current_record = NULL;
    size_t n = 0;
    int chars_num;

    for (size_t i = 0; i < rec_count; i++) {
        chars_num = getline(&current_record, &n, file);
        if (chars_num != -1) {
            current_data_point = create_labeled_datapoint_csv(current_record, field_count, label_list);
        }
        all_data.data[i] = current_data_point;
        free(current_record);
        current_record = NULL;
        n = 0;
    }

    all_data.label_count = label_list->size;

    return all_data;
}

DataSet split_label(const DataSet data_set, int label_to_separate) {
    DataSet splitted;

    if (data_set.label_count == 0) {
        splitted.data = NULL;

        return splitted;
    }

    size_t rec_count = data_set.rec_count;
    size_t field_count = data_set.field_count;
    size_t new_rec_count = 0;

    splitted.data = malloc(rec_count*(sizeof(DataPoint) + field_count*sizeof(double)));
    
    for (size_t i = 0; i < rec_count; i++) {
        if (data_set.data[i]->label_num == label_to_separate) {
            splitted.data[new_rec_count] = copy_datapoint(data_set.data[i]);
            new_rec_count++;
        }
    }

    splitted.rec_count = new_rec_count;
    splitted.label_count = 1;

    DataPoint **temp = realloc(splitted.data, new_rec_count*(sizeof(DataPoint) + field_count*sizeof(double)));
    if (temp != NULL) {
        splitted.data = temp;
    }
    else splitted.data = NULL;

    return splitted;
}