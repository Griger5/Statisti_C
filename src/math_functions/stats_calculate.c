#include "stats_calculate.h"

double sum_1d(DataPoint **data, size_t rec_count, int dim_to_sum) {
    double sum = 0;

    for (size_t i = 0; i < rec_count; i++) {
        sum += data[i]->data[dim_to_sum]; 
    }

    return sum;
}

double arith_mean(DataPoint **data, size_t rec_count, int dim_to_sum) {
    double sum = sum_1d(data, rec_count, dim_to_sum);

    return sum/rec_count;
}