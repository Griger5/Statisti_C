#include <stdlib.h>

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
    free(matrix->values[0]);
    free(matrix->values);
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

void subtract_rows(size_t rows, size_t cols, double (*matrix)[cols], size_t row_minuend, size_t row_subtrahend, double multiplier) {
    if (row_minuend < rows && row_subtrahend < rows && row_minuend != row_subtrahend) {
        for (size_t i = 0; i < cols; i++) {
            matrix[row_minuend][i] = matrix[row_minuend][i] - multiplier * matrix[row_subtrahend][i];
        }
    }
}

void multiply_row_scalar(size_t rows, size_t cols, double (*matrix)[cols], size_t row_num, double scalar) {
    if (row_num < rows) {
        for (size_t i = 0; i < cols; i++) {
            matrix[row_num][i] = matrix[row_num][i] * scalar;
        }
    }
}

void switch_rows(size_t rows, size_t cols, double (*matrix)[cols], size_t row_1, size_t row_2) {
    double temp;

    if (row_1 < rows && row_2 < rows) {
        for (size_t i = 0; i < cols; i++) {
            temp = matrix[row_1][i];
            matrix[row_1][i] = matrix[row_2][i];
            matrix[row_2][i] = temp;        
        }
    }
}

void matrix_multiply(size_t rows_a, size_t cols_a, double (*matrix_a)[cols_a], size_t rows_b, size_t cols_b, double (*matrix_b)[cols_b], double (*result)[cols_b]) {
    if (cols_a != rows_b) return;
    
    for(size_t row = 0; row < rows_a; row++) {
        for(size_t col=0; col < cols_b; col++) {
            result[row][col] = 0;
            for (size_t k=0; k < rows_b; k++) {
                result[row][col] += matrix_a[row][k] * matrix_b[k][col];
            }
        }
    }
}

/* double determinant(size_t N, const double (*matrix)[N]) {   
    if (N == 1) return matrix[0][0];

    if (N == 2) return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);

    if (N == 3) {

        double aei = matrix[0][0] * matrix[1][1] * matrix[2][2];
        double bfg = matrix[0][1] * matrix[1][2] * matrix[2][0];
        double cdh = matrix[0][2] * matrix[1][0] * matrix[2][1];   

        double ceg = matrix[0][2] * matrix[1][1] * matrix[2][0];
        double bdi = matrix[0][1] * matrix[1][0] * matrix[2][2];
        double afh = matrix[0][0] * matrix[1][2] * matrix[2][1];

        return aei + bfg + cdh - ceg - bdi - afh;
    }

    double (*matrix_copy)[N] = malloc(N * sizeof(*matrix));
    copy_matrix(N, N, matrix, matrix_copy);

    double ratio;
    double determinant = 1;

    if (matrix_copy[0][0] == 0) {
        for (size_t i = 1; i < N; i++) {
            if (matrix_copy[i][i] != 0) {
                switch_rows(N, N, matrix_copy, 0, i);
                determinant *= -1;
                break;
            }       
        }
    }

    for (size_t i = 0; i < N; i++) {
        if (matrix_copy[i][i] == 0) return 0;

        for (size_t j = i+1; j < N; j++) {
            ratio = matrix_copy[j][i] / matrix_copy[i][i];
            subtract_rows(N, N, matrix_copy, j, i, ratio);
        }
        
        determinant *= matrix_copy[i][i];
    }

    free(matrix_copy);

    return determinant;
}

void invert_matrix(size_t N, const double (*matrix)[N], double (*inverted)[N]) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            inverted[i][j] = 0;
        }
        inverted[i][i] = 1;
    }

    if (determinant(N, matrix) == 0) return;

    double (*matrix_copy)[N] = malloc(N * sizeof(*matrix_copy));
    copy_matrix(N, N, matrix, matrix_copy);

    double ratio;

    for (size_t i = 0; i < N; i++) {
        if (matrix_copy[i][i] == 0) return;

        for (size_t j = i+1; j < N; j++) {
            ratio = matrix_copy[j][i] / matrix_copy[i][i];
            subtract_rows(N, N, matrix_copy, j, i, ratio);
            subtract_rows(N, N, inverted, j, i, ratio);
        }
    }

    for (int i = N-1; i >= 0; i--) {
        for (int j = i; j >= 0; j--) {
            ratio = matrix_copy[j][i] / matrix_copy[i][i];
            subtract_rows(N, N, matrix_copy, j, i, ratio);
            subtract_rows(N, N, inverted, j, i, ratio);
        }
    }

    for (size_t i = 0; i < N; i++) {
        multiply_row_scalar(N, N, inverted, i, 1/matrix_copy[i][i]);
    }

    free(matrix_copy);
} */