#ifndef DATA_POINT_H
#define DATA_POINT_H

#include <stdio.h>

typedef struct _DataPoint {
    size_t dims;
    double data[];
} DataPoint;

void print_data(DataPoint *);

DataPoint *create_data_point(char *, size_t);

DataPoint **load_data_csv(FILE *, size_t, size_t);

void free_all_data(DataPoint **, size_t);

#endif