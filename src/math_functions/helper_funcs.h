#ifndef HELPER_FUNCS_H
#define HELPER_FUNCS_H

#include <stddef.h>

#include "../logic/data_structs/data_point.h"

double sum_data_1d(DataPoint **,  size_t, int);

double mean_arith_data(DataPoint **, size_t, int);

double *data_mean_diff(DataPoint **, size_t, int);

#endif