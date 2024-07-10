#ifndef STATS_CALCULATE_H
#define STATS_CALCULATE_H

#include "../logic/data_structs/data_point.h"

double std_var_biased_1d(DataPoint **, size_t, int);
double std_dev_uncorr_1d(DataPoint **, size_t, int);

double std_covar_popul(DataPoint **, size_t, int, int);

#endif