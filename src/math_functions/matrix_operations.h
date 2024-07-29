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

Matrix copy_matrix(const Matrix matrix_to_copy);

void subtract_rows(size_t rows, size_t cols, double (*matrix)[cols], size_t row_minuend, size_t row_subtrahend, double multiplier);

void switch_rows(size_t rows, size_t cols, double (*matrix)[cols], size_t row_1, size_t row_2);

void matrix_multiply(size_t rows_a, size_t cols_a, double (*matrix_a)[cols_a], size_t rows_b, size_t cols_b, double (*matrix_b)[cols_b], double (*result)[cols_b]);

double determinant(size_t N, const double (*matrix)[N]);

void invert_matrix(size_t N, const double (*matrix)[N], double (*inverted)[N]);

#endif