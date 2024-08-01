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
    printf("vec_length: %ld\n", vec_length);
    double covar_determinant = determinant(covariance_matrix);
    printf("covar_determinant: %f\n", covar_determinant);

    double normalization_factor = 1/sqrt(pow(2*M_PI, (double)vec_length) * covar_determinant);
    printf("normalization_factor: %f\n", normalization_factor);

    Matrix inverse_covar = invert_matrix(covariance_matrix);
    printf("inverse_covar:\n");
    print_matrix(inverse_covar);
    Matrix mean_input_diff = matrix_subtract_elements(input_vector, mean_vector);
    printf("mean_input_diff:\n");
    print_matrix(mean_input_diff);

    Matrix invcov_multi_diff = matrix_multiply(mean_input_diff, inverse_covar);
    printf("first multiplication:\n");
    print_matrix(invcov_multi_diff);
    invcov_multi_diff = matrix_multiply_elements(invcov_multi_diff, mean_input_diff);
    printf("second multiplication:\n");
    print_matrix(invcov_multi_diff);

    double sum = sum_row(invcov_multi_diff, 0);
    printf("sum: %f\n", sum);

    double exponent = -0.5 * sum;
    printf("exponent: %f\n", exponent);

    double value = pow(M_E, exponent);
    printf("value: %f\n", value);
    printf("final value: %.20f\n", value*normalization_factor);

    free_matrix(&inverse_covar);
    free_matrix(&mean_input_diff);
    free_matrix(&invcov_multi_diff);

    return value*normalization_factor;
}