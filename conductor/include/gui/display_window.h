#ifndef __DISPLAY_WINDOW_H
#define __DISPLAY_WINDOW_H

#include <gtk/gtk.h>

#include "streamer/stream_playback.h"
#include "gui/window.h"
#include "options.h"

void display_window_init(GtkWidget *window, options *option);

void display_close_cb (GtkWidget *widget, GdkEvent *event, options *option);

void switch_tab_cb(GtkNotebook *notebook, GtkWidget *page, guint page_num, options *option);

void finish();


#endif