#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "labeled_data_point.h"
#include "../../utils/file_operation.h"

void print_labeled_data(LabeledDataPoint *a) {
    for (size_t i = 0; i<a->dims; i++) {
        printf("%f\n", a->data[i]);
    }
    printf("label: %s\n", a->label);
}

LabeledDataPoint *create_labeled_data_point(char *data, size_t rec_count) {
    char *token;
    LabeledDataPoint *point = malloc(sizeof(size_t) + rec_count*sizeof(double) + sizeof(char *));
    
    point->dims = rec_count-1;

    token = strtok(data, ",");
    point->data[0] = atof(token);

    for (size_t i = 1; i < rec_count-1; i++) {
        token = strtok(NULL, ",");
        point->data[i] = atof(token);
    };

    token = strtok(NULL, ",");
    strncpy(point->label, token, 31);
    point->label[strcspn(point->label, "\n")] = 0;
    point->label[32] = 0;

    return point;
}

LabeledDataPoint **load_labeled_data_csv(FILE *file, size_t num_records, size_t num_fields) {
    LabeledDataPoint **all_data = malloc(num_records*(sizeof(size_t) + num_fields*sizeof(double)));

    LabeledDataPoint *current_data_point;
    char *current_record = NULL;
    size_t n = 0;
    int chars_num;

    for (size_t i = 0; i < num_records; i++) {
        chars_num = getline(&current_record, &n, file);
        if (chars_num != -1) {
            current_data_point = create_labeled_data_point(current_record, num_fields);
        }
        all_data[i] = current_data_point;
    }
    free(current_record);

    return all_data;
}

void free_all_labeled_data(LabeledDataPoint **data, size_t num_records) {
    for (size_t i = 0; i < num_records; i++) {
        free(data[i]);
    }

    free(data);
}