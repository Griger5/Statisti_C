#ifndef STATS_CALCULATE_H
#define STATS_CALCULATE_H

#include "../logic/data_structs/data_point.h"
#include "matrix_operations.h"

double std_var_biased_1d(DataSet, int);
double std_dev_uncorr_1d(DataSet, int);

double std_covar_popul(DataSet, int, int);

Matrix std_covar_matrix(DataSet);

#endif