#ifndef LIN_REG_H
#define LIN_REG_H

#include "../data_structs/data_point.h"

double SLR_slope(DataPoint **, size_t);
double SLR_y_intercept(DataPoint **, size_t, double);

#endif