#include <stdlib.h>
#include <math.h>

#include "stats_calculate.h"
#include "helper_funcs.h"
#include "vector_operations.h"

double std_var_biased_1d(DataPoint **data, size_t rec_count, int dim_to_calc) {
    double *mean_diff_vector = data_mean_diff(data, rec_count, dim_to_calc);
    double *mean_diff_vector_square = multi_by_element(mean_diff_vector, mean_diff_vector, rec_count);

    double sum_mean_diff = sum_vector_elem(mean_diff_vector_square, rec_count);

    free(mean_diff_vector);
    free(mean_diff_vector_square);

    return sum_mean_diff/rec_count;
}

double std_dev_uncorr_1d(DataPoint **data, size_t rec_count, int dim_to_calc) {
    double std_var_biased = std_var_biased_1d(data, rec_count, dim_to_calc);

    return sqrt(std_var_biased);
}