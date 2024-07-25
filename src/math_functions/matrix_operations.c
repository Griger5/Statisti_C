#include <stdlib.h>

#include "matrix_operations.h"

void subtract_rows(size_t rows, size_t cols, double (*matrix)[cols], size_t row_minuend, size_t row_subtrahend, double multiplier) {
    if (row_minuend < rows && row_subtrahend < rows && row_minuend != row_subtrahend) {
        for (size_t i = 0; i < cols; i++) {
            matrix[row_minuend][i] = matrix[row_minuend][i] - multiplier * matrix[row_subtrahend][i];
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

double determinant(size_t N, double (*matrix)[N]) {   
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

    double ratio;
    double determinant = 1;

    if (matrix[0][0] == 0) {
        for (size_t i = 1; i < N; i++) {
            if (matrix[i][i] != 0) {
                switch_rows(N, N, matrix, 0, i);
                determinant *= -1;
                break;
            }       
        }
    }

    for (size_t i = 0; i < N; i++) {
        if (matrix[i][i] == 0) return 0;

        for (size_t j = i+1; j < N; j++) {
            ratio = matrix[j][i] / matrix[i][i];
            subtract_rows(N, N, matrix, j, i, ratio);
        }
        
        determinant *= matrix[i][i];
    }

    return determinant;
}