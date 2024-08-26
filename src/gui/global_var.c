#include "global_var.h"

static DataSet data_set;

void set_dataset(DataSet new_data) {
    data_set = new_data;
}

DataSet get_dataset(void) {
    return data_set;
}

static MultiPlot to_plot; 

void set_to_plot(MultiPlot new_plots) {
    to_plot = new_plots;
}

MultiPlot get_to_plot(void) {
    return to_plot;
}

MultiPlot *get_to_plot_ptr(void) {
    return &to_plot;
}

static FILE *gnupipe;

void set_gnupipe(FILE *new_pipe) {
    gnupipe = new_pipe;
}

FILE *get_gnupipe(void) {
    return gnupipe;
}