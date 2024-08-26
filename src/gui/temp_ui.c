#include "temp_ui.h"
#include "../logic/regression/lin_reg.h"
#include "../plotting/standard_plot.h"
#include "../plotting/regression_plot.h"
#include "global_var.h"

GtkBox *regression_menu_box_init(void) {
    GtkWidget *reg_menubox;

    GtkWidget *linreg_button;

    reg_menubox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);

    linreg_button = gtk_button_new_with_label("linear regression");
    g_signal_connect(linreg_button, "clicked", G_CALLBACK(do_lin_reg), NULL);

    gtk_box_append(GTK_BOX(reg_menubox), linreg_button);

    return GTK_BOX(reg_menubox);
}

void do_lin_reg(void) {
    DataSet temp_data = get_dataset();

    double slope = SLR_slope(temp_data);
    double y_intercept = SLR_y_intercept(temp_data, slope);
    
    add_linreg_to_multiplot(get_to_plot_ptr(), slope, y_intercept);
    plot_multiplot(get_gnupipe(), get_to_plot());
}