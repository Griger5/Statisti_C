#include <stdlib.h>

#include "helper_funcs.h"
#include "matrix_operations.h"

double sum_data_1d(DataSet data_set, int dim_to_sum) {
    size_t rec_count = data_set.rec_count;
    double sum = 0;

    for (size_t i = 0; i < rec_count; i++) {
        sum += data_set.data[i]->values[dim_to_sum]; 
    }

    return sum;
}

double mean_arith_data(DataSet data_set, int dim_to_sum) {
    double sum = sum_data_1d(data_set, dim_to_sum);

    return sum/data_set.rec_count;
}

Matrix data_mean_diff(DataSet data_set, int dim_to_calc) {
    double mean_x = mean_arith_data(data_set, dim_to_calc);

    size_t rec_count = data_set.rec_count;

    Matrix mean_diff_vector = init_matrix(1, rec_count);

    for (size_t i = 0; i < rec_count; i++) {
        mean_diff_vector.values[0][i] = data_set.data[i]->values[dim_to_calc] - mean_x;
    }

    return mean_diff_vector;
}