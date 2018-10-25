#ifndef __CONTROL_WINDOW_H
#define __CONTROL_WINDOW_H

#include <gtk/gtk.h>

#include "gui/window.h"
#include "options.h"

void control_window_init(GtkWidget *window, options *option, GtkNotebook **tab);

void tab_decklink_cb(GtkButton *button, GtkNotebook *tab);

void tab_webview_cb(GtkButton *button, GtkNotebook *tab);

void tab_nextpage_cb(GtkButton *button, GtkNotebook *tab);

void decklink_input_hdmi(GtkButton *button, decklink_options *option);

void decklink_input_sdi(GtkButton *button, decklink_options *option);

void open_display_window_cb(GtkButton *button, options *option);

#endif