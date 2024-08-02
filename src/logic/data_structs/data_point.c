#include <stdlib.h>
#include <string.h>

#include "data_point.h"
#include "../../utils/file_operation.h"

void print_data(DataPoint *a) {
    for (size_t i = 0; i<a->dims; i++) {
        printf("%f\n", a->values[i]);
    }
}

DataPoint *copy_datapoint(const DataPoint *to_copy) {
    size_t field_count = to_copy->dims;

    DataPoint *point = malloc(sizeof(DataPoint) + field_count*sizeof(double));

    if (point != NULL) {
        point->dims = field_count;
        point->label_num = to_copy->label_num;
        for (size_t i = 0; i < field_count; i++) {
            point->values[i] = to_copy->values[i];
        }
    }

    return point;
}

DataPoint *create_datapoint_csv(char *data, size_t field_count) {
    char *token;
    DataPoint *point = malloc(sizeof(DataPoint) + field_count*sizeof(double));
    
    point->dims = field_count;
    point->label_num = -1;

    token = strtok(data, ",");
    point->values[0] = atof(token);

    for (size_t i = 1; i < field_count; i++) {
        token = strtok(NULL, ",");
        point->values[i] = atof(token);
    }

    return point;
}

DataSet load_data_csv(FILE *file, size_t rec_count, size_t field_count) {
    DataSet all_data;
    all_data.rec_count = rec_count;
    all_data.field_count = field_count;
    all_data.label_count = 0;
    all_data.data = malloc(rec_count*(sizeof(DataPoint) + field_count*sizeof(double)));

    DataPoint *current_data_point;
    char *current_record = NULL;
    size_t n = 0;
    int chars_num;

    for (size_t i = 0; i < rec_count; i++) {
        chars_num = getline(&current_record, &n, file);
        if (chars_num != -1) {
            current_data_point = create_datapoint_csv(current_record, field_count);
        }
        all_data.data[i] = current_data_point;
    }
    free(current_record);

    return all_data;
}

void free_dataset(DataSet data_set) {
    size_t rec_count = data_set.rec_count;
    
    for (size_t i = 0; i < rec_count; i++) {
        free(data_set.data[i]);
    }

    free(data_set.data);
}

void free_array_of_datasets(DataSet *array, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free_dataset(array[i]);
    }

    free(array);
}   