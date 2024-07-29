#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "matrix_operations.h"

Matrix init_matrix(size_t rows, size_t cols) {
    Matrix matrix;
    
    matrix.rows = rows;
    matrix.cols = cols;

    matrix.values = malloc(rows * sizeof(double *));

    if (matrix.values != NULL) {
        matrix.values[0] = calloc(rows, cols * sizeof(double));

        if (matrix.values[0] != NULL) {
            for (size_t i = 1; i < rows; i++) {
                matrix.values[i] = matrix.values[0] + i*cols;
            }
        }
        else matrix.values = NULL;
    }

    return matrix;
}

void free_matrix(Matrix *matrix) {
    if (matrix->values != NULL) {
        free(matrix->values[0]);
        free(matrix->values);
    }
}

Matrix vector_to_matrix(double *vector, size_t length) {
    Matrix matrix = init_matrix(1, length);

    if (matrix.values != NULL) {
        for (size_t i = 0; i < length; i++) {
            matrix.values[0][i] = vector[i];
        }
    }
    
    return matrix;
}

void print_matrix(const Matrix matrix) {
    size_t rows = matrix.rows;
    size_t cols = matrix.cols;

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%f ", matrix.values[i][j]);
        }
        printf("\n");
    }
}

Matrix identity_matrix(size_t N) {
    Matrix identity = init_matrix(N, N);

    for (size_t i = 0; i < N; i++) {
        identity.values[i][i] = 1.0;
    }

    return identity;
}

Matrix copy_matrix(const Matrix matrix_to_copy) {
    size_t rows = matrix_to_copy.rows;
    size_t cols = matrix_to_copy.cols;

    Matrix copy = init_matrix(rows, cols);
    
    if (copy.values != NULL) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                copy.values[i][j] = matrix_to_copy.values[i][j];
            }
        }
    }

    return copy;
}

void subtract_rows(Matrix *matrix, size_t row_minuend, size_t row_subtrahend, double multiplier) {
    if (row_minuend < matrix->rows && row_subtrahend < matrix->rows && row_minuend != row_subtrahend) {
        for (size_t i = 0; i < matrix->cols; i++) {
            matrix->values[row_minuend][i] = matrix->values[row_minuend][i] - multiplier * matrix->values[row_subtrahend][i];
        }
    }
}

void multiply_row_scalar(Matrix *matrix, size_t row_num, double scalar) {
    size_t cols = matrix->cols;
    
    if (row_num < matrix->rows) {
        for (size_t i = 0; i < cols; i++) {
            matrix->values[row_num][i] = matrix->values[row_num][i] * scalar;
        }
    }
}

void switch_rows(Matrix *matrix, size_t row_1, size_t row_2) {
    size_t cols = matrix->cols;
    double temp;

    if (row_1 < matrix->rows && row_2 < matrix->rows) {
        for (size_t i = 0; i < cols; i++) {
            temp = matrix->values[row_1][i];
            matrix->values[row_1][i] = matrix->values[row_2][i];
            matrix->values[row_2][i] = temp;        
        }
    }
}

Matrix matrix_multiply(const Matrix matrix_a, const Matrix matrix_b) {
    size_t rows = matrix_a.rows;
    size_t cols = matrix_b.cols;

    Matrix result;
    
    if (matrix_a.cols != matrix_b.rows) {
        result.rows = rows;
        result.cols = cols;
        result.values = NULL;

        return result;
    }

    result = init_matrix(rows, cols);

    if (result.values != NULL) {
        for(size_t row = 0; row < rows; row++) {
            for(size_t col = 0; col < cols; col++) {
                for (size_t k=0; k < rows; k++) {
                    result.values[row][col] += matrix_a.values[row][k] * matrix_b.values[k][col];
                }
            }
        }
    }

    return result;
}

double determinant(const Matrix matrix) {   
    if (matrix.rows != matrix.cols) return NAN;

    size_t N = matrix.rows;
    
    if (N == 1) return matrix.values[0][0];

    if (N == 2) return (matrix.values[0][0] * matrix.values[1][1] - matrix.values[0][1] * matrix.values[1][0]);

    if (N == 3) {

        double aei = matrix.values[0][0] * matrix.values[1][1] * matrix.values[2][2];
        double bfg = matrix.values[0][1] * matrix.values[1][2] * matrix.values[2][0];
        double cdh = matrix.values[0][2] * matrix.values[1][0] * matrix.values[2][1];

        double ceg = matrix.values[0][2] * matrix.values[1][1] * matrix.values[2][0];
        double bdi = matrix.values[0][1] * matrix.values[1][0] * matrix.values[2][2];
        double afh = matrix.values[0][0] * matrix.values[1][2] * matrix.values[2][1];

        return aei + bfg + cdh - ceg - bdi - afh;
    }

    Matrix matrix_copy = copy_matrix(matrix);

    double ratio;
    double determinant = 1;

    if (matrix_copy.values[0][0] == 0) {
        for (size_t i = 1; i < N; i++) {
            if (matrix_copy.values[i][i] != 0) {
                switch_rows(&matrix_copy, 0, i);
                determinant *= -1;
                break;
            }       
        }
    }

    for (size_t i = 0; i < N; i++) {
        if (matrix_copy.values[i][i] == 0) return 0;

        for (size_t j = i+1; j < N; j++) {
            ratio = matrix_copy.values[j][i] / matrix_copy.values[i][i];
            subtract_rows(&matrix_copy, j, i, ratio);
        }
        
        determinant *= matrix_copy.values[i][i];
    }

    free_matrix(&matrix_copy);

    return determinant;
}

Matrix invert_matrix(const Matrix matrix) {
    Matrix nulled;
    nulled.rows = matrix.rows;
    nulled.cols = matrix.cols;
    nulled.values = NULL;
    
    if (matrix.rows != matrix.cols || determinant(matrix) == 0) return nulled;

    size_t N = matrix.rows;
    Matrix inverted = identity_matrix(N);

    Matrix matrix_copy = copy_matrix(matrix);

    double ratio;

    for (size_t i = 0; i < N; i++) {
        if (matrix_copy.values[i][i] == 0) return nulled;

        for (size_t j = i+1; j < N; j++) {
            ratio = matrix_copy.values[j][i] / matrix_copy.values[i][i];
            subtract_rows(&matrix_copy, j, i, ratio);
            subtract_rows(&inverted, j, i, ratio);
        }
    }

    for (int i = N-1; i >= 0; i--) {
        for (int j = i; j >= 0; j--) {
            ratio = matrix_copy.values[j][i] / matrix_copy.values[i][i];
            subtract_rows(&matrix_copy, j, i, ratio);
            subtract_rows(&inverted, j, i, ratio);
        }
    }

    for (size_t i = 0; i < N; i++) {
        multiply_row_scalar(&inverted, i, 1/matrix_copy.values[i][i]);
    }

    free_matrix(&matrix_copy);

    return inverted;
}