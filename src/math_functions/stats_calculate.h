#ifndef STATS_CALCULATE_H
#define STATS_CALCULATE_H

#include "../logic/data_structs/data_point.h"

double sum_array(double *, size_t);

double sum_data_1d(DataPoint **,  size_t, int);

double arith_mean_data(DataPoint **, size_t, int);

#endif