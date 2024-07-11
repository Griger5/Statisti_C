#ifndef LABELED_DATA_POINT_H
#define LABELED_DATA_POINT_H

#include <stdio.h>

typedef struct _LabeledDataPoint {
    size_t dims;
    char label[32];
    double data[];
} LabeledDataPoint;

void print_labeled_data(LabeledDataPoint *);

LabeledDataPoint *create_labeled_data_point(char *, size_t);

LabeledDataPoint **load_labeled_data_csv(FILE *, size_t, size_t);

void free_all_labeled_data(LabeledDataPoint **, size_t);

#endif