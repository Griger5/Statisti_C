#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H

#include "../data_structs/data_point.h"
#include "../../math_functions/matrix_operations.h"

Matrix *naive_bayes_train(const DataSet data_set);

int naive_bayes_classify(const Matrix input_vector, const Matrix *parameter_key);

#endif