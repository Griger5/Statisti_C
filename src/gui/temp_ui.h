#ifndef TEMP_UI_H
#define TEMP_UI_H

#include <gtk/gtk.h>
#include "../logic/data_structs/data_point.h"

GtkBox *regression_menu_box_init(void);

void do_lin_reg(void);

#endif