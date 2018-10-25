#ifndef __DISPLAY_WINDOW_H
#define __DISPLAY_WINDOW_H

#include <gtk/gtk.h>

#include "gui/stream_playback.h"
#include "gui/window.h"
#include "options.h"

void display_window_init(GtkWidget *window, options *option, GtkNotebook **tab);

void display_close_cb (GtkWidget *widget, GdkEvent *event, options *option);

void switch_tab_cb(GtkNotebook *notebook, GtkWidget *page, guint page_num, stream_data *data);


#endif