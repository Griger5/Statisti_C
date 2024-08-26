#include "regression_plot.h"

void add_linreg_to_multiplot(MultiPlot *multiplot, double slope, double y_intercept) {
    char buffer[100];

    char buff_slope[32];
    char buff_y_inter[32];

    snprintf(buff_slope, 32, "%f", slope);
    snprintf(buff_y_inter, 32, "%f", y_intercept);

    for (int i = 0; i < 32; i++) {
        if (buff_slope[i] == ',') buff_slope[i] = '.';
        if (buff_y_inter[i] == ',') buff_y_inter[i] = '.';
    }

    snprintf(buffer, 100, "%s*x+%s", buff_slope, buff_y_inter);

    add_plot_to_multiplot(multiplot, buffer);
}