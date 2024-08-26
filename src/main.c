#include "gui/temp_ui.h"
#include "logic/data_structs/data_point.h"
#include "utils/file_operation.h"
#include "gui/global_var.h"
#include "plotting/standard_plot.h"

DataSet init_data(char *filename) {
    DataSet data_set;
    
    FILE *file = open_file(filename);

    size_t rec_count = count_records(file);
    size_t field_count = count_fields(file);

    data_set = load_data_csv(file, rec_count, field_count);

    fclose(file);

    return data_set;
}

void close_program(void) {
    pclose(get_gnupipe());
    free_dataset(get_dataset());
    free_multiplot(get_to_plot_ptr());
}

static void activate(GtkApplication *app, GApplicationCommandLine *cmdline) {
    gint argc;
    gchar **argv;

    argv = g_application_command_line_get_arguments(cmdline, &argc);

    if (argc < 2) {
        printf("Error, no file specified\n");
        return;
    }

    set_dataset(init_data(argv[1]));

    set_to_plot(init_multiplot());
    
    add_dataset_to_temp_file(get_dataset(), 0, 1);
    add_temp_file_to_multiplot(get_to_plot_ptr());
    
    set_gnupipe(init_gnuplot());

    GtkWidget *window;

    GtkBox *reg_menubox;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Statisti_C");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    g_signal_connect(window, "destroy", G_CALLBACK(close_program), NULL);

    reg_menubox = regression_menu_box_init();
    gtk_window_set_child(GTK_WINDOW(window), GTK_WIDGET(reg_menubox));
    
    gtk_window_present(GTK_WINDOW(window));
}

int main (int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("Statisti.C", G_APPLICATION_HANDLES_COMMAND_LINE);
    g_signal_connect(app, "command-line", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}