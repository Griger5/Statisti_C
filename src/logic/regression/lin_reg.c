#include "lin_reg.h"
#include "../../math_functions/stats_calculate.h"
#include "../../math_functions/helper_funcs.h"

double SLR_slope(DataSet data_set) {
    double covar_xy = std_covar_popul(data_set, 0, 1);
    double var_x = std_var_biased_1d(data_set, 0);

    return covar_xy/var_x;
}

double SLR_y_intercept(DataSet data_set, double slope) {
    double mean_x = mean_arith_data(data_set, 0);
    double mean_y = mean_arith_data(data_set, 1);

    double y_intercept = mean_y - slope * mean_x;

    return y_intercept;
}