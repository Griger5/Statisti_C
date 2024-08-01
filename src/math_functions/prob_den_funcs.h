#ifndef PROB_DEN_FUNCS_H
#define PROB_DEN_FUNCS_H

#include "matrix_operations.h"

double normal_pdf(const double mean, const double std_dev, const double input);

double multi_var_normal_pdf(const Matrix mean_vector, const Matrix covariance_matrix, const Matrix input_vector);

#endif