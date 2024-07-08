#include "stats_calculate.h"

double sum_array(double *array, size_t length) {
    double sum = 0;

    for (size_t i = 0; i < length; i++) {
        sum += array[i]; 
    }

    return sum;
}

double sum_data_1d(DataPoint **data, size_t rec_count, int dim_to_sum) {
    double sum = 0;

    for (size_t i = 0; i < rec_count; i++) {
        sum += data[i]->data[dim_to_sum]; 
    }

    return sum;
}

double arith_mean_data(DataPoint **data, size_t rec_count, int dim_to_sum) {
    double sum = sum_data_1d(data, rec_count, dim_to_sum);

    return sum/rec_count;
}