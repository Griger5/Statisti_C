#ifndef DATA_POINT_H
#define DATA_POINT_H

#include <stdio.h>

typedef struct _DataPoint {
    int label_num;
    size_t dims;
    double values[];
} DataPoint;

typedef struct _DataSet {
    size_t rec_count;
    size_t field_count;
    DataPoint **data;
} DataSet;

void print_data(DataPoint *);

DataPoint *create_datapoint_csv(char *, size_t);

DataSet load_data_csv(FILE *, size_t, size_t);

void free_all_data(DataSet);

#endif