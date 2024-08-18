#ifndef STANDARD_PLOT_H
#define STANDARD_PLOT_H

#include <stdio.h>

#include "../logic/data_structs/data_point.h"

typedef struct _MultiPlot {
    size_t size;
    char **plots;
} MultiPlot;

FILE *init_gnuplot(void);

MultiPlot init_multiplot(void);

void add_dataset_to_temp_file(const DataSet data_set, size_t dim_to_plot1, size_t dim_to_plot2);

void add_plot_to_multiplot(MultiPlot *multiplot, char *plot);

void add_temp_file_to_multiplot(MultiPlot *multiplot);

void add_linreg_to_multiplot(MultiPlot *multiplot, double slope, double y_intercept);

void plot_multiplot(FILE *gnupipe, const MultiPlot multiplot);

#endif