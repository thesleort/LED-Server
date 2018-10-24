#ifndef __CONTROL_WINDOW_H
#define __CONTROL_WINDOW_H

#include <gtk/gtk.h>

#include "gui/stream_playback.h"
#include "gui/window.h"

void control_window_init(GtkWidget *window, stream_data *data, GtkNotebook **tab);

void tab_decklink_cb(GtkButton *button, GtkNotebook *tab);

void tab_webview_cb(GtkButton *button, GtkNotebook *tab);

void tab_nextpage_cb(GtkButton *button, GtkNotebook *tab);

#endif