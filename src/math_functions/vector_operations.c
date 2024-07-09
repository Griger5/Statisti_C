#include <stdlib.h>

#include "vector_operations.h"

double sum_vector_elem(double *vector, size_t length) {
    double sum = 0;

    for (size_t i = 0; i < length; i++) {
        sum += vector[i]; 
    }

    return sum;
}

double *vector_sub_scalar(double *vector, size_t length, double scalar) {
    double *result = malloc(length*sizeof(double));

    for (size_t i = 0; i < length; i++) {
        result[i] = vector[i] - scalar;
    }

    return result;
}

double *multi_by_element(double *vector_a, double *vector_b, size_t length) {
    double *result = malloc(length*sizeof(double));

    for (size_t i = 0; i < length; i++) {
        result[i] = vector_a[i] * vector_b[i];
    }

    return result;
}