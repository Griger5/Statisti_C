#ifndef HELPER_FUNCS_H
#define HELPER_FUNCS_H

#include <stddef.h>

#include "../logic/data_structs/data_point.h"
#include "matrix_operations.h"

double sum_data_1d(DataSet, int);

double mean_arith_data(DataSet, int);

Matrix data_mean_diff(DataSet, int);

#endif