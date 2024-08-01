#include <stdlib.h>
#include <math.h>

#include "stats_calculate.h"
#include "helper_funcs.h"
#include "matrix_operations.h"

double std_var_biased_1d(DataSet data_set, int dim_to_calc) {
    Matrix mean_diff_vector = data_mean_diff(data_set, dim_to_calc);
    Matrix mean_diff_vector_square = matrix_multiply_elements(mean_diff_vector, mean_diff_vector);

    double sum_mean_diff = sum_row(mean_diff_vector_square, 0);

    free_matrix(&mean_diff_vector);
    free_matrix(&mean_diff_vector_square);

    return sum_mean_diff/data_set.rec_count;
}

double std_dev_uncorr_1d(DataSet data_set, int dim_to_calc) {
    double std_var_biased = std_var_biased_1d(data_set, dim_to_calc);

    return sqrt(std_var_biased);
}

double std_covar_popul(DataSet data_set, int dim1, int dim2) {
    Matrix mean_diff_vector1 = data_mean_diff(data_set, dim1);
    Matrix mean_diff_vector2 = data_mean_diff(data_set, dim2);

    Matrix multiplied_vectors = matrix_multiply_elements(mean_diff_vector1, mean_diff_vector2);
    double sum_of_multiplied = sum_row(multiplied_vectors, 0);

    free_matrix(&mean_diff_vector1);
    free_matrix(&mean_diff_vector2);
    free_matrix(&multiplied_vectors);

    return sum_of_multiplied/data_set.rec_count;
}

Matrix std_covar_matrix(DataSet data_set) {
    size_t dims = data_set.data[0]->dims;

    Matrix covar_matrix = init_matrix(dims, dims);

    for (size_t i = 0; i < dims; i++) {
        for (size_t j = i; j < dims; j++) {
            covar_matrix.values[i][j] = std_covar_popul(data_set, i, j);
        }
    }

    for (size_t i = 0; i < dims; i++) {
        for (size_t j = i; j < dims; j++) {
            covar_matrix.values[j][i] = covar_matrix.values[i][j];
        }
    }

    return covar_matrix;
}