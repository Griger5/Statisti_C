#include <stdlib.h>
#include <math.h>

#include "stats_calculate.h"
#include "helper_funcs.h"
#include "matrix_operations.h"

double std_var_biased_1d(DataPoint **data, size_t rec_count, int dim_to_calc) {
    Matrix mean_diff_vector = data_mean_diff(data, rec_count, dim_to_calc);
    Matrix mean_diff_vector_square = matrix_multiply_elements(mean_diff_vector, mean_diff_vector);

    double sum_mean_diff = sum_row(mean_diff_vector_square, 0);

    free_matrix(&mean_diff_vector);
    free_matrix(&mean_diff_vector_square);

    return sum_mean_diff/rec_count;
}

double std_dev_uncorr_1d(DataPoint **data, size_t rec_count, int dim_to_calc) {
    double std_var_biased = std_var_biased_1d(data, rec_count, dim_to_calc);

    return sqrt(std_var_biased);
}

double std_covar_popul(DataPoint **data, size_t rec_count, int dim1, int dim2) {
    Matrix mean_diff_vector1 = data_mean_diff(data, rec_count, dim1);
    Matrix mean_diff_vector2 = data_mean_diff(data, rec_count, dim2);

    Matrix multiplied_vectors = matrix_multiply_elements(mean_diff_vector1, mean_diff_vector2);
    double sum_of_multiplied = sum_row(multiplied_vectors, 0);

    free_matrix(&mean_diff_vector1);
    free_matrix(&mean_diff_vector2);
    free_matrix(&multiplied_vectors);

    return sum_of_multiplied/rec_count;
}