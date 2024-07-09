#include <stdlib.h>

#include "helper_funcs.h"

double sum_data_1d(DataPoint **data, size_t rec_count, int dim_to_sum) {
    double sum = 0;

    for (size_t i = 0; i < rec_count; i++) {
        sum += data[i]->data[dim_to_sum]; 
    }

    return sum;
}

double mean_arith_data(DataPoint **data, size_t rec_count, int dim_to_sum) {
    double sum = sum_data_1d(data, rec_count, dim_to_sum);

    return sum/rec_count;
}

double *data_mean_diff(DataPoint **data, size_t rec_count, int dim_to_calc) {
    double mean_x = mean_arith_data(data, rec_count, dim_to_calc);

    double *mean_diff_vector = malloc(rec_count * sizeof(double));

    for (size_t i = 0; i < rec_count; i++) {
        mean_diff_vector[i] = data[i]->data[dim_to_calc] - mean_x;
    }

    return mean_diff_vector;
}