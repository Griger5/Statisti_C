#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <stddef.h>

typedef struct _Matrix {
    size_t rows;
    size_t cols;
    double **values;
} Matrix;

Matrix init_matrix(size_t rows, size_t cols);

void free_matrix(Matrix *matrix);

Matrix vector_to_matrix(double *vector, size_t length);

void print_matrix(const Matrix matrix);

Matrix identity_matrix(size_t N);

Matrix copy_matrix(const Matrix matrix_to_copy);

void subtract_rows(Matrix *matrix, size_t row_minuend, size_t row_subtrahend, double multiplier);

void multiply_row_scalar(Matrix *matrix, size_t row_num, double scalar);

void switch_rows(Matrix *matrix, size_t row_1, size_t row_2);

Matrix matrix_multiply(const Matrix matrix_a, const Matrix matrix_b);

double determinant(const Matrix matrix);

Matrix invert_matrix(const Matrix matrix);

#endif