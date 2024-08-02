#ifndef LABELED_DATA_POINT_H
#define LABELED_DATA_POINT_H

#include <stdio.h>

#include "data_point.h"
#include "../../utils/label_list.h"

void print_labeled_data(DataPoint *);

DataPoint *create_labeled_datapoint_csv(char *, size_t, LabelList *);

DataSet load_labeled_data_csv(FILE *, size_t, size_t, LabelList *);

DataSet split_label(const DataSet data_set, int label_to_separate);

#endif