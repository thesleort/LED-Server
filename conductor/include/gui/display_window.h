#ifndef __DISPLAY_WINDOW_H
#define __DISPLAY_WINDOW_H

#include <gtk/gtk.h>

#include "gui/stream_playback.h"
#include "gui/window.h"

void display_window_init(GtkWidget *window, stream_data *data, GtkNotebook **tab);

void display_close_cb (GtkWidget *widget, GdkEvent *event, stream_data *data);

#endif