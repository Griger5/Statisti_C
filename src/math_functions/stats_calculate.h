#ifndef STATS_CALCULATE_H
#define STATS_CALCULATE_H

#include "../logic/data_structs/data_point.h"
#include "matrix_operations.h"

double std_var_biased_1d(DataPoint **, size_t, int);
double std_dev_uncorr_1d(DataPoint **, size_t, int);

double std_covar_popul(DataPoint **, size_t, int, int);

Matrix std_covar_matrix(DataPoint **data, size_t rec_count);

#endif