#include <stdlib.h>
#include <string.h>

#include "standard_plot.h"

FILE *init_gnuplot(void) {
    FILE *gnupipe = popen("gnuplot", "w");

    if (gnupipe == NULL) return NULL;

    fprintf(gnupipe, "set term qt persist\n");

    return gnupipe; 
}

MultiPlot init_multiplot(void) {
    MultiPlot to_plot;
    to_plot.size = 0;
    to_plot.plots = NULL;

    return to_plot;
}

void free_multiplot(MultiPlot *multiplot) {
    free(multiplot->plots);
}

void add_dataset_to_temp_file(const DataSet data_set, size_t dim_to_plot1, size_t dim_to_plot2) {
    size_t rec_count = data_set.rec_count;
    size_t field_count = data_set.field_count;

    if (dim_to_plot1 >= field_count || dim_to_plot2 >= field_count) return;
    
    FILE *file = fopen("build/data.temp", "w");

    if (file != NULL) {
        for (size_t i = 0; i < rec_count; i++) {
            fprintf(file, "%f %f\n", data_set.data[i]->values[dim_to_plot1], data_set.data[i]->values[dim_to_plot2]);
        }

        fclose(file);
    }
}

void add_plot_to_multiplot(MultiPlot *multiplot, char *plot) {
    size_t curr_size = multiplot->size;
    
    if (curr_size == 0) {
        multiplot->plots = malloc((curr_size+1) * sizeof(char*));
        if (multiplot->plots != NULL) {
            multiplot->size++;
            multiplot->plots[curr_size] = plot;
        }

        return;
    }

    for (size_t i = 0; i < curr_size; i++) {
        if (strcmp(plot, multiplot->plots[i]) == 0) return;
    }

    char **temp = realloc(multiplot->plots, (curr_size+1)*sizeof(char*));

    if (temp != NULL) {
        multiplot->size++;
        multiplot->plots = temp;
        multiplot->plots[curr_size] = plot;
    }

    return;
}

void add_temp_file_to_multiplot(MultiPlot *multiplot) {
    add_plot_to_multiplot(multiplot, "'build/data.temp' pointtype 7");
}

void plot_multiplot(FILE* gnupipe, const MultiPlot multiplot) {
    size_t size = multiplot.size;

    if (size == 0) return;

    fprintf(gnupipe, "plot %s", multiplot.plots[0]);

    for (size_t i = 1; i < size; i++) {
        fprintf(gnupipe, ", %s", multiplot.plots[i]);
    }

    fprintf(gnupipe, "\n");
    fflush(gnupipe);
}