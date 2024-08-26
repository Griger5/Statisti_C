#include <stdio.h>

#include "../logic/data_structs/data_point.h"
#include "../plotting/standard_plot.h"

void set_dataset(DataSet new_data);

DataSet get_dataset(void);

void set_to_plot(MultiPlot new_plots);

MultiPlot get_to_plot(void);

MultiPlot *get_to_plot_ptr(void);

void set_gnupipe(FILE *new_pipe);

FILE *get_gnupipe(void);