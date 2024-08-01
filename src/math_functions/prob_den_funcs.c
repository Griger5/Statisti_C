#include <math.h>

#include "prob_den_funcs.h"
//#include "matrix_operations.h"

double normal_pdf(const double mean, const double std_dev, const double input) {
    double normalization_factor = 1/sqrt(2*M_PI*pow(std_dev, 2.0));
    double exponent = -0.5 * pow((input-mean)/std_dev, 2);
    double value = pow(M_E, exponent);

    return value*normalization_factor;
}
#include <stdio.h>
double multi_var_normal_pdf(const Matrix mean_vector, const Matrix covariance_matrix, const Matrix input_vector) {
    if (mean_vector.cols != input_vector.cols || input_vector.cols != covariance_matrix.rows) return NAN;

    size_t vec_length = mean_vector.cols;
    double covar_determinant = determinant(covariance_matrix);

    double normalization_factor = 1/sqrt(pow(2*M_PI, (double)vec_length) * covar_determinant);

    Matrix inverse_covar = invert_matrix(covariance_matrix);

    Matrix mean_input_diff = matrix_subtract_elements(input_vector, mean_vector);

    Matrix invcov_multi_diff = matrix_multiply(mean_input_diff, inverse_covar);    
    Matrix invcov_multi_diff2 = matrix_multiply_elements(invcov_multi_diff, mean_input_diff);

    double sum = sum_row(invcov_multi_diff, 0);

    double exponent = -0.5 * sum;

    double value = pow(M_E, exponent);

    free_matrix(&inverse_covar);
    free_matrix(&mean_input_diff);
    free_matrix(&invcov_multi_diff);
    free_matrix(&invcov_multi_diff2);

    return value*normalization_factor;
}