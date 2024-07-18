#ifndef LABELED_DATA_POINT_H
#define LABELED_DATA_POINT_H

#include <stdio.h>

#include "../../utils/label_list.h"

typedef struct _LabeledDataPoint {
    size_t dims;
    //char label[32];
    int label_num;
    double data[];
} LabeledDataPoint;

void print_labeled_data(LabeledDataPoint *);

LabeledDataPoint *create_labeled_data_point(char *, size_t, LabelList *);

LabeledDataPoint **load_labeled_data_csv(FILE *, size_t, size_t, LabelList *);

void free_all_labeled_data(LabeledDataPoint **, size_t);

#endif