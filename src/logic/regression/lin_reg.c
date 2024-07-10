#include "lin_reg.h"
#include "../../math_functions/stats_calculate.h"
#include "../../math_functions/helper_funcs.h"

double SLR_slope(DataPoint **data, size_t rec_count) {
    double covar_xy = std_covar_popul(data, rec_count, 0, 1);
    double var_x = std_var_biased_1d(data, rec_count, 0);

    return covar_xy/var_x;
}

double SLR_y_intercept(DataPoint **data, size_t rec_count, double slope) {
    double mean_x = mean_arith_data(data, rec_count, 0);
    double mean_y = mean_arith_data(data, rec_count, 1);

    double y_intercept = mean_y - slope * mean_x;

    return y_intercept;
}