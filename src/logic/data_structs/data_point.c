#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_point.h"
#include "../../utils/file_operation.h"

void print_data(DataPoint *a) {
    for (size_t i = 0; i<a->dims; i++) {
        printf("%f\n", a->data[i]);
    }
}

DataPoint *create_data_point(char *data, size_t dims) {
    char *token;
    DataPoint *point = malloc(sizeof(size_t) + dims*sizeof(double));
    
    point->dims = dims;

    token = strtok(data, ",");
    point->data[0] = atof(token);

    for (size_t i = 1; i < dims; i++) {
        token = strtok(NULL, ",");
        point->data[i] = atof(token);
    }

    return point;
}

DataPoint **load_data_csv(FILE *file, size_t num_records, size_t num_fields) {
    DataPoint **all_data = malloc(num_records*(sizeof(size_t) + num_fields*sizeof(double)));

    DataPoint *current_data_point;
    char *current_record = NULL;
    size_t n = 0;
    int chars_num;

    for (size_t i = 0; i < num_records; i++) {
        chars_num = getline(&current_record, &n, file);
        if (chars_num != -1) {
            current_data_point = create_data_point(current_record, num_fields);
        }
        all_data[i] = current_data_point;
    }
    free(current_record);

    return all_data;
}

void free_all_data(DataPoint **data, size_t num_records) {
    for (size_t i = 0; i < num_records; i++) {
        free(data[i]);
    }

    free(data);
}